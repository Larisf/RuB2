#define MAXLINE 4069

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, char *argv[]) {
  char  line[MAXLINE];
 int n;
  while (n = read (STDIN_FILENO, line, MAXLINE) > 0)
  {
	int i = 0;
	while (line[i]) {
		line[i] = (char)(toupper(line[i]));
		i++;
	}
	write (STDOUT_FILENO, line, n);
  }
  
  return 0;
}
