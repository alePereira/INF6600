#include "systemc.h"

SC_MODULE(Alarm)
{
	sc_in<sc_bit> sol1_5;
	sc_in<sc_bit> sol1_1;
	sc_in<sc_bit> sol2_5;
	sc_in<sc_bit> sol2_1;
	sc_in<sc_bit> hypoglycemiae;

	void sol1_5_handler();
	void sol1_1_handler();
	void sol2_5_handler();
	void sol2_1_handler();
	void hypoglycemiae_handler();

	SC_CTOR(Alarm)
	{
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

		SC_METHOD(hypoglycemiae_handler);
		sensitive(hypoglycemiae);
		dont_initialize();
	}
};
