#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void mergeArr(vector<int>& nums, int start, int mid, int end, vector<int>& tmp){
    int pLeft = start, pRight = mid+1, pTmp = 0;
    while (pLeft<=mid&&pRight<=end)
    {
        if(nums[pLeft]<nums[pRight]){
            tmp[pTmp++]=nums[pLeft++];
        }else{
            tmp[pTmp++]=nums[pRight++];
        }
    }
    while (pLeft<=mid)
    {
        tmp[pTmp++]=nums[pLeft++];
    }
    while (pRight<=end)
    {
        tmp[pTmp++]=nums[pRight++];
    }
    
    for(int i=0;i<pTmp;++i){
        nums[start+i]=tmp[i];
    }
}

void mergeSort(vector<int>& nums, int start, int end, vector<int>& tmp){
    if(start<end){
        int mid = start + (end-start)/2;
        mergeSort(nums,start,mid,tmp);
        mergeSort(nums,mid+1,end,tmp);
        mergeArr(nums,start,mid,end,tmp);
    }
}

vector<int> sortArray(vector<int>& nums) {
    int numsLen = nums.size();
    vector<int> tmp(0,numsLen);
    int start = 0, end = numsLen-1;
    if(start<end){
        mergeSort(nums,start,end,tmp);
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