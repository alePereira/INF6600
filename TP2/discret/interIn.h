#include "systemc.h"
#include "def.h"

SC_MODULE(interIN) // 
{
	//port declaration

	//state event port declaration
	sc_out<sc_bit> sol1_5;
	sc_out<sc_bit> sol1_1;
	sc_out<sc_bit> sol2_5;
	sc_out<sc_bit> sol2_1;
	sc_out<sc_bit> stop_antibiotic;
	sc_out<sc_bit> hypoglycemiae;
	sc_out<sc_bit> glycemiae_reached;

	//process declaration

	void sol1_5_handler();
	void sol1_1_handler();
	void sol2_5_handler();
	void sol2_1_handler();
	void antibiotic_handler();
	void hypoglycemiae_handler();
	void glycemiae_handler();


	//process declaration for state event

	//void state_event_process_name();

	// module constructor
	SC_CTOR(interIN)
	{

		/*SC_THREAD(read);
		sensitive_pos << clock;
		dont_initialize();*/

		//state event declaration	
		et_mat0 = new sc_event;
		et_mat1 = new sc_event;
		et_mat2 = new sc_event;
		et_mat3 = new sc_event;
		et_mat4 = new sc_event;
		et_mat5 = new sc_event;
		et_mat6 = new sc_event;


		//state event process
		SC_METHOD(sol1_5_handler);
		sensitive(et_mat0);
		dont_initialize();

		SC_METHOD(sol1_1_handler);
		sensitive(et_mat1);
		dont_initialize();

		SC_METHOD(sol2_5_handler);
		sensitive(et_mat2);
		dont_initialize();

		SC_METHOD(sol2_1_handler);
		sensitive(et_mat3);
		dont_initialize();

		SC_METHOD(antibiotic_handler);
		sensitive(et_mat4);
		dont_initialize();

		SC_METHOD(hypoglycemiae_handler);
		sensitive(et_mat5);
		dont_initialize();

		SC_METHOD(glycemiae_handler);
		sensitive(et_mat6);
		dont_initialize();

	}
};