##  函数对象

### 函数对象的基本概念

**函数对象**：如果一个类重载了运算符`()`，及重载了括号运算符的类，其产生的对象都将成为函数对象。函数对象是个对象，但是用起来看上去像函数调用，实际上也执行了函数调用。

```cpp
// 函数对象类
class CMyAverage{
public:
    double operator() (int a, int b, int c){
        return (double)(a+b+c)/3;
    }
};

int main(){
    CMyAverage average; // 函数对象
    cout<<average(3,2,3); // 等价与 average.operator()(3,2,3)
    return 0;
}
```

### 函数对象的实际应用

例如C++中的`accumulate`的实现源码如下：

```cpp
template<typename _InputIterator, typename _Tp, typename _BinaryOperation>
_Tp accumulate(_InputIterator _first, _InputIterator _last, _Tp init, _BinaryOperation _binary_op){
    for(;_first != _last; ++_first){
        _init = _binary_op(_init, *_first); // 传入的实参可以是函数或者函数对象
    }
    return _init;
}
```

在调用`accumulate`时，和`_binary_op`形参对应的实参可以是函数或者函数对象

值得注意的是在定义模板`template`时，使用关键字`typename, class`并没有什么不同，但是他们又有细微的差别，具体请参考[template关键字typename和class的区别,以及模板默认参数](https://blog.csdn.net/anye3000/article/details/6574580)

### 函数对象的应用示例

```cpp
//累加平方值
int sumSquares(int total, int value){
    return total + value*value;
}
// 输出区间[first,last)中的所有元素
template <typename T>
void printInterval(T first, T last){
    for(;first!=last;++first){
        cout << *first<<" ";
    }
    cout << endl;
}
// 类模板，计算power次方并累加
template <typename T>
class SumPowers{
private:
    int power;
public:
    SumPowers(int p):power(p){}
    const T operator()(const T& total, const T& value){
        T v = value;
        for(int i=0;i<power-1;++i){
            v = v*value;
        }
        return total+v;
    }
};
// 调用示例
int main(){
    vector<int> v{1,2,3,4,5,6,7,8,9,10};
    cout<<"1)";printInterval(v.begin(),v.end()); // 输出v的所有元素
    int result = accumulate(v.begin(),v.end(),0,sumSquares); // 使用sumSquares求平方和
    cout<<"2)"<<result<<endl;
    result = accumulate(v.begin(),v.end(),0,SumPowers<int>(3)); // SumPowers<int> 是由类模板构造的整型模板类，该模板类由实例化了函数对象SumPowers<int>(3)，来求立方和
    cout<<"3)"<<result<<endl;
    result = accumulate(v.begin(),v.end(),0,SumPowers<int>(4));
    cout<<"4)"<<result<<endl;
    return 0;
}
```

上述示例中的函数调用实例化过程：

1. 求平方和实例化：可以使用函数指针指向函数

```cpp
int result = accumulate(v.begin(),v.end(),0,sumSquares); // 使用sumSquares求平方和
// 实例化出
int accumulate(vector<int>::iterator first,vector<int>::iterator last,int init,int ( * op)( int,int)) // 用函数指针指向函数
{
    for ( ; first != last; ++first){
    	init = op(init, *first);
    }
    return init;
}
```

2. 求立方和实例化：直接使用函数对象指向函数，这样使用面向对象的思想，不用**重复编写**求次方和的函数

```cpp
result = accumulate(v.begin(),v.end(),0,SumPowers<int>(3));
// 实例化出
int accumulate(vector<int>::iterator first, vector<int>::iterator last, int init, SumPowers<int> op) // 实例化为函数对象
{
    for ( ; first != last; ++first)
    {
        init = op(init, *first);
    }
    return init;
}
```

### STL 中的函数对象类模板

​	STL 中由很多类模板可以用来生成函数对象，例如：`euqal_to, greater, less`等，他们都包含在`#include<functional>`头文件中。

#### Greater 函数对象类模板

​	`greater`函数对象类模板源码

```cpp
template<class T>
struct greater : public binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const {
		return x > y; //数值大的元素反而小
	}
};
```

​	`greater`函数对象的一个典型应用是在双向队列`list`的`sort`成员函数，因为`list`元素顺序的特殊性不能直接使用 STL 算法提供的`sort`函数

* 不带参数的sort函数 `void sort()`：将 *list* 中的元素按 `<` 运算符规定的比较方法**升序排列**

* 带函数对象参数的sort函数

  > ```cpp
  > template <typename T>
  > void sort(T op);
  > ```
  >
  > ​	将 *list* 中的元素按 op 规定的比较方法升序排列，即要比较 x,y 的大小时，看 `op(x,y)`的返回值，如果返回值为 *true* 则认为 x小于y，所以 x 应该排在前面

```cpp
#include <list>
#include <iostream>
#include <iterator>
using namespace std;
class myLess {
public:
    bool operator()(const int & c1, const int & c2){
    	return (c1 % 10) < (c2 % 10); // 个位数较小的元素整体较小
    }
};

template <typename T>
void myPrint(T first, T last){
    for(;first!=last;++first){
        cout<<*first<<",";
    }
}

int main()
{
    const int SIZE = 5;
    int a[SIZE] = {5,21,14,2,3};
    list<int> lst(a,a+SIZE);
    lst.sort(myLess()); // 使用函数对象myLess进行排序
    myPrint(lst.begin(),lst.end());
    lst.sort(greater<int>()); // 使用greater<int>()函数对象进行排序 数值大的元素反而小
    //本句进行降序排序
    myPrint(lst.begin(),lst.end());
    cout<<endl;
    return 0;
}
```

#### STL 中的大小关系

​	关联容器和STL中许多算法，都是可以自定义比较器的; 在自定义了比较器op的情况下，以下三种说法是等价的：

* x 小于 y
* op(x,y) 返回值为 true
* y 大于 x

自定义大小关系示例如下：

```cpp
// 函数对象类
class myLess {
public:
    bool operator()(const int & c1, const int & c2){
    	return (c1 % 10) < (c2 % 10); // 个位数较小的元素整体较小
    }
};

// 函数调用
bool myCompare(const int & c1, const int & c2){
    	return (c1 % 10) > (c2 % 10); // 个位数较小的元素整体较小
}

// 模板类
template <class T, class Pred>
T MyMax( T* p, int n, Pred op)
{
    T tmpmax = p[0];
    for( int i = 1;i < n;i ++ ){
        if(op(tmpmax,p[i]))
        	tmpmax = p[i];
    } 
    return tmpmax;
};

int main()
{
    int a[] = {35,7,13,19,12};
    cout << MyMax(a,5,MyLess()) << endl; // 自定义函数对象大小比较
    cout << MyMax(a,5,MyCompare) << endl; // 自定义函数大小比较
    return 0;
}
```

