## C++ 泛型编程

### 函数模板

**函数模板的概念**： 

​	是一种特殊的函数，可以使用**不同的类型**进行调用，对于功能相同的函数，不需要重复编写代码，实现**代码复用**，并且函数模板与普通函数看起来很类似，区别就是类型可以被参数化。所谓模板就是可以以此为基础批量生成相似的事物，函数模板就是可以用它来自动生成很多**相似**的函数，更高级的函数重载。函数模板通过 `template` 与 `typename/class` 关键字来定义，另外，函数模板中可以有不只一种类型的参数。

```cpp
template <class Type1, class Type2, ...>
返回值类型 模板名(Type1 arg1, Type2 arg2, ...)
{
    /* function body */
}
```

**函数模板的调用**：

​	函数模板在被调用是，可以**隐示**地进行自动类型推导调用 `maxElement(arr1, 5);`，也可以使用具体类型**显示**调用 `maxElement<double>(arr2, 5);` 如下实例是求数组最大元素的`maxElement` 函数模板：

```cpp
template <class T>
T maxElement(T a[], int size){
    T tempMax = a[0];
    for(int i=1; i<size; ++i){
        if(tempMax < a[i]){
            tempMax = a[i];
        }
    }
    return tempMax;
}

int main(){
    int arr1 = {1,2,3,4,5};
    double arr2 = {1.1,2.2,3.3,4.4,5.5};
    cout << maxElement(arr1, 5);
    cout << maxElement<double>(arr2, 5);
    return 0;
}
```

**函数模板的重载**：

​	和普通函数一样，函数模板也可以被重载，只要它们的**形参表或类型参数表**不同即可。

```cpp
template <typename T>
void print(T arg1, T arg2)
{
    cout << "void print(T arg1, T arg2)" << endl;
}
 
template <typename T1, typename T2> // 类型参数表不一致
void print(T1 arg1, T1 arg2)
{
    cout << "void print(T1 arg1, T1 arg2)" << endl;
}

template <typename T1, typename T2>
void print(T1 arg1, T2 arg2) // 形参表不一致
{
    cout << "void print(T1 arg1, T2 arg2)" << endl;
}
```

​	函数模板除了可以重载之外，普通函数的名字也可以和函数模板相同，在这种情况下编译器处理函数调用语句的原则是：

* 优先找参数完全匹配的**普通函数**，而非由模板实例化而得到的函数
* 第二选择是寻找参数完全匹配的**模板函数**
* 最后的选择是寻找**实参**可以通过**自动类型转换**能够匹配的**普通函数**，值得注意的是在匹配模板函数时，不会对实参进行类型自动转换。

**函数模板重要实例 Map 底层实现**：Map 函数的作用是根据**提供的函数**对**指定的序列**做映射，实例如下：

```cpp
template<class T, class Pred>
void map(T s, T e, T x, Pred op){
    for( ; s != e; ++s, ++x){
        *x = op(*s);
    }
}

int cube(int x){
    return x*x*x;
}
double square(double x){
    return x*x;
}

int main(){
    int a[5] = {1,2,3,4,5}, b[5];
    double c[5] = {1.1,2.2,3.3,4.4,5.5}, d[5];

    map(a,a+5,b,cube);
    for(int i=0; i<5; ++i){
        cout << b[i] << ' ';
    }
    cout << endl;

    map(a,a+5,b,square);
    for(int i=0; i<5; ++i){
        cout << b[i] << ' ';
    }
    cout << endl;
    
    map(c,c+5,d,square);
    for(int i=0; i<5; ++i){
        cout << d[i] << ' ';
    }
    cout << endl;

    return 0;
}
```

​	在下面的实现中，map 函数模板的形参表 `T s, T e, T x, Pred op` 分别表示指定序列的起始位置 `s` 、结束位置 `e` 、新序列的起始位置 `x` 和提供的映射函数 `op`。在 `main` 函数中调用模板函数时，函数模板被实例化为对应的函数，例如调用语句 `map(a, a+5, b, square)` 被实例化为如下函数：

```cpp
void map(int *s, int *e, int *x, double(*op)(double)){
     for( ; s != e; ++s, ++x){
        *x = op(*s); // 以*s作为参数去调用op所指向的函数，并把函数执行结果赋值给*x
    }
}
```

### 类模板

**类模板的基本概念**：

​	为了多快好省地定义出一批**相似的类**，可以定义类模板，然后由类模板生成不同的类。将模板的思想应用于类，只考虑类的功能实现，不需要关注具体数据元素的类型，这种思想非常适用于编写数据结构相关的代码，比如数组类、线性表、栈和堆等，只需要实现他们的逻辑功能，不必关注具体的数据类型。

​	和函数模板一样，类模板也通过 `template` 与 `typename/class` 关键字来定义，类模板里的成员函数的定义也需要添加类型参数表，使用类模板定义对象时需要添加**实际类型参数表**，如下所示：

```cpp
// 类模板的定义
template <class Type1, class Type2, ...>
class 类模板名
{
    /* class body: 成员变量和成员函数 */
};

// 类模板成员函数的定义
template <class Type1, class Type2, ...>
返回值类型 类模板名<类型参数名列表>::成员函数名(形参表)
{
    /* function body */
}

// 用类模板定义对象
类模板名<真实类型参数表> 对象名(构造函数实参表);
```

​	类模板的定义中**类型参数表**可以包含**非类型参数**，如下实例中的 `size` 参数：

```cpp
template <class T, int size>
class myArray{
    T array[size];
};
```

**类模板实例 Pair 类模板**：

