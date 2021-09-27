#include "/home/wanghaihua/Desktop/TechnicalRoute/CLearning/WebServer/MulWebSerLite/general.h"


int main(void) {
	char *buf, *p;
  	char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
  	int n1=0, n2=0;
	int op = 1;
	char *method;

   	/* 根据CGI环境变量读取参数 */
    if ((buf = getenv("QUERY_STRING")) != NULL) {
    	p = strchr(buf, '&');
	    *p = '\0';
	    sscanf(buf, "first=%d", &n1);
	    sscanf(p+1, "second=%d", &n2);
		sscanf(p+2, "operation=%d", &op);
  	}
	method = getenv("REQUEST_METHOD");

    /* 创建HTTP响应主体 */
    sprintf(content, "Welcome to WangHaihua WebServer: ");
    sprintf(content, "%sThese's the dynamic content service based on CGI\r\n<p>", content);
	if(op == 1)
    	sprintf(content, "%sThe answer is: %d + %d = %d\r\n<p>", content, n1, n2, n1 + n2);
	else if(op == 2)
		sprintf(content, "%sThe answer is: %d - %d = %d\r\n<p>", content, n1, n2, n1 - n2);
    sprintf(content, "%sThanks for visiting!\r\n", content);

	 /* 形成HTTP响应 */
    printf("Connection: close\r\n");
    printf("Content-length: %d\r\n", (int)strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    if(strcasecmp(method, "HEAD") !=0 )
		printf("%s", content);
	fflush(stdout);
    exit(0);
}
