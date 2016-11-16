#include "capteur.h"
#include <iostream>

#define TAG "[Cap]"
#include "Utils.h"

int fd_glycemie_capteur;

#define HYPOGLYCEMIE 60
#define NORMAL_GLYCEMIE 120

void* capteur(void* args){
	double local_glycemie;
	
	fd_glycemie_capteur = open(FIFO_STRING,O_WRONLY);
	CHECK(fd_glycemie_capteur<0,"Open capteur failed")
		
	while(1){
		pthread_mutex_lock(&mutex_glycemie);
		local_glycemie= glycemie;
		pthread_mutex_unlock(&mutex_glycemie);
		if(local_glycemie<HYPOGLYCEMIE){
			write(fd_glycemie_capteur,"Hypoglycémie",50);
			pthread_mutex_lock(&mutex_mode_glucose);
			mode_glucose= MODE_HYPOGLYCEMIE;
			pthread_mutex_unlock(&mutex_mode_glucose);
		}else if(local_glycemie < NORMAL_GLYCEMIE){
			pthread_mutex_lock(&mutex_mode_glucose);
			mode_glucose= MODE_GLUCOSE;
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

		sleep(5);
	}
}