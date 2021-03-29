#include <iostream>
using namespace std;

class Base{
    public:
        void func1(){ func2(); } // void func1(){ this->func2(); }  this指针指向当前被调对象
        virtual void func2(){cout<< "Base func2 called!"<<endl;}
        virtual void hello(){cout<<"Base hello"<<endl;}
};

class Derived:public Base{
    public:  
        virtual void func2(){cout<< "Derived func2 called!"<<endl;}
        void hello(){cout<<"Derived hello"<<endl;}
        Derived(){hello();}
        ~Derived(){hello();}
};

int main(){
    Derived d;
    Base* pb = &d;
    pb->func1();
    return 0;
}