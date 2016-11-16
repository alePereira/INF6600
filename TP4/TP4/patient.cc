#include "patient.h"
#include "def.h"
#include <iostream>
#include <semaphore.h>
#include <string.h>
#include <errno.h>

#define TAG "[Patient]"
#include "Utils.h"
using namespace std;


int fd_patient;

#define KG 1.6
#define KI 1.36

double glycemie;

//tache modelisant le patient
void *patient(void *arg){
	fd_patient = open(FIFO_STRING,O_WRONLY);
	CHECK(fd_patient<0,"Open patient failed")
	
	pthread_mutex_lock(&mutex_glycemie);
	glycemie = 62;
	pthread_mutex_unlock(&mutex_glycemie);
	
	while(true){
		double glucose;
		double insuline;
		
		mq_receive(mq_glucose,(char*)&glucose,sizeof(double),NULL);
		Utils::debug("G received",TAG);
		mq_receive(mq_insuline,(char*)&insuline,sizeof(double),NULL);
		Utils::debug("I received",TAG);
		
		pthread_mutex_lock(&mutex_glycemie);
		glycemie += KG*glucose - KI*(insuline+0.5);
		char buff[50];
		sprintf(buff,"Glycemie patient %f",glycemie);
		write(fd_patient,buff,sizeof(buff));
		pthread_mutex_unlock(&mutex_glycemie);
		
	}
	
}