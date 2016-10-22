#include "systemc.h"

SC_MODULE(interOut) 
{
	//portes
	sc_in<sc_bit> sol1;
	sc_in<sc_bit> sol2;
	sc_in<sc_bit> antibiotic;
	sc_in<sc_bit> anticoagulant;
	sc_in<sc_bit> glucose;

	void sol1_handler();
	void sol2_handler();
	void antibiotic_handler();
	void anticoagulant_handler();
	void glucose_handler();

	SC_CTOR(interOut) 
	{
		SC_METHOD(sol1_handler);
		sensitive << sol1;
		dont_initialize();

		SC_METHOD(sol2_handler);
		sensitive << sol2;
		dont_initialize();

		SC_METHOD(antibiotic_handler);
		sensitive << antibiotic;
		dont_initialize();

		SC_METHOD(anticoagulant_handler);
		sensitive << anticoagulant;
		dont_initialize();

		SC_METHOD(glucose_handler);
		sensitive << glucose;
		dont_initialize();
	}

};