#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int search(vector<int>& nums, int target) {
    int lhs = 0, rhs = nums.size()-1;
    while(lhs<=rhs){
        int mid = lhs + (rhs-lhs)/2;
        if(nums[mid]==target){
            return mid;
        }
        if(nums[mid]<=nums[rhs]){
            if(nums[mid]<target && target<=nums[rhs]){
                lhs = mid + 1;
            }else{
                rhs = mid - 1;
            }
        }else{
            if(nums[mid]>target && target>=nums[lhs]){
                rhs = mid - 1;
            }else{
                lhs = mid+1;
            }
        }
    }
    return -1;
}

int main(){
    vector<int> nums{3,5,1};
    int ans = search(nums,3);
    return 0;
}