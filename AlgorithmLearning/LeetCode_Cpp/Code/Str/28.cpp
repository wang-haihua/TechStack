#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:

    void getNext(string needle, vector<int>& next){
        int head = -1;
        next[0] = -1;
        for(int tail=1;tail<needle.length();++tail){
            while(head>-1 && needle[head+1]!=needle[tail]){
                head = next[head];
            }
            if(needle[head+1]==needle[tail]){
                ++head;
            }
            next[tail] = head;
        }
    }

    int strStr(string haystack, string needle) {
        int cur = -1;
        int m = haystack.size(), n = needle.size();
        vector<int> next(n,-1);
        getNext(needle,next);
        for(int i=0;i<m;++i){
            while(cur>-1 && haystack[i]!=needle[cur+1]){
                cur = next[cur];
            }
            if(haystack[i]==needle[cur+1]){
                ++cur;
            }
            if(cur == n-1){
                return i - cur + 1;
            }
        }
        return -1;
    }
};

int main(){
    string haystack ="hello", needle="ll";
    Solution s;
    int res = s.strStr(haystack,needle);
    return 0;
}