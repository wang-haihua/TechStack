/* $begin mem_map_wra.c */
#include "head.h"

/******************
 * 内存映射函数封装
 ******************/

/*
* 
* Mmap()函数
*
* Usage:
*   创建新的虚拟内存区域，并将对象映射到这些区域中
*
* Return:
*   0-调用成功返回指向映射区域的指针
*   1-调用失败返回错误信息
*
*/
void *Mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset) 
{
    void *ptr;

    if ((ptr = mmap(addr, len, prot, flags, fd, offset)) == ((void *) -1))
	unix_error("mmap error");
    return(ptr);
}

/*
* 
* Munmap()函数
*
* Usage:
*   删除虚拟内存区域，删除从虚拟地址start开始，由接下来length个字节组成的区域
*
* Return:
*   1-无返回值但是调用失败返回错误信息
*
*/
void Munmap(void *start, size_t length) 
{
    if (munmap(start, length) < 0)
	unix_error("munmap error");
}
/*$end mem_map_wra.c*/
