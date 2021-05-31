#include<iostream>
#include<vector>

using namespace std;

int maxSumR(vector<vector<int>> arr, int i, int j){
    if(i==arr.size()-1){
        return arr[i][j];
    }
    int x = maxSumR(arr,i+1,j);
    int y = maxSumR(arr,i+1,j+1);
    return max(x,y)+arr[i][j];
}

vector<vector<int>> maxSumRes(5,vector<int>(5,-1)); // 声明一个5行5列元素全为-1的二维数组
int maxSumStorage(vector<vector<int>> arr, int i, int j){
    // arr[i][j]的路径值已经被计算过
    if(maxSumRes[i][j] != -1){
        return maxSumRes[i][j];
    }
    // arr[i][j]的路径值没有被计算过，递归进行计算
    if(i == arr.size()-1){
        maxSumRes[i][j] = arr[i][j];
    }else{
        int x = maxSumStorage(arr,i+1,j);
        int y = maxSumStorage(arr,i+1,j+1);
        maxSumRes[i][j] = max(x,y) + arr[i][j];
    }
    return maxSumRes[i][j];
}

vector<vector<int>> maxSumRes2D(5,vector<int>(5,0)); // 声明一个5行5列元素全为-1的二维数组
int maxSum2D(vector<vector<int>> arr){
    for(int j = 0; j < arr[arr.size()-1].size();++j){
        maxSumRes2D[arr.size()-1][j] = arr[arr.size()-1][j];
    }
    for(int i = arr.size()-2;i>=0;--i){
        for(int j=0;j<=i;++j){
            maxSumRes2D[i][j] = max(maxSumRes2D[i+1][j],maxSumRes2D[i+1][j+1]) + arr[i][j];
        }
    }
    return maxSumRes2D[0][0];
}

vector<int> maxSumRes1D(5,0); 
int maxSum1D(vector<vector<int>> arr){
    for(int j = 0; j < arr[arr.size()-1].size();++j){
        maxSumRes1D[j] = arr[arr.size()-1][j];
    }
    for(int i = arr.size()-2;i>=0;--i){
        for(int j=0;j<=i;++j){
            maxSumRes1D[j] = max(maxSumRes1D[j],maxSumRes1D[j+1]) + arr[i][j];
        }
    }
    return maxSumRes1D[0];
}

int main(){
    vector<vector<int>> numTri(5);
    numTri[0].push_back(7);
    numTri[1].push_back(3);numTri[1].push_back(8);
    numTri[2].push_back(8);numTri[2].push_back(1);numTri[2].push_back(0);
    numTri[3].push_back(2);numTri[3].push_back(7);numTri[3].push_back(4);numTri[3].push_back(4);
    numTri[4].push_back(4);numTri[4].push_back(5);numTri[4].push_back(2);numTri[4].push_back(6);numTri[4].push_back(5);
    int res = maxSumR(numTri,0,0);
    cout << res << endl;
    int resS = maxSumStorage(numTri,0,0);
    cout << resS << endl;
    int res2D = maxSum2D(numTri);
    cout << res2D << endl;
    int res1D = maxSum1D(numTri);
    cout << res1D << endl;
    return 0;
}