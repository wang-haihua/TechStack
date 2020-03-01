/*$begin unixIO_wra.c*/
#include "head.h"

/********************************
 * Unix I/O封装
 * 与系统内核进行I/O的低级应用接口
 ********************************/

/*
* 
* Open()函数
*
* Usage:
*   打开一个已经存在的文件或者创建一个新文件
*   将filename转换为一个文件描述符
*
* Return:
*   0-打开/创建成功返回文件描述符数字
*   1-打开/创建失败返回错误信息
* 
*/
int Open(const char *pathname, int flags, mode_t mode) 
{
    int rc;

    if ((rc = open(pathname, flags, mode))  < 0)
	unix_error("Open error");
    return rc;
}

/*
* 
* Read()函数
*
* Usage:
*   从文件描述符为fd的当前文件位置复制最多count个字节到内存位置buf
*
* Return:
*   0-调用成功则返回实际传送的直接数量
*   1-调用失败返回错误信息
* 
*/
ssize_t Read(int fd, void *buf, size_t count) 
{
    ssize_t rc;

    if ((rc = read(fd, buf, count)) < 0) 
	unix_error("Read error");
    return rc;
}

/*
* 
* Write()函数
*
* Usage:
*   从内存位置buf复制最多count个字节到文件描述符为fd的当前文件位置
*
* Return:
*   0-调用成功则返回实际传送的直接数量
*   1-调用失败返回错误信息
* 
*/
ssize_t Write(int fd, const void *buf, size_t count) 
{
    ssize_t rc;

    if ((rc = write(fd, buf, count)) < 0)
	unix_error("Write error");
    return rc;
}

/*
* 
* Lseek()函数
*
* Usage:
*   显示地修改当前文件的位置
*
* Return:
*   0-调用成功则返回修改后的文件位置
*   1-调用失败返回错误信息
* 
*/
off_t Lseek(int fildes, off_t offset, int whence) 
{
    off_t rc;

    if ((rc = lseek(fildes, offset, whence)) < 0)
	unix_error("Lseek error");
    return rc;
}

/*
* 
* Close()函数
*
* Usage:
*   关闭一个文件
*
* Return:
*   0-无返回值，但是关闭失败返回错误信息
* 
*/
void Close(int fd) 
{
    int rc;

    if ((rc = close(fd)) < 0)
	unix_error("Close error");
}

/*
int Select(int  n, fd_set *readfds, fd_set *writefds,
	   fd_set *exceptfds, struct timeval *timeout) 
{
    int rc;

    if ((rc = select(n, readfds, writefds, exceptfds, timeout)) < 0)
	unix_error("Select error");
    return rc;
}
*/

/*
* 
* Dup2()函数
*
* Usage:
*   I/O重定向，Dup2()函数将旧文件的文件描述符表项复制到新文件的文件描述符表项
*
* Return:
*   0-调用成功则返回非负的描述符
*   1-调用失败返回错误信息
* 
*/
int Dup2(int fd1, int fd2) 
{
    int rc;

    if ((rc = dup2(fd1, fd2)) < 0)
	unix_error("Dup2 error");
    return rc;
}

/*
* 
* Stat()函数
*
* Usage:
*   以文件名filename作为输入检索关于文件的信息又称为文件的元数据
*
* Return:
*   0-无返回值，但是关闭失败返回错误信息
* 
*/
void Stat(const char *filename, struct stat *buf) 
{
    if (stat(filename, buf) < 0)
	unix_error("Stat error");
}

/*
* 
* FStat()函数
*
* Usage:
*   以文件描述符fd作为输入检索关于文件的信息又称为文件的元数据
*
* Return:
*   0-无返回值，但是关闭失败返回错误信息
* 
*/
void Fstat(int fd, struct stat *buf) 
{
    if (fstat(fd, buf) < 0)
	unix_error("Fstat error");
}

/*$end unixIO_wra.c*/
