#include <iostream>
#include <string>
using namespace std;

class MySort{

    public:
        void bubble_sort(int* A, int len); // 冒泡排序
        void violence_sort(int* A, int len); // 选择排序
        void insert_sort(int* A, int len); // 插入排序
        void shell_sort(int A[], int len); // 希尔排序
        void merge_sort(int A[], int low, int mid, int high); // 归并排序
        
        // 快速排序
        int patition(int* p, int left, int right);
        void quick_sort(int* p, int left, int right);

        // 堆排序
        void max_heapify(int* A, int i, int size);
        void build_max_heap(int* A, int size);
        void heap_sort(int* A, int len);

}


void MySort::bubble_sort(int* A, int len){

    return ;
}

