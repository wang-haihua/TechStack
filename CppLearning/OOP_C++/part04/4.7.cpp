#include <iostream>

using namespace std;

class Sample{
private:
    int n;
public:
    Sample(int i=0):n(i){}
    Sample & operator++();
    Sample operator++(int);
    friend Sample & operator--(Sample & s);
    friend Sample operator--(Sample & s, int);
    operator int(){return n;}
};

Sample & Sample::operator++(){
    ++n;
    return * this;
}

Sample::Sample operator++(int){
    Sample tmp(*this); // 记录修改前的对象
    n++;
    return tmp; // 返回修改后的对象
}

Sample & operator--(Sample & s){
    s.n--;
    return s;
}

Sample operator--(Sample & s, int){
    Sample tmp(s);
    s.n--;
    return tmp;
}
