#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

//缓存池结构体
struct BufferPool
{
	char Buffer[5][100];
	int Index[5];
};

int main(int argc, char const *argv[])
{
	int running = -1;
	//---------创建共享内存-------
	void *shm = NULL;
	struct BufferPool *shared;
	int shmid;
	int index;
	shmid = shmget((key_t)1234, sizeof(struct BufferPool), 0666|IPC_CREAT);
	if(shmid == -1)
	{
		exit(EXIT_FAILURE);
	}
	//----------------------------
	shm = shmat(shmid, 0, 0); //链接共享内存到进程的地址空间
	if(shm == (void*)-1)
	{
		exit(EXIT_FAILURE);
	}
	shared = (struct BufferPool*)shm;
	//--------消费者读取共享内存---
	while(running)
	{
		index = 0;
		if(shared->Index[index] == 1)
		{
			printf("consume buffer : %s",shared->Buffer[index]);
			shared->Index[index] = 0;
			sleep(rand() % 3);
			if(strncmp(shared->Buffer[index], "end",3) == 0)
				running = 0;
		}else{
			sleep(1);
			index++;
		}
	}
	//-----------------------------
	//断开进程地址空间与共享内存的链接
	if(shmdt(shm) == -1)
		exit(EXIT_FAILURE);
	if(shmctl(shmid, IPC_RMID, 0) == -1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
