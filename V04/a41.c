#include <stdio.h> 
#include <stdlib.h>
#define MAXLINE 4096

int main(void) {
  int   fd[2];
  char  line[MAXLINE];
  
  if (pipe(fd) < 0) {
    perror("pipe error");
    exit(1);
  } 

  printf("fd[0]: %d\n", fd[0]);
  printf("fd[1]: %d\n", fd[1]);


  write(fd[1], "hello world", 12);
  read(fd[0], line, MAXLINE);

  // Ausgabe von gelesenem Buffer
  printf("reading...\n %s\n", line);
  
    
}