```cpp
template <class T1, class T2>
class Pair{
public:
    T1 key;
    T2 value;
    Pair(T1 k, T2 v):key(k), value(v){};
    bool operator < (const Pair<T1, T2> &p) const; // const Pair<T1, T2> & p 是Pair类模板对象的引用
};

// Pair类模板的成员函数 operator <
template<class T1, class T2>
bool Pair<T1, T2>::operator < (const Pair<T1, T2> &p) const{
    return key < p.key;
}

int main(){
    Pair<string, int> student("Tom",19); // 实例化一个类
    cout << student.key << " " << student.value << endl;
    return 0;
}
```

​	编译器由类模板生成类的过程叫类模板的实例化，由类模板实例化得到的类，叫**模板类**。值得注意的是，同一个类模板的两个模板类是不兼容的，例如 `Pair<string, int> * p; Pair<string, double> a; p = &a; ` 是非法的赋值。

**函数模板作为类模板的成员函数**：

```cpp
#include <iostream>
using namespace std;
template <class T>
class A{
public:
    // 函数模板作为类模板的成员函数
    template <class T2>
    void Func(T2 t){cout << t;} 
};
int main(){
    A<int> a;
    a.Func('K'); // 成员函数模板 Func 被实例化为形参为 char 类型
    a.Func('hello'); // 成员函数模板 Func 被实例化为形参为 string 类型
    return 0;
}
```

### 类模板与继承

#### 类模板与派生

​	类模板与继承关系，自上而下有以下四种情况：类模板从类模板派生、类模板从模板类派生、类模板从普通类派生、普通类从模板类派生。

**类模板从类模板派生**：多片森林

```cpp
// 模板从模板派生
template <class T1, class T2>
class A{
    T1 v1; T2 v2;
};

template <class T1, class T2>
class B:public A<T2, T1>{
    T1 v3; T2 v4;
};

int main(){
    B<int, double> obj;
    return 0;
}

/* 第13行类模板生成对象 obj 时实例化了两个模板类 */
class B<int, double>:public A<double, int>{
	int v3; double v4;  
};
class A<double, int>{
    double v1; int v2;
};
```

**类模板从模板类派生**：一片森林

```cpp
template <class T1, class T2>
class A{
    T1 v1; T2 v2;
};

template <class T>
class B:public A<int, double>{
    T v3;
};

int main(){
    B<int> obj;
    return 0;
}

/* 第12行类模板生成对象 obj 时实例化了两个模板类 */
class B<int>:public A<int, double>{
	int v3; 
};
class A<int, double>{
    int v1; double v2;
};
```

**类模板从普通类派生**：一棵树

```cpp
class A{
    int v1;
};

template <class T>
class B:public A{ // 所有从类模板B实例化得到的类，都是A的派生类
    T v2;
};

int main(){
    B<int> obj;
    return 0;
}
```

**普通类从模板类派生**：

```cpp
template <class T>
class A{
    T v1;
};

class B:public A<int>{
    int v2;
};

int main(){
    B obj;
    return 0;
}
```

#### 类模板与友元

​	类模板的友元可以是普通函数、函数模板、普通类、普通类的成员函数、类模板；函数模板也可以作为普通类的友元。

```cpp
void Func1(){} // 普通函数
class A{}; // 普通类
class B{
public:
    void FuncB(){} // 普通类的成员函数
};

template <class T>
class FriTmp{
    friend void Func1();
    friend class A;
    friend void B::FuncB();
};
```

​	**函数模板作为类模板的友元** STL 实例 Pair：任意从函数模板生成的函数都是任意Pair模板类的友元

```cpp
#include <iostream>
#include <string>
using namespace std;
template <class T1, class T2>
class Pair{
private:
    T1 key;
    T2 value;
public:
    Pair(T1 k, T2 v):key(k),value(v){}
    bool operator < (const Pair<T1, T2> & p) const;
    // 函数模板作为类模板友元，任意从函数模板生成的函数都是任意Pair模板类的友元
    template <class T3, class T4>
    friend ostream & operator<< (ostream& o, const Pair<T3, T4>& p);
};

template <class T1, class T2>
bool operator< (const Pair<T1,T2>& p) const{
    return key < p.key;
}
template <class T3, class T4>
ostream& operator<< (ostream& o, const Pair<T3,T4>& p){
    o << "(" << p.key << "," << p.value << ")";
    return o;
}

int main(){
    Pair<string, int> student("Tom",14);
    Pair<int, double> obj(12, 4.32);
    cout << student << " " << obj;
    return 0;
}
```

​	**类模板作为类模板的友元**：从被声明为友元的类模板实例化出来的类，都是任何包含友元类模板的类模板实例化出来的类的友元。

```cpp
template <class T>
class B{
    T v;
public:
    B(T n):v(n){}
    // 声明其他类模板作为类模板的友元
    template <class T2>
    friend class A;
};

template <class T>
class A{
public:
    // A 类模板作为友元，其成员函数可以直接访问 B 类模板的成员变量
    void Func(){B<int> b(10); cout << b.v << endl;}
};
```

#### 类模板与静态成员变量

​	类模板中可以定义静态成员 *(static)* ，那么从该类模板实例化得到的所有类都包含同样的静态成员。

```cpp
template <class T>
class A{
private:
    static int count;
    T v;
public:
    A(T n):v(n){count++;}
    ~A(){count--;}
    A(A& a){count++;}
    static void PrintCount(){cout << count << endl;}
};

// 和普通类一样，类模板的静态成员变量也需要在类外单独声明
template<> int A<int>::count = 0;
template<> int A<double>::count = 0;

int main(){
    A<int> ia;
    A<double> da;
    ia.PrintCount();
    da.PrintCount();
    return 0;
}
```

### Reference

[C++中的函数模板](https://blog.csdn.net/lms1008611/article/details/81985815)