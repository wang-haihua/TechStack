/* $begin adder */
#include "/home/wanghaihua/Desktop/TechnicalRoute/CLearning/WebServer/MulWebSerLite/general.h"

int main(void) {
    char *buf, *p;
    char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
    int n1=0, n2=0;
	char *method;

    /* Extract the two arguments */
    if ((buf = getenv("QUERY_STRING")) != NULL) {
	p = strchr(buf, '&');
	*p = '\0';
	/*
	strcpy(arg1, buf);
	strcpy(arg2, p+1);
	n1 = atoi(arg1);
	n2 = atoi(arg2);
	*/
		/* 通过浏览器输入参数 */
		sscanf(buf, "first = %d", &n1);
		sscanf(p+1, "second = %d", &n2);
    }

	method = getenv("REQUEST_METHOD");

    /* Make the response body */
    sprintf(content, "Welcome to add.com: ");
    sprintf(content, "%sTHE Internet addition portal.\r\n<p>", content);
    sprintf(content, "%sThe answer is: %d + %d = %d\r\n<p>", 
	    content, n1, n2, n1 + n2);
    sprintf(content, "%sThanks for visiting!\r\n", content);
  
    /* Generate the HTTP response */
    printf("Content-length: %d\r\n", (int)strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    //printf("%s", content);
    if(strcasecmp(method, "HEAD") !=0 )
		printf("%s", content);

	fflush(stdout);
    exit(0);
}
/* $end adder */
