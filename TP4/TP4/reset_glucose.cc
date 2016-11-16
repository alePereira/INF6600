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
	CHECK(sem_init(&sem_glucose,0,0)<0, "Sem init reset glucose failed")
	struct sigaction sa;
	memset(&sa,0,sizeof(sa));
	CHECK(sigemptyset(&sa.sa_mask),"Sig empty set failed (reset glucose 1)")
	sa.sa_flags=0;
	sa.sa_handler = reset_glucose_handler;
	CHECK(sigaction(SIGUSR1,&sa,NULL),"Sigaction SIGUSR1 failed")
	sigset_t set;
	CHECK(sigemptyset(&set),"Sig empty set failed (reset glucose 2)")
	CHECK(sigaddset(&set,SIGUSR1), "Sig add set SIGUSR1 failed")
	CHECK(pthread_sigmask(SIG_UNBLOCK,&set,NULL),"Pthread sigmask failed (unblock SIGUSR1)")
	
	while(true){
		int ret = sem_wait(&sem_glucose);
		if(ret)
			sem_wait(&sem_glucose);
			
		Utils::debug("Sem end",TAG);		
		pthread_mutex_lock(&mutex_glucose);
		glucose = TOTAL;
		pthread_mutex_unlock(&mutex_glucose);
	}
}