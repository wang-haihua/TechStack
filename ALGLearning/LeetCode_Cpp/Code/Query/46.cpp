#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    void backTracking(vector<int> nums, vector<int>& output, int level, vector<bool>& used, vector<vector<int>>& ans){
        if(level == nums.size()){
            ans.push_back(output);
            return;
        }
        
        for(int i=0;i<nums.size();++i){
            if(used[i]){
                continue;
            }
            used[i] = true;
            output.push_back(nums[i]);
            backTracking(nums,output,level+1,used,ans);
            used[i] = false;
            output.pop_back();
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        int len = nums.size();
        vector<vector<int>> ans;
        if(len==0){
            return ans;
        }
        vector<int> output;
        vector<bool> used(len,false);
        backTracking(nums,output,0,used,ans);
        return ans;
    }
};

int main(){
    vector<int> nums{1,2,3};
    Solution s;
    s.permute(nums);
}