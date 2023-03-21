#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Code Content
bool search(vector<int>& nums, int target) {
    int lhs = 0, rhs = nums.size()-1;
    while(lhs<=rhs){
        int mid = lhs + (rhs - lhs)/2;
        if(nums[mid]==target){  
            return true;
        }
        if(nums[lhs]==nums[mid]){ // 如果出现相等情况，跳过
            ++lhs;
        }else if(nums[mid]<=nums[rhs]){
            if(target>nums[mid]&&target<=nums[rhs]){ // target在(mid,rhs]区间内
                lhs = mid + 1;
            }else{
                rhs = mid - 1;
            }
        }else{
            if(target<nums[mid]&&target>=nums[lhs]){ // target在[lhs,mid)区间内
                rhs = mid - 1;
            }else{
                lhs = mid + 1;
            }
        }
    }
    return false;
}

int main(){

    return 0;
}