//Adding the required libraries
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

//Main function
int main(int argc, char const *argv[])
{
 //Creating file descriptor var, bytes_leidos var (to store the bytes that were read)
 //longitud var to store the bytes that will be read and texto (pointer var)
 int fd;
 int bytes_leidos = 0;
 // Why 117? Because that number are the bytes that were written
 // in write_con_fd.c program
 int longitud = 117;
 char* texto;

 //Using an 'if' statement to verify if open() function can open and read the file
 if( (fd = open("archivo_con_fd.txt",  O_RDONLY | O_CREAT) ) == -1 )
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

  // Before reading the file, the memory must be reserved for the text
  // But we need to know the text length to be read
  texto = malloc(longitud);

  //Using an 'if' statement to verify if read() function can perform its task successfully
  if( (bytes_leidos = read(fd, texto, longitud ) ) == -1 )
  {
   //read() function has returned -1 and cannot write in the file
   printf("Error al leer el archivo\n");
   exit(0);
  }
  else
  {
   //printing the bytes that were read in the file
   printf("lei %d bytes del archivo\n", bytes_leidos);
   //printing the text
   printf("texto: %s\n", texto);
  }
 }
 return 0;
}