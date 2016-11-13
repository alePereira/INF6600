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
		double insuline;
		if (inject)
			insuline = 1 ;
		else
			insuline= 0;
		Utils::debug("Sending insuline",TAG);
		
		int ret = mq_send(mq_insuline,(char*)&insuline,sizeof(double),NULL);
		//Utils::debug("Sent insuline " + ret + " " + errno,TAG);
		pthread_mutex_lock(&mutex_mode_insuline);
		inject = mode_insuline;
		pthread_mutex_unlock(&mutex_mode_insuline);
		sleep(10);
	}
}