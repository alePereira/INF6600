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
	CHECK(sem_init(&sem_insuline,0,0), "Sem init reset insuline failed")
	struct sigaction sa;
	memset(&sa,0,sizeof(sa));
	CHECK(sigemptyset(&sa.sa_mask),"Sig empty set failed (reset insuline 1)")
	sa.sa_flags=0;
	sa.sa_handler = reset_insuline_handler;
	CHECK(sigaction(SIGUSR2,&sa,NULL),"Sigaction SIGUSR2 failed")
	sigset_t set;
	CHECK(sigemptyset(&set),"Sig empty set failed (reset insuline 2)")
	CHECK(sigaddset(&set,SIGUSR2), "Sig add set SIGUSR2 failed")
	CHECK(pthread_sigmask(SIG_UNBLOCK,&set,NULL),"Pthread sigmask failed (unblock SIGUSR2)")
	
	while(true){
		int ret = sem_wait(&sem_insuline);
		if(ret)
			sem_wait(&sem_insuline);
			
		Utils::debug("Sem end",TAG);		
		pthread_mutex_lock(&mutex_insuline);
		insuline = TOTAL;
		pthread_mutex_unlock(&mutex_insuline);
	}
}