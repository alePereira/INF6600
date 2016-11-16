#include "insuline.h"
#include "def.h"
#include <iostream>
#include <errno.h>

#define TAG "[Insuline]"
#include "Utils.h"
int mode_insuline;

void* insuline_handler(void* args){
		
	int inject = MODE_INSULINE_ON;
	
	while(1){
		double local_insuline;
		if (inject)
			local_insuline = 1 ;
		else
			local_insuline= 0;
			
		Utils::debug("Sending insuline",TAG);
		pthread_mutex_lock(&mutex_insuline);
		local_insuline = local_insuline<insuline ? local_insuline : insuline;
		insuline-=local_insuline;
		pthread_mutex_unlock(&mutex_insuline);
		
		mq_send(mq_insuline,(char*)&local_insuline,sizeof(double),NULL);

		pthread_mutex_lock(&mutex_mode_insuline);
		inject = mode_insuline;
		pthread_mutex_unlock(&mutex_mode_insuline);
		sleep(1);
	}
}