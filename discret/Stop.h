#include "systemc.h"

SC_MODULE(Stop)
{
	sc_in<sc_bit> stop;
	
	void stop_handler();

	SC_CTOR(Stop)
	{
		SC_METHOD(stop_handler);
		sensitive << stop;
		dont_initialize();
	}
};