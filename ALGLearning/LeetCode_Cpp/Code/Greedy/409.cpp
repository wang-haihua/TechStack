#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

//Code Content
int longestPalindrome(string s) {
    vector<int> cnt(256,0);
    for(int i = 0;i<s.size();++i){
        cnt[s[i]]+=1;
    }
    bool flag = true;
    int ans = 0;
    for(int i=0;i<cnt.size();++i){
        if(cnt[i]!=0){
            if((cnt[i]&1)==0){ // 比较运算符优先级高于位运算符
                ans+=cnt[i];
            }else{
                ans+=cnt[i]-1;
                flag = false;
            }
        }
    }
    return flag ? ans : ans+1;
}


int main(){
    string s="abccccdd";
    int ans = longestPalindrome(s);

    return 0;
}