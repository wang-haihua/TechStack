#include<iostream>
using namespace std;

class Complex{
    public:
    	double real,img;
    	Complex(double r = 0.0, double i = 0.0):real(r),img(i){}
    	~Complex(){}
    	Complex operator-(const Complex & c);
};
// 运算符重载为成员函数
Complex Complex::operator-(const Complex & c){
    return Complex(real-c.real,img-c.img); // 返回一个无名临时对象
}

// 运算符重载为普通函数
Complex operator+(const Complex & c1, const Complex & c2){
    return Complex(c1.real+c2.real, c1.img+c2.img); // 返回一个无名临时对象
}

int main()
{
    Complex a(3,3),b(2,2),c;
    c = a + b; // operator+(a,b)
    cout<<c.real<<','<<c.img<<endl;
    cout<<(a-b).real<<','<<(a-b).img<<endl; // a.operator-(b)
    return 0;
}
