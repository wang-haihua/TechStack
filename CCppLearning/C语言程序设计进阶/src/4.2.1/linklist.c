#include "linklist.h"
#include<stdio.h>
#include<stdlib.h>

void initList(Linklist *L)
{
	L = (Linklist *)malloc(sizeof(Linklist));
	L->next = NULL;
}

void createListHead(Linklist *L)
{
	Linklist * s;
	printf("input the value of the node end with -1:\n");
	int number = 0;
	while(1){
		scanf("%d",&number);
		if(number == -1)
			break;
		s = (Linklist *)malloc(sizeof(Linklist));
		s->value = number;
	    s->next = L->next;
		L->next = s;	
	}
	printf("completed!!!\n");
}

void createListTail(Linklist *L)
{
	Linklist * s,*r;
	r = L;
	printf("input the value of the node end with -1:\n");
	int number = 0;
	while(1){
		scanf("%d",&number);
		if(number == -1)
			break;
		if(L->next == NULL){
			s = (Linklist *)malloc(sizeof(Linklist));
			s->value = number;
			L->next = s;
			s->next = NULL;
			r = s;
		}
		s = (Linklist *)malloc(sizeof(Linklist));
		s->value = number;
		r->next = s;
		r = s;
	}
	r->next = NULL;
}

int lengthList(const Linklist *L)
{
	Linklist * p;
	p = L->next;
	int count = 0;
	while(p != NULL){
		count++;
		p = p->next;
	}
	return count;
}

int getElem(const Linklist *L, int i, int *e)
{
	int j = 0;
	Linklist * p;
	p = L->next;
	while( j<i && p!=NULL){
		j++;
		p = p->next;
	}	
	if(p==NULL){
		return -1;
	}else{
		e = p->value;
		return 1;
	}
}

int insertList(Linklist *L, int i, int e)
{
	Linklist *p,*s;
	p = L->next;
	int j = 0;
	while( j<i-1 && p!=NULL){
		j++;
		p = p->next;
	}
	if(p == NULL){
		return -1;
	}
	s = (Linklist *)malloc(sizeof(Linklist));
	s->value = e;
	s->next = p->next;
	p->next = s;
	return 1;
}

int deleteList(Linklist *L, int i, int *e)
{
	Linklist *p,*q,*s;
	p = L->next;
	int j = 0;
	while( j<i-1 && p!=NULL){
		j++;
		p = p->next;
	}
	if(p == NULL){
		return -1;
	}
	q = p->next;
	if(q == NULL){
		return -1;
	}
	p->next = p->next->next;
	e = q->value;
	free(q);	
	return 1;
}

int updateList(Linklist *L, int i,int e)
{
	Linklist *p,*s;
	p = L->next;
	int j = 0;
	while( j<i && p!=NULL){
		j++;
		p = p->next;
	}
	if(p == NULL){
		return -1;
	}
	p->value = e;
	return 1;
}	

void freeList(Linklist *L)
{
	Linklist *p,*q;
	p = L->next;
	while(p!=NULL){
		q = p;
		p = p->next;
		free(q);
	}	
	free(L);
	printf("successfully clear the Linklist!\n");
}

void displayList(const Linklist *L)
{
	Linklist *p;
	p = L->next;
	while(p!=NULL){
		printf("%d ",p->value);
		p = p->next;
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{
	Linklist L;
	initList(&L);
	createListHead(&L);
	//printf("the length of the Linklist is: %d",lengthList(&L));
	printf("the contains of the Linklist is:\n");
	displayList(&L);
	int e1 = 0;
	if(getElem(&L,5,&e1)==1){
		printf("the 5's element is %d\n",e1);
	}
	int e2 = 100;
	updateList(&L,5,e2);
	if(getElem(&L,5,&e1)==1){
		printf("the 5's element is %d\n",e1);
	}
	int e3 = 25;
	insertList(&L,5,e3);
	displayList(&L);
	deleteList(&L,5,&e1);
	displayList(&L);
	freeList(&L);

	return 0;

}
