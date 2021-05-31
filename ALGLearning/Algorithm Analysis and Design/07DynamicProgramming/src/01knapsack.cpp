#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> F(100,vector<int>(100,0));
int zoKnapsack(vector<int> w, vector<int> v, int num, int vol){
    for(int i=1;i<=num;++i){
        for(int j=1;j<=vol;++j){
            F[i][j] = F[i-1][j];
            if(j-w[i]>=0){
                F[i][j] = max(F[i-1][j],F[i-1][j-w[i]]+v[i]);
            }
        }
    }
    return F[num][vol];
}

int main(){
    vector<int> w{1,1,2,4,12};
    vector<int> v{1,1,5,5,20};
    int maxval = zoKnapsack(w,v,5,15);
    cout << maxval << endl;
    return 0;
}