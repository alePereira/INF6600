#include "affichage.h"
#include "def.h"
#include <iostream.h>

int fd_affichage;

using namespace std;

void *affichage(void *args)
{
	char buf[FIFO_MAX_SIZE];
	fd_affichage = open(FIFO_STRING, O_RDONLY );
	CHECK(fd_affichage<0,"Open affichage failed")
	
	while(true)
	{
		int ret = read(fd_affichage,buf,FIFO_MAX_SIZE);
		if(ret>=0)
			cout <<  buf << endl;
	}
		
	return 0;
}