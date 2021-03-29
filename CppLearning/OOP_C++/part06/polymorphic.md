## C++ 多态

### 虚函数和多态的概念

**虚函数**：

* 在类的定义中，有 `virtual` 关键字的成员函数就是虚函数，形如：

  ```cpp
  class Base{
      public:
      	virtual int get();  
  };
  int Base::get(){} // virtual 关键字只需要在类内声明
  
  class Derived:public Base{
      public:
      	virtual int get();
  };
  int Derived::get(){}
  
  int main(){
      Derived de;
      Base b;
      Base* p = & de;
      Base& r = de;
      p->get(); // 多态 调用派生类虚函数
      r.get();
      p = & b;
      p->get(); // 多态 调用ji类虚函数
      return 0;
  }
  ```

* `virtual` 关键字只用在类定义内的函数声明中使用，在类外写函数体时不用写 `virtual` 关键字。

* 构造函数和静态成员函数不能是虚函数

* 虚函数和普通函数的区别在于：虚函数能够参与多态，而普通函数不可以

* 在非构造函数和非析构函数的**成员函数中调用虚函数**，就是多态。反之在构造函数和析构函数中调用虚函数，不是多态；因为在编译时就能确定被调用的虚函数是基类还是派生类的，不用等到运行才确定。**为什么构造函数中调用函数不是多态？**因为派生类调用构造函数期间会先调用基类构造函数，如果基类构造函数中存在多态并调用了派生类的虚函数，这时派生类还未调用构造函数进行初始化，这将导致错误的运行结果。

* 在派生类中和基类中虚函数同名同参数表的函数，不加 `virtual` 关键字也自动成为虚函数

```cpp
#include <iostream>
using namespace std;

class Base{
    public:
        void func1(){ func2(); } // void func1(){ this->func2(); }  this指针指向当前被调对象 多态
        virtual void func2(){cout<< "Base func2 called!"<<endl;}
        virtual void hello(){cout<<"Base hello"<<endl;}
};

class Derived:public Base{
    public:  
        virtual void func2(){cout<< "Derived func2 called!"<<endl;}
        void hello(){cout<<"Derived hello"<<endl;}
        Derived(){hello();} // 不是多态
        ~Derived(){hello();}
};

int main(){
    Derived d;
    Base* pb = &d;
    pb->func1();
    return 0;
}
```

**多态的表现形式**：

* 通过**基类指针**调用基类和派生类中的同名**虚函数**时：
  * 指针指向一个基类的对象，那么被调用的是基类的虚函数
  * 指针指向一个派生类的对象，那么被调用的是派生类的虚函数
* 通过**基类引用**调用基类和派生类中的同名**虚函数**时：
  * 引用引用的是一个基类的对象，那么被调用的是基类的虚函数
  * 引用引用的是一个派生类的对象，那么被调用的是派生类的虚函数

**多态的作用**：

​	在面向对象的程序设计中使用多态能够增强程序的可扩充性，即程序需要修改或增加功能的时候，避免大量代码的改动和增加。但是多态的机制会增加程序执行时在**时间和空间**上的**开销**，空间上是由于存在虚函数的类的每个对象在创建时都会多出 4 个字节的额外空间开销用于存放虚函数表的地址；时间上是由于在查虚函数表的过程中需要消耗一定的时间。

**虚析构函数**：

​	当通过基类指针销毁派生类对象时，通常只有基类的构造函数被调用，一般是先调用派生类析构函数，再调用基类构造函数，这就出现了析构不完整的情况。为此，可以将基类的析构函数声明为虚函数，即**虚析构函数**，派生类的析构函数就不需要进行虚函数声明，自动成为虚函数；这时，通过基类指针析构派生类对象时调用的就是派生类的析构函数，派生类的析构函数中会调用基类的析构函数。

​	一般来说，一个**类定义了虚函数**，则应该将该类的析构函数声明为虚函数；另外，如果一个**类要被作为基类使用**，则也应该将该类的析构函数声明为虚函数。

