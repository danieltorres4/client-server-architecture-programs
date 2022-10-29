/*        CLIENT-SERVER ARCHITECTURE TEST     */
/*          SANCHEZ TORRES SERGIO DANIEL      */
/*                NOVEMBER 3rd 2022           */
/*                program 05: wait.c          */

//Adding the required libraries 
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

//Main function
int main()
{
  printf("SANCHEZ TORRES SERGIO DANIEL\n\n");
  //Creating arg_wait var
  int arg_wait;

  //Using printf() to announce that the process is starting
  printf( "Iniciando proceso con pid %d\n", getpid() );
  printf( "Llamando a wait\n" );

  //Creating retorno_wait var and declarating with wait() function.
  //wait() function is useful to put a process on standby but in this
  //case there is not a second process (child process) to put in standby
  //and wait() function will return -1.
  //wait() is receiving a pointer as argument, then wait() writes
  //in the pointer information of how the process has ended
  int retorno_wait = wait( &arg_wait );

  //Using printf() to announce that wait() function has ended
  printf( "Despues de wait\n" );

  //Using printf() to show the hexadecimal value of the pointer
  printf( "El valor &arg_wait=%X\n",&arg_wait );

  //Using printf() to show the arg_wait int value
  printf( "La variable arg_wait=%d\n",arg_wait );

  //Using printf() to show the retorno_wait int value
  printf( "La variable retorno_wait=%d\n",retorno_wait );
  return 0;
}