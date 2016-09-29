#include "interIn.h"
#include "cosim.h"


//return_type_if_any
//module_name:: member_function_name() {
interIN:: member_function_name() {
	member_function_body
} 

//void module_name::process_name(){
void interIn::cosim_out_syn(){
	.
//name_port ->write(ReadSignalFromSimulink(0)); //read from shared memory
name_port ->write(ReadSignalFromSimulink(0));
wait();

}

void  module_name:: state_event_process_name() {
	state_event_process_body
}


//Si le type choisi pour « state event » est « bit » la syntaxe est:

// déclaration des ports – header file

sc_out<sc_bit> name_port_state_event; 


//implementation du processus - .cpp file

void module_name::process_name(){

sc_bit s;

	s = name_port_state_event.read();
	name_port_state_event.write(~s);
}
