/* $begin service.c */

#include "general.h"

/*********************
 * 服务器服务函数封装
 *********************/

/*
 * 
 * handle_http_trans()函数
 *
 * Usage:
 *  处理一个HTTP事务，从请求报头读取到URI解析再到对应资源操作和最后响应请求一个完整的
 *  HTTP处理过程 
 *
 * Return:
 *    0-无返回值，但在正确响应是返回对应响应内容，响应失败时返回对应错误信息
 * 
 */ 
void handle_http_trans(int fd)
{
	char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE], filename[MAXLINE], cgiargs[MAXLINE];
	int static_req;
	struct stat sbuf; //文件描述信息表项
	rio_t rio;        //Robust I/O缓冲区描述

	/* 读请求报头 */
	Rio_readinitb(&rio, fd);
	Rio_readlineb(&rio, buf, MAXLINE);
	sscanf(buf , "%s %s %s", method, uri, version);
	if (!(strcasecmp(method, "GET") == 0 || strcasecmp(method, "HEAD") == 0 || strcasecmp(method, "POST") == 0))
	{
		report_error(fd, method, "501", "Not Implemented", "This WebSever doesn't implement this method"); //请求方法错误报告
		return;
	}
	//read_request_header(&rio);
	int param_len = read_request_header(&rio, method);
	Rio_readnb(&rio, buf, param_len);

	/* 解析请求报头和请求行中的URI */
	static_req = parsing_uri(uri, filename, cgiargs);
	if (stat(filename, &sbuf) < 0) {
		report_error(fd, filename, "404", "Not found", "This WebServer couldn't find this file"); // 文件不存在报错
		return; 
	}

	/* 静态内容服务 */
	if(static_req){
		if(!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)){
			report_error(fd, filename, "403", "Forbidden", "This WebServer couldn't read the file"); // 文件无读取权限报错
			return ;
		}
		//static_content_service(fd, filename, sbuf.st_size);
		static_content_service(fd, filename, sbuf.st_size, method);
	}else{
	/* 动态内容服务 */
		if(!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)){
			report_error(fd, filename, "403", "Forbidden", "This WebServer couldn't run the CGI program"); // 无法执行动态服务程序报错
			return ;
		}
		//dynamic_content_service(fd, filename, cgiargs);
		//dynamic_content_service(fd, filename, cgiargs, method);
		if(strcasecmp(method, "GET") == 0 || strcasecmp(method, "HEAD") == 0)
		{
			dynamic_content_service(fd, filename, cgiargs, method);
		}else{
			dynamic_content_service(fd, filename, buf, method);
		}
	}
}

/*
 * 
 * read_request_header()函数
 *
 * Usage:
 *  读取请求报头中的信息，根据请求报头固定格式以空文本行结尾作为循环条件
 *
 * Return:
 * 	0-返回参数长度
 * 
 */ 
int read_request_header(rio_t *rp, char *method)
{
	char buf[MAXLINE];
	int len = 0;

	/* 读取请求报头和请求行的所有信息并打印 */
	/*
	Rio_readlineb(rp, buf, MAXLINE);
	while(strcmp(buf, "\r\n")){
		Rio_readlineb(rp, buf, MAXLINE);
		printf("%s", buf);
	}
	return ;
	*/

	do{
		Rio_readlineb(rp, buf, MAXLINE);
		printf("%s", buf);

		if(strcasecmp(method, "POST") == 0 && strncasecmp(buf, "Content-Length:", 15) == 0)
		{
			sscanf(buf, "Content-Length: %d", &len);
		}
	}while(strcmp(buf, "\r\n"));
	return len;
}

/*
 * 
 * parsing_uri()函数
 *
 * Usage:
 *	解析URI中客户端所请求的服务类型，并生成指向对应服务资源的路径 
 *
 * Return:
 *    0-返回值为0，URI被认为是请求动态内容服务
 *    1-返回值为1，URI被认为是请求静态内容服务
 * 
 */ 
int parsing_uri(char *uri, char *filename, char *cgiargs)
{
	char *ptr;
	
	/* 静态内容服务 */
	if (!strstr(uri, "bin")){
		strcpy(cgiargs, ""); // 清除CGI参数字符串
		strcpy(filename, "./src"); // 将URI转换为一个指向静态内容资源的相对路径
		strcat(filename, uri);
		if(uri[strlen(uri)-1] == '/'){
			strcat(filename, "index.html"); // 默认请求index.html文件
		}
		return 1;

	}else{
	/* 动态内容服务 */

		/* 截取所有CGI参数 */
		ptr = index(uri, '?');
		if (ptr) {
			strcpy(cgiargs, ptr+1);
			*ptr = '\0';
		}else{
			strcpy(cgiargs, "");
		}

		/* 将URI剩余部分转换为对应资源的相对路径 */
		strcpy(filename, ".");
		strcat(filename, uri);
		return 0;
	}
}

/*
 * 
 * static_content_service()函数
 *
 * Usage:
 *	提供五种常见类型的静态内容包括HTML文件、TXT文本文件、GIF、PNG和JPG格式的图片 
 *
 * Return:
 *    0-无返回值，但打印响应信息
 * 
 */ 
