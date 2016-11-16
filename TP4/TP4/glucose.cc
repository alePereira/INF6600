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
		double g ;
		if (inject==MODE_HYPOGLYCEMIE)
			g= 5;
		else if (inject==MODE_GLUCOSE)
			g = 1 ;
		else
			g= 0;

		pthread_mutex_lock(&mutex_glucose);
		glucose-=g;
		if(glucose <0)
			glucose=0;
		pthread_mutex_unlock(&mutex_glucose);
		
		Utils::debug("Sending glucose",TAG);
		std::cout << TAG << "g val " << g  << " " << inject << std::endl;
		int ret = mq_send(mq_glucose,(char*)&g,sizeof(double),NULL);
		std::cout << TAG << "SEND " <<ret << std::endl;
		//Utils::debug("Sent glucose " + std::string(ret) + " " + errno,TAG);
		
		pthread_mutex_lock(&mutex_mode_glucose);
		inject = mode_glucose;
		std::cout << "HERE " << g  << " " << inject << std::endl;
		pthread_mutex_unlock(&mutex_mode_glucose);
		sleep(5);
	}
}