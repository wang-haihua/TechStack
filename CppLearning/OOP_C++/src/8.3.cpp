#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class A{
    int v;
public:
    A(int n):v(n){};
    bool operator<(const A& a2) const{
        cout << v << "<" << a2.v << "?" << endl;
        return false;
    }
    bool operator==(const A& a2) const{
        cout << v << "==" << a2.v << "?" <<endl;
        return v == a2.v;
    }
};

int main(){
    /*
    vector<A> av;
    av.push_back(A(1)); av.push_back(A(2)); av.push_back(A(3)); av.push_back(A(4)); av.push_back(A(5));
    cout << binary_search(av.begin(),av.end(),A(9));
    */
    A a[] = {A(1),A(2),A(3),A(4),A(5)};
    cout << binary_search(a,a+4,A(9));
    return 0;
}