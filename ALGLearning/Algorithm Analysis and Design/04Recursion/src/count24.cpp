#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
vector<double> termArr(5);
// 浮点数相等比较
bool isEqual(double param1, double param2){
    return fabs(param1-param2) < 0;
}

bool count24(vector<double>& term, int n){
    // 边界条件，一个数算 24
    if(n == 1){
        if(isEqual(termArr[0],24)){
            return true;
        }else{
            return false;
        }
    }

    // 算两个数
    vector<double> tempArr(5);
    for(int i=0; i<n-1; ++i){
        for(int j=i+1; j<n; ++j){
            // 将剩下的数放到 tempArr中
            int m = 0;
            for(int k = 0; k < n-2; ++k){
                if(k !=i && k != j){
                    tempArr[m++] = termArr[k];
                }
            }
            // 遍历所有两个数的运算组合, 将运算结果添加到 tempArr 中
            tempArr[m] = termArr[i] + termArr[j];
            if(count24(tempArr,m+1)){
                return true;
            }
            tempArr[m] = termArr[i] - termArr[j];
            if(count24(tempArr,m+1)){
                return true;
            }
            tempArr[m] = termArr[j] - termArr[i];
            if(count24(tempArr,m+1)){
                return true;
            }
            tempArr[m] = termArr[j] * termArr[i];
            if(count24(tempArr,m+1)){
                return true;
            }
            if(!isEqual(tempArr[j],0)){
                tempArr[m] = termArr[i] / termArr[j];
                if(count24(tempArr,m+1)){
                    return true;
                }
            }
            if(!isEqual(tempArr[i],0)){
                tempArr[m] = termArr[j] / termArr[i];
                if(count24(tempArr,m+1)){
                    return true;
                }
            }
        }
    }
}

int main(){
    termArr = {5,5,5,1};
    if(count24(termArr,4)){
        cout << "Yes" << endl;
    }else{
        cout << "No" << endl;
    }
    return 0;
}