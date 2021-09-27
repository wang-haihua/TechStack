#include <stdio.h>

void f(int i);
void g(int i);
void h(int i);
void k(int i);

int main(int argc,char const *argv[])
{
	int i = 0;
	void (*fa[])(int) = {f,g,h,k}; //定义一个分别指向不同函数的指针数组fa
	printf("input {1,2,3,4} to choose a func {f,g,h,k}\n");
	scanf("%d",&i);
	if(i>0 && i<=sizeof(fa)/sizeof(fa[0])){
		(*fa[i-1])(0);
	}
}

void f(int i)
{
	printf("in f func\n");
}

void g(int i)
{
	printf("in g func\n");
}

void h(int i)
{
	printf("in h func\n");
}

void k(int i)
{
	printf("in k func\n");
}
