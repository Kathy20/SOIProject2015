/* Instituto Tecnológico de Costa Rica.
   Centro Académico de San José
   Ingeniería en Computación

   Estudiante
   Kathy Brenes Guerrero

   Principios de Sistemas Operativos
   Fecha: 17 de Noviembre del 2015

   	El Cliente
—————————

El cliente puede ser desarrollado en cualquier lenguaje de programación que considere pertinente, y en la plataforma que prefiera: desktop, móvil, web, etc.

Para iniciar sesión se solicitará un nombre al usuario para iniciar sesión. 

El cliente solicitará, mediante un “protocolo” o mensajes que usted defina, la lista de canciones disponibles para ser escuchadas. 
El usuario mediante el programa cliente podrá seleccionar una canción de entre la lista disponible para su inmediata reproducción. El usuario podrá pausar la canción, saltar a otra antes de que finalice o devolverse al menos al inicio de la canción actual para repetirla. 

Una vez iniciada una canción para su reproducción el programa deberá reproducir la siguiente en la lista sin necesidad de intervención del usuario o bien en un modo aleatorio si el usuario lo desea. 

La creatividad de la interfaz y facilidad de uso del programa cliente será parte de la calificación del cliente.



 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>   
#include <pthread.h>
#include <unistd.h>   
#include <errno.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>

int solicitudCliente(char* user, char* password){

	int sockfd;
	int len;
	struct sockaddr_in address; // *
	int result;
	char ch = 'A';

	// 2. create a socket for the client

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// 3. Name the socket, as agreed with the server

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);//inet_addr("127.0.0.1");
	address.sin_port = htons(9737);
	len = sizeof(address);

	// igual al local client

	result = connect(sockfd, (struct sockaddr *)&address, len);
	
	if (result == -1){
		perror("oops: client2");
		exit(1);
	}

	char algo[2000] = "Hola";
	//------------
	int new_port = 0;
	
	read(sockfd, &new_port, sizeof(int));
	printf("tomela: %i", new_port);

	close(sockfd);

	sleep(1); // si no no recibe el puerto a tiempo y antes de que lo reciba se trata de conectar

	//while (new_port == 0);

	int sockfd2;
    struct sockaddr_in address2;
    int len2;
     
    sockfd2 = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd2 == -1)
    {
        printf("Could not create socket");
    }

    address2.sin_family = AF_INET;
	address2.sin_addr.s_addr = htonl(INADDR_ANY); //inet_addr("127.0.0.1");
	printf("new_port: %i", new_port);
	address2.sin_port = htons(new_port);
	len2 = sizeof(address2);

	result = connect(sockfd2, (struct sockaddr *)&address2, len2);
	
	if (result == -1){
		perror("oops: client1");
		exit(1);
	}

	//-----------

	read(sockfd2, &algo, 2000);
	printf("tomela: %s", algo);

	// Read de las variables del nuevo socket

//-
	int flag = 1;
	char b = 'A';
	while (b != EOF) {

		printf("int from client = %i\n", flag);
		algo[strlen(algo)] = '\0';
				
		write(sockfd2, &algo, strlen(algo));
		read(sockfd2, &b, sizeof(char));
		printf("char from server = %c\n",b);

	}
	close(sockfd2);
	exit(0);

}