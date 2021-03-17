## C++ 类和对象提高

### this 指针

**this 指针的概念**：是一个隐含于每一个**非静态**成员函数中的特殊指针，其作用就是指向调用该成员函数的那个对象。换言之，**非静态**成员函数中可以直接使用 this 来代表指向该函数作用的对象的指针。

```cpp
class Complex{
    public:
    	double real, img;
    	Print(){cout<<real<<" , "<<img<<endl;}
    	Complex(double r, double i){real = r; img = i;}
    	Complex addOne(){
            // this 指针的使用
            this->real++;
            this->Print();
            return * this;
        }
};

int main(){
    Complex c1(0,0), c2(4,4);
    c1.Print();
    c1 = c2.addOne(); // c2.real加一之后赋值给c1
    return 0;
}
/* output:
0 , 0
5 , 4
*/
```

**C++ 程序到 C 程序的翻译**：C++ 程序的最原始的编译过程可以看作是先将 C++ 程序翻译成 C 程序，然后再使用 C 程序的编译器进行编译。下面是一个 C++ 程序翻译到 C 程序的示例：

```cpp
class Car{
    public:
    	int price;
    	void setPrice(int p);
};
void Car::setPrice(int p){
    price = p;
}

int main(){
    Car car;
    car.setPrice(20000);
    return 0;
}
```

​	上述 C++ 程序翻译成 C 程序如下：

```c
struct Car{
    int price;
    // C 结构体中无法定义成员函数
};
void setPrice(struct Car* this, int p){
    this->price = p; // 多一个参数用 this 指针指向 car 对象修改其 price 属性
}

int main(){
    struct Car car;
    setPrice(& car, 20000); // 传 car 对象的地址和 price 修改值
    return 0;
}
```

**更好的理解 this 指针的作用**：当对一个对象调用成员函数时，编译程序先将对象的地址赋给 `this` 指针，然后调用成员函数，每次成员函数存取数据成员时，都隐式使用 `this` 指针。

```cpp
class Sample{
    private:
    	int x;
    public:
    	void hello(){cout << "hello" << endl;}
    	void xHello(){cout << x << ", hello" << endl;}
};

int main(){
    Sample* p1 = null;
    Sample* p2 = null;
    p1->hello(); // success
    /*
    p1->hello(); 能够成功运行，调用过程可以看作如下：
    	p1->hello(); => hello(p1); => hello(null);
    	void hello(){cout<<"hello"<<endl;} => void hello(Sample* this){cout<<"hello"<<endl;} => void hello(null){cout<<"hello"<<endl;}
    */
    
    p2->xHello(); // error
    /*
    p2->xHello(); 运行错误
    	p2->xHello(); => p2->xHello(p1); => p2->xHello(null);
    	void xHello(){cout << x << ", hello" << endl;} => void xHello(Sample* this){cout << this.x << ", hello" << endl;} => void xHello(null){cout << null.x << ", hello" << endl;}
    */
    return 0;
}
```

**this 指针的特点**：

* `this` 并不是一个常规变量，而是个**右值**，所以不能取得 `this` 的地址（不能 `&this`）
* 静态成员函数中不能使用 `this` 指针，因为静态成员函数是类的对象公共的，并不具体作用于某个对象；因此当静态成员函数被调用时，编译程序不会在其参数中添加 `this` 指针，即其真实参数个数不会改变。
* 在一些场景中需要**显示的**引用 `this` 指针
  * 为实现对象的链式引用
  * 为避免对同一对象进行赋值操作
  * 在实现一些数据结构时，例如 `list`

### 类中的静态成员

**static 关键字**：

* 修饰普通变量，修改变量的存储区域和生命周期，使变量存储在静态区，在 main 函数运行前就分配了空间，如果有初始值就用初始值初始化它，如果没有初始值系统用默认值初始化它。

* 修饰普通函数，表明函数的作用范围，仅在定义该函数的文件内才能使用。在多人开发项目时，为了防止与他人命名空间里的函数重名，可以将函数定位为 static。

* 修饰类的成员变量，修饰成员变量使所有的对象都共享一个该变量，而且不需要生成对象就可以访问该成员。在类中，`sizeof` 运算符不会计算静态成员变量所占用的空间，例如：

  ```cpp
  class Sample{
      private:
      	int a;
      	static int b;
  };
  // sizeof(Sample) 的结果是 4 而不是 8
  ```

* 修饰类的成员函数，修饰成员函数使得不需要生成对象就可以访问该函数，但是在 static 函数内不能访问非静态成员。

**静态成员**：普通成员变量每个对象都有各自的一份，而**静态成员变量**总共只有一份，所有对象共享；普通成员函数必须具体作用于某个对象，而**静态成员函数**并不具体作用于某个对象；静态成员不需要通过对象就能访问。静态成员有如下四种访问方式：

* 类名 `::` 成员名 `Rectangle::PrintTotal();`
* 对象名 `.` 成员名 `Rectangle r; r.PrintTotal();` 对象可以访问静态成员，但不具体作用于该对象
* 指针 `->` 成员名 `Rectangle* p = &r; p->PrintTotal();`
* 引用 `.` 成员名 `Rectangle& ref = r; ref.PrintTotal();`

静态成员变量本质上是**全局变量**，静态成员函数本质上也是**全局函数**。设置静态成员这种机制的目的在于：将和某些类紧密相关的全局变量和全局函数写到类内，这样使得这些全局变量和函数更加易于维护和理解。

**静态成员的一个应用示例**：随时输出矩形总数和总共面积

