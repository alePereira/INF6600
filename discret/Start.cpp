#include "Start.h"

#include "Utils.h"
#define debug(s) Utils::debug(s,"[Start]");

void Start::sol1_5_handler()
{
	debug("Solution 1 at 5%");
}

void Start::sol1_1_handler()
{
	debug("Solution 1 at 1%");
	sols[0] = false;
	if (!sols[1])
		stop.write(sc_bit(1));
	else{
		current_sol = 1;
		sol1.write(sc_bit(0));
		sol2.write(sc_bit(1));
	}
		
}

void Start::sol2_5_handler()
{
	debug("Solution 2 at 5%")
}

void Start::sol2_1_handler()
{
	debug("Solution 2 at 1%");
	sols[1] = false;
	if (!sols[0])
		stop.write(sc_bit(1));
	else{
		current_sol = 0;
		sol2.write(sc_bit(0));
		sol1.write(sc_bit(1));
	}
}

void Start::antibiotic_handler()
{
	antibiotic.write(sc_bit(0));
	debug("Antibiotic");
}

void Start::hypoglycemiae_handler()
{
	if (hypoglycemiae == '1'){
		sol1.write(sc_bit(0));
		sol2.write(sc_bit(0));
		antibiotic.write(sc_bit(0));
		anticoagulant.write(sc_bit(0));
		glucose.write(sc_bit(1));
		debug("Hypoglycemiae!")
	}
}

void Start::glycemiae_handler()
{
	if (!current_sol)
		sol1.write(sc_bit(1));
	else
		sol2.write(sc_bit(1));
	antibiotic.write(sc_bit(0));
	anticoagulant.write(sc_bit(0));
	glucose.write(sc_bit(0));
	debug("Normal glycemiae")
}

void Start::reset_handler()
{
	int param = reset.read();
	if (param != 0 && param != 1)
		return;
	debug("reset");
	sols[param] = true;
}


