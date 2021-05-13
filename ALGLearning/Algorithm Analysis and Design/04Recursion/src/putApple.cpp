#include<iostream>

using namespace std;

int putApple(int ap, int pl){
    if(ap < pl){
        return putApple(ap,ap);
    }else{
        if(ap == 0){
            return 1;
        }
        if(pl <= 0){
            return 0;
        }
    }

    return putApple(ap, pl-1) + putApple(ap-pl,pl);
}

int main(){
    int ap = 7, pl = 3;
    cout<<putApple(ap,pl)<<endl;
    return 0;
}