#include "systemc.h"
#include <queue>

#define CFG "toto.cfg"

class Event{
public:
	int time;
	int id;
	int param;
	Event(int time, int id, int param) :time(time), id(id), param(param){}
	
};

class EventCmp{
public:
	bool operator() (const Event& lhs, const Event& rhs) const{
		return lhs.time > rhs.time;
	}
};

SC_MODULE(UserInterface)
{
	sc_out<sc_bit> stop;
	sc_in<bool> clk;
	sc_out<int> reset;
	sc_out<int> timer;
	int time;
	
	std::priority_queue<Event, std::vector<Event>, EventCmp> queue;

	void ui();
	bool first;

	void init(std::string filename);

	SC_CTOR(UserInterface)
	{
		first = true;
		time = -1 ;
		init(CFG);

		SC_THREAD(ui);
		sensitive_pos << clk;
		dont_initialize();
	}


};