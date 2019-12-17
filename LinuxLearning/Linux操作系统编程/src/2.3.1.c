#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
	int fd;
	int ret;
	fd = open("hello.txt",O_WRONLY|O_CREAT|O_TRUNC,0644);
	/* //undefined reference to `ERR_EXIT`
	if(fd == -1)
		ERR_EXIT("open error");
	*/
	write(fd,"hello\n",6);
	ret = lseek(fd,1024*1024*1024,SEEK_CUR);
	/*
	if(ret == -1)
		ERR_EXIT("lseek error");
	*/
	write(fd,"world\n",6);
	close(fd);
	return 0;
}
