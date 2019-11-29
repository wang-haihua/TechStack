#include "array.h"
#include<stdio.h>
#include<stdlib.h>

const int BLOCK = 5;

Array arrayCreate(int arraySize)
{
	Array a;
	a.size = arraySize;
	a.array = (int *)malloc(a.size*sizeof(int));
	return a;
}

void arrayFree(Array *a)
{
	free(a->array);
	a->array = NULL;
	a->size = 0;
}

int arraySize(const Array *a)
{
	return a->size;
}

int* arrayAt(Array *a,int index)
{
	if(a->size <= index)
	{
		arrayInflate(a,(index/BLOCK+1)*BLOCK - a->size);
	}
	return &a->array[index];
}

void arrayInflate(Array *a,int moreSize)
{
	int *p = (int *)malloc(sizeof(int)*(a->size+moreSize));
	int i = 0;
	for(i;i<a->size;i++)
	{
		p[i]=a->array[i];
	}
	i = a->size;
	for(i;i<a->size+moreSize;i++)
	{
		p[i] = -1;
	}
	free(a->array);
	a->array = p;
	a->size = a->size + moreSize;
}

void arrayDisplay(const Array *a)
{
	int i = 0;
	for(i;i<a->size;i++)
	{
		printf("%d ",a->array[i]);
	}
	printf("\n");
}

int main(int argc,char const *argv[])
{
	Array a = arrayCreate(10);
	printf("the size of the array is : %d\n",arraySize(&a));
	int number = 0;
	int count = 0;
	printf("input integers end with -1\n");
	while(number != -1)
	{
		scanf("%d",&number);
		*arrayAt(&a,count++) = number;
	}
	arrayDisplay(&a);
	printf("the %d's element of the array is %d\n",12,*arrayAt(&a,12));
	arrayFree(&a);

	return 0;
}
