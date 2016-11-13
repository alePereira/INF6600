#include "patient.h"
#include "def.h"
#include <iostream>
#include <semaphore.h>
#include <string.h>

#define TAG "[Patient]"
#include "Utils.h"
using namespace std;

#define KG 1.6
#define KI 1.36

double glycemie;

//tache modelisant le patient
void *patient(void *arg){
	
	int fd;
	fd = open(FIFO_STRING,O_WRONLY);
	if(fd < 0)
		Utils::debug("Open failed",TAG);
	
	//write(fd,"Hi",sizeof("Hi"));
	
	pthread_mutex_lock(&mutex_glycemie);
	glycemie = 200;
	pthread_mutex_unlock(&mutex_glycemie);
	while(true){
		double glucose;
		double insuline;
		mq_receive(mq_glucose,(char*)&glucose,sizeof(double),NULL);
		Utils::debug("G received",TAG);
		mq_receive(mq_insuline,(char*)&insuline,sizeof(double),NULL);
		Utils::debug("I received",TAG);
		pthread_mutex_lock(&mutex_glycemie);
		glycemie += KG*glucose - KI*(insuline+0.1);
		char buff[50];
		sprintf(buff,"Coucou %f",glycemie);
		//write(fd,buff,50);
		pthread_mutex_unlock(&mutex_glycemie);
		
		sleep(5);
	}
	
	return 0; 
}