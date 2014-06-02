#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h> 

#define MAXLINE 4096	/* max line length */

int main(void) {
  char	buf[MAXLINE];
  pid_t   pid;
  int		status;
  
// SIGTERM und INT ignorieren
  signal(SIGTERM, SIG_IGN);
  signal(SIGINT, SIG_IGN); 
	

  printf("%% ");  /* print prompt (printf requires %% to print %) */
  while (fgets(buf, MAXLINE, stdin) != NULL) {
    buf[strlen(buf) - 1] = 0;	/* replace newline with null */
    
// Ende bei Q eingabe
    if (buf[0] == 'q' && strlen(buf) < 2)
	exit(0);
	
    if ( (pid = fork()) < 0)
      perror("fork error");
    	
    else 
    if (pid == 0) {		/* child */
	if (buf[strlen(buf) - 1] == '&')
		buf[strlen(buf) - 2] = '\0';
      execlp(buf, buf, (char *) 0);
      printf("couldn't execute: %s\n", buf); 
      exit(127);
    }


    
if (buf[strlen(buf) - 1] != '&') {
 //   if ( (pid = waitpid(pid, &status, 0)) < 0)
   //   perror("waitpid error"); 
printf("\n In parent %d \n",getpid());
waitpid(pid,&status,NULL);
printf("\n Child return status %d \n",WEXITSTATUS(status));
}
    printf("%% ");
  }
  exit(0);

}
