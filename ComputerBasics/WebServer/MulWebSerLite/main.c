/* $begin main.c */
#include "general.h"

/************************
 *套接字地址的结构体类型
 ************************/

/*
 * struct sockaddr_in {
 *	uint16_t sin_family; //协议簇AF_INET
 *	uint16_t sin_port;   //16位端口号
 *	struct in_addr sin_addr; //32位IP地址
 *	unsigned char sin_zero[8]; //通用套接字结构地址结构体sockaddr所占大小
 * };
 *
 * struct sockaddr{
 *	uint16_t sa_family; //协议簇
 *	char sa_data[14];   //地址信息
 * };
 */

int main(int argc, const char *argv[])
{
    int listenfd, connfd, port, clientlen;
    struct sockaddr_in clientaddr;

	/* 检查命令行参数，并将第1个参数作为端口号port */
    if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(1);
    }
    port = atoi(argv[1]);

	/* 在SIGCHLD处理程序中回收操作系统分配给CGI子进程的资源 */
	/*
	if(Signal(SIGCHLD, sigchild_handler) == SIG_ERR)
	{
		unix_error("signal child handler error");
	}
	*/

    listenfd = Open_listenfd(port); //将输入port与服务器套接字地址建立联系，形成监听套接字

	/*无限服务器循环，不断地接收连接请求*/
    while (1) {
		clientlen = sizeof(clientaddr);
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);//使用Accept()函数等待客户端连接
		if(Fork() == 0){
		    Close(listenfd);
		    handle_http_trans(connfd);
          	Close(connfd);
		    exit(0);
		}
		Close(connfd);                                         
    }
}

/* $end main.c */
