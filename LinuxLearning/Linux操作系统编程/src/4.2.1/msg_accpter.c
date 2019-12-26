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
	long int msgtype = 0;
	int msgid = -1;
	msgid = msgget((key_t)1234, 0666|IPC_CREAT);
	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error : %d\n",errno);
		exit(EXIT_FAILURE);
	}
	while(running)
	{
		if(msgrcv(msgid,(void*)&data, 1024, msgtype, 0) == -1)
		{
			fprintf(stderr,"msgrcv failed with errno: %d\n", errno);
			eixt(EXIT_FAILURE);		
		}	
		printf("You wrote : %s\n", data.text);
		if(strncmp(data.text,"end",3) == 0)
			running = 0;
	}	
	if(msgctl(msgid, IPC_RMID,0) == -1)
	{
		fprintf(stderr,"msgctl(IPC_RMID) failed\n");
		eixt(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
