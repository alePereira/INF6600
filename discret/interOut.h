#include "systemc.h"

SC_MODULE(interOut) 
{
	//portes
	sc_in<double>name_port1
	
		
		void nom_process1();


	
	SC_CTOR(interOut) 
	{
		SC_METHOD(nom_process);

		
		dont_initialize();
	}
};