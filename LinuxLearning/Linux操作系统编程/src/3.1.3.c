#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	printf("entering main process\n");
	if(fork()==0)
	{
		execl("/bin/ls","ls","-l",NULL);
		printf("exiting main process\n");
	}
	return 0;
}
