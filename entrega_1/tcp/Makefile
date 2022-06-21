all: client server

client:
	gcc cliente.c cliente_tcp.h cliente_tcp.c servidor_tcp.h servidor_tcp.c -o client -lm

server:
	gcc servidor.c cliente_tcp.h cliente_tcp.c servidor_tcp.h servidor_tcp.c -o server -lm
