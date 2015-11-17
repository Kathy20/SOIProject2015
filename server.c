/* Instituto Tecnológico de Costa Rica.
   Centro Académico de San José
   Ingeniería en Computación

   Estudiante
   Kathy Brenes Guerrero

   Principios de Sistemas Operativos
   Fecha: 17 de Noviembre del 2015

    El Servidor
—————————

1) El servidor deberá estar programado completamente sobre un sistema 
operativo Linux y en el lenguaje C, usando el compilador gcc. 
2) Deberá usar sockets para la comunicación de los clientes remotos 
hacia un puerto y una IP conocidos el cual deberá establecer o bien 
configurar una resolución de nombres vía DNS o similar. 
3)El servidor deberá atender las solicitudes y al recibir una conexión 
deberá crear un proceso thread para que atienda a dicho cliente. 
4) Cada thread deberá enviar los datos de música al cliente el cual 
va a reproducir los datos conforme los recibe, se puede utilizar 
un buffer para almacenamiento temporal de información que se vaya 
a reproducir.
5) El programa servidor deberá informar mediante una bitácora en 
pantalla de las acciones que ocurren en el sistema tales como: 
un usuario conectado, un cliente que reproduce una canción, 
identificando dicho cliente con su nombre de inicio de sesión y 
la canción que solicita. Dicha información debe quedar almacenada 
en un archivo de texto en el servidor. 
6) El servidor leerá la música desde una carpeta en el sistema 
donde corre y debe ser fácil poder agregar y registrar nueva 
música en el sistema. Es decir, la música disponible no debería 
estar “alambrada” en el código .

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


void *connection_client(void *arg);

int main ()
{
  int listenning=1;
  int socket_server, socket_cliente;
  int server_len, client_len;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  //Create a main socket server for the clients
  socket_server = socket(AF_INET, SOCK_STREAM, 0);
  printf("Creation server socket for the client: %s\n",strerror(errno));  
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY); //inet_addr("127.0.0.1");
  server_address.sin_port = htons(9737);
  server_len = sizeof(server_address);
  bind(socket_server, (struct sockaddr *)&server_address, server_len);
  printf("Server socket Bind (assigned address): %s\n",strerror(errno));  
  //Request locales
  listen(socket_server, 1);
  printf("Server socket Listen: %s\n",strerror(errno));
  while(listenning) {
    pthread_t a_thread;
    
    while( (socket_cliente = accept(socket_server, (struct sockaddr *)&client_address, (socklen_t*)&client_len)) )
      {
          puts("Connection accepted");
           
          if( pthread_create( &a_thread, NULL ,  connection_client , (void*) &socket_cliente) < 0)
          {
              perror("could not create thread");
              //return 1;
          }
           
          //Now join the thread , so that we dont terminate before the thread
          //pthread_join( a_thread , NULL);
          puts("Handler assigned");
      }

        return 0;
  }
}

void *connection_client(void *socket_desc)
{
  int sock = *(int*)socket_desc;
  int read_size;
  char *message , client_message[2000];
  //--------------------
  int socket_server, clientfd;
  struct sockaddr_in address, address2;
  int len, len2;
  /* Creación del socket */  
  socket_server = socket(AF_INET, SOCK_STREAM, 0);
  printf("Socket Creation: %s\n",strerror(errno)); 
  srand(rand());
    int port = rand() % 10000 + 2350;
    printf("new port: %i\n", port);

    address.sin_family = AF_INET;
  address.sin_addr.s_addr = htonl(INADDR_ANY); //inet_addr("127.0.0.1");
  address.sin_port = htons(port);
  len = sizeof(address);
  bind(socket_server, (struct sockaddr *)&address, len); 
  printf("Client socket Bind (assigned address): %s\n",strerror(errno));  
  write(sock, &port , sizeof(int));
  close(sock);
  listen(socket_server, 1);
  clientfd = accept(socket_server, (struct sockaddr *)&address2, (socklen_t*)&len2);
  puts("conecction accepted thread");
    
    //close(socket_server);
    return 0;
}
