## 运算符重载

### 运算符重载的基本概念

**运算符重载的应用场景**：运算符重载的需求是在对象运算中体现的，C++ 中希望通过对运算符的重载**扩展运算符的适用范围，使对象也能通过运算符进行运算**，这样可以使代码更加简洁和易理解。

**运算符重载的形式**：

```cpp
// ReturnType:返回值类型; OperatorType:运算符类型; ParamList:形参表
ReturnType operator OperatorType(ParamList)
{
    Function Body;
}
```

* 运算符重载实际上是函数重载：

  * 重载为成员函数，参数个数为运算符目数减一（被对象调用，对象作为一个被操作数）
  * 重载为普通函数，参数个数为运算符目数

* 运算符被多次重载时根据实参的类型决定函数的调用

* 对运算符的重载，应该尽可能保持运算符原始的运算特性仅仅扩展其可操作的数据对象

  运算符重载示例如下：

```cpp
class Complex{
    private:
    	double real,img;
    public:
    	Complex(double r=0.0, double i=0.0):real(r),img(i){}
    	~Complex(){}
    	Complex operator-(const Complex & c);
    	friend Complex operator+(const Complex & c1, const Complex & c2);
    	friend Complex operator+(double r,const Complex & c);
};
// 运算符重载为成员函数
Complex Complex::operator-(const Complex & c){
    return Complex(real-c.real,img-c.img); // 返回一个无名临时对象
}

// 运算符重载为普通函数
Complex operator+(const Complex & c1, const Complex & c2){
    return Complex(c1.real+c2.real, c1.img+c2.img); // 返回一个无名临时对象
}
e
// 被声明为友元函数，可以访问私有成员
Complex operator+(double r,const Complex & c){
    return Complex(real+r,img+c.img);
}


int main()
{
    Complex a(3,3),b(2,2),c,d;
    c = a + b; // operator+(a,b)
    cout<<c.real<<','<<c.img<<endl;
    d = 5 + a; // operator+(5,a)
    cout<<d.real<<','<<d.img<<endl;
    cout<<(a-b).real<<','<<(a-b).img<<endl; // a.operator-(b)
    return 0;
}
/* output:
5,5
8,3
1,1
*/
```

### 赋值运算符重载

**赋值运算符的应用场景**：对赋值运算符重载实现 `=` 两边的类型可以不匹配，值得注意的是，**赋值运算符 `=` 只能被重载为成员函数**

```cpp
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
    return 0;
}
```

