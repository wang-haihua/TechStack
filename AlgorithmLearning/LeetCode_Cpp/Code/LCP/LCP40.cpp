#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    
    bool isOuShu(int n){
        return n%2==0;
    }
    
    int maxmiumScore(vector<int>& cards, int cnt) {
        sort(cards.begin(),cards.end());
        reverse(cards.begin(),cards.end());
        int cardsLen = cards.size();
        vector<int> o;
        vector<int> j;
        for(int i=0;i<cardsLen;++i){
            if(isOuShu(cards[i])){
                if(o.empty()){
                    o.push_back(cards[i]);
                }else{
                    o.push_back(cards[i]+o.back());
                }
            }else{
                if(j.empty()){
                    j.push_back(cards[i]);
                }else{
                    j.push_back(cards[i]+j.back());
                }
            }
        }
        int sum = 0 , res = 0;
        if(o.size()>=cnt){
            res = o[cnt];
        }
        for(int i=1;i<j.size();i+=2){
            if(cnt-i>o.size()||cnt-i<=0){
                continue;
            }
            sum = j[i] + o[cnt-1-i];
            res = max(res,sum);
        }
        return res;
    }
};

int main(){
    vector<int> cards{1,2,8,9};
    Solution s;
    s.maxmiumScore(cards,3);
    return 0;
}