### 纯虚函数和抽象类

**纯虚函数**：没有函数体的虚函数，`virtual void Print() = 0;`

**抽象类**：包含纯虚函数的类称为抽象类

* 抽象类只能作为基类来派生新类使用，不能创建抽象类的对象
* 抽象类的**指针/引用**可以用来**指向/引用**由抽象类派生出来的类的对象
* 抽象类的成员函数内可以调用纯虚函数（如果能够创建抽象类的对象，而其成员函数调用了没有函数体的纯虚函数将导致程序错误），但是在其构造函数和析构函数中不能调用纯虚函数
* 如果一个类从抽象类派生而来，那么当且仅当它实现了基类中的所有纯虚函数时，它才能成为非抽象类（**类似 Java 中的接口**）

### 多态的实现原理

​	多态的关键在于通过**基类指针**或**基类引用**调用虚函数时，编译时还不确定该语句调用的是基类函数还是派生类函数，直到运行时才能确定，这种机制也称为**动态联编**。

#### 虚函数表

​	每一个有虚函数的类（或有虚函数的类的派生类）都有一个**虚函数表**，该类的**任何对象**中都放着该虚函数表的指针（可以认为这是由编译器自动添加到构造函数中的指令完成的）。虚函数表中列出了该类的虚函数地址，有虚函数的类会多出 **4 个字节**（64 位中是 8 个字节）用于存放虚函数表的地址。虚函数表是编译器生成的，程序运行时被载入内存。

```cpp
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
    cout << sizeof(A) << ", " << sizeof(B);  // A B都多出4/8个字节存虚函数表地址
    A* pa = new B();
    pa->func();
    // 64位程序指针是 8 个字节与 long long * 所占空间相同
	A a;
    long long * p1 = (long long *)& a; // 取对象 a 的前 8 个字节即虚函数表地址存储位置
    long long * p2 = (long long *) pa; 
    * p2 = * p1; // 将虚函数表地址互换
    pa->func(); // pa 的虚函数表地址变成了 a 的
    return 0;
}
```

​	上述类 A 和类 B 的内存空间占用如下图所示，首部 4 个字节用于存放该类的虚函数表地址接着再存成员变量。根据虚函数表可以更好的理解多态机制，在编译过程中，存在多态的函数语句被编译成一系列依据**基类指针/基类引用**所**指向/引用**的对象中存放的**虚函数表的地址**，在虚函数表中查找虚函数地址，并调用虚函数的指令。例如上述代码中第一个 `pa->func();` ，`pa` 指向 B 的对象，则依据类 B 的虚函数表地址找到虚函数表，然后在虚函数表中找到 虚函数 `B::func` 的地址，最后根据地址找到并调用虚函数 `B:func` 的指令 。

![虚函数表A](D:\01BasicLearning\TechnicalRoute\CppLearning\OOP_C++\part06\虚函数表.png)

**多态实例-野怪**

* 每个野怪类都要有 `Attack(),FightBack(),Hurted()` 成员函数
* `Attack()` 函数表现攻击动作，攻击某个野怪，并调用被攻击野怪的 `Hurted()` 函数，以减少被攻击野怪的生命值，同时也调用被攻击野怪的 `FightBack()` 成员函数，遭受被攻击野怪反击。

```cpp
// 基类 Creature
class Creature{
    protected:
    	int m_nLifeValue, m_nPower;
    public:
    	virtual void Attack(Creature* pC){}
    	virtual void Hurted(int nPower){}
    	virtual void FightBack(Creature* pc){}
};

class Dragon:public Creature{
    public:
    	virtual void Attack(Creature* pC);
    	virtual void Hurted(int nPower);
    	virtual void FightBack(Creature* pc);    	
};

void Dragon::Attack(Creature* p){
    p->Hurted(m_nPower);
    p->FightBack(this);
}
void Dragon::Hurted(int nPower){
    m_nLifeValue -= nPower;
}
void Dragon::FightBack(Creature* p){
    p->Hurted(m_nPower/2);
}

class Wolf:public Creature{ ... };
class Bird:public Creature{ ... };
class Fish:public Creature{ ... };

int main(){
    Dragon dragon;
    Wolf wolf;
    Bird bird;
    Fish fish;
    dargon.Attack(& wolf); // 多态 调用 wolf.Hurted(); wolf.FightBack();
    dargon.Attack(& bird); // 多态 调用 bird.Hurted(); bird.FightBack();
    dargon.Attack(& fish); // 多态 调用 fish.Hurted(); fish.FightBack();
    return 0;
}
```

