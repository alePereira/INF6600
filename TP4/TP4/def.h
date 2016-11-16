#ifndef _DEF_H_
#define _DEF_H_

#include <mqueue.h>
#include <semaphore.h>
#include <pthread.h>


//Semaphore
extern sem_t sem_glucose;
extern sem_t sem_insuline;

//FIFO
#define FIFO_MAX_SIZE 1024
#define FIFO_STRING "/tmp/toto"
extern int fd_affichage;
extern int fd_glucose_capteur;
extern int fd_insuline_capteur;
extern int fd_glycemie_capteur;

//Variables globales
extern double glycemie;
extern double glucose;
extern double insuline;

//Mutex for global variables
extern pthread_mutex_t mutex_glycemie;
extern pthread_mutex_t mutex_glucose;
extern pthread_mutex_t mutex_insuline;

// File de messages
#define MQ_GLUCOSE "glucose"
#define MQ_INSULINE "insuline"
#define MQ_MAX_SIZE sizeof(double)
extern mqd_t mq_glucose;
extern mqd_t mq_insuline;

//Modes d'injection de glucose
#define MODE_HYPOGLYCEMIE 1
#define MODE_GLUCOSE 2
#define MODE_GLUCOSE_OFF 0
extern int mode_glucose;
extern pthread_mutex_t mutex_mode_glucose;

//Modes d'injection de insuline
#define MODE_INSULINE_ON 1
#define MODE_INSULINE_OFF 0
extern int mode_insuline;
extern pthread_mutex_t mutex_mode_insuline;

#endif //_DEF_H_
