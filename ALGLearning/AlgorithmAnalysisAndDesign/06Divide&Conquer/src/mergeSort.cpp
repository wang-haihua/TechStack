#include<iostream>
#include<vector>

using namespace std;

void merge(vector<int>& arr, int start, int mid, int end, vector<int> tmp){
    int pTmp = 0;
    int pLeft = start; int pRight = mid+1;
    while(pLeft<=mid&&pRight<=end){
        if(arr[pLeft] < arr[pRight]){
            tmp[pTmp++] = arr[pLeft++];
        }else{
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

void mergeSort(vector<int>& arr, int start, int end, vector<int> tmp){
    if(start < end){
        int mid = start + (end-start)/2;
        mergeSort(arr,start,mid,tmp);
        mergeSort(arr,mid+1,end,tmp);
        merge(arr,start,mid,end,tmp);
    }
}

int main(){
    int arr[8] = {8,4,5,7,1,3,6,2};
    vector<int> arrVec(arr,arr+8);
    vector<int> tmp(8);
    mergeSort(arrVec,0,arrVec.size()-1,tmp);
    for(int i=0;i<arrVec.size();i++){
        cout<< arrVec[i] << ',';
    }
    cout << endl;
    return 0;
}