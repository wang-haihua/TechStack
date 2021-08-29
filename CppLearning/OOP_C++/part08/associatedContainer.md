## C++ 标准模板库 STL 关联容器
|        容器        | 数据结构 |           时间复杂度            | 顺序性 |  重复性  |
| :----------------: | :------: | :-----------------------------: | :----: | :------: |
|        set         |  红黑树  |    插入、删除、查找 O(log2n)    |  有序  | 不可重复 |
|      multiset      |  红黑树  |    插入、删除、查找 O(log2n)    |  有序  |  可重复  |
|        map         |  红黑树  |    插入、删除、查找 O(log2n)    |  有序  | 不可重复 |
|      multimap      |  红黑树  |    插入、删除、查找 O(log2n)    |  有序  |  可重复  |
|   unordered_set    |  哈希表  | 插入、删除、查找 O(1) 最差 O(n) |  无序  | 不可重复 |
| unordered_multiset |  哈希表  | 插入、删除、查找 O(1) 最差 O(n) |  无序  |  可重复  |
|   unordered_map    |  哈希表  | 插入、删除、查找 O(1) 最差 O(n) |  无序  | 不可重复 |
| unordered_multimap |  哈希表  | 插入、删除、查找 O(1) 最差 O(n) |  无序  |  可重复  |

### 关联容器概述

