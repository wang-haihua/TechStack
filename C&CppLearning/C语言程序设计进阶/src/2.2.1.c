#include<stdio.h>

int main(){
	
	char ac[] = {1,2,3,4,5,6,7,8,9,0};
	char *pc = ac;
	for(int i=0;i<sizeof(ac)/sizeof(ac[0]);i++){
		printf("%d\n",ac[i]);
	}
	
	while(*pc != 0){
		printf("%d\n",*pc++);//*pc++
	}
	return 0;
}

