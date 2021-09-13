#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Code Content
class Solution {
public:

    void backTracking(int n, int k, int begin, vector<int>& output, vector<bool>& used, vector<vector<int>>& ans){
        if(output.size() == k){
            ans.push_back(output);
            return;
        }
        for(int i=begin;i<n;++i){ // 关键在于剪枝，i=begin
            if(used[i]){
                continue;
            }
            used[i] = true;
            output.push_back(i+1);
            backTracking(n,k,i+1,output,used,ans); // begin = i+1
            used[i] = false;
            output.pop_back();
        }
    }

    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        vector<int> output;
        vector<bool> used(n,false);
        backTracking(n,k,0,output,used,ans);
        return ans;
    }
};

int main(){
    Solution s;
    s.combine(4,2);
    return 0;
}