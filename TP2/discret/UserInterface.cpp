#include "UserInterface.h"
#include <string>
#include <sstream>

#include "Utils.h"
#define debug(s) Utils::debug(s,"[UI]");
using namespace std;


void UserInterface::init(string filename)
{
	string buffer;
	ifstream infile;
	infile.open(filename);
	while (!infile.eof()){
		getline(infile, buffer);
		int time;
		stringstream stream(buffer);
		stream >> time;
		if (time < 0)
			continue;
		int id;
		stream >> id;
		if (id < 0 || id>2)
			continue;
		int param;
		stream >> param;
		if (id == 0 && (param != 0 && param != 1))
			continue;
		queue.push({ time, id, param });
	}

	infile.close();
}

void UserInterface::ui()
{
	while (true){
		time += 1;
		if (!queue.empty()){
			Event top = queue.top();
			while (top.time <= time){
				if (top.id == 0){
					debug("reset");
					reset.write(top.param);
				}else if (top.id == 1)
					timer.write(top.param);
				else
					stop.write(sc_bit(1));
				queue.pop();
				top = queue.top();
			}
		}
		wait();
	}
}
