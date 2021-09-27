/* $begin service.h */
#ifndef __SERVICE_H__
#define __SERVICE_H__

#include "general.h"
/* HTTP事务处理函数 */
void handle_http_trans(int fd); 

/* 读客户端请求报头函数 */
void read_request_header(rio_t *rp);

/* URI解析函数 */
int parsing_uri(char *uri, char *filename, char cgiargs);

/* 静态内容服务函数 */
void static_content_service(int fd, char *filename, int filesize);

/* 获取文件类型函数 */
void get_filetype(char *filename, char *filetype);

/* 动态内容服务函数 */
void dynamic_content_service(int fd, char *filename, char cgiargs);

/* 错误报告函数 */
void report_error(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);

#endif /* __SERVICE_H__ */

/* $end service.h */

