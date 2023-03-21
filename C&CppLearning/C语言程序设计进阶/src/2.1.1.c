/*
 *指针变量作为形式参数返回函数结果
 */
#include<stdio.h>

void swap(int *pa, int *pb);

int main()
{
	int a = 1;
	int b = 2;
	swap(&a,&b);
	printf("a=%d,b=%d\n",a,b);
	return 0;
}

void swap(int *pa, int *pb)
{
	int temp = *pa;
	*pa = *pb;
	*pb = temp;
}
