#include "Alarm.h"

void Alarm::sol1_5_handler()
{
	cout << "Alarm : Solution 1 at 5%" << endl;
}

void Alarm::sol1_1_handler()
{
	cout << "Alarm : Solution 1 at 1%" << endl;
}

void Alarm::sol2_5_handler()
{
	cout << "Alarm : Solution 2 at 5%" << endl;
}

void Alarm::sol2_1_handler()
{
	cout << "Alarm : Solution 2 at 1%" << endl;
}

void Alarm::hypoglycemiae_handler()
{
	if (hypoglycemiae == '1')
		cout << "Alarm : Hypoglycemiae!" << endl;
}

