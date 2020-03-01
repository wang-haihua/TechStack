/* $begin CS_helper_funcs.c */

#include "head.h"

/************************
 * 套接字接口的辅助函数
 ************************/

/*
* 
* open_clientfd()函数
*
* Usage:
*   建立与服务器的连接，该服务器运行在主机hostname上，并在端口好port上监听连接请求
*
* Return:
*   0-调用成功返回客户端描述符clientfd
*   1- Unix I/O出错 返回-1
*   2- DNS域名解析出错 返回-2
*
*/
int open_clientfd(char *hostname, int port) 
{
    int clientfd;
    struct hostent *hp;
    struct sockaddr_in serveraddr;

    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	return -1; 


    if ((hp = gethostbyname(hostname)) == NULL)
	return -2; 
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)hp->h_addr_list[0], 
	  (char *)&serveraddr.sin_addr.s_addr, hp->h_length);
    serveraddr.sin_port = htons(port);

    if (connect(clientfd, (SA *) &serveraddr, sizeof(serveraddr)) < 0)
	return -1;
    return clientfd;
}


/*
* 
* open_listenfd()函数
*
* Usage:
*   服务器创建一个监听套接字描述符，准备好接收连接请求
*
* Return:
*   0-调用成功返回服务器描述符listenfd
*   1-调用出错 返回-1
*
*/
int open_listenfd(int port) 
{
    int listenfd, optval=1;
    struct sockaddr_in serveraddr;
  

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	return -1;
 

    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, 
		   (const void *)&optval , sizeof(int)) < 0)
	return -1;

    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET; 
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    serveraddr.sin_port = htons((unsigned short)port); 
    if (bind(listenfd, (SA *)&serveraddr, sizeof(serveraddr)) < 0)
	return -1;

    if (listen(listenfd, LISTENQ) < 0)
	return -1;
    return listenfd;
}


/*****************************
 * 对套接字结构辅助函数的封装
 *****************************/

/*
* 
* Open_clientfd()函数
*
* Usage:
*   对open_clientfd()函数的封装,建立与服务器的连接，该服务器运行在主机hostname上，
*   并在端口好port上监听连接请求
*
* Return:
*   0-调用成功返回客户端描述符clientfd
*   1-调用出错报告对应错误信息
*
*/
int Open_clientfd(char *hostname, int port) 
{
    int rc;

    if ((rc = open_clientfd(hostname, port)) < 0) {
	if (rc == -1)
	    unix_error("Open_clientfd Unix error");
	else        
	    dns_error("Open_clientfd DNS error");
    }
    return rc;
}

/*
* 
* Open_listenfd()函数
*
* Usage:
*   对open_listenfd()函数的封装，服务器创建一个监听套接字描述符，准备好接收连接请求
*
* Return:
*   0-调用成功返回服务器描述符listenfd
*   1-调用出错报告对应错误信息
*
*/
int Open_listenfd(int port) 
{
    int rc;

    if ((rc = open_listenfd(port)) < 0)
	unix_error("Open_listenfd error");
    return rc;
}
/* $end CS_helper_funcs.c */

