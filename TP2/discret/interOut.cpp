#include "interOut.h"
#include "cosim.h"

void interOut::sol1_handler()
{
	WriteSignalToSimulink(sol1.read(), 0);
}

void interOut::sol2_handler()
{
	WriteSignalToSimulink(sol2.read(), 1);
}

void interOut::anticoagulant_handler()
{
	WriteSignalToSimulink(anticoagulant.read(), 2);
}

void interOut::antibiotic_handler()
{
	WriteSignalToSimulink(antibiotic.read(), 3);
}

void interOut::glucose_handler()
{
	WriteSignalToSimulink(glucose.read(), 4);
}


