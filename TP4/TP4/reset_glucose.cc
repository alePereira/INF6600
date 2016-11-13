#include "reset_glucose.h"
#include "def.h"
#include <semaphore.h>
#include <signal.h>
#include <string.h>

#define TAG "[Reset gl]"
#include "Utils.h"

sem_t sem;

void reset_glucose_handler(int sig){
	Utils::debug("Entered",TAG);
	sem_post(&sem);
}

void* reset_glucose(void* args){
	sem_init(&sem,0,1);
	struct sigaction sa;
	memset(&sa,0,sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=0;
	sa.sa_handler = reset_glucose_handler;
	sigaction(SIGSTOP,&sa,NULL);
	sigaction(SIGTSTP,&sa,NULL);
		
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGSTOP);
	sigaddset(&set,SIGTSTP);
	pthread_sigmask(SIG_UNBLOCK,&set,NULL);
	
	while(true){
		sem_wait(&sem);
		Utils::debug("Sem end",TAG);		
		pthread_mutex_lock(&mutex_glucose);
		glucose = 100; //TODO change
		pthread_mutex_unlock(&mutex_glucose);
	}
}