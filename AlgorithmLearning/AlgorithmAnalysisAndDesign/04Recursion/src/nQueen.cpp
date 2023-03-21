#include<iostream>
#include<vector>
using namespace std;

int n = 8;
vector<int> queenPos(100);

void nQueen(int k){
   // 第 n 个皇后放入完毕，输出一种摆放方案
   if(k == n){
       for(int i=0; i<n; ++i){
           cout << queenPos[i]+1 << ' ';
       }
       cout << endl;
       return;
   } 

   // 放入第 k 个皇后
   for(int i=0; i<n; ++i){
       // 判断放入第 k 个皇后的位置和之前 k-1 个皇后的位置是否冲突
       int j = 0;
       for(j; j<k; ++j){
           // 任意两个皇后棋子都不能处于同一行、同一列或同一斜线上
           if(i == queenPos[j] || abs(k-j) == abs(queenPos[j]-i)){
               break;
           }
       }
       if(j == k){
           queenPos[k] = i;
           nQueen(k+1);
       }
   }
}

int main(){
    nQueen(0);
    return 0;
}

