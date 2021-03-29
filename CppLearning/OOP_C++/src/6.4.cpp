#include <iostream>
using namespace std;
class A
{
public:
    int i;
    virtual void func() {cout << "A func" <<endl;}
    virtual void func2() {}
};
class B : public A
{
    int j;
    void func() {cout << "B func" <<endl;}
};
int main()
{
    cout << sizeof(A) << ", " << sizeof(B) << endl;  //输出 8,12 都多出4个字节存虚函数表地址
    A* pa = new B();
    pa->func();
    A a;
    long long * p1 = (long long *)& a; // 取对象 a 的前 8 个字节即虚函数表地址存储位置
    long long * p2 = (long long *) pa; 
    * p2 = * p1; // 将虚函数表地址互换
    pa->func(); // pa 的虚函数表地址变成了 a 的
    return 0;
}