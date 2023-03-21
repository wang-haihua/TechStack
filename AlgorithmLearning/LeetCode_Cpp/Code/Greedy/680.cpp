#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

//Code Content
bool validPalindrome(string s) {
    vector<int> cnt(256,0);
    for(int i=0;i<s.size();++i){
        cnt[s[i]]+=1;
    }
    int oddCnt = 0;
    for(int i=0;i<cnt.size();++i){
        if(cnt[i]!=0){
            if((cnt[i]&1)!=0){
                oddCnt+=1;
            }
        }
    }
    return oddCnt<=1;
}

int main(){
    string s="abca";
    bool ans = validPalindrome(s);

    return 0;
}