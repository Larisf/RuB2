#include <stdio.h>
int main() {
	printf("PID: %d\n", getpid());
	printf("Guten %d\n", fork());
	
	printf("Pid %d, Ppid %d\n", getpid(), getppid());

	printf("Tag %d\n", fork());
}
