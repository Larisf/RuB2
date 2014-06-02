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

  if (pipe(fda) < 0 || pipe(fdb) < 0) {
    perror("pipe error");
    exit(1);
  }     
//1 write, 0 read
  pid = fork();
  if (pid < 0) {
    perror("fork error");
    exit(1);
  }     
  
  else if (pid > 0) {           /* parent */
    close(fda[0]);
    close(fdb[1]);

	write(fda[1], argv[1], strlen(argv[1]));
	close(fda[1]);
	
	while (n = read(fdb[0], line, MAXLINE > 0)) {
		write(STDOUT_FILENO, line, n);
	}
   
    close(fdb[0]);
    waitpid(pid, NULL, 0);
  } 
  else {                        /* child */
    close(fda[1]);
    close(fdb[0]);

    dup2(fda[0], STDIN_FILENO);
    dup2(fda[1], STDOUT_FILENO);

    execlp("./aufg1", "./aufg1", NULL);
  }
  wait(NULL);
  return 0;
}
