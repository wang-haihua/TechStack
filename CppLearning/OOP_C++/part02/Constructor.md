## C++ 构造函数与析构函数

### 构造函数的基本概念

**构造函数**：

​	构造函数是类的一种特殊成员函数，它的名字**和类名相同**，可以有参数，但是**没有返回值**。类中定义的构造函数在**对象生成时**被调用，其作用是对对象初始化，进行成员变量赋值之类的操作。如果类中没有定义构造函数，编译器在编译过程中会为类生成一个默认的**无参**构造函数，并不进行任何操作。

​	构造函数的意义：简化了对象的初始化工作，有了构造函数就不用专门再写初始化函数，也不用担心在生成对象时忘记调用初始化函数。对象名也相当于一个指针，如果没被初始化就使用将导致程序出错。

```cpp
class Complex{
    private:
    	double real;
    	double img;
    public:
    	// 一个类可以声明多个重载的构造函数，参数个数或参数类型不同
    	Complex(double r){real = r;}
    	Complex(double real_, double img_ = 0);
    	Complex(Complex c1, Complex c2);
};

Complex::Complex(double real_, double img_){
    real = real_;
    img = img_;
}

Complex::Complex(Complex c1, Complex c2){
    real = c1.real + c2.real;
    img = c1.img + c2.img;
}

int main(){
    Complex c1; // 这种声明方式是错误的，应为定义的构造函数为 Complex(r,i); 缺少构造函数参数
    Complex* pc = new Complex; // 也是错误的，没有参数
    Complex c2(2);
    Complex* pc2 = new Complex(2,3);
    return 0;
}
```

**构造函数在数组中的使用**：

```c++
class Sample{
    private:
    	int x;
    	int y;
    public:
    	Sample(){cout<<"Constructor 1 called"<<endl;}
    	Sample(int x_){x = x_; y = 0; cout<<"Constructor 2 called"<<endl;}
    	Sample(int x_, int y_){x = x_; y = y_; cout<<"Constructor 3 called"<<endl;}
};

int main(){
    Sample array1[2];
    cout<<"step1"<<endl;
    Sample array2[2] = {4,5};
    cout<<"step2"<<endl;
    Sample array3[2] = {3}; // array3[0]用Sample(3)初始化，array3[1]用Sample()初始化
    cout<<"step3"<<endl;
    Sample array4[3] = {3, Sample(4,5)};
    cout<<"step4"<<endl;
    Sample* array4 = new Sample[2];
    cout<<"step5"<<endl;
    Sample* parray[3] = {new Sample(3), new Sample(4,5)}; // 注意和第18行代码对比，parray是指针，没有进行初始化就是空指针不会调用构造函数
    delete [] parray;
    delete [] array4; // 被new出来的对象一定要用delete释放
    return 0;
}
/* output:
Constructor 1 called
Constructor 1 called
step1
Constructor 2 called
Constructor 2 called
step2
Constructor 2 called
Constructor 1 called
step3
Constructor 2 called
Constructor 3 called
Constructor 1 called
step4
Constructor 1 called
Constructor 1 called
step5
Constructor 2 called
Constructor 3 called
*/
```

### 拷贝构造函数

**拷贝构造函数**：

​	拷贝构造函数**有且仅有一个**同类对象引用的参数 （参数只能是引用不能是对象），形如 `Object::Object(const Object &)` 使用常量对象作为参数更安全，当然也可以不用 `const`。如果类中没有定义拷贝构造函数，编译器会在编译过程中为类生成默认的拷贝构造函数，其功能就是完成拷贝功能。

```c++
class Complex{
    private:
    	double real;
    	double img;
    public:
    	Complex(int r, int i){real = r; img = i;}
    	Complex(const Complex & c);
};

Complex::Complex(const Complex & c){
    real = c.real;
    img = c.img;
    cout<<"Copy Constructor called"<<endl;
}

int main(){
    Complex c1(1,2);
    Complex c2(c1);
}
```

**拷贝构造函数起作用的情况**

* **用对象进行初始化**：当用一个对象去初始化同类的另一个对象时，会引发拷贝构造函数被调用。

  ```c++
  Complex c2(c1);
  Complex c2 = c1; //调用拷贝构造函数
  ```

  ​	上述示例中的两条语句都会引发拷贝构造函数的调用，这两条语句是等价的，都用以初始化 c2。值得注意的是，第二条语句是初始化语句，不是赋值语句。赋值语句的等号左边通常是一个早**已有定义**的变量，赋值语句不会引发复制构造函数的调用，示例如下：

  ```c++
  Complex c1(1,2);
  Complex c2;
  c2 = c1; //赋值语句
  ```

* **对象作为函数形参**：如果函数 F 的一个参数是类 A 的对象，那么当 F 被调用时，类 A 的拷贝构造函数将被调用。换句话说，作为形参的对象是用拷贝构造函数初始化的，而且调用拷贝构造函数对其进行初始化的参数就是调用函数时所给的实参。

