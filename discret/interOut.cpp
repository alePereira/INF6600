#include "interOut.h"
#include "cosim.h"

void interOut :: nom_process1()
{
	
	//WriteSignalToSimulink (nom_module1.read(),0);
	
	//WriteSignalToSimulink (nom_module2.read(),1);

	WriteSignalToSimulink (cosim_in_g.read(),0);

}