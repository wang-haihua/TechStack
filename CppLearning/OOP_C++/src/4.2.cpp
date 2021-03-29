#include<iostream>
#include<cstring>
using namespace std;

class String{
    private:
    	char * str;
    public:
    	String():str(new char[1]){str[0] = 0;}
    	~String(){delete [] str;}
    	const char * c_str(){return str;}
    	String & operator=(const char * s);
};

// 重载赋值运算符使得 String s; s = "hello"; 能够成立
String & String::operator=(const char * s){
    delete [] str; // 先清空当前对象的 str
    str = new char[strlen(s)+1]; // 申请能够存储字符串 s 的空间
    strcpy(str,s);
    return * this;
}

int main(){
    String s;
    s = "hello, world"; // 调用 s.operator=("hello,world")
    // String s2 = "hello"; 这里的等号是初始化不是赋值，会调用构造函数进行初始化，等价于 String s2("hello"); 如果没有定义这样的构造函数会导致程序出错
    cout<<s.c_str()<<endl;
    return 0;
}
