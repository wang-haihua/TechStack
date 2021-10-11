#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> s;
        int len = temperatures.size();
        vector<int> ans(len);
        for(int i=0;i<len;++i){
            if(s.empty() || temperatures[s.top()] > temperatures[i]){
                s.push(i);
            }else if(temperatures[s.top()] < temperatures[i]){
                int pre = s.top();
                s.pop();
                ans[pre] = i - pre;
                s.push(i);
            }
        }
        while(!s.empty()){
            ans[s.top()] = 0;
            s.pop();
        }
        return ans;
    }
};

int main(){
    vector<int> t{73,74,75,71,69,72,76,73};
    Solution s;
    vector<int> ans = s.dailyTemperatures(t); 
    return 0;
}