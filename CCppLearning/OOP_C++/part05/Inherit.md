## C++ 继承

### 继承和派生的概念

**继承**：在定义一个新的类 B 时，如果该类与某个已有的类 A 相似，指的是 B 拥有 A 的全部特点，在属性上 A 是 B 的子集；那么就可以把 A 作为一个**基类**，而把 B 作为基类的一个**派生类**也称为**子类**。

**派生类**：派生类是通过对基类进行修改和扩充得到的。在派生类中，继承了基类的全部成员函数和成员变量，不论是 `private, protected , public`，但是在派生类的各成员函数中，仍旧不能直接访问基类中的 `private` 成员；除此之外派生类还可以扩充新的成员变量和成员函数。派生类被定义之后，可以独立使用，不依赖于基类。

**派生类的写法**：

```cpp
class SubClassName:public BaseClassName
{ 
    // class body 
};
```

**派生类对象的内存空间**：派生类对象占用的内存空间等于基类对象占用的内存空间，再加上自身成员变量所占用的内存空间。**在派生类对象中包含这基类对象**，而且基类对象的存储位置位于派生类对象自身成员变量之前。

**覆盖**：派生类可以定义一个和基类成员同名的成员，这种机制称为覆盖。在派生类中访问由基类定义的同名成员时，要使用作用域符号 `ClassName::Member` ；在派生类中同名成员没有使用作用域符号 `::` 的缺省情况时，访问的是派生类自身定义的成员。

**派生类的构造函数**：

​	和封闭类类似，派生类的构造函数也使用参数表的形式进行初始化，详细内容请参考 [C++ 类和对象提高：成员对象和封闭类](https://blog.csdn.net/qq_41773806/article/details/114823700) 。

​	派生类的构造函数执行顺序和封闭类也类似，在创建派生类的对象时，需要先调用基类的构造函数初始化派生类从基类继承来的成员，再调用自身的构造函数初始化自身成员变量。同理，在派生类对象消亡时，派生类的析构函数总是先于基类析构函数被调用。如果派生类包含成员对象，成员对象的构造函数后于基类构造函数调用，先于派生类自身构造函数调用；析构函数反之。

```cpp
class Student{
    private:
    	string name;
    	string id;
    	char gender;
    	int age;
    public:
    	Student(const string & name_, const string & id_, char gender_, int age_){
            name = name_;
            id = id_;
            gender = gender_;
            age = age_;
        }
    	~Student(){cout<<"base class destructor called"<<endl;}
    	void printInfo(){
            cout<<"name:"<<name<<endl<<"id:"<<id<<endl<<"gender:"<<gender<<endl<<"age:"<<age<<endl;
        }
    	void setInfo(const string & name_, const string & id_, char gender_, int age_){
            name = name_;
            id = id_;
            gender = gender_;
            age = age_;
        } // 基类的成员变量是 private 的，派生类无法直接访问，通过成员函数隐藏
    	string getName(){
            return name;
        }
};

class UnderStudent:public Student{
    private:
    	string department;
    public:
    	UnderStudent(const string & name_, const string & id_, char gender_, int age_, const string & department_):Student(name_, id_, gender_, age_){
            department = department_;
        } // 派生类的构造函数使用参数表进行初始化
    	~UnderStudent(){cout<<"sub class destructor called"<<endl;}
    	void qulifiedForBaoYan(){
            cout<<"QulifiedForBaoYan"<<endl;
        }
    	void printInfo(){
            Student::printInfo(); //调用基类成员函数
            cout<<"department:"<<department<<endl;
        }
    	void setInfo(const string & name_, const string & id_, char gender_, int age_, const string & department_){
            Student::setInfo(name_, id_, gender_, age_); //调用基类成员函数
            department = department_;
        }
};
```

### 类之间的关系

**继承关系**：

​	B 是 A 的派生类，那么 B 的对象也**是** A 的对象，则 A 和 B 是继承关系。

​	例如：Man 类与 Woman 类和 Human 类都是继承关系

**复合关系**：

​	D 的对象是 C 的对象的固有属性或组成部分，即 C 是封闭类其成员对象是 D，则 C 和 D 是复合关系。

​	例如：Point 类和 Circle 类是复合关系，圆不是点，所以圆心 Point 作为 Circle 类的成员对象。

### 公有继承的赋值兼容

public **继承的赋值兼容规则**：如果继承方式为 private 或 protected 则下述规则不成立

* 派生类对象可以赋值给基类对象
* 派生类对象可以初始化基类引用
* 派生类对象的地址可以赋值给基类指针

**间接基类**：派生类在声明时只需要列出其**直接基类**，并自动沿着类的层次关系继承其他间接基类；在派生类中也继承了间接基类的所有成员。

```cpp
class Base{
    public:
    	int base;
    	Base(int base_):base(base_){cout<<"base constructor called"<<endl;}
    	~Base(){cout<<"base destructor called"<<endl;}
};

class Derived:public Base{
    public:
    	Derived(int base_):Base(base_){cout<<"derived constructor called"<<endl;}
    	~Derived(){cout<<"derived destructor called"<<endl;}
};

class MoreDerived:public Derived{
    public:
    	MoreDerived(int base_):Derived(base_){cout<<"moreDerived constructor called"<<endl;} // 间接基类的初始化
    	~MoreDerived(){cout<<"moreDerived destructor called"<<endl;}
};

int main(){
    MoreDerived obj(4);
    return 0;
}
/* output:
base constructor called
derived constructor called
moreDerived constructor called
moreDerived destructor called
derived destructor called
base destructor called
*/
```

