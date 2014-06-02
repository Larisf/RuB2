#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NR_OF_PHIL 5

static int gabel_vorhanden[NR_OF_PHIL],rechts[NR_OF_PHIL],links[NR_OF_PHIL]; 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *phil(void *arg);
int gabeln_holen(int i);
void gabeln_abgeben(int i);
void init_gabeln(int nr);

int main (void)
{
	int i,status;
	pthread_t thread[NR_OF_PHIL];

	init_gabeln(NR_OF_PHIL);

	/* Starte die Threads */
	for(i=0;i<NR_OF_PHIL;i++){
		status=pthread_create(&thread[i], NULL, phil, i);
		if(status!=0){
			fprintf(stderr,"Error: Konnte Thread %d nicht erzeugen\n",i);
			exit(-1);		
		}
	}

	/* Warte auf Terminierung */
	for(i=0;i<NR_OF_PHIL;i++)
		pthread_join(thread[i],NULL);

	exit(0);
}

void *phil(void *arg){

	int nr = (int)arg;
	int i;

	printf("Philosoph %d gestartet\n",nr);

	for(i=0;i<20;i++)
	{
		gabeln_holen(nr);
		printf("Philosoph %d isst\n",nr);
		sleep(nr/2);
		gabeln_abgeben(nr);
		sleep(1);
	}

	printf("Philosoph %d ist fertig\n",nr);

	return NULL;
}

int gabeln_holen(int i){

	int erfolg=0;
	
	while (!erfolg) {
		pthread_mutex_lock(&mutex);
		
		if (gabel_vorhanden[i] == 2) {
			gabel_vorhanden[i] = 0;
			gabel_vorhanden[links[i]] -= 1;
			gabel_vorhanden[rechts[i]] -= 1;
			
			erfolg = 1;
		}
		
		pthread_mutex_unlock(&mutex);
	}
	
	return erfolg;
}

void gabeln_abgeben(int i){
	pthread_mutex_lock(&mutex);
	gabel_vorhanden[i] = 2;
	gabel_vorhanden[links[i]] += 1;
	gabel_vorhanden[rechts[i]] += 1;
	pthread_mutex_unlock(&mutex);
 
}

void init_gabeln(int nr){

	int i;

	for(i=0;i<nr;i++){
		gabel_vorhanden[i]=2;
		rechts[i]=(i+1)%nr;
		links[i]=(i-1+nr)%nr;
	}
}
