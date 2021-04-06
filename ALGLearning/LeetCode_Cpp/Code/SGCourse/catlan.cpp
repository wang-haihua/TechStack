#include <iostream>
using namespace std;

int ctl(int i, int j){
    if ( 1 == i && 1 == j){
        return 1;
    }
    if(i<j && i > 1 && j > 1){
        return (ctl(i-1, j) + ctl(i, j-1));
    }
    if(i == j){
        return (ctl(i-1,j));
    }
    if(i == 1){
        return(ctl(i,j-1));
    }

    return (0);
}

int main(){
    cout << ctl(4,4) <<endl;
}