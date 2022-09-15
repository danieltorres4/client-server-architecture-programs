#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Este ejemplo muestra la funcion execle
// invocando a un programa nuestro getenv_user
// para leer la variable de entorno USER
int main(void)
{
  // como es execle entonces es una lista 
  // y ademas puede leer variables de entorno que vienen en un arreglo 
  // y que solo son validas para esta ejecucion
  // la sintaxis es:
  // int execle(char *path, char *arg0,... char*argn, (char *)0, char *envp[ ]);
  // path es la ruta incluyendo el nombre del comando/ejecutable
  // En C el nombre del comando/ejecutable es el argumento 0
  // por eso se repite
  // con NULL se indica que se llego al final de la lista de argumentos
  char *variables_entorno[] = { "PATH=/bin:/usr/bin", "USER=joe", NULL };
  printf("SANCHEZ TORRES SERGIO DANIEL\n\n");
  printf( "el valor de la variable de entorno USER es: %s\n", getenv("USER") );
  printf( "ahora ejecutando ./getenv_user, el valor de la variable de entorno USER es: \n" );
  if( execle("./getenv_user1", "./getenv_user1", NULL, variables_entorno) == -1)
  {
    perror("execle");
    exit(EXIT_FAILURE);
  }
  puts("Si execle es exitoso, esto no se imprime");
  exit(EXIT_SUCCESS);
}