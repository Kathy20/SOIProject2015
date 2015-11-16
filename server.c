/* Instituto Tecnológico de Costa Rica.
   Centro Académico de San José
   Ingeniería en Computación

   Estudiante
   Kathy Brenes Guerrero

   Principios de Sistemas Operativos

   Fecha: 17 de Noviembre del 2015

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>   
#include <pthread.h>
#include <unistd.h>   
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>


void *thread_function(void *arg);

int main ()
{
  int server_sockfd, client_sockfd;
  int server_len, client_len;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;

  // 2. create a socket for the client

  server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sockfd == -1)
    {
        printf("Could not create socket");
    }

  // 3. Name the socket

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY); //inet_addr("127.0.0.1");
  server_address.sin_port = htons(9737);
  server_len = sizeof(server_address);
  if (bind(server_sockfd, (struct sockaddr *)&server_address, server_len) < 0) {
    //print the error message
        perror("bind failed. Error");
        return 1;
  }

  // Igual al local server
  listen(server_sockfd, 1);
  while(1) {
    pthread_t a_thread;
    
    while( (client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, (socklen_t*)&client_len)) )
      {
          puts("Connection accepted");
           
          if( pthread_create( &a_thread, NULL ,  thread_function , (void*) &client_sockfd) < 0)
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

void *thread_function(void *socket_desc)
{
  int sock = *(int*)socket_desc;
    int read_size;
    char *message , client_message[2000];
//--------------------
    int sockfd, clientfd;
    struct sockaddr_in address, address2;
    int len, len2;
     
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Could not create socket");
    }

    srand(rand());
    int port = rand() % 10000 + 2000;
    printf("new port: %i\n", port);

    address.sin_family = AF_INET;
  address.sin_addr.s_addr = htonl(INADDR_ANY); //inet_addr("127.0.0.1");
  address.sin_port = htons(port);
  len = sizeof(address);
  if (bind(sockfd, (struct sockaddr *)&address, len) < 0) {
    //print the error message
        perror("bind failed. Error");
        //return 1;
  }
//--------------
   write(sock, &port , sizeof(int));
    close(sock);

    listen(sockfd, 1);

    FILE* fd = NULL;

    fd = fopen("alert.mp3", "r");
    char b;
    int flag;

    while (b = fgetc(fd) != EOF) {
      printf("c = %c\n", b);
    }

    clientfd = accept(sockfd, (struct sockaddr *)&address2, (socklen_t*)&len2);
    puts("conecction accepted thread");
    message = "Now type something and i shall repeat what you type \n";
  write(clientfd, message , strlen(message));

    while((read_size = recv(sockfd , &flag, sizeof(int) , 0)) > 0 && (b = fgetc(fd)) != EOF)
    {
    write(clientfd , &b , sizeof(char));
    printf("b = %c", b);
  }
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
  
    //close(server_sockfd);
    return 0;
}
