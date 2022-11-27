#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>


#define BLEN 128

void main(int argc, char *argv[]) {
    struct sockaddr_in socket_cliente;
    struct hostent *h;
    int fd;
    int n;
    char *host;
    char buf[BLEN];

    printf( "1. Se llama a la funcion socket(...) y devuelve el file descriptor propio del cliente fd\n" );
    printf( "fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);\n\n" );
    fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    printf( "2. Se inicializan los atributos de la variable struct sockaddr_in llamada socket_cliente\n\n" );
    printf( "Pero se inicializan con datos del servidor, como son la IP y el puerto\n\n" );

    socket_cliente.sin_family = AF_INET;
    h = gethostbyname(argv[1]);
    socket_cliente.sin_port = htons(atoi(argv[2]));
    memcpy(&socket_cliente.sin_addr, h->h_addr, h->h_length);

    printf( "3. La funcion connect() es la que intenta conectarse al servidor\n" );
    printf( "Esta funcion se relaciona con la funcion accept(...) del servidor\n\n" );
    connect(fd, (struct sockaddr *) &socket_cliente, sizeof(socket_cliente));
        
    printf( "4. Después de que se conectan, empieza el intercambio de mensajes\n" );
    printf("Yo cliente envío el nombre del alumno\n");
    char *nombreAlumno = "SANCHEZ TORRES SERGIO DANIEL";
    send(fd, nombreAlumno, strlen(nombreAlumno), 0);
    printf("Se envío el nombre\n\n");
    
    printf("Y después recibe la respuesta\n");
    n = recv(fd, buf, sizeof(buf), 0);
    write(1, buf, n);
    printf("\n"); 
    printf("\n");

    printf( "5. Por ultimo, se cierra el file descriptor\n" );
    printf( "close(fd);\n" );
    close(fd);
    exit(0);
}