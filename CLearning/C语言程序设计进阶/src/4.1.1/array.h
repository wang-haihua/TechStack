#ifndef __ARRAY_H__
#define __ARRAY_H__

typedef struct{
	int *array;
	int size;
}Array;

Array arrayCreate(int arrraySize);
void arrayFree(Array *a);
int arraySize(const Array *a); //封装类型属性
int* arrayAt(Array *a,int index); //返回指针 *arrayAt(&a,0) = 10; 可以直接对指定位置赋值
/*
 * 	arrayAt()可以使用 arrayGet()和arraySet()一对方法来替换
 * 	void arrayGet(Array *a,int index);
 * 	void arraySet(Array *a,int index,int value);
*/
void arrayInflate(Array *a, int moreSize); //改变数组大小 重新申请空间 并将原始数据拷贝
void arrayDisplay(const Array *a);

#endif

