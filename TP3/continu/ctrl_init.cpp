#define S_FUNCTION_NAME ctrl_init

#include "ttkernel.cpp"
#include <iostream>

#define SOL1 2
#define SOL2 1
#define ANTICOAGULANT 3
#define ANTIBIOTIC 4
#define GLUCOSE 5

class KernelData {
public:
	KernelData(): current_sol{0},time{1} {
		sols[0]=sols[1]=true;
	}
	bool sols[2];
	bool current_sol;
	double time;
};

double glycemiae_handler(int segment, void* data) {

	KernelData *d = (KernelData*)data;
	//std::cout << "test" << std::endl;
	/*if(!d->current_sol)
		ttAnalogOut(SOL1,1);
	else
		ttAnalogOut(SOL2,1);
	ttAnalogOut(ANTIBIOTIC,0);
	ttAnalogOut(ANTICOAGULANT,0);*/
	switch(segment){
		case 1:
		ttAnalogOut(GLUCOSE,0);
		return 0.1;
		default :
		return FINISHED;
	}
}

double sol1_5_handler(int segment, void* data) {

	KernelData *d = (KernelData*)data;
	return FINISHED;

}

double sol1_1_handler(int segment, void* data) {

	KernelData *d = (KernelData*)data;
	return d->time;

}

double sol2_5_handler(int segment, void* data) {

	KernelData *d = (KernelData*)data;
	return d->time;

}

double sol2_1_handler(int segment, void* data) {

	KernelData *d = (KernelData*)data;
	return d->time;

}

double antibiotic_handler(int segment, void* data) {

	KernelData *d = (KernelData*)data;
	return d->time;

}

double hypoglycemiae_handler(int segment, void* data) {

	KernelData *d = (KernelData*)data;
	//std::cout << "enter" << std::endl;
	/*ttAnalogOut(SOL1,0);
	ttAnalogOut(SOL2,0);
	ttAnalogOut(ANTIBIOTIC,0);
	ttAnalogOut(ANTICOAGULANT,0);*/
	switch(segment){
		case 1:
		ttAnalogOut(GLUCOSE,1);
		return 0.1;
		default :
		return FINISHED;
	}

}




void init() {
    // Allocate kernel data memory and store pointer
	KernelData *kernelData = new KernelData;
	ttSetUserData(kernelData);
  
	const char sol1_5 = 1;
	const char sol1_1 = 2;
	const char sol2_5 = 3;
	const char sol2_1 = 4;
	const char antibiotic = 5;
	const char hypoglycemiae = 6;
	const char glycemiae = 7;
	const char val = 8;
  
	ttInitKernel(prioFP);
	
	/*
	ttCreateHandler("sol1_5_handler",4,sol1_5_handler,kernelData);
	ttAttachTriggerHandler(sol1_5,"sol1_5_handler");
  
	ttCreateHandler("sol1_1_handler",2,sol1_1_handler,kernelData);
	ttAttachTriggerHandler(sol1_1,"sol1_1_handler");
  
	ttCreateHandler("sol2_5_handler",5,sol2_5_handler,kernelData);
	ttAttachTriggerHandler(sol2_5,"sol2_5_handler");
  
	ttCreateHandler("sol2_1_handler",3,sol2_1_handler,kernelData);
	ttAttachTriggerHandler(sol2_1,"sol2_1_handler");
  
	ttCreateHandler("antibiotic_handler",7,antibiotic_handler,kernelData);
	ttAttachTriggerHandler(antibiotic,"antibiotic_handler");
  */
	ttCreateHandler("hypoglycemiae_handler",1,hypoglycemiae_handler,kernelData);
	ttAttachTriggerHandler(hypoglycemiae,"hypoglycemiae_handler");
  
	ttCreateHandler("glycemiae_handler",2,glycemiae_handler,kernelData);
	ttAttachTriggerHandler(glycemiae,"glycemiae_handler");
  
}

void cleanup() {
	
	KernelData *kernelData = (KernelData*)ttGetUserData();
	delete kernelData;
}
