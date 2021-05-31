#include<iostream>
#include<vector>

using namespace std;

int simpleKnapRcu(vector<int> arr, int w, int k){
    if(w == 0) return 1;
    if(k < 0) return 0;
    return simpleKnapRcu(arr,w,k-1)+simpleKnapRcu(arr,w-arr[k],k-1);
}

int simpleKnapDyn(vector<int> arr, int weight, int num){
    vector<vector<int>> ways(weight+1,vector<int>(num+1));
    for(int i=1;i<num+1;++i){
        ways[0][i] = 1;
    }
    ways[0][0] = 1;
    for(int w=1; w<=weight; ++w){
        for(int k=1; k<=num; ++k){
            ways[w][k] = ways[w][k-1];
            if(w-arr[k]>=0){ // arr[k] 输入数组索引要与k值一致
                ways[w][k] += ways[w-arr[k]][k-1];
            }
        }
    }
    return ways[weight][num];
}


int main(){
    int a[3] = {20,20,20};
    vector<int> arr(a,a+3);
    int ways = simpleKnapRcu(arr,40,2);
    cout << ways << endl;
    int a2[4] = {-1,20,20,20};
    vector<int> arr2(a2,a2+4);
    int ways2 = simpleKnapDyn(arr2,40,3);
    cout << ways2 << endl; 
    return 0;
}