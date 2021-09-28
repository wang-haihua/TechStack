#include<iostream>
#include<vector>

using namespace std;

int basicBinarySearch(vector<int> arr, int target){
    int left = 0;
    int right = arr.size() - 1;
    while(left <= right){
        int mid = left + (right-left)/2;
        if(target == arr[mid]){
            return mid;
        }
        else if (target < arr[mid]){
           right = mid - 1; 
        }
        else if(target > arr[mid]){
            left = mid + 1;
        }
    }
    return -1;
}

int lowerBound(vector<int> arr, int target){
    int left = 0;
    int right = arr.size();
    int pos = -1;
    while(left < right){
        int mid = left + (right-left)/2;
        if(target == arr[mid]){
            pos = mid;
            right = mid;
        }
        else if(target < arr[mid]){
            right = mid;
        }
        else if(target > arr[mid]){
            left = mid + 1;
        }
    }
    return pos;
}

int upperBound(vector<int> arr, int target){
    int left = 0;
    int right = arr.size();
    int pos = -1;
    while (left < right)
    {
        int mid = left + (right-left)/2;
        if(target == arr[mid]){
            pos = mid;
            left = mid + 1;
        }
        else if(target < arr[mid]){
            right = mid;
        }
        else if(target > arr[mid]){
            left = mid + 1;
        }
    }
    return pos;
}

int main(){
    int a[9] = {1,3,4,6,7,8,10,13,14};
    vector<int> arr(a,a+9);
    int index = basicBinarySearch(arr,4);
    cout<<index<<endl;

    int b[8] = {1,2,4,4,4,4,5,6};
    vector<int> arr2(b,b+8);
    index = basicBinarySearch(arr2,4);
    int pos = lowerBound(arr2,4);
    cout << index << "," << pos << endl;
    pos = upperBound(arr2,4);
    cout << index << "," << pos << endl;
    

    return 0;
}