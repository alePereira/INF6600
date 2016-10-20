#include "systemc.h"

SC_MODULE(Start)
{
	sc_in<sc_bit> sol1_5;
	sc_in<sc_bit> sol1_1;
	sc_in<sc_bit> sol2_5;
	sc_in<sc_bit> sol2_1;
	sc_in<sc_bit> stop_antibiotic;
	sc_in<sc_bit> hypoglycemiae;
	sc_in<sc_bit> glycemiae_reached;

	sc_out<sc_bit> sol1;
	sc_out<sc_bit> sol2;
	sc_out<sc_bit> antibiotic;
	sc_out<sc_bit> anticoagulant;
	sc_out<sc_bit> glucose;

	sc_out<sc_bit> stop;

	sc_in<int> reset;

	bool sols[2];
	bool current_sol;

	void sol1_5_handler();
	void sol1_1_handler();
	void sol2_5_handler();
	void sol2_1_handler();
	void antibiotic_handler();
	void hypoglycemiae_handler();
	void glycemiae_handler();
	void reset_handler();
	


	SC_CTOR(Start)
	{
		sols[0] = true;
		sols[1] = true;
		current_sol = 0;
		SC_METHOD(sol1_5_handler);
		sensitive(sol1_5);
		dont_initialize();

		SC_METHOD(sol1_1_handler);
		sensitive(sol1_1);
		dont_initialize();

		SC_METHOD(sol2_5_handler);
		sensitive(sol2_5);
		dont_initialize();

		SC_METHOD(sol2_1_handler);
		sensitive(sol2_1);
		dont_initialize();

		SC_METHOD(antibiotic_handler);
		sensitive(antibiotic);
		dont_initialize();

		SC_METHOD(hypoglycemiae_handler);
		sensitive << hypoglycemiae;
		dont_initialize();

		SC_METHOD(glycemiae_handler);
		sensitive(glycemiae_reached);
		dont_initialize();

		SC_METHOD(reset_handler);
		sensitive(reset);
		dont_initialize();
	}


};

