#include "affichage.h"
#include "def.h"
#include <iostream.h>

int fd_affichage;

using namespace std;

void *affichage(void *args)
{
	char buf[FIFO_MAX_SIZE];
	fd_affichage = open(FIFO_STRING, O_RDONLY );
	while(true)
	{
		int ret = read(fd_affichage,buf,FIFO_MAX_SIZE);
		if(ret>=0)
			cout << buf  <<" " << ret<< endl;
	}
		
	return 0;
}