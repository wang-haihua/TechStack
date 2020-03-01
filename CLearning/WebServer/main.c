#include "csapp.h"

void handle_http_trans(int fd); //fd软磁盘 可移动存储介质
void read_request_header(rio_t *rp);
int parsing_uri(char *uri, char *filename, char cgiargs);
void static_content_service(int fd, char *filename, int filesize);
void get_filetype(char *filename, char *filetype);
void dynamic_content_service(int fd, char *filename, char cgiargs);
void report_error(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);

int main(int argc, const char *argv[])
{
    int listenfd, connfd, port, clientlen;
    struct sockaddr_in clientaddr;

    /* Check command line args */
    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(1);
    }
    port = atoi(argv[1]);

    listenfd = Open_listenfd(port);
    while (1) {
	clientlen = sizeof(clientaddr);
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); //line:netp:tiny:accept
	handle_http_trans(connfd);                                //line:netp:tiny:doit
	Close(connfd);                                            //line:netp:tiny:close
    }
}


