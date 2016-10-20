#include "Stop.h"

void Stop::stop_handler()
{
	if (stop=='1')
		sc_stop();
}