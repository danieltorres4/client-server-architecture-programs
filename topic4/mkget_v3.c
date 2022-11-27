#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#include <sys/wait.h>

#define BUFFER_SIZE 1024

int socket_connect(char *host, in_port_t port)
{
  struct hostent *hp;
  struct sockaddr_in addr;
  int on = 1, sock;     

  if((hp = gethostbyname(host)) == NULL)
  {
    herror("gethostbyname");
    exit(1);
  }

  bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
  addr.sin_port = htons(port);
  addr.sin_family = AF_INET;
  sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));

  if(sock == -1)
  {
    perror("setsockopt");
    exit(1);
  }
																		
  if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1)
  {
    perror("connect");
    exit(1);
  }

  return sock;
}

int main(int argc, char *argv[])
{
  int fd;
  char buffer[BUFFER_SIZE];

  if(argc < 3)
  {
    fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
    exit(1); 
  }

  int contador_de_hijos = 0;
  int retorno_fork;
  while( contador_de_hijos < atoi( argv[3] ) )
  {
    if( (retorno_fork = fork()) == 0 )
    {
      fd = socket_connect(argv[1], atoi(argv[2])); 
      printf("Hijo %d enviando peticion...\n", contador_de_hijos);
      sprintf (buffer, "GET /Hello1/ HTTP/1.0\n\n");
      write (fd, buffer, strlen (buffer));

      /* 
      No queremos leer la respuesta para no saturar nuestro cliente
      
      while(read(fd, buffer, BUFFER_SIZE - 1) != 0)
      {
        fprintf(stderr, "%s", buffer);
        bzero(buffer, BUFFER_SIZE);
      }
      */
 
      /* shutdown(fd, SHUT_RDWR); */
      close(fd);
      exit(0);
    }
    else
    {
      
      int returnStatus;
      //parecido a wait(), en este caso esperará a que terminen todos los hijos
      waitpid(retorno_fork, &returnStatus, 0);
      if (returnStatus == 0)
      {
        printf("The child process %d terminated normally\n", retorno_fork);
      }
      else
      {
        printf("The child process terminated with an error!.");
      }
      
      contador_de_hijos++;
    }
  }

  return 0;
}