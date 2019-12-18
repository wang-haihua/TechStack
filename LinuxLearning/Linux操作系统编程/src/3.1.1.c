#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
	printf("real uid: %d,real gid: %d \n",getuid(),getgid());
	printf("effective uid: %d, effective gid: %d\n",geteuid(),getegid());
	exit(0);
}
