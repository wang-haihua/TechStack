#include<iostream>
#include<vector>

using namespace std;

void swap(int& a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}

void arrangeRight(vector<int>& arr, int start, int end, int k){
    if(start > end) return;
    int pHead = start; int pTail = end;
    int key = arr[start];
    while(pHead < pTail){
        while (pTail>pHead&&arr[pTail]>=key) 
        {
            pTail--;
        }
        swap(arr[pHead],arr[pTail]);
        while (pHead<pTail&&arr[pHead]<=key)
        {
            pHead++;
        }
        swap(arr[pHead],arr[pTail]);
    }
    int a = end - pHead; // 包括 key 的数组右侧元素数量
    if(a==k){
        arrangeRight(arr,pTail+1,end,k); // 如果刚好为 k 个元素就对着 k 个元素进行排序
    }else if (a > k)
    {
        arrangeRight(arr,pTail,end,k);
    }else{
        arrangeRight(arr,start,pHead-1,k-a);
    }
}

int main(){
    int a[10] = {6,1,2,7,9,3,4,5,10,8};
    int k = 4;
    vector<int> arr(a,a+10);
    arrangeRight(arr,0,arr.size()-1,k);
    for(int i=0;i<k;i++){
        cout<<arr[arr.size()-1-i]<<',';
    }
    cout<<endl;
    return 0;
}