#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
#include<string>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        int ans = 0;
        for(int i=0;i<n;++i){
            unordered_set<char> hash;
            int j;
            for(j=i;j<n;++j){
                if(hash.find(s[j])!=hash.end()){
                    break;
                }
                hash.insert(s[i]);
            }
            ans = max(ans,j-i);
            hash.clear();
        }
        return ans;
    }
};

int main(){
    string s="abcabcbb";
    int ans = Solution().lengthOfLongestSubstring(s);
    return 0;
}