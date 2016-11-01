#define S_FUNCTION_NAME simple_init
#include "ttkernel.cpp"
#include <iostream>

//in ports numbers
#define SOL1 1
#define SOL2 2
#define ANTICOAGULANT 3
#define ANTIBIOTIC 4
#define GLUCOSE 5

//out ports numbers
#define SOL1_5 1
#define SOL1_1 2
#define SOL2_5 3
#define SOL2_1 4
#define OUT_ANTIBIOTIC 5
#define HYPOGLYCEMIAE 6
#define GLYCEMIAE 7
#define DIFF_REF 8

// Data structure used for the task data
struct TaskData {
  double exectime;
  bool currentSol;
  bool sols[2];
};

//---------------------------CONTROLLER "MODULES"---------------------
void stop(){
	//ttAbortSimulation();
	std::cout << "stop simulation" << std::endl;
	}

void alarm(char* message){
	std::cout << "ALARM : " << message << std::endl;
}

void reset(int solReset, bool* sols){
	if(solReset != 0 && solReset != 1)
		return;
	sols[solReset] = true;
}

//-------------------------------HANDLERS-----------------------------

//handler for sol1 5% level
double sol1_5_handler(int segment, void* data){
	TaskData *d = (TaskData*)data;
	switch (segment){
	case 1:
		alarm("Solution 1 at 5%");
		return d->exectime;
	default:
		return FINISHED;
	}
}

//handler for sol1 1% level
double sol1_1_handler(int segment, void* data){
	TaskData *d = (TaskData*)data;
	switch (segment){
	case 1:
		alarm("Solution 1 at 1%");
		d->sols[0] = false;
		if(!d->sols[1])
			stop();
		else{
			d->currentSol = 1;
			ttAnalogOut(SOL1,0);
			ttAnalogOut(SOL2,1);
		}
		return d->exectime;
	default:
		return FINISHED;
	}
}

//handler for sol2 5% level
double sol2_5_handler(int segment, void* data){
	TaskData *d = (TaskData*)data;
	switch (segment){
	case 1:
		alarm("Solution 2 at 5%");
		return d->exectime;
	default:
		return FINISHED;
	}
}

//handler for sol2 1% level
double sol2_1_handler(int segment, void* data){
	TaskData *d = (TaskData*)data;
	switch (segment){
	case 1:
		alarm("Solution 2 at 1%");
		d->sols[1] = false;
		if(!d->sols[0])
			stop();
		else{
			d->currentSol = 0;
			ttAnalogOut(SOL1,1);
			ttAnalogOut(SOL2,0);
		}
		return d->exectime;
	default:
		return FINISHED;
	}
}

//handler for antibiotic event
double antibiotic_handler(int segment, void* data){
	TaskData *d = (TaskData*)data;
	switch (segment){
	case 1:
		return d->exectime;
	default:
		ttAnalogOut(ANTIBIOTIC,1);
		return FINISHED;
	}
}

//handler for glycemiae level reached
double glycemiae_handler(int segment, void* data){
	TaskData *d = (TaskData*)data;
	switch (segment){
	case 1:
		std::cout << "Glycemie normale" << std::endl;
		return d->exectime;
	default:
		if(!d->currentSol)
			ttAnalogOut(SOL1,1);
		else
			ttAnalogOut(SOL2,1);
		ttAnalogOut(ANTIBIOTIC,0);
		ttAnalogOut(ANTICOAGULANT,0);
		ttAnalogOut(GLUCOSE,0);
		return FINISHED;
	}
}
//handler for hypoglycemiae
double hypoglycemiae_handler(int segment, void* data){
	TaskData *d = (TaskData*)data;
	switch (segment){
	case 1:
		alarm("Hypoglycemiae !");
		return d->exectime;
	default:
		ttAnalogOut(SOL1,0);
		ttAnalogOut(SOL2,0);
		ttAnalogOut(ANTIBIOTIC,0);
		ttAnalogOut(ANTICOAGULANT,0);
		ttAnalogOut(GLUCOSE,1);
		return FINISHED;
	}
}


//----------------------------PERIODIC TASKS--------------------------


double anticoag_injection(int segment, void* data) {

  TaskData *d = (TaskData*)data;  
  switch (segment) {
  case 1:
	ttAnalogOut(ANTICOAGULANT, 1);
	std::cout << "injection anticoag" << std::endl;
    return d->exectime;
  default:
    ttAnalogOut(ANTICOAGULANT, 0);
    return FINISHED;
  }
}

//idle task
double idle(int segment, void* data) {

  TaskData *d = (TaskData*)data;
  double y;
  
  switch (segment) {
  case 1:
    return d->exectime;
  default:
    return FINISHED;
  }
}


//--------------------------------KERNEL------------------------------

// Kernel init function    
void init() {
	
  // Allocate memory for the task and store pointer in UserData
  TaskData *data = new TaskData;
  ttSetUserData(data);
  //initialisation des solutions actives
  data->currentSol = 0;
  data->sols[0] = true;
  data->sols[1] = true;
  data->exectime = 0.1;

  
  ttInitKernel(prioFP);

  //timer creation
  ttCreateHandler("idle_handler", 30, idle, data);
  ttCreatePeriodicTimer("timer", 0.5, "idle_handler"); 
  
  //perdiodic injection for anticoagulant
  ttCreatePeriodicTask("anticoag_injection", 30.0, 40.0, anticoag_injection, data);
  
  
  //handlers init
  ttCreateHandler("glycemiae_handler", 2, glycemiae_handler, data);
  ttAttachTriggerHandler(GLYCEMIAE, "glycemiae_handler");
  
  ttCreateHandler("hypoglycemiae_handler", 1, hypoglycemiae_handler, data);
  ttAttachTriggerHandler(HYPOGLYCEMIAE, "hypoglycemiae_handler");
  
  ttCreateHandler("sol1_5_handler", 10, sol1_5_handler, data);
  ttAttachTriggerHandler(SOL1_5, "sol1_5_handler");
  
  ttCreateHandler("sol2_5_handler", 11, sol2_5_handler, data);
  ttAttachTriggerHandler(SOL2_5, "sol2_5_handler");
  
  
  // ca bug ici !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  
  /*ttCreateHandler("sol1_1_handler", 3, sol1_1_handler, data);
  ttAttachTriggerHandler(SOL1_5, "sol1_5_handler");
  
  ttCreateHandler("sol2_1_handler", 4, sol2_1_handler, data);
  ttAttachTriggerHandler(SOL1_5, "sol2_1_handler");*/
}

// Kernel cleanup function
void cleanup() {

  // Free the allocated memory
  TaskData *d = (TaskData *)ttGetUserData();
  delete d;
}






























