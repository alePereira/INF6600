#include "patient.h"
#include "def.h"
#include <iostream>
#include <semaphore.h>
#include <string.h>
#include <errno.h>

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
	glycemie = 62;
	pthread_mutex_unlock(&mutex_glycemie);
	while(true){
		double glucose;
		double insuline;
		int ret = mq_receive(mq_glucose,(char*)&glucose,sizeof(double),NULL);
		cout << "mq_gl " << ret  << " " << errno << " end"<<endl;
		Utils::debug("G received",TAG);
		mq_receive(mq_insuline,(char*)&insuline,sizeof(double),NULL);
		Utils::debug("I received",TAG);
		pthread_mutex_lock(&mutex_glycemie);
		glycemie += KG*glucose - KI*(insuline+0.1);
		cout << TAG << " vals HERE " << glucose << " " << insuline << endl;
		char buff[50];
		sprintf(buff,"Coucou %f",glycemie);
		write(fd,buff,sizeof(buff));
		pthread_mutex_unlock(&mutex_glycemie);
		
		sleep(1);
	}
	
	return 0; 
}