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
        *x = op(*s);
    }
}
```



### Reference

[C++中的函数模板](https://blog.csdn.net/lms1008611/article/details/81985815)