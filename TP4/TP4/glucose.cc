#include "glucose.h"
#include "def.h"
#include <sys/time.h>
#include <iostream>
#include <errno.h>

#define TAG "[Glucose]"
#include "Utils.h"

int mode_glucose;

void* glucose_handler(void* args){
	int inject = MODE_GLUCOSE_OFF;
	while(1){
		double local_glucose ;
		if (inject==MODE_HYPOGLYCEMIE)
			local_glucose= 5;
		else if (inject==MODE_GLUCOSE)
			local_glucose = 1 ;
		else
			local_glucose= 0;

		pthread_mutex_lock(&mutex_glucose);
		local_glucose = local_glucose<glucose ? local_glucose : glucose;
		glucose-=local_glucose;
		pthread_mutex_unlock(&mutex_glucose);
		
		Utils::debug("Sending glucose",TAG);
		mq_send(mq_glucose,(char*)&local_glucose,sizeof(double),NULL);
		
		pthread_mutex_lock(&mutex_mode_glucose);
		inject = mode_glucose;
		pthread_mutex_unlock(&mutex_mode_glucose);
		sleep(1);
	}
}