#include "capteur_glucose.h"
#include "def.h"

#define TAG "[Capt gl]"
#include "Utils.h"

double glucose;

#define TOTAL 100

#define SEUIL5 5*TOTAL/100
#define SEUIL1 1*TOTAL/100

void* capteur_glucose(void* args){
		
	int fd;
	fd = open(FIFO_STRING,O_WRONLY);
	if(fd < 0)
		Utils::debug("Open failed",TAG);
	
	while(1){
		double local_glucose;
		pthread_mutex_lock(&mutex_glucose);
		local_glucose = glucose;
		pthread_mutex_unlock(&mutex_glucose);
		
		if(local_glucose < SEUIL1){
			write(fd,"GLUCOSE A 1%",50);
		}else if(local_glucose < SEUIL5){
			write(fd,"GLUCOSE A 5%",50);
		}
		
	}
}