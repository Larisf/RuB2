#include <signal.h> 

static void	sig_usr(int);

int main() {
	//kill (getpid(), SIGTERM);
	if (signal(SIGTERM, sig_usr) == SIG_ERR)
    		perror("kann SIGTERM nicht abfangen");

	kill(getpid(), SIGTERM);
	return ;
}

static void sig_usr(int signo)		/* Argument ist Signalnummer */
{
	if (signo == SIGTERM)
		printf("sig_usr: SIGTERM abgefangen\n");
	else if (signo == SIGINT)
		printf("sig_usr: SIGINT abgefangen\n");
	else
		printf("sig_usr: Signal %d empfangen\n", signo);

	return;
}
