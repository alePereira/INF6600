#include "reset_insuline.h"
#include "def.h"
#include <iostream>
#include <semaphore.h>
#include <signal.h>
#include <string.h>

#define TAG "[Reset ins]"
#include "Utils.h"

sem_t sem_insuline;

void reset_insuline_handler(int sig){
	Utils::debug("Entered",TAG);
	sem_post(&sem_insuline);
}

void* reset_insuline(void* args){
	sem_init(&sem_insuline,0,0);
	struct sigaction sa;
	memset(&sa,0,sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=0;
	sa.sa_handler = reset_insuline_handler;
	sigaction(SIGUSR2,&sa,NULL);
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGUSR2);
	pthread_sigmask(SIG_UNBLOCK,&set,NULL);
	
	while(true){
		int ret = sem_wait(&sem_insuline);
		if(ret)
			sem_wait(&sem_insuline);
		Utils::debug("Sem end",TAG);		
		pthread_mutex_lock(&mutex_insuline);
		insuline = 100; //TODO change
		pthread_mutex_unlock(&mutex_insuline);
	}
}