#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

#define BUFFERSIZE 512

const char fA[] = "/tmp/fA"; // FIFO READ
const char fB[] = "/tmp/fB"; // FIFO WRITE

void sighandler(int);

int main(int argc, char* argv[]){
unlink(fA);
unlink(fB);
  if ((mkfifo(fA, 0664) == -1) || (mkfifo(fB, 0664) == -1)) {
	perror("Error create fifo");
	return EXIT_FAILURE;
  }
  
  printf("Sighandler bekannt machen\n");
  signal(SIGINT, sighandler); 
  signal(SIGTERM, sighandler); 
  

  
  int fd_A; // File descriptor A
  int fd_B; // File descriptor B
  
  while (TRUE) {
	printf("open fifo a...\n");
	fd_A = open(fA, O_RDONLY);
	printf("open fifo b...\n");	 
	fd_B = open(fB, O_WRONLY); 
	
	if (fd_A < 0 || fd_B < 0) {
		perror("error in open");
		return EXIT_FAILURE;
	}
	else {
		printf("fifos are open");
	}
	ssize_t num, num2;
	char buf[BUFFERSIZE];

	while ((num = read(fd_A, buf, BUFFERSIZE)) > 0) {
		printf("<<< %d\n", (int)num);

		int i = 0;
		while (i < num) {
			buf[i] = toupper(buf[i]);
			i++;
		}

		if ((num2 = write(fd_B, buf, num)) == -1) {
			perror("Error write");
		}
		else {
			printf("%d >>>\n", (int)num2); 
		}
		break;
	}
    
	if (close(fd_A) || close(fd_B)) { 
		exit(-1);
	}
return EXIT_SUCCESS;
}
  
  
}



void sighandler(int nr){
  if(nr == SIGINT || nr == SIGTERM){
    if(unlink(fA) == -1){
      perror("Error unlink");
    }
    if(unlink(fB) == -1){
     perror("Error unlink"); 
    }
    exit(0);
  }
}
