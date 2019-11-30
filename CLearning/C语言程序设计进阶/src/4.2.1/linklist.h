#ifndef __LINKLIST_H__
#define __LINKLIST_H__

typedef struct LNode{
	int value;
	struct LNode *next;
}Linklist;

void initList(Linklist *L);
void createListHead(Linklist *L);
void createListTail(Linklist *L);
int lengthList(const Linklist *L);
int getElem(const Linklist *L, int i, int *e); //查
int insertList(Linklist *L, int i, int e); //增
int deleteList(Linklist *L, int i, int *e); //删
int updateList(Linklist *L, int i, int e); //改
void freeList(Linklist *L);
void displayList(const Linklist *L);

#endif
