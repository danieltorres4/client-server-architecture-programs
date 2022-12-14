#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main()
{
 // este es el descriptor de archivo o file descriptor
 // se le asignara el valor devuelto por la funcion socket
 int socket_fd;

 // creamos el socket
 // la funcion socket devuelve un int que es el file descriptor
 printf("socket (AF_UNIX, SOCK_STREAM, 0)\n");
 socket_fd = socket (AF_UNIX, SOCK_STREAM, 0);
 printf("socket_fd=%d\n",socket_fd);//imprimiendo valor de fd

 // una variable de tipo struct sockaddr_un
 // que sera nuestra estructura server socket
 struct sockaddr_un servidor;

 // un apuntador a la variable anterior
 struct sockaddr* pservidor = (struct sockaddr*)&servidor;

 // este int almacenara el size de la estructura
 // sockaddr_un que es nuestra estructura server socket
 int size_servidor = sizeof(servidor);

 // el archivo con el que se nombrara al socket
 // el archivo no debe existir y se creara con size 0
 const char* const socket_name = "socket"; //se crea en el mismo directorio del ejecutable

 // inicializamos el atributo sun_family de la struct
 servidor.sun_family = AF_UNIX;

 // inicializamos el atributo sun_path con el nombre del archivo
 strcpy( servidor.sun_path, socket_name );

 // Ligamos el socket con la estructura servidor y como esta
 // tiene el nombre del archivo, entonces el socket se hace
 // un socket nombrado
 printf("bind(socket_fd,pservidor,size_servidor)\n");
 bind(socket_fd,pservidor,size_servidor);
 printf("socket_fd=%d\n",socket_fd);

 // El servidor se pone en modo de escucha para conexiones cliente
 printf("listen (socket_fd, 5)\n");
 listen (socket_fd, 5);

 // Las siguientes 3 sentencias crean una estructura sockadd_un
 // Obtiene su apuntador y su size o longitud
 // Esta estructura se "hablara" con el socket del lado del cliente
 // en cuanto sea aceptada la conexion del cliente
 struct sockaddr_un cliente;
 struct sockaddr* pcliente = (struct sockaddr*)&cliente;
 int size_cliente = sizeof(cliente);

 printf("Antes de la funcion accept()\n");
 // Esta funcion bloquea hasta que llegue una peticion de conexion de un cliente
 int client_socket_fd = accept (socket_fd, (struct sockaddr *)pcliente, &size_cliente); //devuelve fd del cliente
 printf("Se acepto la conexion de un cliente\n");
 printf("socket_fd=%d\n",socket_fd);
 printf("client_socket_fd=%d\n",client_socket_fd);

 printf("close(socket_fd)\n");
 close( socket_fd );
 printf("close(client_socket_fd)\n");
 close( client_socket_fd );
 printf("unlink( socket_name )\n");
 unlink( socket_name );
 printf("socket_fd=%d\n",socket_fd);
 printf("client_socket_fd=%d\n",client_socket_fd);
 return 0;
}