/*        CLIENT-SERVER ARCHITECTURE TEST     */
/*          SANCHEZ TORRES SERGIO DANIEL      */
/*                NOVEMBER 3rd 2022           */
/*             program 01: for-exec.c         */

//Adding the required libraries 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

//Defining the spawn function
int spawn (char* program, char** arg_list)
{
 //Creating child_pid var of type pid_t
 pid_t child_pid;

 //Creating the child process with fork() (child process is
 //and exact copy of parent process)
 child_pid = fork ();

 //Parent process enters to 'if' statement if child_pid is not zero
 if (child_pid != 0)
  return child_pid;
 //Child process enters to 'else' statement if child_pid is zero
 else
 {
  //The execvp function receives two arguments: file name and a pointer array
  //that ends with a NULL string
  execvp (program, arg_list);

  //if there are no problems with execvp function, the following 2 lines will 
  //not be executed
  fprintf (stderr, "ocurrio un error al ejecutar execvp(...)\n");
  abort ();
 }
}

int main ()
{
  printf("SANCHEZ TORRES SERGIO DANIEL\n\n");

  //Creating a pointer array to store the command to be executed.
  //This pointer array has to end with a NULL string. Every string
  //in the pointer array has the next form: name=value
  char* arg_list[] = {
   "ls",
   "-l",
   "/",
   NULL
  };

  //Calling spawn() function and giving the following parameters: command name and
  //pointer array
  spawn ("ls", arg_list);

  //Using printf() to know when the parent process ends
  printf ("Termina el proceso padre\n");

  //to verify if the program could end successfully
  return 0;
}