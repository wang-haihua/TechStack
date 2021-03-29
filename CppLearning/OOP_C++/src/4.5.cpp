#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Complex{
    // private:
    //  	double real,img;
    public:
        double real,img;
    	Complex(double r=0.0, double i=0.0):real(r),img(i){}
    	friend ostream & operator<<(ostream & os, const Complex & c);
    	friend istream & operator>>(istream & is, const Complex & c);
};

ostream & operator<<(ostream & os, const Complex & c){
    os<<c.real<<'+'<<c.img<<'i';
    return os;
}

istream & operator>>(istream & is, Complex & c){
    string s;
    is >> s; // 将"a+bi"作为字符串读入，"a+bi"中间不能有空格
    int pos = s.find('+',0);
    string sTmp = s.substr(0,pos); // 分离出实部的字符串
    c.real = atof(sTmp.c_str()); // atof库函数能将const char*指针指向的内容转换为float
    sTmp = s.substr(pos+1,s.length()-pos-2);
    c.img = atof(sTmp.c_str());
    return is;
}

int main(){
    Complex c;
    int n;
    cin >> c >> n;
    cout << c <<','<<n;
    return 0;
}
