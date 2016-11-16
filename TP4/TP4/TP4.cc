#include <cstdlib>
#include <mqueue.h>
#include <iostream>
#include <sched.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/syspage.h>
#include <sys/neutrino.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include "def.h"
#include "patient.h"
#include "affichage.h"
#include "glucose.h"
#include "insuline.h"
#include "capteur.h"
#include "capteur_glucose.h"
#include "capteur_insuline.h"
#include "reset_glucose.h"
#include "reset_insuline.h"

using namespace std;

#define TAG "[TP4]"
#include "Utils.h"

mqd_t mq_glucose;
mqd_t mq_insuline;

pthread_mutex_t mutex_glycemie;
pthread_mutex_t mutex_glucose;
pthread_mutex_t mutex_insuline;

pthread_mutex_t mutex_mode_glucose;
pthread_mutex_t mutex_mode_insuline;

void cleanup(){
	
	//Semaphore
	sem_destroy(&sem_glucose);
	sem_destroy(&sem_insuline);	
	
	//FIFO 
	unlink(FIFO_STRING);
	close(fd_affichage);
	close(fd_glucose_capteur);
	close(fd_insuline_capteur);
	close(fd_glycemie_capteur);

	
	
	//Mutex
	pthread_mutex_destroy(&mutex_glycemie);
	pthread_mutex_destroy(&mutex_glucose);
	pthread_mutex_destroy(&mutex_insuline);
	pthread_mutex_destroy(&mutex_mode_glucose);
	pthread_mutex_destroy(&mutex_mode_insuline);
	
	//File de messages
	mq_close(mq_glucose);
	mq_unlink(MQ_GLUCOSE);
	mq_close(mq_insuline);
	mq_unlink(MQ_INSULINE);
}

void sigend(int sig){
	(void) sig;
}


void Q_init(void)
{
	pthread_t tid[9];
	pthread_attr_t attrib;
	struct sched_param mySchedParam;
	

	if(mkfifo(FIFO_STRING,0666))
		Utils::debug("Mkfifo failed",TAG);
	
	struct mq_attr attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = MQ_MAX_SIZE;
	attr.mq_curmsgs = 0;
	
	mq_glucose = mq_open(MQ_GLUCOSE, O_CREAT | O_RDWR, 0644,&attr);
	if(mq_glucose<0)
		cout << "mq open failed " << errno << endl;
	else
		cout << "mq open succ" << endl;
	mq_insuline = mq_open(MQ_INSULINE , O_CREAT | O_RDWR, 0644,&attr);

	pthread_mutex_init(&mutex_glycemie,NULL);
	pthread_mutex_init(&mutex_glucose,NULL);
	pthread_mutex_init(&mutex_insuline,NULL);
	
	pthread_mutex_init(&mutex_mode_glucose,NULL);
	pthread_mutex_init(&mutex_mode_glucose,NULL);
	
	setprio(0,20);
	pthread_attr_init(&attrib);
	pthread_attr_setinheritsched(&attrib,PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attrib,SCHED_FIFO);
	
	sigset_t set;
	sigfillset(&set);
	pthread_sigmask(SIG_BLOCK,&set,NULL);
	mySchedParam.sched_priority = 1;
	pthread_attr_setschedparam(&attrib,&mySchedParam);
	if(pthread_create(&tid[0],&attrib,affichage,NULL) < 0)
		cout << "erreur lors de la creation de la tache affichage" << endl;


	mySchedParam.sched_priority = 2;
	pthread_attr_setschedparam(&attrib,&mySchedParam);
	if(pthread_create(&tid[1],&attrib,patient,NULL) < 0)
		cout << "erreur lors de la creation de la tache patient" << endl;
	
	mySchedParam.sched_priority = 3;
	pthread_attr_setschedparam(&attrib,&mySchedParam);
	if(pthread_create(&tid[2],&attrib,glucose_handler,NULL) < 0)
		cout << "erreur lors de la creation de la tache glucose" << endl;
	
	
	mySchedParam.sched_priority = 4;
	pthread_attr_setschedparam(&attrib,&mySchedParam);
	if(pthread_create(&tid[3],&attrib,insuline_handler,NULL) < 0)
		cout << "erreur lors de la creation de la tache insuline" << endl;
		
	mySchedParam.sched_priority = 5;
	pthread_attr_setschedparam(&attrib,&mySchedParam);
	if(pthread_create(&tid[4],&attrib,capteur,NULL) < 0)
		cout << "erreur lors de la creation de la tache capteur" << endl;
		
	mySchedParam.sched_priority = 6;
	pthread_attr_setschedparam(&attrib,&mySchedParam);
	if(pthread_create(&tid[5],&attrib,capteur_glucose,NULL) < 0)
		cout << "erreur lors de la creation de la tache capteur glucose" << endl;
	
	mySchedParam.sched_priority = 7;
	pthread_attr_setschedparam(&attrib,&mySchedParam);
	if(pthread_create(&tid[6],&attrib,capteur_insuline,NULL) < 0)
		cout << "erreur lors de la creation de la tache capteur insuline" << endl;
		
	mySchedParam.sched_priority = 8;
	pthread_attr_setschedparam(&attrib,&mySchedParam);
	if(pthread_create(&tid[7],&attrib,reset_glucose,NULL) < 0)
		cout << "erreur lors de la creation de la tache reset glucose" << endl;
	
	mySchedParam.sched_priority = 9;
	pthread_attr_setschedparam(&attrib,&mySchedParam);
	if(pthread_create(&tid[8],&attrib,reset_insuline,NULL) < 0)
		cout << "erreur lors de la creation de la tache reset insuline" << endl;
		
	struct sigaction sa;
	memset(&sa,0,sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=0;
	sa.sa_handler = sigend;
	sigaction(SIGINT,&sa,NULL);
	sigaction(SIGTERM,&sa,NULL);
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	sigaddset(&set,SIGTERM);
	pthread_sigmask(SIG_UNBLOCK,&set,NULL);
	
	pause();
	pthread_cancel(tid[0]);
	pthread_cancel(tid[1]);
	pthread_cancel(tid[2]);
	pthread_cancel(tid[3]);
	pthread_cancel(tid[4]);
	pthread_cancel(tid[5]);
	pthread_cancel(tid[6]);
	pthread_cancel(tid[7]);
	pthread_cancel(tid[8]);
			
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	pthread_join(tid[2],NULL);
	pthread_join(tid[3],NULL);
	pthread_join(tid[4],NULL);
	pthread_join(tid[5],NULL);
	pthread_join(tid[6],NULL);
	pthread_join(tid[7],NULL);
	pthread_join(tid[8],NULL);
		
	cleanup();
	cout << "finish" << endl;
	return;
	
}

int main(int argc, char *argv[]) {
	
	//signal(SIGTERM,cleanup);
	Q_init();
	
	return EXIT_SUCCESS;
}
