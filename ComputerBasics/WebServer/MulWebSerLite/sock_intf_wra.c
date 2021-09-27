/* $begin sock_intf_wra.c */

#include "general.h"

/******************** 
 * 套接字接口函数封装
 ********************/

/*
* 
* Socket()函数
*
* Usage:
*   客户端和服务器使用socket()函数创建一个套接字描述符
*
* Return:
*   0-调用成功则返回套接字描述符
*   1-调用失败返回错误信息
*
*/
int Socket(int domain, int type, int protocol) 
{
    int rc;

    if ((rc = socket(domain, type, protocol)) < 0)
	unix_error("Socket error");
    return rc;
}

/*
* 
* Setsockopt()函数
*
* Usage:
*   配置服务器，使得服务器能够被终止、重启和开启接收连接请求
*
* Return:
*   0-无返回值但是调用失败返回错误信息
*
*/
void Setsockopt(int s, int level, int optname, const void *optval, int optlen) 
{
    int rc;

    if ((rc = setsockopt(s, level, optname, optval, optlen)) < 0)
	unix_error("Setsockopt error");
}


/*
* 
* Bind()函数
*
* Usage:
*   使得内核将服务器套接字地址和套接字描述符联系起来
*
* Return:
*   0-无返回值但是调用失败返回错误信息
*
*/
void Bind(int sockfd, struct sockaddr *my_addr, int addrlen) 
{
    int rc;

    if ((rc = bind(sockfd, my_addr, addrlen)) < 0)
	unix_error("Bind error");
}

/*
* 
* Listen()函数
*
* Usage:
*   监听客户端连接请求，backlog参数记录排队等待连接的请求数量
*
* Return:
*   0-无返回值但是调用失败返回错误信息
*
*/
void Listen(int s, int backlog) 
{
    int rc;

    if ((rc = listen(s,  backlog)) < 0)
	unix_error("Listen error");
}

/*
* 
* Accept()函数
*
* Usage:
*   服务器使用Accept()函数等待来自客户端的连接请求
*
* Return:
*   0-调用成功则返回连接的套接字描述符
*   1-调用失败返回错误信息
*
*/
int Accept(int s, struct sockaddr *addr, socklen_t *addrlen) 
{
    int rc;

    if ((rc = accept(s, addr, addrlen)) < 0)
	unix_error("Accept error");
    return rc;
}

/*
* 
* Connect()函数
*
* Usage:
*   客户端调用connect()函数来建立与服务器的连接
*
* Return:
*   0-无返回值但是调用失败返回错误信息
*
*/
void Connect(int sockfd, struct sockaddr *serv_addr, int addrlen) 
{
    int rc;

    if ((rc = connect(sockfd, serv_addr, addrlen)) < 0)
	unix_error("Connect error");
}

/* $end sock_intf_wra.c */
