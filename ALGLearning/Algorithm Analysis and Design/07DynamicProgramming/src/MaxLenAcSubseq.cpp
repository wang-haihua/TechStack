#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int maxLen(vector<int> arr){
    vector<int> maxLenRes(arr.size(),1);
    for(int k=1;k<arr.size();++k){
        for(int i=0;i<k;++i){
            if(arr[k]>arr[i]){
                maxLenRes[k] = max(maxLenRes[k],maxLenRes[i]+1); // 以ak为终点的子序列的长度为已记录最大长度和新长度中的较大值
            }
        }
    }
    // 输出 maxLenRes 中的最大值
    vector<int>::iterator max = max_element(maxLenRes.begin(),maxLenRes.end());
    return *max;
}

int main(){
    int a[7] = {1,7,3,5,9,4,8};
    vector<int> arr(a,a+7);
    int maxLenAcsSubseq = maxLen(arr);
    cout << maxLenAcsSubseq << endl;
    return 0;
}