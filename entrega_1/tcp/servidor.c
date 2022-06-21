#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
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

int main(int argc, char*argv[]) {

    if(argc != 4) {
		printf("Uso: %s <Porta Escuta> <IP do Servidor> <Porta Envio>\n", argv[0]);
		exit(1);
	}

	unsigned short servidorPortaEscuta = atoi(argv[1]);
    char *IP_Servidor = argv[2];
	unsigned short servidorPortaEnvio = atoi(argv[3]);

    Data data;
    start_server(servidorPortaEscuta, (char *)&data);

    Result res = findNumbers(data.v, data.start, data.end);
    start_client(IP_Servidor, servidorPortaEnvio, (char *)&res, sizeof(Result));
   
    return 0;
}