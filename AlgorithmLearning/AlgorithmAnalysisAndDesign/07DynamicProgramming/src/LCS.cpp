#include<iostream>
#include<string>
#include<vector>

using namespace std;

int lcs(string s1,string s2){
    vector<vector<int>> maxLen(s1.length()+1,vector<int>(s2.length()+1));
    // s1 或 s2 为空串的情况下两者的公共子序列为 0
    /*
    for(int i=0;i<s1.length();++i){
        maxLen[i][0] = 0;
    }
    for(int j=0;j<s2.length();++j){
        maxLen[0][j] = 0;
    }
    */
    // s1,s2 均为非空
    for(int i=1;i<=s1.length();++i){
        for(int j=1;j<=s2.length();++j){
            if(s1[i-1]==s2[j-1]){
                maxLen[i][j] = maxLen[i-1][j-1] + 1;
            }else{
                maxLen[i][j] = max(maxLen[i][j-1],maxLen[i-1][j]);
            }
        }
    }
    return maxLen[s1.length()][s2.length()];
}

int main(){
    string s1 = "abcfbc";
    string s2 = "abfcab";
    int maxlen = lcs(s1,s2);
    cout << maxlen << endl;
    return 0;   
}