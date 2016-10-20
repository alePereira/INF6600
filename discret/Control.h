#include "systemc.h"

SC_MODULE(Control)
{
	sc_in<bool> clk;

	sc_out<sc_bit> anticoagulant;
	sc_out<sc_bit> antibiotic;

	int period;
	int time = -1;
	const int seconds_in_day = 60 * 60 * 24;

	void antibiotic_handler();

	SC_CTOR(Control)
	{
		SC_THREAD(antibiotic_handler);
		sensitive_pos << clk;
		dont_initialize();
	}
};
