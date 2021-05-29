#include<iostream>
#include<vector>

using namespace std;

void swap(int& a, int&b){
    int tmp = a;
    a = b;
    b = tmp;
}

void quickSort(vector<int>& arr, int start, int end){
    if(start >= end) return;
    int pHead = start; int pTail = end;
    int key = arr[start];
    while(pHead<pTail){
        // 右边小于 key 的元素移到其左边 
        // 比较大小要用大于等于，直接跳过相等的值，只招小于的值
        while(pTail>pHead&&arr[pTail]>=key){
            pTail--;
        }
        swap(arr[pHead],arr[pTail]);
        // 左边大于 key 的元素移到其右边
        while(pHead<pTail&&arr[pHead]<=key){
            pHead++;
        }
        swap(arr[pHead],arr[pTail]);
    }
    quickSort(arr,start,pHead-1); // 减 1 不要忘，每确定一个key的位置在整个数组就不再改变
    quickSort(arr,pTail+1,end);
}

int main(){
    int a[10] = {6,1,2,7,9,3,4,5,10,8};
    vector<int> arr(a,a+10);
    quickSort(arr,0,arr.size()-1);
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<',';
    }
    cout<<endl;
    return 0;
}