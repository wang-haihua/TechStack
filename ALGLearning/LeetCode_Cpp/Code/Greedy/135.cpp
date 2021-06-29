#include<iostream>
#include<vector>
#include<numeric>
using  namespace std;

int candy(vector<int>& ratings) {
    int len = ratings.size();
    if(len < 2){
        return len;
    }
    vector<int> num(len,1);
    for(int i=1;i<len;++i){
        if(ratings[i]>ratings[i-1]){
            num[i] = num[i-1]+1;
        }
    }
    for(int i=len-2;i>=0;--i){
        if(ratings[i]>ratings[i+1]){
            num[i] = max(num[i],num[i+1]+1);
        }
    }
    return accumulate(num.begin(),num.end(),0); // STL 快捷数组求和
}