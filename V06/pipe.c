#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define BUFFERSIZE 512

const char fA[] = "/tmp/fA"; // FIFO READ
const char fB[] = "/tmp/fB"; // FIFO WRITE

void convert(const char*);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Zu wenig Argumente.");
	return EXIT_FAILURE;
  }
  
  int i = 1;
  while (i < argc) { 
    convert(argv[i]);
    i++;
  }
  
  return EXIT_SUCCESS;
}

void convert(const char *arg) {
  pid_t pid = fork();
  
  // PARENT, liest
  if(pid == 0) {
    printf("Open FIFO B\n");
    int fd_B = open(fB, O_RDONLY);
	if (fd_B == -1) {
		perror("Error open");
		exit (-1);
	}
      
    ssize_t num;
    char buf[BUFFERSIZE];
    buf[BUFFERSIZE - 1] = '\0';
    
    printf("Lese ...\n");
    while ((num = read(fd_B, buf, (BUFFERSIZE - 1))) > 0) {
      buf[num] = '\0';
      printf("<- %s\n", buf);
    }
    
    if (num == -1) {
      perror("Error convert read");
    }
      
    if (close(fd_B) == -1) {
      perror("Error close fd_B"); 
    }
    
    exit(0);
  }
  
  // CHILD, write
  else if (pid > 0) {
	printf("Open FIFO A\n");
    int fd_A = open(fA, O_WRONLY);
	if (fd_A  == -1) {
		perror("Error open");
		exit (-1);
	}
  
    printf("%s ->\n", arg);
    if (write(fd_A, arg, strlen(arg)) == -1) { // Argument schreiben
      perror("Error write argument");
      exit (-1);
    }
    
    if (close(fd_A) == -1) {
      perror("Error close fd_A"); 
	  exit (-1);
    }
    
    printf("Warte auf Kind\n");
    waitpid(pid, NULL, 0);
  }
  else {
    perror("Error fork");
    exit (-1);
  }
  exit (0);
}
