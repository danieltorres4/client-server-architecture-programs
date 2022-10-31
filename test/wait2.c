/*        CLIENT-SERVER ARCHITECTURE TEST     */
/*          SANCHEZ TORRES SERGIO DANIEL      */
/*                NOVEMBER 3rd 2022           */
/*               program 03: wait2.c          */

//Adding the required libraries 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//Main function
int main()
{
  printf("SANCHEZ TORRES SERGIO DANIEL\n\n");
  //Declaring retorno_fork var to store the fork() return value
  int retorno_fork;

  //Declaring arg_wait var to store info
  int arg_wait;

  //pid var to store process pid
  int pid = getpid();

  //Using printf() to show pid process
  printf( "Iniciando proceso con pid %d\n", pid );

  //Using printf() to annouce the calling to fork() function
  printf( "Llamando a fork\n" );

  //Crating a child process. The retorno_fork var will store pid process
  retorno_fork = fork();

  //Parent process will enter to 'if' statement due to retorno_fork value
  if( retorno_fork != 0 )
  {
    //Using printf() to show retorno_fork() value: child process
    printf( "Proceso padre, la variable retorno_fork=%d\n",retorno_fork );

    //Using printf() to announce that parent proccess will call wait()
    printf( "Proceso padre, llamando a wait\n" );

    //Calling wait() function. In this case, there is a second process
    //(child process) and wait() will return child process pid
    int retorno_wait =  wait( &arg_wait );
    printf( "Proceso padre, despues de wait\n" );

    //Using printf() to show the hexadecimal value of the pointer
    printf( "Proceso padre, el valor &arg_wait=%p\n",&arg_wait );

    //Using printf() to show the int value of arg_wait
    printf( "Proceso padre, la variable arg_wait=%d\n",arg_wait );

    //Using printf() to show WIFEXITED(arg_wait) value
    //WIFEXITED() will return TRUE (or any non-zero value) when process
    //could finish with an exit() or wait() call
    printf( "Proceso padre, WIFEXITED(arg_wait)=%d\n",WIFEXITED(arg_wait) );

    //Using printf() to show WEXITSTATUS(arg_wait) value
    //WEXITSTATUS can be used if WIFEXITED is 'true' and will return the less
    //signigicant bits to parent process
    printf( "Proceso padre, WEXITSTATUS(arg_wait) codigo de salida del hijo=%d\n",WEXITSTATUS(arg_wait) );

    //Using printf() to show retorno_wait value. In this case, wait() will return
    //pid process that takes the current process out of its waiting time
    printf( "Proceso padre, la variable retorno_wait=%d\n",retorno_wait );

    //Using printf() to show the EXIT_SUCCESS value
    printf( "EXIT_SUCCESS en el proceso padre=%d\n", EXIT_SUCCESS );
    exit( EXIT_SUCCESS );
  }
  //Child process will enter to 'else' statement due to retorno_fork value
  else
  {
    //Using printf() to show child process pid
    printf( "Proceso hijo, el pid es %d\n", getpid() );
    printf( "Proceso hijo, a dormir 10 seg\n" );

    //Using sleep() with 10 seconds just to sleep child process
    sleep( 10 );
    printf( "Proceso hijo, despierta\n" );
    printf( "proceso hijo=%d\n", 0 );

    //exit value
    exit( 0 );
  }
}