#include "capteur_insuline.h"
#include "def.h"
#include <iostream>

#define TAG "[Capt ins]"
#include "Utils.h"

double insuline;
int fd_insuline_capteur;


#define SEUIL5 10
#define SEUIL1 5

void* capteur_insuline(void* args){
	fd_insuline_capteur = open(FIFO_STRING,O_WRONLY);
	CHECK(fd_insuline_capteur<0,"Open capteur insuline failed")
		
	pthread_mutex_lock(&mutex_insuline);
	insuline = TOTAL;
	pthread_mutex_unlock(&mutex_insuline);
	
	while(1){
		double local_insuline;
		
		pthread_mutex_lock(&mutex_insuline);
		local_insuline = insuline;
		if(DEBUG)
			std::cout << TAG << " ----------------------------- " << local_insuline<< std::endl;	
		pthread_mutex_unlock(&mutex_insuline);
		
		if(local_insuline < SEUIL1){
			write(fd_insuline_capteur,"INSULINE A 1%",sizeof("INSULINE A 1%"));
		}else if(local_insuline < SEUIL5){
			write(fd_insuline_capteur,"INSULINE A 5%",sizeof("INSULINE A 5%"));
		}
		sleep(5);
	}
}