​	关联容器和[顺序容器](https://blog.csdn.net/qq_41773806/article/details/116651544)的本质的不同在于：关联容器中的元素是按关键字来保存和访问的；与之相对，顺序容器中的元素是按它们在容器中的位置来顺序保存和访问的。关联容器支持高效的关键字查找与访问，其内部元素有序排列，新元素插入的位置取决于它的值，查找速度快。两个主要的关联容器类型是map与set，除了各容器都有的函数外，还支持以下成员函数：

|    函数     |                           函数描述                           |
| :---------: | :----------------------------------------------------------: |
|    find     | 在容器中搜索具有等于 key 键的元素，如果找到则返回一个迭代器  |
|    count    |   在容器中搜索具有等于 key 键的键的元素，并返回匹配的数量    |
| lower_bound | 返回一个非递减序列 `[first, last)`中的第一个大于等于值 val 的位置的迭代器 |
| upper_bound | 返回一个非递减序列 `[first, last)`中第一个大于 val 的位置的迭代器 |
| equal_range | 获取相同元素的范围，返回包含容器中所有具有与  key 等价的键的元素的范围边界 |
|   insert    |                  用以插入一个元素或一个区间                  |

​	关联容器的基础是名为 **pair** 的标准库类型，它定义在头文件utility中。pair是一个用来生成特定类型的模板，一个pair保存两个数据成员。当创建一个pair时，需要提供两个类型名，pair的数据成员将具有对应的类型，一个pair类型的对象，其实存储的是一个键值对（key-value）。pair 模板的源码如下所示：

```cpp
template<class _T1, class _T2>
struct
pair
{
    typedef _T1 first_type ;
    typedef _T2 second_type ;
    // pair 存储的键值对
    _T1 first ;
    _T2 second ;
    // pair 的三种构造函数
    pair(): first(), second() { }
    pair(const _T1& __a, const _T2& __b): first(__a), second(__b) { }
    template<class _U1, class _U2>
    pair(const pair<_U1, _U2>& __p): first(__p.first ), second(__p.second) { }
};

// 第三个构造函数的使用示例
pair<int,int>
p(pair<double,double>(5.5,4.6));
//p.first = 5, p.second = 4
```

### 集合 set/multiset

​	*set/multiset* `#include<set>` 集合：*set* 集合中**不允许**存在相同的元素，*multiset* 集合中**允许**存在相同的元素。

#### multiset

​	*multiset* 类模板定义中有3个模板参数如下：

```cpp
template <typename Key, typename Pred = less<Key>, typename A = allocator<Key> >
class multiset { …… };
```

​	*multiset* 类模板中3个模板参数的后两个模板参数是可以缺省的，其中第二个模板参数 Pred 类型的变量决定了*multiset* 中的元素，大小顺序是怎么定义的。*multiset* 运行过程中，比较两个元素x,y的大小的做法，就是生成一个  Pred 类型的变量，假定为 op，若表达式op(x,y) 返回值为true,则 x比y小。Pred 的缺省类型是 `less<Key>`，起模板定义如下：

```cpp
// 第二个模板参数Pred中的模板函数less是使用<运算符比较大小，其模板定义如下
template<class T>
struct less : public binary_function<T, T, bool>{ 
    bool operator()(const T& x, const T& y) { 
        return x < y ; 
    } 
    const; 
};
```

​	一种由第二个模板参数缺省导致错误的 *multiset* 使用错误：

```cpp
#include <set>
using namespace std;
class A { };
int main() {
    multiset<A> a;
    a.insert(A()); // Error
}
```

​	由于参数缺省，`multiset<A> a;` 就等价于 `multiset<A, less<A>> a;`；插入元素时，*multiset* 会将被插入元素和已有元素进行比较。由于 less 模板是用 < 进行比较的；所以，这都要求 A 的对象能用 < 比较，即需要该对象中对 < 运算符进行了重载。

```cpp
class A {
private:
	int n;
public:
    A(int n_ ) { n = n_; }
    friend bool operator< ( const A & a1, const A & a2 ) { // 重载 < 运算符
        return a1.n < a2.n; 
    }
};
```

#### multiset 成员函数

|                        函数                        |                           函数描述                           |
| :------------------------------------------------: | :----------------------------------------------------------: |
|            iterator find(const T & val)            | 在容器中查找值为val的元素，返回其迭代器; 如果找不到，返回end() |
|           iterator insert(const T & val)           |               将val插入到容器中并返回其迭代器                |
|     void insert( iterator first,iterator last)     |                  将区间[first,last)插入容器                  |
|              int count(const T & val)              |                统计有多少个元素的值和val相等                 |
|        iterator lower_bound(const T & val)         | 查找一个最大的位置 it,使得[begin(),it) 中所有的元素都比 val 小 |
|        iterator upper_bound(const T & val)         | 查找一个最小的位置 it,使得[it,end()) 中所有的元素都比 val 大 |
| pair<iterator,iterator> equal_range(const T & val) |               同时求得lower_bound和upper_bound               |
|            iterator erase(iterator it)             |          删除it指向的元素，返回其后面的元素的迭代器          |

​	一个 *multiset* 常用函数使用实例如下：

```cpp
#include <iostream>
#include <set> //使用multiset须包含此文件
using namespace std;

// 输出[first,last)内的所有元素
template <class T>
void Print(T first, T last){ 
    for(;first != last ; ++first)
        cout << * first << " ";
	cout << endl;
}

class A {
private:
	int n;
public:
    A(int n_ ) { n = n_; }
    friend bool operator< ( const A & a1, const A & a2 ) { // 重载 < 运算符
        return a1.n < a2.n; 
    }
    friend ostream & operator<< ( ostream & o, const A & a2 ) { 
        o << a2.n; 
        return o; 
    }
    friend class MyLess;
};

struct MyLess { 
	bool operator()( const A & a1, const A & a2){ 
        return ( a1.n % 10 ) < (a2.n % 10); //按个位数比较大小
    }
};

// 定义两个使用不同大小比较方式的 Multiset
typedef multiset<A> MSET1; //MSET1用默认方式的 < 运算符比较大小
typedef multiset<A,MyLess> MSET2; //MSET2用 MyLess::operator()比较大小

int main()
{
    const int SIZE = 6;
    A a[SIZE] = {4,22,19,8,33,40};
    // m1中的元素默认大小比较方式排序
    MSET1 m1; 
    m1.insert(a,a+SIZE);
    m1.insert(22);
    
	// 使用count成员函数获取元素值为22的元素个数
    cout << "1) " << m1.count(22) << endl; 
    //输出m1的所有元素： 4 8 19 22 22 33 40
    cout << "2) "; Print(m1.begin(),m1.end()); 
    
    // 使用find成员函数查找元素值为19的元素
    MSET1::iterator pp = m1.find(19);
    if( pp != m1.end() ) //条件为真说明找到
    	cout << "found" << endl;
   
    // 使用 lower_bound 成员函数返回m1中第一个大于等于22的元素的迭代器
    // upper_bound 成员函数返回m1中最后一个大于等于22的元素的迭代器
    cout << "3) "; cout << *m1.lower_bound(22) << "," << *m1.upper_bound(22)<< endl;
    
    // 使用 erase 成员函数删除区间内的元素
    pp = m1.erase(m1.lower_bound(22),m1.upper_bound(22)); //pp指向被删元素的下一个元素
    cout << "4) "; Print(m1.begin(),m1.end()); // 4 8 19 33 40
    cout << "5) "; cout << * pp << endl; // 33
    
    // m2里的元素按n的个位数从小到大排
    MSET2 m2; 
    m2.insert(a,a+SIZE);
    cout << "6) "; Print(m2.begin(),m2.end()); //输出 6) 40 22 33 4 8 19
    return 0;
}
```

#### set

​	和 *multiset* 相似 *set* 类模板定义中有3个模板参数如下：

```cpp
template <typename Key, typename Pred = less<Key>, typename A = allocator<Key> >
class set { …… };=
```

​	**set和multiset的最大区别**：set支持去重， multiset不支持，所以他们的成员函数大都相同，但是在使用`insert()` 成员函数时，如果插入set中的是已存在的元素，则忽略插入。

​	一个 *set* 常用函数使用实例如下：

```cpp
#include <iostream>
#include <set>
using namespace std;
int main() {
    typedef set<int>::iterator IT;
    int a[5] = { 3,4,6,1,2 };
    set<int> st(a,a+5); // st里是 1 2 3 4 6 有序集合
    pair< IT,bool> result;
    result = st.insert(5); // st变成 1 2 3 4 5 6 插入数据时会和已有数据进行比较
    if(result.second) //插入成功则输出被插入元素
    	cout << * result.first << " inserted" << endl; // 输出: 5 inserted
    if( st.insert(5).second ) 
        cout << * result.first << endl;
    else
    	cout << * result.first << " already exists" << endl; //输出 5 already exists
    pair<IT,IT> bounds = st.equal_range(4); // 使用equal_range成员函数同时求得lower_bound和upper_bound
    cout << * bounds.first << "," << * bounds.second ; //输出：4,5
    return 0;
}
```

### 键值对集合 map/multimap

​	*map/multimap* `#include <map>` 键值对集合：**map/multimap里放着的都是pair模版类的对象，且按first从小到大排序**。所以，map 和 set 的不同在于前者存放的元素有且仅有两个成员变量 (first,second)，一个名为 first，另一个名为 second ，first 的值用来对整体元素进行从小到大的排序，并可以通过 first 快速检索元素。

#### multimap

​	*multimap* 类模板定义中有4个模板参数如下：

```cpp
template <typename Key, typename T, typename Pred = less<Key>, typename A = allocator<Key> >
class multiset { …… };
```

​	*multimap* 类模板中4个模板参数的后两个模板参数是可以缺省的，其中第一个模板参数`key`代表关键字的类型，第二个模板参数`T`代表值的类型，第三个模板参数 Pred 类型和set类似，该变量决定了*multimap* 中的元素大小比较的规则。

* multimap 中的元素由`<关键字,值>`组成，每个元素是一个**pair对象**，关键字就是 first 成员变量，其类型是Key
* multimap 中允许多个元素的**关键字相同**。元素按照first成员变量从小到大排列，缺省情况下用 `less<Key>` 定义关键字的小于关系

​	所有适用于 *set* 的操作都适用于 *map*，一个 *multimap* 使用实例如下：

```cpp
#include <iostream>
#include <map>
using namespace std;
int main()
{
    typedef multimap<int,double,less<int> > mmid;
    mmid pairs;
    // 使用insert()函数插入键值对
    pairs.insert(pair<int,double>(15,4.2));
    pairs.insert(make_pair(15,3.1));
    pairs.insert(mmid::value_type(15,2.7));
    pairs.insert(mmid::value_type(15,99.3));
    // 使用count()函数求关键字等于某值的元素个数
    cout << pairs.count(15) << endl;
    pairs.insert(mmid::value_type(30,111.11));
    pairs.insert(mmid::value_type(10,22.22));
    pairs.insert(mmid::value_type(25,33.333));
    pairs.insert(mmid::value_type(20,9.3));
    // 使用erase()函数删除关键字为25的元素
    pairs.erase(25)
    for( mmid::const_iterator i = pairs.begin();
        i != pairs.end() ;i ++ )
        cout << "(" << i->first << "," << i->second << ")" << ",";
}
```

​	*map* 插入数据是需要插入一个`pair`对象，从上例中有三种插入方式：

* `pair<int,double>()`：pair构造函数生成pair对象，需要指定first和second的类型

* `make_pair()`：无需写出类型就可以生成一个pair对象，通过实参自动匹配类型；但是需要注意的是`pair<int, float>(1, 1.1);`和`make_pair(1, 1.1);`是不同的，前者指定了second就是float，而后再会将其匹配成double
* `mmid::value_type()`：在定义mmid时会同时定义value_type，`typedef pair<const Key, T> value_type;`所以也可以使用value_type构造pair对象

#### map

​	和 *multimap* 一样 *map* 类模板定义中有4个模板参数如下：

```cpp
template <typename Key, typename T, typename Pred = less<Key>, typename A = allocator<Key> >
class multiset { 
    …… 
	typedef pair<const Key, T> value_type;
    …… 
};
```

​	和 *multimap* 一样 *map* 中的元素也是由`<关键字,值>`组成，每个元素是一个**pair对象**；但是，和 *multimap* 的主要区别在于 ***map* 的关键字也就是 first 成员变量各不相同**，不存在重复的关键字。同样，在第三个模板参数缺省的情况下，其中的元素使用`less<Key>` 大小比较方法，按照关键字从小到大排列。

**map的[ ]成员函数**

​	因为 *map* 中的元素关键字都是各不相同的，所以可以使用类似于顺序容器的`[]`对元素进行检索与修改。若 `mymap` 为 *map* 模版类的对象，则可以使用`mymap[key]`返回对关键字等于key的元素的值（second成员变量）的引用。若没有关键字为key的元素，则会往mymap里插入一个关键字为key的元素，其值用无参构造函数初始化，并返回其值的引用。

​	一个 *map* 使用实例如下：

```cpp
#include <iostream>
#include <map>
using namespace std;

// 重载 << 运算符，用于输出map元素
template <class Key,class Value>
ostream & operator <<( ostream & o, const pair<Key,Value> & p){
    o << "(" << p.first << "," << p.second << ")";
    return o;
}

int main() {
    typedef map<int, double,less<int> > mmid;
    mmid pairs;
    pairs.insert(mmid::value_type(15,2.7));
    cout << pairs.count(15) << endl;
    pairs.insert(mmid::value_type(20,9.3));
    mmid::iterator i; 
    for( i = pairs.begin(); i != pairs.end();i ++ ) 
    	cout << * i << ",";
    cout << endl;
   	// 使用[]成员函数检索map元素，如果没有关键字为40的元素，则插入一个
    int n = pairs[40];
    for( i = pairs.begin(); i != pairs.end();i ++ )
    	cout << * i << ",";
    cout << endl;
    cout << "5) ";
    // 使用[]成员函数修改map元素，把关键字为15的元素值改成6.28
    pairs[15] = 6.28; 
    for( i = pairs.begin(); i != pairs.end();i ++ )
    	cout << * i << ",";
}
```

