#include<iostream>
#include<vector>

using namespace std;

void mergeAndCount(vector<int>& arr, int start, int mid, int end, vector<int> tmp, int& count){
    int pTmp = 0;
    int pLeft = start; int pRight = mid+1;
    while(pLeft<=mid&&pRight<=end){
        if(arr[pLeft] < arr[pRight]){
            tmp[pTmp++] = arr[pLeft++];
        }else{
            // 一旦移动右侧的元素，那么当前左侧指针指向到位置到左侧末尾的元素都大于被移动的右侧元素
            for(int i = pLeft;i<=mid;i++){
                cout<<'('<<arr[i]<<','<<arr[pRight]<<')'<<endl;
                count++;
            }
            tmp[pTmp++] = arr[pRight++];
        }
    }
    while(pLeft<=mid){
        tmp[pTmp++] = arr[pLeft++];
    }
    while (pRight<=end)
    {
        tmp[pTmp++] = arr[pRight++];
    }
    for(int i=0;i<pTmp;i++){
        arr[start+i] = tmp[i];
    }
}

void mergeSort(vector<int>& arr, int start, int end, vector<int> tmp,int& count){
    if(start < end){
        int mid = start + (end-start)/2;
        mergeSort(arr,start,mid,tmp,count);
        mergeSort(arr,mid+1,end,tmp,count);
        mergeAndCount(arr,start,mid,end,tmp,count);
    }
}

int main(){
    int arr[6] = {2,6,3,4,5,1};
    int count = 0;
    vector<int> arrVec(arr,arr+6);
    vector<int> tmp(6);
    mergeSort(arrVec,0,arrVec.size()-1,tmp,count);
    cout << count << endl;
    return 0;
}
