/*****************************************************************************
 
  main.cpp 
 
 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#include "systemc.h"

#include "conio.h"

#include "def.h"
#include "interIn.h"
#include "interOut.h"
//tous les #include 

int sc_main(int ac, char *av[])
{
  
  //signaux interin aussi l'horloge
  
  sc_clock clk1("clk1",1,SC_SEC);

 

   //signaux interout
  
 //signaux les autres modules

  

   //liens modules



//interfaces SystemC<->Simulink
  


SET_COSIM

 MIXED_SIGNAL = true;
 FS = true;
 Speriod_0 = 0.01;

  sc_start(9000, SC_SEC); 

  _getch();

 CLOSE_COSIM 
  return 0;
}

