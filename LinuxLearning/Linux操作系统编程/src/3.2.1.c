#include <unistd.h>
#include <pthread.h> //pthread.h非LINUX默认库在编译是需要使用 -lpthread 命令行参数 例如gcc 1.c -o 1 -lpthread
#include <stdio.h>
#include <stdlib.h>

void *childthread(void)
{
	int i;
	for(i=0;i<10;i++)
	{
		printf("childthread message\n");
		sleep(1);
	}
}

int main(int argc,char const *argv[])
{
	pthread_t tid;
	printf("creating childthread\n");
	pthread_create(&tid,NULL,(void*)childthread,NULL);
	pthread_join(tid,NULL);
	printf("childthread exit\n");
	return 0;
}