* **对象作为函数返回值**：如果函数的返冋值是类 A 的对象，则函数返冋时，类 A 的拷贝构造函数被调用。换言之，作为函数返回值的对象是用拷贝构造函数初始化的，而调用拷贝构造函数时的实参，就是 return 语句所返回的对象。

  ```c++
  class A{
      public:
      	int x;
      	A(int n){x=n;}
      	A(const A & a){
              x = a.x; // 这个语句说明，拷贝构造函数的实参和形参的值不一定一样，这取决于该类的拷贝构造函数的定义方式(x = 100;)
              cout<<"Copy construct called"<<endl;
          }
  };
  
  void F(A a){ // a做为形参，通过拷贝构造函数进行初始化
      cout<<a.x<<endl;
  }
  // 对象形参常引用参数的使用:优点在于减少了生成形参对象是调用拷贝构造函数的开销，如果需要保证实参的值不被改变加上 const
  void F(const A & a){
      cout<<a.x<<endl;
  }
  
  A Func(){
      A b(2);
      return b; // b作为返回值，通过拷贝构造函数进行初始化
  }
  
  int main(){
      A a1(1);
      F(a1); // a1作为拷贝构造函数的实参
      cout << Func().v << endl;
      return 0;
  }
  ```

**深拷贝和浅拷贝**：

* 浅拷贝：又称值拷贝，将源对象的值拷贝到目标对象中去，本质上来说源对象和目标对象共用一份实体，只是所引用的变量名不同，地址其实还是相同的。（问题：浅拷贝和对象引用的区别是什么？）
* 深拷贝：深拷贝的时候先开辟出和源对象大小一样的空间，然后将源对象里的内容拷贝到目标对象中去，这样两个指针就指向了不同的内存位置。
* 深拷贝和浅拷贝可以简单理解为：如果一个类拥有资源，当这个类的对象发生复制过程的时候，资源重新分配，这个过程就是深拷贝，反之，没有重新分配资源，就是浅拷贝。

### 类型转换构造函数

**类型转换构造函数**：用途在于自动将其他类型的数据对象转换为该类对象。类型转化构造函数和拷贝构造函数类似，**只有一个参数**，但是其参数不是该类对象。在需要的时候，编译系统在编译过程中自动调用转换构造函数，建立一个无名的临时对象。

```c++
class Complex(){
    private:
    	double real,img;
    public:
    	Complex(double r, double i){
            real = r;
            img = i;
        }
    	Complex(int n){
            real = n;
            img = 0;
            cout << "Int Constructor called"<<endl;
        }
    	getReal(){return real;}
    	getImg(){return img;}
};

int main(){
    Complex c1(1,2);
    c1 = 3; // 调用类型构造函数，将3转换一个临时Complex对象
    cout << c1.getReal() << c1.getImg() << endl;
    return 0;
}
/* output:
3 0
*/
```

### 析构函数

**析构函数**：

​	析构函数与构造函数对应，在对象生命周期结束时被自动调用，析构函数的作用是在对象消亡前做类似释放内存空间等善后工作。其名字和类目相同，在前面加 `~` ，没有参数和返回值，**一个类最多只有一个析构函数**。如果类中没有定义析构函数，编译器在编译过程中会生成缺省析构函数，并不进行任何操作。 

```c++
class String{
    private:
    	char* p;
    public:
    	String(){
            p = new char[10]; // new 申请动态内存空间
        }
    	~String();
};
String::~String(){
    delete [] p; // delete 释放动态内存空间
}
```

**析构函数在数组中的使用**：对象数组生命周期结束时，对象数组中的每个元素的析构函数都会被调用。

**析构函数与 delete** ：被 new 出来的对象一定要用 delete 释放，否则不会调用析构函数去释放对象；如果 new 的是一个对象数组，那么使用 `delete []` 释放，如果只使用 delete ，那么只会调用一次析构函数释放一个对象。

**构造函数和析构函数的调用时机**：值得注意的是，对象作为函数形参和返回值均会调用拷贝构造函数产生临时对象，那么这些对象在函数调用完成之后会自动调用析构函数释放资源。

```c++
class Sample{
    private:
    	int x;
    public:
    	Sample(int n){x=n; cout<<x<<"constructor called"<<endl;}
    	~Sample(){cout<<x<<"destructor called"<<endl;}
};

Sample s1(1); // 全局变量，调用构造函数 

void F(){
    static Sample s2(2); // 静态局部变量在函数调用结束时不会消亡，整个程序执行完毕之和才会消亡
    Sample s3(3);
    cout << "F called" << endl;
}

int main(){
    Sample s4(4); 
    s4 = 6; // 类型转换构造函数参数临时对象 
    cout<<"main"<<endl;
    if(true){
        Sample s5(5); // 局部变量在生命周期结束后调用析构
    }
    F();
    cout<<"main end"<<endl;
    return 0;
}

/* output:
1 constructor called
4 constructor called
6 constructor called
6 destructor called
main
5 constructor called
5 destructor called
2 constructor called
3 constructor called
F called
3 destructor called
main end
6 destructor called (s4)
2 destructor called (static)
1 destructor called (global)
*/
```

​	值得注意的是，构造函数只负责初始化工作不负责内存空间分配，析构函数不负责内存空间回收；将对象比作房子，入住之前调用构造函数进行**装修**，拆迁之前调用析构函数**搬东西**。

### Reference

[拷贝构造函数详解](http://c.biancheng.net/view/151.html)

[深拷贝于浅拷贝](https://www.cnblogs.com/cxq0017/p/10617313.html)