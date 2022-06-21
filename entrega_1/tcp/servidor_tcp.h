#ifndef SERVIDOR_TCP_H
#define SERVIDOR_TCP_H

void TrataClienteTCP(int socketCliente, char *buffer);
void start_server(unsigned short servidorPorta, char *buffer);

#endif