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
#include "Start.h"
#include "Alarm.h"
#include "Stop.h"
#include "UserInterface.h"
#include "Control.h"

//tous les #include 

int sc_main(int ac, char *av[])
{
  
  //signaux interin aussi l'horloge
  
  sc_clock clk1("clk1",1,SC_SEC);

 

   //signaux interout
  sc_signal<sc_bit> sol1_5;
  sc_signal<sc_bit> sol1_1;
  sc_signal<sc_bit> sol2_5;
  sc_signal<sc_bit> sol2_1;
  sc_signal<sc_bit> stop_antibiotic;
  sc_signal<sc_bit> hypoglycemiae;
  sc_signal<sc_bit> glycemiae_reached;

  sc_signal<sc_bit> sol1;
  sc_signal<sc_bit> sol2;
  sc_signal<sc_bit> antibiotic;
  sc_signal<sc_bit> anticoagulant;
  sc_signal<sc_bit> glucose;

  sc_signal<sc_bit> stop;

  sc_signal<int> reset;
  sc_signal<int> timer;

 //signaux les autres modules
  int period = 0;
  cout << "Choose time interval for antibiotic" << endl;
  cout << "1. 4h" << endl;
  cout << "2. 6h" << endl;
  cout << "3. 8h" << endl;
  cout << "4. 12h" << endl;

  while (period < 1 || period>4){
	  cin >> period;
  }

  switch (period){
  case 1:
	  period = 4 * 60 * 60;
	  break;
  case 2:
	  period = 6 * 60 * 60;
	  break;
  case 3:
	  period = 8 * 60 * 60;
	  break;
  case 4:
	  period = 12 * 60 * 60;
	  break;
  }

   //liens modules

  interIN in("interIN");
  interOut out("interOut");
  Start start("start");
  Stop stopMod("stop");
  Alarm alarm("alarm");
  UserInterface ui("userinterface");
  Control control("control");

  control.period = period;
  
  ui.clk(clk1);

  start.reset(reset);
  ui.reset(reset);

  ui.timer(timer);

  in.sol1_5(sol1_5);
  in.sol1_1(sol1_1);
  in.sol2_5(sol2_5);
  in.sol2_1(sol2_1);
  in.stop_antibiotic(stop_antibiotic);
  in.hypoglycemiae(hypoglycemiae);
  in.glycemiae_reached(glycemiae_reached);

  start.sol1_5(sol1_5);
  start.sol1_1(sol1_1);
  start.sol2_5(sol2_5);
  start.sol2_1(sol2_1);
  start.stop_antibiotic(stop_antibiotic);
  start.hypoglycemiae(hypoglycemiae);
  start.glycemiae_reached(glycemiae_reached);

  alarm.sol1_5(sol1_5);
  alarm.sol1_1(sol1_1);
  alarm.sol2_5(sol2_5);
  alarm.sol2_1(sol2_1);
  alarm.hypoglycemiae(hypoglycemiae);

  start.stop(stop);
  ui.stop(stop);
  stopMod.stop(stop);
  

  start.sol1(sol1);
  start.sol2(sol2);
  start.antibiotic(antibiotic);
  start.anticoagulant(anticoagulant);
  start.glucose(glucose);

  out.sol1(sol1);
  out.sol2(sol2);
  out.antibiotic(antibiotic);
  out.anticoagulant(anticoagulant);
  out.glucose(glucose);

  control.clk(clk1);
  control.antibiotic(antibiotic);
  control.anticoagulant(anticoagulant);

  sol1.write(sc_bit(1));
  reset.write(-1);

//interfaces SystemC<->Simulink
  


SET_COSIM

 MIXED_SIGNAL = true;
 FS = true;
 Speriod_0 = 0.01;

  //sc_start(9000, SC_SEC); 
 sc_start();
  _getch();

 CLOSE_COSIM 
  return 0;
}

