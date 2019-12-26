#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_st
{
	long int msg_type;
	char text[1024];
};

int main(int argc, char const *argv[])
{
	int running = 1;

	//创建消息队列对象
	struct msg_st data;
	char buffer[1024];
	int msgid = -1;
	msgid = msgget((key_t)1234, 0666|IPC_CREAT);
	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error : %d\n",errno);
		exit(EXIT_FAILURE);
	}
	while(running)
	{
		printf("Enter some text: ");
		fgets(buffer, 1024, stdin);
		data.msg_type = 1;
		strcpy(data.text, buffer);
		if(msgsnd(msgid,(void*)&data,1024,0) == -1 )
		{
			fprintf(stderr,"msgsnd failed\n");
			exit(EXIT_FAILURE);
		}
		if(strncmp(buffer,"end",3) == 0)
			running = 0;
		sleep(1);
	}
	exit(EXIT_SUCCESS);
}
