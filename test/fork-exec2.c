/*        CLIENT-SERVER ARCHITECTURE TEST     */
/*          SANCHEZ TORRES SERGIO DANIEL      */
/*                NOVEMBER 3rd 2022           */
/*            program 05: fork-exec3.c        */

//Adding the required libraries 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

//Defining the spawn function
int spawn (char* program, char** arg_list)
{
  //Creating child_pid var of type pid_t
  pid_t child_pid;

  /* Duplicate this process. */
  //Creating the child process with fork() (child process is
  //and exact copy of parent process)
  child_pid = fork ();

  //Parent process enters to 'if' statement if child_pid is not zero
  if (child_pid != 0) /* This is the parent process. */
    return child_pid;
  //Child process enters to 'else' statement if child_pid is zero
  else {
    /* Now execute PROGRAM, searching for it in the path. */
    printf("soy el hijo, lanzo el ls y termino\n");

    //The execvp function receives two arguments: file name and a pointer array
    //that ends with a NULL string
    execvp (program, arg_list);
    /* The execvp function returns only if an error occurs. */
    //if there are no problems with execvp function, the following 2 lines will 
    //not be executed
    fprintf (stderr, "an error occurred in execvp\n");
    abort ();
  }
}

//Main function
int main ()
{
  printf("SANCHEZ TORRES SERGIO DANIEL\n\n");

  //Creating a var to store the child process status
  int child_status=1;
  printf("1.child_status=%d\n",child_status);

  /* The argument list to pass to the "ls" command. */
  //Creating a pointer array to store the command to be executed.
  //This pointer array has to end with a NULL string. Every string
  //in the pointer array has the next form: name=value
  char* arg_list[] = {
    "ls", /* argv[0], the name of the program. */
    "-l",
    "/",
    NULL /* The argument list must end with a NULL. */
  };

  /* Spawn a child process running the "ls" command. Ignore the
   * 	returned child process ID. */
  //Calling spawn() function and giving the following parameters: command name and
  //pointer array
  spawn ("ls", arg_list);
  printf("soy el padre, voy a esperar a que el hijo termine\n");


  /* Wait for the child process to complete. */
  //Calling wait() function
  //wait() is receiving a pointer as argument. In this argument, wait() will save
  //information about how the process that takes us out of standby status was completed
  wait (&child_status);

  //If WIFEXITED is 'true' (this only happens when the function returns a non-zero value), 
  //it will show the child process status 
  if (WIFEXITED (child_status)){
    printf("2.child_status=%d\n",child_status);

    //Using WEXITSTATUS to return the less signigicant bits to parent process
    printf ("the child process exited normally, with exit code %d\n", WEXITSTATUS (child_status));
  }
  //If WIFEXITED was not 'true'
  else
    printf ("the child process exited abnormally\n");

  //to verify if the program could end successfully
  return 0;
}
