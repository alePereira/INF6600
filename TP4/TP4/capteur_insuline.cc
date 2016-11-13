#include "capteur_insuline.h"
#include "def.h"
#include <iostream>

#define TAG "[Capt ins]"
#include "Utils.h"

double insuline;

#define TOTAL 100

#define SEUIL5 5*TOTAL/100
#define SEUIL1 1*TOTAL/100

void* capteur_insuline(void* args){
		
	int fd;
	fd = open(FIFO_STRING,O_WRONLY);
	if(fd < 0)
		Utils::debug("Open failed",TAG);
	
	while(1){
		double local_insuline;
		
		pthread_mutex_lock(&mutex_insuline);
		local_insuline = insuline;
		pthread_mutex_unlock(&mutex_insuline);
		
		if(local_insuline < SEUIL1){
			write(fd,"INSULINE A 1%",50);
		}else if(local_insuline < SEUIL5){
			write(fd,"INSULINE A 5%",50);
		}
		
	}
}