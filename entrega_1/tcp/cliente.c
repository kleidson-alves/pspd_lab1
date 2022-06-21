#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include "cliente_tcp.h"
#include "servidor_tcp.h"

#define X 500000

typedef struct Result {
    float min;
    float max;
} Result;

typedef struct Data {
    float v[X];
    int start;
    int end;
} Data;

int f_aleat() {
    int aleat = rand() % X;
    return aleat;
}

void generateNumbers(float *v) {
    for(int i = 0; i < X; i++) {
        v[i] = sqrt(pow(i - (f_aleat()/2.0), 2));
    }
}

int main(int argc, char* argv[]) {

    if(argc != 4) {
		printf("Uso: %s <Porta Escuta> <IP do Servidor> <Porta Envio>\n", argv[0]);
		exit(1);
	}
    
	unsigned short servidorPortaEscuta = atoi(argv[1]);
    char *IP_Servidor = argv[2];
	unsigned short servidorPortaEnvio = atoi(argv[3]);
       
    srand(time(NULL));
    Data data;
    Result msg;
    
    generateNumbers(data.v);
    data.start = 0;
    data.end = X - 1;

    start_client(IP_Servidor, servidorPortaEnvio, (char *)&data, sizeof(Data));
    start_server(servidorPortaEscuta,(char *) &msg);

    printf("min = %.2f\nmax = %.2f\n", msg.min, msg.max);
    return 0;
}