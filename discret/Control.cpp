#include "Control.h"

void Control::antibiotic_handler()
{
	while (true){
		time += 1;
		if (time == seconds_in_day)
			time = 0;
		if (time == period - 120)
			anticoagulant.write(sc_bit(1));
		if (time == period)
			antibiotic.write(sc_bit(1));
		wait();
	}
}
