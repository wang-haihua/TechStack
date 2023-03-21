#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int mySqrt(int x) {
    if(x==0) return x;
    int lhs = 0, rhs = x;
    while(lhs<rhs){
        int mid = lhs+(rhs-lhs)/2;
        int tmp = x / mid;
        if(tmp == mid){
            return tmp;
        }else if(tmp < mid){
            lhs = tmp;
        }else{
            rhs = tmp;
        }
    }
    return lhs;
}

int mySqrt2(int x){
    long a = x;
    while(a*a > x){
        a = (a+x/a)/2;
    }
    return a;
}

int main(){

    int x = 8;
    int ans = mySqrt2(x);
    return 0;
}