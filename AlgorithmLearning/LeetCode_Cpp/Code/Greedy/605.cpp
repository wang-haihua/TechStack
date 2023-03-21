#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Code Content
bool canPlaceFlowers(vector<int>& flowerbed, int n) {
    if(n==0){
        return true;
    }
    int len = flowerbed.size();
    if(1==len&&flowerbed[0]==0){
        return true;
    }

    for(int i=0;i<len-1;++i){
        if(flowerbed[i]==1){
            continue;
        }else if(flowerbed[i]==0){
        if(i>1&&flowerbed[i-1]==0&&flowerbed[i+1]==0){
                --n;
                flowerbed[i] = 1;
            }else if(i==1&&flowerbed[0]==0){
                    --n;
                flowerbed[0] = 1;               
            }
        if(i==len-2&&flowerbed[len-2]==0&&flowerbed[len-1]==0){
            --n;
            flowerbed[len-1] = 1;
        }
        }
    }
    if(n<=0){
        return true;
    }else{
        return false;
    }
}

// 代码优化
bool canPlaceFlowers_v2(vector<int>& flowerbed, int n) {\
    int len = flowerbed.size();
    int count = 0;
    for(int i=0;i<len;++i){
        // 从左到右，能放就放，贪心策略
        if(flowerbed[i]==0&&(0==i||flowerbed[i-1]==0)&&(len-1==i||flowerbed[i+1]==0)){
            count++;
            flowerbed[i]=1;
        }
    }
    return count >= n;
}

int main(){
    cout << "input flowerbed len and elem:"<<endl;
    int len;
    cin>>len;
    std::vector<int> flowerbed;
    for(int i=0;i<len;++i){
        int elem;
        cin>>elem;
        flowerbed.push_back(elem);
    }
    cout << "input n:" << endl;
    int n;
    cin>>n;
    bool ans = canPlaceFlowers(flowerbed,n);
    return 0;
}