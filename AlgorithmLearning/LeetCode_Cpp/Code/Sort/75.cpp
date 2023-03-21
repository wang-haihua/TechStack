#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Code Content
void sortColors(vector<int>& nums) {
    int lsh = 0, rsh = nums.size()-1;
    while(lsh<rsh){
        if(nums[lsh]==2){
            while(lsh<rsh&&nums[rsh]==2){
                --rsh;
            }
            swap(nums[lsh],nums[rsh]);
        }
        ++lsh;
    } 
    lsh = 0;
    while(lsh<rsh){
        if(nums[rsh]==0){
            while(lsh<rsh&&nums[lsh]==0){
                ++lsh;
            }
            swap(nums[rsh],nums[lsh]);
        }
        --rsh;
    }
}

int main(){
    vector<int> nums{2,0,2,1,1,0};
    sortColors(nums);
    for(auto num:nums){
        cout<<num<<',';
    }
    cout<<endl;
    return 0;
}