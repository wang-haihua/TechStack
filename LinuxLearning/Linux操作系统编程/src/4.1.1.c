#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//本程序实现减法操作，为了避免被减数为0的情况，使用条件变量让加法线程在减法线程之前执行

void *decrement_count(void *arg);
void *increment_count(void *arg);

pthread_mutex_t count_lock;
pthread_cond_t count_ready;
int count = 0;

int main(int argc, char const *argv[])
{
	pthread_t tid1, tid2;
	//初始化互斥量和条件变量
	pthread_mutex_init(&count_lock,NULL);
	pthread_cond_init(&count_ready,NULL);
	//创建减法线程decrement_count 和 加法线程 increment_count
	pthread_create(&tid1,NULL,decrement_count,NULL);
	sleep(2);
	pthread_create(&tid2,NULL,increment_count,NULL);
	//终止线程
	pthread_join(tid1,NULL);
	//printf("decrement_count quit\n");
	pthread_join(tid2,NULL);
	return 0;
}

void *decrement_count(void *arg)
{
	pthread_mutex_lock(&count_lock);
	printf("decrement_count is waiting\n");
	pthread_cond_wait(&count_ready,&count_lock);
	count = count - 1; //等待条件变量过程中，互斥量仍然可用
	printf("decrement_count: count = %d\n",count);
	pthread_mutex_unlock(&count_lock);
	printf("decrement_count quit\n");
	pthread_exit(NULL);
}

void *increment_count(void *arg)
{
	pthread_mutex_lock(&count_lock);
	printf("increment_count is running\n");
	count = count + 1;
	pthread_cond_signal(&count_ready); // 触发条件变量
	printf("increment_count: count = %d\n",count);
	pthread_mutex_unlock(&count_lock);
	printf("increment_count quit\n");
	pthread_exit(NULL);
}
