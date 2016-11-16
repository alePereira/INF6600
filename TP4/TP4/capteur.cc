#include "capteur.h"
#include <iostream>

#define TAG "[Cap]"
#include "Utils.h"

#define HYPOGLYCEMIE 60
#define NORMAL_GLYCEMIE 120

void* capteur(void* args){
	double local_glycemie;
	double local_glucose;
	double local_insuline;
	
		
	int fd;
	fd = open(FIFO_STRING,O_WRONLY);
	if(fd < 0)
		Utils::debug("Open failed",TAG);
		
	while(1){
		pthread_mutex_lock(&mutex_glycemie);
		local_glycemie= glycemie;
		pthread_mutex_unlock(&mutex_glycemie);
		if(local_glycemie<HYPOGLYCEMIE){
			write(fd,"Hypoglycémie",50);
			pthread_mutex_lock(&mutex_mode_glucose);
			mode_glucose= MODE_HYPOGLYCEMIE;
			std::cout << TAG << " hypo " <<mode_glucose <<std::endl;
			pthread_mutex_unlock(&mutex_mode_glucose);
		}else if(local_glycemie < NORMAL_GLYCEMIE){
			pthread_mutex_lock(&mutex_mode_glucose);
			mode_glucose= MODE_GLUCOSE;
			std::cout << TAG << " Normal glycemie " <<mode_glucose <<std::endl;
			pthread_mutex_unlock(&mutex_mode_glucose);
		}else{
			pthread_mutex_lock(&mutex_mode_glucose);
			mode_glucose= MODE_GLUCOSE_OFF;
			pthread_mutex_unlock(&mutex_mode_glucose);
		}
		
		if(local_glycemie < NORMAL_GLYCEMIE){
			pthread_mutex_lock(&mutex_mode_insuline);
			mode_insuline= MODE_INSULINE_OFF;
			pthread_mutex_unlock(&mutex_mode_insuline);
		}else{
			pthread_mutex_lock(&mutex_mode_insuline);
			mode_insuline= MODE_INSULINE_ON;
			pthread_mutex_unlock(&mutex_mode_insuline);
		}
		std::cout << TAG << " " <<mode_glucose <<std::endl;
		sleep(1);
	}
}