**赋值中的浅拷贝和深拷贝**: [拷贝构造函数：深拷贝与浅拷贝](https://blog.csdn.net/qq_41773806/article/details/114699302) 

​	看如下示例，使用默认的赋值运算符 `S1 = S2;`，使用类中默认的赋值运算符，会将对象中的所有位于 stack 中的域进行相应的复制操作；同时，如果对象有位于 heap 上的域，则不会为目标对象分配 heap 上的空间，而只是让**目标对象指向源对象 heap 上的同一个地址**如下图所示。由于源对象和目标对象都指向 heap 的同一段内容，所以在对象调用析构函数的时候，就会连续两次释放 heap 上的那一块内存区域，从而导致程序异常。

<img src="D:\01BasicLearning\TechnicalRoute\CppLearning\OOP_C++\part04\浅拷贝和深拷贝.png" alt="浅拷贝和深拷贝" style="zoom:50%;" />

​	另外，如果执行 `S1 = "other"` ，根据上面的赋值运算符重载方法 S1 会指向新 new 的空间，同时将原始空间 delete 掉，这将导致赋值后的 S2 指向了一个已经被 delete 的空间导致程序存在隐患。为此对上述赋值运算符重载方法进行改进，**添加一个处理用对象赋值的成员函数**，并避免`s=s;`语句导致出错增加判断语句。

```cpp
String & String::operator=(const String & s){
    if(this == &s){
        return * this;
    }
    delete [] str;
    str = new char[strlen(s.str) + 1];
    strcpy(str,s.str);
    return * this;
}
```

​	值得注意的是，赋值运算符重载的返回值是`DataType &` 引用，这样可以保持赋值运算符传递的运算特点 `a = b = c;` 等价于 `a.operator=(b.operator=(c));`

**拷贝构造函数的需要**：和类中的默认赋值运算符一样，其默认的拷贝构造函数也存在同样的浅拷贝和深拷贝问题，为了避免浅拷贝导致指向同一空间的问题，使用同样的方法自定义拷贝构造函数。

```cpp
String(const String & s){
    str = new char[strlen(s.str)+1];
    strcpy(str,s.str);
}
```

### 流插入流提取运算符重载

**流插入运算符重载**：`cout` 是在 `iostream` 中定义的 `ostream` 类的对象，`<<` 能够作为流插入是在 `iostream` 中进行了重载，为了能够让 `<<` 能够连续插入形如 `cout << 5 << "this"` 重载函数的返回值是 `ostream &` 类型。

```cpp
// << 重载可以如下形式
ostream & operator<<(int n){
    // ... 输出代码块
    return * this;
}
ostream & operator<<(const char * s){
    // ... 输出代码块
    return * this;
}
```

​	当 `<<` 的操作数是对象时，需要对其进行重载，但是又不能重载成成员函数，因为`cout` 已经被定义在 `iostream` 头文件中，所以只能重载为普通函数，示例如下：

```cpp
class Student{
    public:
    	int age;
};

ostream & operator<<(ostream & o, const Student & s){
    o<<s.age;
    return o;
}

int main(){
    Student s;
    s.age = 5;
    cout<<s<<"years old"<<endl;
    return 0;
}
```

**流提取运算符重载：**`cin` 是在 `iostream` 中定义的 `istream` 类的对象，`>>` 能够作为流提取是在 `iostream` 中进行了重载，为了能够让 `>>` 能够连续提取内容重载函数的返回值是 `istream &` 类型。

**流插入流提取运算符重载示例**：c 是 Complex复数类的对象，现在希望让 `cout<<c;` 能够输出 c 的`a+bi` 的值，让 `cin>>c;` 能够从接盘接受 `a+bi`的输入，其中 `c.real = a; c.img = b;`

```cpp
class Complex{
    private:
    	double real,img;
    public:
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
    c.imag = atof(sTmp.c_str());
    return is;
}

int main(){
    Complex c;
    int n;
    cin >> c >> n;
    cout << c <<','<<n;
    return 0;
}
```

### 重载类型转换运算符

**类型转换运算符重载**：将对象转换为 `int float double` 等类型，一旦类中定义了类型转换运算符重载，在类型转换运算符出现处的对象都会被调用类型转换运算符重载函数进行类型转换。值得注意的是，类型转换运算符重载函数和构造函数相似没有返回值类型。

```cpp
class Complex{
    private:
    	double real,img;
    public:
    	Complex(double r=0.0,double i=0.0):real(r),img(i){}
    	operator double(){return real;}
};

int main(){
    Complex c(1.2,3.2);
    cout<<(double)c<<endl;
    double n = 2 + c; // 相当于 n = 2 + c.operator double()
    cout<<n<<endl;
    return 0;
}
/* output:
1.2
3.2
*/
```

### 自增自减运算符重载

**前置后置运算符的区分**：

​	自增 `++` 和自减 `--` 运算符有前置和后置之分，为了区分前置和后置运算符，C++ 规定：

* 前置运算符作为一元运算符重载：
  * 重载为成员函数 `DataType & operator++/--();`
  * 重载为普通函数 `DataType1 & operator++/--(DataType2);`
* 后置运算符作为二元运算符重载，**多写一个没用的参数**：
  * 重载为成员函数 `DataType  operator++/--(int);`
  * 重载为普通函数 `DataType1  operator++/--(DataType2,int);`

值得注意的是前置运算符重载函数的返回值类型是**引用**，而后置运算符重载函数的**对象**，`++a = 1;` 是成立的，然而 `a++ = 1;`是错误的后置返回的是临时对象。**不用产生临时对象**的前置运算符的效率在一定程度上优于后置运算符，为此在不影响结果的情况下，尽量使用前置运算符。

```cpp
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

Sample::Sample operator++(int k){
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
```

### Reference

[C++类对象的赋值与复制](https://blog.csdn.net/liitdar/article/details/81874541)