#include "capteur_glucose.h"
#include "def.h"
#include <stdlib.h>

#define TAG "[Capt gl]"
#include "Utils.h"

double glucose;
int fd_glucose_capteur;


#define SEUIL5 10
#define SEUIL1 5

void* capteur_glucose(void* args){
	fd_glucose_capteur = open(FIFO_STRING,O_WRONLY);
	
	CHECK(fd_glucose_capteur<0,"Open capteur glucose failed")
	
	pthread_mutex_lock(&mutex_glucose);
	glucose = TOTAL;
	pthread_mutex_unlock(&mutex_glucose);
	
	while(1){
		double local_glucose;
		
		pthread_mutex_lock(&mutex_glucose);
		local_glucose = glucose;
		if(DEBUG)
			std::cout << TAG << " ----------------------------- " << local_glucose<< std::endl;		
		pthread_mutex_unlock(&mutex_glucose);
		
		if(local_glucose < SEUIL1){
			write(fd_glucose_capteur,"GLUCOSE A 1%",sizeof("GLUCOSE A 1%"));
		}else if(local_glucose < SEUIL5){
			write(fd_glucose_capteur,"GLUCOSE A 5%",sizeof("GLUCOSE A 5%"));
		}
		sleep(5);
	}
}