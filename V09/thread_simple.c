#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *schlafe(void *arg);

int main (int argc, char *argv[])
{
	if (argc < 1) {
		printf("Zu wenig Parameter angegeben.\n");
		exit(-1);
	}
	else {
		printf("Erstelle Threads.\n");
	}
	
	int i;
	int status;
	int threadAnzahl = argc - 1;
	pthread_t thread[threadAnzahl];
	int sleepTime[threadAnzahl];

	/* Starte den Thread */
	for (i = 1; i <= threadAnzahl; i++) {
		sleepTime[i - 1] = atoi(argv[i]);
		printf("Sleeptime %d: %d\n", i, sleepTime[i - 1]);
		status = pthread_create(&thread[i - 1], NULL, schlafe, &sleepTime[i - 1]);

		if (status != 0) {
			printf("Status: %d\n", status);
			fprintf(stderr,"Error: Konnte Thread nicht erzeugen\n");
			exit(-1);
		}
	}
	
	/* Warte auf Terminierung */
	for (i = 0; i < threadAnzahl; i++) {
		pthread_join(thread[i], NULL);
	}

	exit(0);
}

void *schlafe(void *arg){
	int sek = *((int*)arg);
	printf("Habe folgende Zeit erhalten: %d\n",sek);
	sleep(sek);
	printf("Thread mit der Zeit - %d Sekunden - wid terminiert.\n", sek);
	
	return NULL;
}
