#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

string findLongestWord(string s, vector<string>& dictionary) {
    vector<int> sCnt(128,0);
    for(int i=0;i<s.size();++i){
        sCnt[s[i]]++;
    }
    string ans = "";
    for(int i=0;i<dictionary.size();++i){
        int maxLen = 0;
        bool flag = true;
        vector<int> tmpCnt(sCnt);
        for(int j=0;j<dictionary[i].size();++j){
            tmpCnt[dictionary[i][j]]-=1;
            if(tmpCnt[dictionary[i][j]]>=0){
                continue;
            }else{
                flag = false;
                break;
            }
        }
        if(flag&&dictionary[i].size()>ans.size()){
            ans = dictionary[i];
        }
    }
    return ans;
}

int main(){
    string s = "abpcplea";
    vector<string> dictionary{"ale","apple","monkey","plea"};
    string ans = findLongestWord(s,dictionary);
    return 0;
}