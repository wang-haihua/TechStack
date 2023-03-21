#include <iostream>
using namespace std;

template<class T, class Pred>
void map(T s, T e, T x, Pred op){
    for( ; s != e; ++s, ++x){
        *x = op(*s);
    }
}

int cube(int x){
    return x*x*x;
}
double square(double x){
    return x*x;
}

int main(){
    int a[5] = {1,2,3,4,5}, b[5];
    double c[5] = {1.1,2.2,3.3,4.4,5.5}, d[5];

    map(a,a+5,b,cube);
    for(int i=0; i<5; ++i){
        cout << b[i] << ' ';
    }
    cout << endl;

    map(a,a+5,b,square);
    for(int i=0; i<5; ++i){
        cout << b[i] << ' ';
    }
    cout << endl;
    
    map(c,c+5,d,square);
    for(int i=0; i<5; ++i){
        cout << d[i] << ' ';
    }
    cout << endl;

    return 0;
}
