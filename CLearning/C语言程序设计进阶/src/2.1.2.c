#include<stdio.h>
/*
 * @return 如果除法成功返回1；否则返回0. 
 */

int divide(int a, int b, int *res);

int main()
{
	int a = 10;
	int b = 2;
	int c = 5;
	int result;
	if(divide(a,b,&result))
	{
		printf("%d / %d = %d\n",a,b,result);
	}else{
		printf("the reference 'b' shouldn't be initialed as zero!\n");
	}
	return 0;
}

int divide(int a, int b, int *res)
{
	int status = 1;
	if(0 == b)
	{
		status = 0;
	}else{
		*res = a / b;
	}
	return status;
}
