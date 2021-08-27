#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Code Content
int singleNonDuplicate(vector<int>& nums) {
    int start = 0, end = nums.size()-1;
    while(start < end){
        int mid = start + (end - start)/2;
        bool flag = mid % 2 == 0; //通过判别奇偶性的改变，判断目标元素所在区间
        if(nums[mid]==nums[mid-1]){
            if(flag){
                end = mid-2;
            }else{
                start = mid + 1;
            }
        }else if(nums[mid]==nums[mid+1]){
            if(!flag){ // nums[mid]==nums[mid+1] 的情况下奇偶性判别与 nums[mid]==nums[mid-1] 相反
                end = mid-1;
            }else{
                start = mid + 2;
            }
        }else{
            return nums[mid]; 
        }
    }
    return nums[start]; // start == end 的情况下说明找到最后一个被检索的元素
}


int main(){

    return 0;
}