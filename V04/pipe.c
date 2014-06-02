#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#define MAXLINE 4096

int main(int argc, char *argv[]) {
  int   n, fda[2], fdb[2], err;
  pid_t pid;
  char  line[MAXLINE];

  if (argc < 1)
	exit(1);
  

  if (pipe(fda) < 0 || pipe(fdb) < 0) {
    perror("pipe error");
    exit(1);
  }     

  pid = fork();
  if (pid < 0) {
    perror("fork error");
    exit(1);
  }     
  
  else if (pid > 0) {           /* parent */
    close(fda[0]);
    write(fda[1], argv[1], strlen(argv[1]) + 1);
    close(fdb[1]);
    read(fdb[0], line, MAXLINE);
    printf("parent line: %s\n", line);
  } 
  else {                        /* child */
    close(fda[1]);
    n = read(fda[0], line, MAXLINE);
    sleep(1);

    int i = 0;
    while (line[i]) {
	line[i] = (char)(toupper(line[i]));
        i++;
    }
    
    close(fdb[0]);
    write(fdb[1], line, strlen(line));
  }
  wait(NULL);
  return 0;
}
