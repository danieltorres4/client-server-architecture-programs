//Adding the required libraries
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

//Main function
int main(int argc, char const *argv[])
{
  //Creating file descriptor var, bytes_escritos var (to store the bytes that were written)
  //and buff array
  int fd;
  int bytes_escritos = 0;
  char buff[] = "Prueba para escribir este texto a archivo, con file descriptor\nMi nombre es: SANCHEZ TORRES SERGIO DANIEL\nMateria ACS";
  
  //Using an 'if' statement to verify if open() function can create a file and open the file
  if( (fd = open("archivo_con_fd.txt",  O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) ) == -1 )
  {
    //the file could not be opened, the open() function has returned -1
    printf("fallo apertura de archivo\n");
    exit(0);
  }
  else
  {
    //the file was opened, file descriptor will be printed
    printf("apertura de archivo exitosa\n");
    printf("file descriptor: %d\n", fd);

    //Using an 'if' statement to verify if write() function can perform its task successfully
    if( (bytes_escritos = write(fd, buff, strlen(buff) ) ) == -1 )
    {
      //write() function has returned -1 and cannot write in the file
      printf("Error al escribir al archivo\n");
      exit(0);
    }
    else
    {
      //printing the bytes that were written in the file
      printf("escribi %d bytes al archivo\n", bytes_escritos);
      close(fd);
    }
  }
  return 0;
}