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
	printf("Memory attached at %X\n",(int)shm);
	shared = (struct BufferPool*)shm;
	//--------生产者写入共享内存---
	while(running)
	{
		index = 0;
		if(shared->Index[index] == 1)
		{
			sleep(1);
			index++;
		}else{
			printf("Enter some text:");
			fgets(buffer, 100, stdin);
			strncpy(shared->Buffer[index], buffer,100);
			shared->Index[index] = 1;
			if(strncmp(buffer, "end", 3) == 0)
				running = 0;
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
