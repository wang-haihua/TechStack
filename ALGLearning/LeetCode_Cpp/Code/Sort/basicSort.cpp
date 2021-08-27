#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

template<class T>
void myswap(T &a, T &b){
    T tmp = a;
    a = b;
    b = tmp;
}

void selectSort(vector<int> &nums){
    int numsLen = nums.size();
    for(int i=0;i<numsLen-1;++i){
        int s = i;
        for(int j=i+1;j<numsLen;++j){
            if(nums[s]>nums[j]){
                s = j;
            }
        }
        myswap(nums[i],nums[s]);
    }
}

void insertSrot(vector<int> &nums){
    int numsLen = nums.size();
    for(int i=0;i<numsLen;++i){
        for(int j=i;j>0&&nums[j]<nums[j-1];--j){
            myswap(nums[j],nums[j-1]);
        }
    }
}

void bubbleSort(vector<int> &nums){
    int numsLen = nums.size();
    for(int i=0;i<numsLen-1;++i){
        bool swapped = false;
        for(int j=1;j<numsLen-i;++j){
            if(nums[j]<nums[j-1]){
                myswap(nums[j],nums[j-1]);
                swapped = true;
            }
        }
        if(!swapped){
            break;
        }
    }
}

void quickSort(vector<int> &nums, int start, int end){
    if(start + 1 >= end) return;
    int lsh = start, rsh = end-1;
    int key = nums[start];
    while(lsh < rsh){
        while (lsh<rsh&&nums[rsh]>=key)
        {
            --rsh;
        }
        nums[lsh]=nums[rsh];
        while (lsh<rsh&&nums[lsh]<=key)
        {
            ++lsh;
        }
        nums[rsh]=nums[lsh];
    }
    nums[lsh] = key;
    quickSort(nums,start,lsh);
    quickSort(nums,rsh+1,end);
}

void mergeSort(vector<int> &nums, int start, int end, vector<int> &tmp){
    if(start>end) return;
    int mid = start + (end-start)/2;
    mergeSort(nums,start,mid,tmp);
    mergeSort(nums,mid,end,tmp);
    int lsh = start, rsh = mid, i = start;
    while(lsh<mid || rsh<end){
        if(rsh>=end || (lsh<mid&&(nums[lsh]<=nums[rsh]))){
            tmp[i++]=nums[lsh++];
        }else{
            tmp[i++]=nums[rsh++];
        }
    }
    for(int i=start;i<end;++i){
        nums[i]=tmp[i];
    }
}

void quick_sort(vector<int> &nums, int start, int end){
    if(start+1>=end){
        return;
    }
    int p = start, q = end-1;
    int pivot = nums[start];
    while(p<q){
        while(q>p&&nums[q]>=pivot){
            --q;
        }
        nums[p] = nums[q];
        while (p<q&&nums[p]<=pivot)
        {
            ++p;
        }
        nums[q] = nums[p];
    }
    nums[p] = pivot;
    quick_sort(nums,start,p);
    quick_sort(nums,q+1,end);
}

void merge_sort(vector<int> &nums, int start, int end, vector<int> tmp){
    if(start+1>=end){
        return;
    }
    int mid = start + (end - start)/2;
    merge_sort(nums,start,mid,tmp);
    merge_sort(nums,mid,end,tmp);
    int p = start, q = mid, i=start;
    while(p<start||q<end){
        if(q>=end||(p<start&&(nums[p]<=nums[q]))){
            tmp[i++] = nums[p++];
        }else{
            tmp[i++] = nums[q++];
        }
    } 
    for(int i=start;i<end;++i){
        nums[i]=tmp[i];
    }
}

int main(){
    vector<int> arr{5,3,6,8,1,2,7,4};
    // selectSort(arr);
    // insertSrot(arr);
    // bubbleSort(arr);
    // quickSort(arr,0,arr.size());
    vector<int> tmp(8,0);
    mergeSort(arr,0,arr.size(),tmp);
    return 0;
}