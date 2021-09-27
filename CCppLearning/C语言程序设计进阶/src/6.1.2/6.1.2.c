#include <stdio.h>

int main(int argc, char const *argv[])
{
	FILE *fp = fopen("6.1.2.in","r");
	if(fp){
		int num;
		fscanf(fp,"%d",&num);
		printf("%d\n",num);
		fclose(fp);
	}else{
		printf("open the file failed!\n");
	}

	return 0;
}
