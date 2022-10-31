/*        CLIENT-SERVER ARCHITECTURE TEST     */
/*          SANCHEZ TORRES SERGIO DANIEL      */
/*                NOVEMBER 3rd 2022           */
/*               program 04: wait3.c          */

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

  //Using printf() to annouce the calling to fork() function for the first time
  printf( "Llamando a fork la primera vez\n" );

  //Crating the first child process. The retorno_fork var will store pid process
  retorno_fork = fork();

  //Parent process will enter to 'if' statement due to retorno_fork value
  if( retorno_fork != 0 )
  {
    //Using printf() to show retorno_fork() value: child process
    printf( "Proceso padre, la variable retorno_fork la primera vez=%d\n",retorno_fork );

    //Using printf() to annouce the calling to fork() function for the second time
    printf( "Llamando a fork la segunda vez\n" );

    //Crating the second child process. The retorno_fork var will store pid process
    retorno_fork = fork();

    //Parent process will enter to 'if' statement due to retorno_fork value
    if( retorno_fork != 0 )
    {
      //Using printf() to announce that parent proccess will call wait()
      printf( "Proceso padre, llamando a wait\n" );

      //Calling wait() function. In this case, there are a two other processes
      //(child process 1 and 2) and wait() will return child process pid
      int retorno_wait =  wait( &arg_wait );
      printf( "Proceso padre, despues de wait\n" );

      //Using printf() to show the hexadecimal value of the pointer
      printf( "Proceso padre, el valor &arg_wait=%p\n",&arg_wait );

      //Using printf() to show the int value of arg_wait
      printf( "Proceso padre, la variable arg_wait=%d\n",arg_wait );

      //Using printf() to show WIFEXITED(arg_wait) value
      //WIFEXITED() will return TRUE (or any non-zero value) when process
      //could finish with an exit() or wait() call
      printf("Proceso padre, WIFEXITED(arg_wait)=%d\n",WIFEXITED(arg_wait));

      //Using printf() to show WEXITSTATUS(arg_wait) value
      //WEXITSTATUS can be used if WIFEXITED is 'true' and will return the less
      //signigicant bits to parent process
      printf( "Proceso padre, WEXITSTATUS(arg_wait) codigo de salida del hijo=%d\n",WEXITSTATUS(arg_wait));

      //Using printf() to show retorno_wait value. In this case, wait() will return
      //pid process that takes the current process out of its waiting time
      printf( "Proceso padre, la variable retorno_wait=%d\n",retorno_wait );

      //Using printf() to show the EXIT_SUCCESS value
      printf( "EXIT_SUCCESS en el proceso padre=%d\n", EXIT_SUCCESS );
      exit( EXIT_SUCCESS );
    }
    //The second child process will enter to 'else' statement due to retorno_fork value
    else
    {
      //Using printf() to show the second child process pid
      printf( "Proceso hijo 2, el pid es %d\n", getpid() );
      printf( "Proceso hijo 2, a dormir 10 seg\n" ); 

      //Using sleep() with 10 seconds just to sleep the second child process
      sleep( 10 );
      printf( "Proceso hijo 2, despierta\n" );
      printf( "EXIT_SUCCESS en el proceso hijo 2=%d\n", EXIT_SUCCESS );
      
      //exit value
      exit( EXIT_SUCCESS );
    }
  }
  //The first child process will enter to 'else' statement due to retorno_fork value
  else
  {
    //Using printf() to show the first child process pid
    printf( "Proceso hijo 1, el pid es %d\n", getpid() );
    printf( "Proceso hijo 1, a dormir 10 seg\n" );

    //Using sleep() with 10 seconds just to sleep the first child process
    sleep( 10 );
    printf( "Proceso hijo 1, despierta\n" );
    printf( "EXIT_SUCCESS en el proceso hijo 1=%d\n", EXIT_SUCCESS );
    
    //exit value
    exit( EXIT_SUCCESS );
  }
}