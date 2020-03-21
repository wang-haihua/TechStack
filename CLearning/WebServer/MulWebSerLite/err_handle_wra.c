/* $begin err_handle_wra.c */
#include "general.h"

/******************* 
 * 错误报告函数封装
 *******************/

/*
 * 
 * unix_error()函数
 *
 * Usage:
 *	报告使用unix I/O进行输入输出是的错误
 *
 * Return:
 *   0-无返回值，打印错误信息
 *
 */
void unix_error(char *msg) 
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(0);
}


/*
 * 
 * dns _error()函数
 *
 * Usage:
 *	报告DNS解析错误信息
 *
 * Return:
 *   0-无返回值，打印错误信息
 *
 */
void dns_error(char *msg) 
{
	fprintf(stderr, "%s: DNS error %d\n", msg, h_errno);
	exit(0);
}

/*
 * 
 * app_error()函数
 *
 * Usage:
 *	报告应用运行错误信息
 *
 * Return:
 *   0-无返回值，打印错误信息
 *
 */
void app_error(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(0);
}


/* $end err_handle_wra.c */
