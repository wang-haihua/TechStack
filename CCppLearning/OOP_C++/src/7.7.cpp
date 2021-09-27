#include <iostream>
#include <string>
using namespace std;
template <class T1, class T2>
class Pair{
private:
    T1 key;
    T2 value;
public:
    Pair(T1 k, T2 v):key(k),value(v){}
    bool operator < (const Pair<T1, T2> & p) const;
    // 函数模板作为类模板友元，任意从函数模板生成的函数都是任意Pair模板类的友元
    template <class T3, class T4>
    friend ostream & operator<< (ostream& o, const Pair<T3, T4>& p);
};

template <class T1, class T2>
bool Pair<T1,T2>::operator< (const Pair<T1,T2>& p) const{
    return key < p.key;
}
template <class T3, class T4>
ostream& operator<< (ostream& o, const Pair<T3,T4>& p){
    o << "(" << p.key << "," << p.value << ")";
    return o;
}

int main(){
    Pair<string, int> student("Tom",14);
    Pair<int, double> obj(12, 4.32);
    cout << student << " " << obj;
    return 0;
}