#include<iostream>
#include<vector>

using namespace std;

void swap(int& a, int& b){
    int tmp = a;
    a = b;
    b = tmp;
}

void maxHeap(vector<int>& arr, int start, int end){
    int parent = start;
    int child = parent*2 + 1;
    while (child <= end)
    {
        // 先比较两个子节点大小
        if(child+1 <= end && arr[child] < arr[child+1]){
            child++;
        }
        // 在比较子节点与父节点大小
        if(arr[parent]>arr[child]){
            return;
        }else{ // 父节点比子节点小时要交换其值，并向孙子结点比较
            swap(arr[parent],arr[child]);
            parent = child;
            child = parent*2+1;
        }
    }
}

void maxHeapSort(vector<int>& arr){
    int len = arr.size();
    // 从第一个非叶子结点arr[n/2-1],从下至上，从右至左调整结构
    for(int i=len/2-1;i>=0;--i){ 
        maxHeap(arr,i,len-1);
    }
    // 取出最大元素然后重新调整结构得到第二大元素
    for(int i=len-1;i>0;--i){
        swap(arr[0],arr[i]);
        maxHeap(arr,0,i-1);
    }
}

int main(){
    vector<int> arr{1,5,2,8,4,6,3,7,9};
    maxHeapSort(arr);
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<',';
    }
    return 0;
}