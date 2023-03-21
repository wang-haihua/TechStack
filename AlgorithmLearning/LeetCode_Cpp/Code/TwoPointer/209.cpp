#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int len = nums.size();
        int minlen = 0x3f3f3f3f;
        for(int i=0;i<len;i++){
           int slow = i;
           int fast = slow+1;
           int sum = nums[slow];
           while(sum<target && fast<len){
               sum+= nums[fast++];
           } 
           if(sum<target && fast==len) continue;
           int tmplen = fast-slow;
           if(tmplen<minlen){
               minlen = tmplen;
           }
        }
        if(minlen == 0x3f3f3f3f) minlen = 0;
        return minlen;
    }
};

int main(){
    int target;
    cin>>target;
    vector<int> nums;
    cout<<target;
    int elem;
    while(cin>>elem&&elem!=0){
        nums.push_back(elem);
    }
    Solution s;
    int res = s.minSubArrayLen(target,nums);
    cout << res << endl;
    return 0;
}