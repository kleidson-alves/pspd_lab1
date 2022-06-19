#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "servidor_tcp.h"

void TrataClienteTCP(int socketCliente, char *buffer) {
	char msg[16];
	int pos = 0;
	int tamanhoRecebido;

	if((tamanhoRecebido = recv(socketCliente, msg, 16, 0)) < 0){
		printf("Erro no recv()\n");
	} else {
		memcpy(&buffer[pos], msg, tamanhoRecebido);
		pos += tamanhoRecebido;
	}

	while (tamanhoRecebido > 0) {
		if(send(socketCliente, msg, tamanhoRecebido, 0) != tamanhoRecebido){
			printf("Erro no envio - send()\n");
		}
		
		if((tamanhoRecebido = recv(socketCliente, msg, 16, 0)) < 0){	
			printf("Erro no recv()\n");
		}
		else {
			memcpy(&buffer[pos], msg, tamanhoRecebido);
			pos += tamanhoRecebido;
		}
	}
}

void start_server(unsigned short servidorPorta, char *buffer) {
	int servidorSocket;
	int socketCliente;
	struct sockaddr_in servidorAddr;
	struct sockaddr_in clienteAddr;
	unsigned int clienteLength;

	// Abrir Socket
	if((servidorSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("falha no socker do Servidor\n");

	// Montar a estrutura sockaddr_in
	memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servidorAddr.sin_port = htons(servidorPorta);

	// Bind
	if(bind(servidorSocket, (struct sockaddr *) &servidorAddr, sizeof(servidorAddr)) < 0)
		printf("Falha no Bind\n");

	// Listen
	if(listen(servidorSocket, 10) < 0)
		printf("Falha no Listen\n");		

	clienteLength = sizeof(clienteAddr);
	if((socketCliente = accept(servidorSocket, (struct sockaddr *) &clienteAddr, &clienteLength)) < 0){
		printf("Falha no Accept\n");
	}
				
	TrataClienteTCP(socketCliente, buffer);
	close(socketCliente);
	
	close(servidorSocket);

}