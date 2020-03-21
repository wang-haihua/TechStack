/* $begin concurrent.c */
#include "general.h"

/*
 * init_pool()函数
 *
 * Usage:
 * 	初始化客户端池pool
 *
 * Return:
 *
 */
void init_pool(int listenfd, pool *pl)
{
	/* 初始化客户端可连接槽位 用-1表示可用 */
	int i;
	pl -> maxi = -1;
	for(i = 0; i < FD_SETSIZE; i++)
	{
		pl->clientfd[i] = -1;
	}

	/* 监听描述符listenfd作为select读集合中唯一描述符 */
	pl->maxfd = listenfd;
	FD_ZERO(&pl->read_set);
	FD_SET(listenfd, &pl->read_set);
}

/*
 * add_client()函数
 *
 * Usage:
 *	添加一个新的客户端到活动客户端池中
 *
 * Return:
 *
 */
void add_client(int connfd, pool *pl)
{
	int i;
	pl->nready--;
	/* 寻找可用的活动客户端槽位 */
	for(i = 0; i < FD_SETSIZE; i++)
	{
		if(pl->clientfd[i] < 0){
			/* 添加一个已经建立连接的套接字描述符到活动客户端池中 */
			pl->clientfd[i] = connfd;
			Rio_readinitb(&pl->clientrio[i], connfd);
			FD_SET(connfd, &pl->read_set);

			/* 修改栈顶的描述符指向 */
			if(connfd > pl->maxfd){
				pl->maxfd = connfd;
			}
			if(i > pl->maxi){
				pl->maxi = i;
			}
			break;
		}
	}
	
	/* 找不到空槽位 */
	if(i == FD_SETSIZE){
		app_error("add_client error: Too many clients");
	}
}


/*
 * check_clients()函数
 *
 * Usage:
 * 	回送来自每个准备好的已连接描述符的一个文本行,
 * 	如果检测到连接结束关闭连接并清除池中的对应描述符
 *
 * Return:
 *
 */
void check_clients(pool *pl)
{
	int i, connfd, n;
	char buf[MAXLINE];
	rio_t rio;

	for(i = 0; (i <= pl->maxi) && (pl->nready > 0); i++){
		connfd = pl->clientfd[i];
		rio = pl->clientrio[i];

		/* 描述符读就绪，就开始回送文本行 */
		if((connfd > 0) && (FD_ISSET(connfd, &pl->ready_set))){
			pl->nready--;
			/* 成功的从描述符读取了一个文本行，并将其回送给客户端 */
			if((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0){
				printf("Server received %d bytes on fd %d\n", n, connfd);
				Rio_writen(connfd, buf, n);
				handle_http_trans(connfd);
			}else{
			/* 客户端关闭了连接，服务器也关闭连接并从pool中清除该描述符 */
				Close(connfd);
				FD_CLR(connfd, &pl->read_set);
				pl->clientfd[i] = -1;
			}
		}
	}
}

/* $end concurrent.c */