void static_content_service(int fd, char *filename, int filesize, char *method)
{
	int srcfd;
	char *srcp;
	char filetype[MAXLINE], buf[MAXLINE];

	/* 发送响应行和响应报头 */
	get_filetype(filename, filetype);
	sprintf(buf, "HTTP/1.0 200 OK!\r\n");
	sprintf(buf, "%s Server: Wanghaihua's Web Server\r\n", buf);
	sprintf(buf, "%s Connection: close!\r\n", buf);
	sprintf(buf, "%s Content-length: %d\r\n", buf, filesize);
	sprintf(buf, "%s Content-type: %s\r\n\r\n", buf, filetype); //响应报头以一个空行标识结尾
	Rio_writen(fd, buf, strlen(buf));
	printf("Response headers:\n");
	printf("%s", buf);

	/* 判断是否是HEAD方法 */
	if (strcasecmp(method, "HEAD") == 0)
		return;

	/* 发送包含一个本地文件内容的响应主体给客户端 */
	srcfd = Open(filename, O_RDONLY, 0);
	srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0); // 将被请求文件映射到一个虚拟内存空间
	Close(srcfd);
	Rio_writen(fd, srcp, filesize);
	Munmap(srcp, filesize); //关闭内存映射
}

/*
 * 
 * get_filetype()函数
 *
 * Usage:
 *  获取对应文件的类型 
 *
 * Return:
 * 
 */ 
void get_filetype(char *filename, char *filetype)
{
	if (strstr(filename, ".html"))
		strcpy(filetype, "text/html");  //HTML
    else if (strstr(filename, ".gif"))
		strcpy(filetype, "image/gif");  //GIF
	else if (strstr(filename, ".jpg"))
		strcpy(filetype, "image/jpeg"); //JPG
	else if (strstr(filename, ".png"))
		strcpy(filetype, "image/png");  //PNG
	else if (strstr(filename, ".mpeg"))
		strcpy(filetype, "video/mpeg"); //MPG
	else
		strcpy(filetype, "text/plain");
}

/*
 * 
 * dynamic_content_service()函数
 *
 * Usage:
 *	通过派生一个子进程来执行CGI程序，实现提供动态内容服务   
 *
 * Return:
 *    0-无返回值，但在正确响应是返回对应响应内容
 * 
 */ 
void dynamic_content_service(int fd, char *filename, char *cgiargs, char *method)
{
	char buf[MAXLINE];
	char *emptylist[] = {NULL};

	/* 发送响应行 */
	sprintf(buf, "HTTP/1.0 200 OK!\r\n");
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Server: Wanghaihua's Web Server\r\n");
	Rio_writen(fd, buf, strlen(buf));

	/* 派生子进程执行CGI程序 */
	if( Fork() == 0 ){
		setenv("QUERY_STRING",cgiargs, 1); //设置CGI环境变量
		setenv("REQUEST_METHOD", method, 1);
		Dup2(fd, STDOUT_FILENO);           //将输出重定向到已连接的文件描述符
		Execve(filename, emptylist, __environ); // 运行CGI程序
	}
	Wait(NULL);  //使用SIGCHLD处理程序回收资源替换显示地等待
}

/*
 * 
 * report_error()函数
 *
 * Usage:
 *	服务器响应失败时报告错误信息   
 *
 * Return:
 *    0-无返回值，打印响应失败时返回对应错误信息
 * 
 */ 
void report_error(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg)
{
	char buf[MAXLINE], body[MAXBUF];

	/* 返回响应失败的HTML页面 */
	sprintf(body, "<html><title>Wanghaihua's Web Server Error!!!</title>");
	sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
	sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
	sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
	sprintf(body, "%s<hr><em>Wanghaihua's Web Server</em>\r\n", body);

	/* 打印响应失败信息 */
	sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
	Rio_writen(fd, buf, strlen(buf));
	printf(buf, "Content-type: text/html\r\n");
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
	Rio_writen(fd, buf, strlen(buf));
	Rio_writen(fd, body, strlen(body));
}

/*
 * 
 * return_req_headers()函数
 *
 * Usage:
 *	原样返回每个请求行和请求报头   
 *
 * Return:
 *    0-无返回值，打印请求行和报头
 * 
 */ 
void return_req_headers(int connfd)
{
	size_t n;
	char buf[MAXLINE];
	rio_t rio;

	Rio_readinitb(&rio, connfd);
	while(( n = Rio_readlineb(&rio, buf, MAXLINE)) != 0){
		if(strcmp(buf, "\r\n") == 0) //请求行以空行结尾
		{
			break;
		}
		Rio_writen(connfd, buf, n);
	}
}

/*
 * 
 * Signal()函数
 *
 * Usage:
 *	信号处理
 *
 * Return:
 * 
 */ 
handler_t *Signal(int signum, handler_t *handler) 
{
	struct sigaction action, old_action;

    action.sa_handler = handler;  
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    if (sigaction(signum, &action, &old_action) < 0)
		unix_error("Signal error");
    return (old_action.sa_handler);
}

/*
 * 
 * sigchild_handler()函数
 *
 * Usage:
 *	CGI子进程状态处理
 *
 * Return:
 * 
 */ 
void sigchild_handler(int sig)
{
	int old_errno = errno;
	int status;
	pid_t pid;
	while((pid = Waitpid(-1, &status, WNOHANG)) > 0)
	{
		//通过判断条件终止循环
	}
	errno = old_errno;
}
/* $end service.c */
