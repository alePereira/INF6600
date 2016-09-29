#include "systemc.h"
#include "def.h"

SC_MODULE (interIN ) // 
{
	//port declaration
	sc_out<double>name_port
		.
		.
	//state event port declaration

	//sc_out<event_data_type> name_port_state_event; 
		.
		.
		.
	//process declaration

//void process_name();
		.
		.

	//process declaration for state event
	
//void state_event_process_name();
		.
		.
		.

	// module constructor

	SC_CTOR(interIN) 
	{
		
SC_THREAD(process_name);
		sensitive<<……;
		dont_initialize();			
	
//state event declaration	
	    	et_mat0 = new sc_event; 
	
//state event process	

	SC_METHOD(state_event_process_name);
	sensitive(et_mat0);
	dont_initialize();
	}