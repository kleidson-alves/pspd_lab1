#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "cliente_tcp.h"
#include "servidor_tcp.h"

#define X 30

typedef struct Result {
    float min;
    float max;
} Result;

int f_aleat() {
    int aleat = rand() % X;
    return aleat;
}

void generateNumbers(float *v) {
    for(int i = 0; i < X; i++) {
        v[i] = sqrt(pow(i - (f_aleat()/2.0), 2));
    }
}

Result findNumbers(float *v, int start, int end) {
    Result res = {-1, -1};
    for(int i = start; i <= end; i++) {
        if(res.min == -1 || res.min > v[i]) {
            res.min = v[i];
        }
        if(res.max < v[i] ){
            res.max = v[i];
        }
    }
    return res;
}

void *init_server(void *args) {
    unsigned short *servidorPortaEscuta = (unsigned short *)args;
    printf("%u\n", *servidorPortaEscuta);
    start_server(*servidorPortaEscuta);
}

int main(int argc, char *argv[]) {
    if(argc != 5) {
		printf("Uso: %s <Porta Escuta> <IP do Servidor> <Porta Envio> <Mensagem>\n", argv[0]);
		exit(1);
	}

	unsigned short servidorPortaEscuta = atoi(argv[1]);
    char *IP_Servidor = argv[2];
	unsigned short servidorPortaEnvio = atoi(argv[3]);
    char *mensagem = argv[4];

    pthread_t thread_server;
    pthread_create(&thread_server, NULL, init_server, &servidorPortaEscuta);
    while(start_client(IP_Servidor, servidorPortaEnvio, mensagem) == - 1){
        sleep(2);
    }

    pthread_join(thread_server, NULL);
    return 0;
}