**多态实例-几何形体**

* 输入若干个几何形体的参数，输出根据每个几何形体的面积排序输出
* 输入：
  * 第一行输入指定几何形体的个数 N，接下来每一行由代表几何形体的字符开头，后面跟其计算面积的参数
  * R 表示矩形，带宽高两个参数；C 表示圆带一个表示半径的参数；T 表示三角形，带三条边三个参数
* 输出：根据每个几何形体的面积排序分别输出其类别和面积大小
* 一个输入输出示例：

```cpp
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

class Shape{
    public:
        virtual double area() = 0; // 纯虚函数 Shape 无法计算面积 没有信息
        virtual void printInfo() = 0;
    	virtual ~Shape(){}; // 虚析构函数 delete pr/pc/pt; 析构完整
};

class Rectangle:public Shape{
    public:
        int width, height;
        virtual double area();
        virtual void printInfo();
};

class Circle:public Shape{
    public:
        int radius;
        virtual double area();
        virtual void printInfo();
};

class Triangle:public Shape{
    public:
        int a, b, c;
        virtual double area();
        virtual void printInfo();
};

double Rectangle::area(){
    return width*height;
}

double Circle::area(){
    return 3.14*pow(radius,2);
}

double Triangle::area(){
    double temp = (a+b+c)/2.0;
    return sqrt(temp*(temp-a)*(temp-b)*(temp-c));
}

void Rectangle::printInfo(){
    cout << "Rectangle:" << area() << endl;
}

void Circle::printInfo(){
    cout << "Circle:" << area() << endl;
}

void Triangle::printInfo(){
    cout << "Triangle:" << area() << endl;
}

Shape* pShape[100];
int compare(const void * s1, const void * s2){
    Shape** p1;
    Shape** p2; // p1 p2 都是指向指针的指针
    p1 = (Shape**)s1; // 从 pShape 中取几何形体都是指向该几何形体 Shape* 类型 所以要用 * 号取值
    p2 = (Shape**)s2;
    double a1,a2;
    a1 = (*p1)->area(); // p1 p2 是基类指针，被调用的 area() 取决与 p1 p2 指向的派生类， 所以此处是多态
    a2 = (*p2)->area();
    if(a1 < a2){
        return -1;
    }
    else if (a2 < a1)
    {
        return 1;
    }
    else{
        return 0;
    }
    
} 

int main(){

    int n;
    cin >> n;
    for(int index = 0; index < n; index++){
        char c;
        cin >> c;
        switch (c)
        {
        case 'R':
            Rectangle* pr;
            pr = new Rectangle();
            cin >> pr->width >> pr->height;
            pShape[index] = pr;
            delete pr;
            break;
        case 'C':
            Circle* pc;
            pc = new Circle();
            cin >> pc->radius;
            pShape[index]= pc;
            delete pc;
            break;
        case 'T':
            Triangle* pt;
            pt = new Triangle();
            cin >> pt->a >> pt->b >> pt->c;
            pShape[index] = pt;
            delete pt;
            break;
        default:
            break;
        }
    }

    qsort(pShape,n,sizeof(Shape*),compare);
    for(int i=0; i<n; i++){
        pShape[i]->printInfo();
    }

    return 0;
}
/* Input:
3
R 3 5
C 9
T 3 4 5
// Output:
Triangle:6
Rectangle:15
Circle:254.34
*/
```



### Reference

[C++虚函数表（多态的实现原理）](http://c.biancheng.net/view/267.html)