/* $begin general.h */
#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* connect(), bind(), accept()函数使用时要求一个指向与协议相关的套接字地址结构的指针
 * 这里解决方法就是让套接字函数指向一个通用的sockaddr结构的指针，然后要求应用程序将与
 * 协议特定的结构的指针强制转换成一个通用结构 
 * struct sockaddr{
 * 	uint16_t sa_family; //协议簇
 *	char sa_data[14];   //地址信息
 * };
 */
typedef struct sockaddr SA;

/* 描述robust I/O的I/O状态的结构体rio_t */
#define RIO_BUFSIZE 8192
typedef struct {
    int rio_fd;                // 缓冲区描述符 
    int rio_cnt;               // 缓冲区内未读字节
    char *rio_bufptr;          // 下一个未读字节
    char rio_buf[RIO_BUFSIZE]; // 缓冲区
} rio_t;

/* 全局变量 */
#define	MAXLINE	 8192  // 最大文本行
#define MAXBUF   8192  // 最大I/O缓冲区
#define LISTENQ  1024  // listen()的第二个参数

/* 错误报告函数 */
void unix_error(char *msg);
void dns_error(char *msg);

/* 进程控制函数封装  */
pid_t Fork(void);
void Execve(const char *filename, char *const argv[], char *const envp[]);
pid_t Wait(int *status);
pid_t Waitpid(pid_t pid, int *iptr, int options);
void Kill(pid_t pid, int signum);
unsigned int Sleep(unsigned int secs);
void Pause(void);
unsigned int Alarm(unsigned int seconds);
void Setpgid(pid_t pid, pid_t pgid);
pid_t Getpgrp();

/* Unix I/O 函数封装 */
int Open(const char *pathname, int flags, mode_t mode);
ssize_t Read(int fd, void *buf, size_t count);
ssize_t Write(int fd, const void *buf, size_t count);
off_t Lseek(int fildes, off_t offset, int whence);
void Close(int fd);
int Select(int  n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, 
	   struct timeval *timeout);
int Dup2(int fd1, int fd2);
void Stat(const char *filename, struct stat *buf);
void Fstat(int fd, struct stat *buf) ;

/* 内存映射函数封装 */
void *Mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
void Munmap(void *start, size_t length);

/* 套接字接口函数封 */
int Socket(int domain, int type, int protocol);
void Setsockopt(int s, int level, int optname, const void *optval, int optlen);
void Bind(int sockfd, struct sockaddr *my_addr, int addrlen);
void Listen(int s, int backlog);
int Accept(int s, struct sockaddr *addr, socklen_t *addrlen);
void Connect(int sockfd, struct sockaddr *serv_addr, int addrlen);

/* Robust I/O 包 */
ssize_t rio_readn(int fd, void *usrbuf, size_t n);
ssize_t rio_writen(int fd, void *usrbuf, size_t n);
void rio_readinitb(rio_t *rp, int fd); 
ssize_t	rio_readnb(rio_t *rp, void *usrbuf, size_t n);
ssize_t	rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);

/* Robust I/O包封装 */
ssize_t Rio_readn(int fd, void *usrbuf, size_t n);
void Rio_writen(int fd, void *usrbuf, size_t n);
void Rio_readinitb(rio_t *rp, int fd); 
ssize_t Rio_readnb(rio_t *rp, void *usrbuf, size_t n);
ssize_t Rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);


/* 客户端服务器辅助函数 */
int open_clientfd(char *hostname, int portno);
int open_listenfd(int portno);

/*  客户端服务器辅助函数封装 */
int Open_clientfd(char *hostname, int port);
int Open_listenfd(int port);

/* HTTP事务处理函数 */
void handle_http_trans(int fd); 

/* 读客户端请求报头函数 */
void read_request_header(rio_t *rp);

/* URI解析函数 */
int parsing_uri(char *uri, char *filename, char *cgiargs);

/* 静态内容服务函数 */
void static_content_service(int fd, char *filename, int filesize);

/* 获取文件类型函数 */
void get_filetype(char *filename, char *filetype);

/* 动态内容服务函数 */
void dynamic_content_service(int fd, char *filename, char *cgiargs);

/* 错误报告函数 */
void report_error(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);

#endif /*  __GENERAL_H__ */ 
/* $end general.h */

