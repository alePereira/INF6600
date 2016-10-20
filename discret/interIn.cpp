#include "interIn.h"
#include "cosim.h"

#include <iostream>
#include "Utils.h"

using namespace std;

#define debug(s) Utils::debug(s,"[interIN]");

//return_type_if_any
//module_name:: member_function_name() {
/*interIN:: member_function_name() {
	member_function_body
} */

//void module_name::process_name(){
/*void interIN::read(){
	sol1_5->write(ReadSignalFromSimulink(0));
//name_port ->write(ReadSignalFromSimulink(0)); //read from shared memory
name_port ->write(ReadSignalFromSimulink(0));
wait();
}*/

/*void  module_name:: state_event_process_name() {
	state_event_process_body
}*/





void interIN::sol1_5_handler(){
	sc_bit s;

	s = sol1_5.read();
	sol1_5.write(~s);
	debug("1_5")
}

void interIN::sol1_1_handler(){
	sc_bit s;

	s = sol1_1.read();
	sol1_1.write(~s);
	debug("1_1")
}

void interIN::sol2_5_handler(){
	sc_bit s;

	s = sol2_5.read();
	sol2_5.write(~s);
	debug("2_5")
}

void interIN::sol2_1_handler(){
	sc_bit s;

	s = sol2_1.read();
	sol2_1.write(~s);
	debug("2_1")
}

void interIN::antibiotic_handler(){
	sc_bit s;

	s = stop_antibiotic.read();
	stop_antibiotic.write(~s);
	debug("antibiotic")
}

void interIN::hypoglycemiae_handler(){
	sc_bit s;
	
	s = hypoglycemiae.read();
	hypoglycemiae.write(~s);
	debug("hypoglycemiae")
}

void interIN::glycemiae_handler(){
	sc_bit s;

	s = glycemiae_reached.read();
	glycemiae_reached.write(~s);
	debug("glycemiae")
}
