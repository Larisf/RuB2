#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include "sm.h"
#include "pv.h"

static int sem_anfordid;

int main(void)
{
	int freie_ressourcen;

	/* Anlegen des Semaphors */
	sem_anfordid = sem_create(SEM_READKEY);
	

	/* Setzen des Sempahors auf 1 */
	sem_set(sem_anfordid, 1);


	/* Beginn Serverschleife */
	while(1) {
		
		/* Abfragen wieviel Ressourcen frei sind, falls 0 Schleife verlassen */
		freie_ressourcen = sem_get(sem_anfordid);
		if (freie_ressourcen == 0)
			break;
		
		/* eine Sekunde warten */
		sleep(1);
		
	/* Ende Serverschleife */
	}
	
	/* Semaphor entfernen */
	sem_rm(sem_anfordid);

	printf("Server terminiert.\n");
	exit(0);
}