```cpp
class Rectangle{
    private:
    	int width, height;
    	static int totalNumber;
    	static int totalArea;
    public:
    	Rectangle(int w, int h);
    	Rectangle(const Rectangle & r); // 如果不定义拷贝构造函数，在拷贝对象的过程中没有修改 totalNumber 和 totalArea, 但是析构函数却修改了，这将导致最终总数变小
    	~Rectangle();
    	static void printTotal();
};

Rectangle::Rectangle(int w, int h){
    width = w;
    height = h;
    totalNumber++;
    totalArea += width*height;
}

Rectangle::Rectangle(const Rectangle &r){
    width = r.width;
    height = r.height;
    totalNumber++;
    totalArea += width*height;
}

Rectangle::~Rectangle(){
    totalNumber--;
    totalArea -= width*height;
}

void Rectangle::printTotal(){
    cout<< totalNumber << " , " << totalArea << endl;
}

// 必须在定义类的文件中对静态成员变量进行一次说明或初始化，否则能通过编译，但是无法链接
int Rectangle::totalNumber = 0;
int Rectangle::totalArea = 0;

int main(){
    Rectangle r1(1,2), r2(2,4);
    cout << Rectangle::totalNumber << endl; // 会执行出错，因为类中定义 totalNumber是私有的
    Rectangle::printTotal();
    return 0;
}
```

​	需要注意的是，在静态成员函数中，不能访问非静态成员变量，也不能调用非静态成员函数，因为非静态成员变量是有对象所属的，而静态成员不特定属于某个对象，这将导致访问的歧义。

### 成员对象和封闭类

**成员对象**：一个类的成员变量如果是另一个类的对象，就称之为**成员对象**

**封闭类**：有成员对象的类叫**封闭类**，例如：

```cpp
class Tyre{
    private:
    	int radius;
    	int width;
    public:
    	Tyre(int r, int w):radius(r), width(w){cout << "Tyre constructor called" <<endl;}
    	~Tyre(){cout<<"Tyre destructor called"<<endl;}
};

class Engine{
  	public:
    	Engine(){cout<<"Engine constructor called"<<endl;}
    	~Engine(){cout<<"Engine destructor called"<<endl;}
};

// Car 封闭类
class Car{
    private:
    	// 声明次序决定了初始化顺序，与初始化列表次序无关
    	int price;
    	Engine engine;
    	Tyre tyre;
    public:
    	Car(int p, int tr, int tw){}
    	~Car(){cout<<"Car destructor called"<<endl;}
};

// 使用初始化列表初始化封闭类：任何生成封闭类对象的语句，都要让编译器明白对象中的成员对象是如何初始化的
Car::Car(int p, int tr, int tw):price(p), tyre(tr,tw){
    cout<<"Car constructor called"<<endl;
}

int main(){
    Car car(2000,125,400);
    return 0;
}
/* output:
Engine constructor called
Tyre constructor called
Car constructor called
Car destructor called
Tyre destructor called
Engine destructor called
*/
```

**初始化列表**：

​	当封闭类的对象生成并初始化时，它包含的成员对象也需要被初始化，这就会引发成员对象构造函数的调用。通过在定义封闭类的构造函数时，添加初始化列表的方式，让编译器明白成员对象初始化时调用的构造函数。初始化列表的写法` 类名::构造函数名(参数表):成员变量1(参数表), 成员变量2(参数表),.....{函数体}`。

​	初始化列表中的成员变量既可以是成员对象，也可以是基本类型的成员变量。对于成员对象，初始化列表的**参数表**中存放的是构造函数的参数（它指明了该成员对象如何初始化）。对于基本类型成员变量，**参数表**中就是一个初始值。

**封闭类的构造函数和析构函数的执行顺序**：

* 封闭类对象生成时，先执行所有对象成员的构造函数，然后才执行封闭类的构造函数。
* 对象成员的构造函数调用次序和对象成员在类中的说明次序一致，与它们在成员初始化列表中出现的次序无关。
* 当封闭类消亡时，先执行封闭类的析构函数，然后再执行对象的析构函数。调用次序和构造函数的调用次序相反。

**封闭类的拷贝构造函数**：成员对象的拷贝调用该对象的拷贝构造函数

```cpp
class A{
    public:
    	A(){cout<<"default"<<endl;}
    	A(const A & a){cout<<"copy"<<endl;}
};
class B{
    private:
    	A a;
};
int mian(){
    B b1;
    B b2(b1);
    return 0;
}

/* output:
default
copy
// b2.a使用类A的拷贝构造函数初始化的，其实参是b1.a
*/
```

### 友元

**友元函数**：一个类的友元函数可以访问该类的私有成员

```cpp
class A{
    private:
    	int a_x;
    public:
    	A(int x){a_x=x;}
    	friend void addOne(A a);
};

void addOne(A a){
    a.a_x++; // 友元函数可以直接访问类的私有成员
}

int main(){
    A a(1);
    addOne(a);
    return 0;
}
```

**友元类**：友元类的成员函数都可以访问该类的私有成员

```cpp
class A{
    private:
    	int a_x;
    	friend class B; // 友元类可以直接访问该类的私有成员
    public:
    	A(int n){a_x = n;}
};

class B{
    public:
    	A a;
    	B(int ax):a(ax){}
    	void addOne();
};

void B::addOne(){
    a.a_x++;
}

int main(){
    B b(1);
    b.addOne();
    return 0;
}
```

**友元的特点**：

* 能访问私有成员
* 破坏封装性
* 友元关系不可传递，不可继承
* 友元关系的单向性
* 友元声明的形式及数量不受限制

### Reference

[C/C++](https://github.com/huihut/interview#cc)

[C++成员对象和封闭类详解](http://c.biancheng.net/view/167.html)