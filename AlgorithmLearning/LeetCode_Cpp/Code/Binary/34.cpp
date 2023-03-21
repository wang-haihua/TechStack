#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> ans(2,-1);
    int lhs = 0, rhs = nums.size();
    while(lhs<rhs){
        int mid = lhs + (rhs-lhs)/2;
        if(target == nums[mid]){
            ans[1] = mid;
            lhs = mid+1;
        }else if(target > nums[mid]){
            lhs = mid + 1;
        }else{
            rhs = mid;
        }
    }
    lhs = 0, rhs = nums.size();
    while(lhs<rhs){
        int mid = lhs + (rhs-lhs)/2;
        if(target == nums[mid]){
            ans[0] = mid;
            rhs = mid;
        }else if(target > nums[mid]){
            lhs = mid + 1;
        }else{
            rhs = mid;
        }
    }
    return ans;
}

// 代码优化

int main(){

    return 0;
}