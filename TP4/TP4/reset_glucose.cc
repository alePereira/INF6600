#include "reset_glucose.h"
#include "def.h"
#include <iostream>
#include <semaphore.h>
#include <signal.h>
#include <string.h>

#define TAG "[Reset gl]"
#include "Utils.h"

sem_t sem_glucose;

void reset_glucose_handler(int sig){
	Utils::debug("Entered",TAG);	
	sem_post(&sem_glucose);
}

void* reset_glucose(void* args){
	sem_init(&sem_glucose,0,0);
	struct sigaction sa;
	memset(&sa,0,sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=0;
	sa.sa_handler = reset_glucose_handler;
	sigaction(SIGUSR1,&sa,NULL);
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGUSR1);
	pthread_sigmask(SIG_UNBLOCK,&set,NULL);
	
	while(true){
		int ret = sem_wait(&sem_glucose);
		if(ret)
			sem_wait(&sem_glucose);
			
		Utils::debug("Sem end",TAG);		
		pthread_mutex_lock(&mutex_glucose);
		glucose = 100; //TODO change
		pthread_mutex_unlock(&mutex_glucose);
	}
}