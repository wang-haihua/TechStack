/* $begin err_handle_wra.c */
#include "head.h"

/****************** 
 * 错误处理函数封装
 ******************/

/*
* 
* unix_error()函数
*
* Usage:
*   unix_error()函数对函数调用进行错误报告
*
* Return:
*   0-无返回值，但是通过strerror()函数返回一个文本串，描述错误相关信息
* 
*/
void unix_error(char *msg) 
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

/*
* 
* dns_error()函数
*
* Usage:
*   dns_error()函数对域名解析进行错误报告
*
* Return:
*   0-无返回值，但是返回一个文本串，描述域名解析错误相关信息
* 
*/
void dns_error(char *msg) 
{
    fprintf(stderr, "%s: DNS error %d\n", msg, h_errno);
    exit(0);
}
/* $end err_handle_wra.c */
