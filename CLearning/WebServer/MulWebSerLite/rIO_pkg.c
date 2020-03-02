/* $begin rIO_pkg.c */

#include "general.h"

/******************************
 * robust I/O 健壮的I/O包
 ******************************/
/*
* robust I/O的特点
* 1-无缓冲的输入输出函数：直接在内存和文件间传送数据，这在二进制数据在网络和内存数据传输中十分重要
* 2-带缓冲的输入函数：高效的从文件中读取文本行和二进制数据
*/

/*
* 
* rio_readn()函数
*
* Usage:
*   从文件描述符为fd的当前文件位置复制最多n个字节到内存位置usrbuf
*
* Return:
*   0-调用成功则返回实际传送的字节数量
*   1-调用失败返回0或-1
* 
*/
ssize_t rio_readn(int fd, void *usrbuf, size_t n) 
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while (nleft > 0) {
	if ((nread = read(fd, bufp, nleft)) < 0) {
	    if (errno == EINTR) 
		nread = 0;      
	    else
		return -1;       
	} 
	else if (nread == 0)
	    break;              
	nleft -= nread;
	bufp += nread;
    }
    return (n - nleft);         
}

/*
* 
* rio_writen()函数
*
* Usage:
*   从内存位置usrbuf复制最多n个字节到文件描述符为fd的当前文件位置
*
* Return:
*   0-调用成功则返回实际传送的字节数量
*   1-调用失败返回0或-1
* 
*/
ssize_t rio_writen(int fd, void *usrbuf, size_t n) 
{
    size_t nleft = n;
    ssize_t nwritten;
    char *bufp = usrbuf;

    while (nleft > 0) {
	if ((nwritten = write(fd, bufp, nleft)) <= 0) {
	    if (errno == EINTR)  
		nwritten = 0;    
	    else
		return -1;       
	}
	nleft -= nwritten;
	bufp += nwritten;
    }
    return n;
}


/*
* 
* rio_read()函数
*
* Usage:
*   rio_read是对Unix I/O中的read()函数的封装，它将最小(n，rio_cnt)字节从内部缓冲区传输到用户缓冲区，
*   其中n是用户请求的字节数，rio_cnt是内部缓冲区中未读的字节数。
*   进入时，如果内部缓冲区为空，rio_read()通过调用read()来重新填充内部缓冲区。
*
* Return:
*   0-调用成功则返回实际传送的字节数量
*   1-调用失败返回0或-1
* 
*/
static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
    int cnt;

    while (rp->rio_cnt <= 0) { 
	rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, 
			   sizeof(rp->rio_buf));
	if (rp->rio_cnt < 0) {
	    if (errno != EINTR) 
		return -1;
	}
	else if (rp->rio_cnt == 0)  
	    return 0;
	else 
	    rp->rio_bufptr = rp->rio_buf; 
    }

    cnt = n;          
    if (rp->rio_cnt < n)   
	cnt = rp->rio_cnt;
    memcpy(usrbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}


/*
* 
* rio_readinitb()函数
*
* Usage:
*   将文件描述符fd和地址rp处的一个类型为rio_t的读缓冲区联系起来
*
* Return:
* 
*/
void rio_readinitb(rio_t *rp, int fd) 
{
    rp->rio_fd = fd;  
    rp->rio_cnt = 0;  
    rp->rio_bufptr = rp->rio_buf;
}


/*
* 
* rio_readnb()函数
*
* Usage:
*   从文件地址rp最多读n个字节到内存位置usrbuf
*
* Return:
*   0-调用成功则返回实际传送的字节数量
*   1-调用失败返回0或-1
*
*/
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n) 
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;
    
    while (nleft > 0) {
	if ((nread = rio_read(rp, bufp, nleft)) < 0) 
            return -1;           
	else if (nread == 0)
	    break;              
	nleft -= nread;
	bufp += nread;
    }
    return (n - nleft);         
}

/*
* 
* rio_readlineb()函数
*
* Usage:
*   从文件地址rp读出下一个文本行并复制到内存位置usrbuf，并且用NULL字符结束文本行
*
* Return:
*   0-调用成功则返回实际传送的字节数量
*   1-调用失败返回0或-1
*
*/
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen) 
{
    int n, rc;
    char c, *bufp = usrbuf;

    for (n = 1; n < maxlen; n++) { 
        if ((rc = rio_read(rp, &c, 1)) == 1) {
	    *bufp++ = c;
	    if (c == '\n') {
                n++;
     		break;
            }
	} else if (rc == 0) {
	    if (n == 1)
		return 0; 
	    else
		break;    
	} else
	    return -1;	 
    }
    *bufp = 0;
    return n-1;
}


/****************************
 * 对robust I/O库的进一步封装
 ****************************/
/*
* 
* Rio_readn()函数
*
* Usage:
*   对rio_readn()的封装，从文件描述符为fd的当前文件位置复制最多nbytes个字节到内存位置usrbuf
*
* Return:
*   0-调用成功则返回实际传送的字节数量
*   1-调用失败返回错误信息
* 
*/
ssize_t Rio_readn(int fd, void *ptr, size_t nbytes) 
{
    ssize_t n;
  
    if ((n = rio_readn(fd, ptr, nbytes)) < 0)
	unix_error("Rio_readn error");
    return n;
}

/*
* 
* Rio_writen()函数
*
* Usage:
*   对rio_writen()的封装，从内存位置usrbuf复制最多n个字节到文件描述符为fd的当前文件位置
*
* Return:
*   1-无返回值但是调用失败返回错误信息
* 
*/
void Rio_writen(int fd, void *usrbuf, size_t n) 
{
    if (rio_writen(fd, usrbuf, n) != n)
	unix_error("Rio_writen error");
}

/*
* 
* Rio_readinitb()函数
*
* Usage:
*   对rio_readinitb()的封装，将文件描述符fd和地址rp处的一个类型为rio_t的读缓冲区联系起来
*
* Return:
* 
*/
void Rio_readinitb(rio_t *rp, int fd)
{
    rio_readinitb(rp, fd);
} 

/*
* 
* Rio_readnb()函数
*
* Usage:
*   对rio_readnb()的封装，从文件地址rp最多读n个字节到内存位置usrbuf
*
* Return:
*   0-调用成功则返回实际传送的字节数量
*   1-调用失败返回错误信息
*
*/
ssize_t Rio_readnb(rio_t *rp, void *usrbuf, size_t n) 
{
    ssize_t rc;

    if ((rc = rio_readnb(rp, usrbuf, n)) < 0)
	unix_error("Rio_readnb error");
    return rc;
}

/*
* 
* Rio_readlineb()函数
*
* Usage:
*   对rio_readlineb()的封装，从文件地址rp读出下一个文本行并复制到内存位置usrbuf，并且用NULL字符结束文本行
*
* Return:
*   0-调用成功则返回实际传送的字节数量
*   1-调用失败返回错误信息
*
*/
ssize_t Rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen) 
{
    ssize_t rc;

    if ((rc = rio_readlineb(rp, usrbuf, maxlen)) < 0)
	unix_error("Rio_readlineb error");
    return rc;
} 

/* $end rIO_pkg.c */
