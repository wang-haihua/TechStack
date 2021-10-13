#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    void handleStr(string& s){
        for(int i=0;i<s.length();++i){
            if(s[i]>='a' && s[i]<='z'){
                continue;
            }else if(s[i]>='A' && s[i]<='Z'){
                s[i] += 32;
            }else if(s[i] == ' '){
                s.erase(i,1);
            }else{
                s.erase(i,2);
            }
        }
    }

    bool isPalindrome(string s) {
        handleStr(s);
        int len = s.length();
        int lsh, rsh = len/2;
        if(len&1){
            lsh = rsh;
        }else{
            lsh = rsh-1;
        }
        while(lsh>=0 && rsh<len){
            if(s[lsh]!=s[rsh]){
                return false;
            }
            --lsh;
            ++rsh;
        }
        return true;
    }
};

int main(){
    string s = "A man, a plan, a canal: Panama";
    Solution so;
    so.isPalindrome(s);
    return 0;
}