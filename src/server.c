/*
 * server.c
 *
 *  Created on: 24/10/2017
 *      Author: utnso
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char** argv) {
	if(argc != 2){
		printf("numero incorrecto de parametros\n");
		return 1;
	}

	int puerto = atoi(argv[1]);

	struct sockaddr_in direccionServidor;
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_addr.s_addr = INADDR_ANY;
	direccionServidor.sin_port = htons(puerto);

	int servidor = socket(AF_INET, SOCK_STREAM, 0);

	int activado = 1;
	setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));

	if (bind(servidor, (void*) &direccionServidor, sizeof(direccionServidor)) != 0) {
		perror("Falló el bind");
		return 1;
	}

	printf("Estoy escuchando\n");
	listen(servidor, 100);

	//------------------------------

	struct sockaddr_in direccionCliente;
	unsigned int tamanioDireccion;

	while(1){
		int cliente = accept(servidor, (void*) &direccionCliente, &tamanioDireccion);

		printf("Recibí una conexión en %d!!\n", cliente);

		//------------------------------

		char* buffer = malloc(1000);

		while (1) {
			int bytesRecibidos = recv(cliente, buffer, 6, 0);
			if (bytesRecibidos <= 0) {
				perror("El chabón se desconectó o bla.");
				break;
			}

			buffer[bytesRecibidos] = '\0';
			printf("Me llegaron %d bytes con %s\n", bytesRecibidos, buffer);
		}

		free(buffer);
	}

	return 0;
}





