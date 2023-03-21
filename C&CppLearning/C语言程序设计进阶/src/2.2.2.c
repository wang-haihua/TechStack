#include<stdio.h>
#include<stdlib.h>

int main(){
	int number;
	printf("Input the number : ");
	scanf("%d",&number);
	int* arr = (int *)malloc(number*sizeof(int));
	int i=0;
	while(i<number)
	{
		printf("Input the element of array: ");
		scanf("%d",&arr[i++]);
	}
	i = number - 1;
	while(i>=0)
	{
		printf("%d ",arr[i--]);
	}	
	printf("\n");
	free(arr); //don't forget to free the space which was malloced
	return 0;
}
