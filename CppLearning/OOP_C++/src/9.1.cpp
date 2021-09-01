#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class A{
public:
    int a; int b;
    A(int _a, int _b):a(_a), b(_b){}
    A(const A& obja){
        a = obja.a; b = obja.b;
    }
};

int main(){
    A a(1,2);
    A a2(a);
    return 0;
}