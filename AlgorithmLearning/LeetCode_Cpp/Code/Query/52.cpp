#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Code Content
class Solution {
public:

    void bactTracking(int n, int& ans, int k, vector<int>& queenPos){
        if(k==n){
            ans++;
            return;
        }

        for(int i=0;i<n;++i){
            int j=0;
            for(j;j<k;++j){
                if(queenPos[j]==i || (abs(k-j)==abs(queenPos[j]-i))){
                    break;
                }
            }
            if(j==k){
                queenPos[k] = i;
                bactTracking(n,ans,k+1,queenPos);
                queenPos[k] = 0;
            }
        }
    }

    int totalNQueens(int n) {
        int ans = 0;
        vector<int> queenPos(n);
        bactTracking(n,ans,0,queenPos);
        return ans;
    }
};

int main(){
    Solution s;
    int ans = s.totalNQueens(4);
    return 0;
}