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

### 动态数组 vector

​	*vector* `#include <vector> ` 动态数组：其元素在内存中是连续存放的，随机存取任何元素都可以在常数时间内完成，在该容器的尾部增删元素也几乎能够在常数时间内完成具有较好的性能。

​	一个 vector 常用函数使用实例如下：

```cpp
#include <iostream>
#include <vector>
using namespace std;
template<class T>
void printVector(T s, T e){
    for(;s != e; ++s){
        cout << *s << ' ';
    }
    cout << endl;
}

int main(){
    int a[5] = {1,2,3,4,5};
    vector<int> v(a,a+5);
    cout << "1)" << v.end() - v.begin() << endl;
    cout << "2)";
    printVector(v.begin(), v.end());
    v.insert(v.begin()+3, 100); // insert()函数插入元素
    cout << "3)";
    printVector(v.begin(), v.end());

    vector<int> v2(5,0);
    v2.insert(v2.begin()+2,v.begin(),v.end()); // insert() 函数数据块插入  
    cout << "4)";
    printVector(v2.begin(), v2.end());   
    v.erase(v.begin()+3); // erase() 函数删除元素 
    cout << "5)";
    printVector(v.begin(), v.end());
    v.erase(v.begin()+2,v.begin()+4); // erase() 函数删除数据块
    cout << "6)";
    printVector(v.begin(), v.end());
 
    return 0;
}
```

#### 构造函数

|         函数          |                          函数描述                          |
| :-------------------: | :--------------------------------------------------------: |
|        vector         |        构造函数创建一个 vector，可以设定大小 nSize         |
| vector(const vector&) |     拷贝构造函数，可以对区间内另一个数组的元素进行拷贝     |
|       operator=       |   将新内容分配给容器，替换其当前内容，并相应地修改其大小   |
|        assign         | 将新内容分配给 vector，替换其当前内容，并相应地修改其 size |

#### 容量管理函数

|     函数      |                         函数描述                         |
| :-----------: | :------------------------------------------------------: |
|     size      |                   返回容器中元素的数量                   |
|   max_size    |                返回容器可容纳的最大元素数                |
|    resize     |         调整容器的大小，使其包含 n（参数）个元素         |
|   capacity    |      返回当前为 vector 分配的存储空间（容量）的大小      |
|     empty     |                   返回 vector 是否为空                   |
|    reserve    |       请求 vector 容量至少足以包含 n（参数）个元素       |
| shrink_to_fit | 要求容器减小其 capacity（容量）以适应其 size（元素数量） |

#### 增删函数

|     函数     |                           函数描述                           |
| :----------: | :----------------------------------------------------------: |
|  push_back   |            在容器的最后一个元素之后添加一个新元素            |
|   pop_back   |     删除容器中的最后一个元素，有效地将容器 size 减少一个     |
|    insert    | 通过在指定位置的元素之前插入新元素来扩展该容器，通过插入元素的数量有效地增加容器大小 |
|    erase     | 从 vector 中删除单个元素（`position`）或一系列元素（`[first，last)`），这有效地减少了被去除的元素的数量，从而破坏了容器的大小 |
|    clear     | 从 vector 中删除所有的元素（被销毁），留下 size 为 0 的容器  |
|   emplace    | 通过在 position（参数）位置处插入新元素 args（参数）来扩展容器 |
| emplace_back | 在 vector 的末尾插入一个新的元素，紧跟在当前的最后一个元素之后 |

#### 索引函数

|    函数    |                 函数描述                 |
| :--------: | :--------------------------------------: |
| operator[] | 返回容器中第 n（参数）个位置的元素的引用 |
|     at     | 返回容器中第 n（参数）个位置的元素的引用 |
|   front    |       返回对容器中第一个元素的引用       |
|    back    |      返回对容器中最后一个元素的引用      |
|    data    |      返回指向容器中第一个元素的指针      |

#### 迭代器函数

|  函数   |                           函数描述                           |
| :-----: | :----------------------------------------------------------: |
|  begin  |               返回指向容器中第一个元素的迭代器               |
|   end   |       返回指向容器中最后一个元素之后的理论元素的迭代器       |
| rbegin  |            返回指向容器中最后一个元素的反向迭代器            |
|  rend   |      返回一个反向迭代器，指向中第一个元素之前的理论元素      |
| cbegin  |    返回指向容器中第一个元素的常量迭代器（const_iterator）    |
|  cend   | 返回指向容器中最后一个元素之后的理论元素的常量迭代器（const_iterator） |
| crbegin | 返回指向容器中最后一个元素的常量反向迭代器（const_reverse_iterator） |
|  crend  | 返回指向容器中第一个元素之前的理论元素的常量反向迭代器（const_reverse_iterator） |

#### 用 vector 实现二维数组

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<vector<int>> arr(3); // arr中有 3 个元素，每个元素都是 vector<int> 容器
    for(int i=0; i<arr.size(); ++i){
        for(int j=0; j<3; ++j){
            arr[i].push_back(j);
        }
    }
    for(int i=0; i<arr.size(); ++i){
        for(int j=0; j<3; ++j){
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}
```

### 双向队列 deque

​	*deque* `#include <deque>` 双向队列：其元素在内存中是连续存放的，随机存取任何元素都可以在常数时间内完成，在该容器的两端增删元素也几乎能够在常数时间内完成具有较好的性能。

​	所有适用于 *vector* 的操作都适用于 *deque*，除此之外，*deque* 还有 `push_front / pop_front` 在最前端插入或删除元素的操作，复杂的都是 $O(1)$ 。

|     函数      |                     函数描述                     |
| :-----------: | :----------------------------------------------: |
|     deque     |                     构造函数                     |
|   push_back   |            在容器的末尾添加一个新元素            |
|  push_front   |            在容器的开头插入一个新元素            |
|   pop_back    | 删除容器中的最后一个元素，同时将容器大小减少一个 |
|   pop_front   |  删除容器中的第一个元素，同时将容器大小减少一个  |
| emplace_front |           在容器的开头插入一个新的元素           |
| emplace_back  |           在容器的末尾插入一个新的元素           |

### 双向链表 list
​	*list* `#include <list>` 双向链表：其元素在内存中是不连续存放的，不支持随机存取，在该容器的任何位置增删元素几乎都能够在常数时间内完成具有较好的性能。

​	*list* 除了具有所有顺序容器都有的成员函数之外，还支持以下8个成员函数：

|    函数    |                           函数描述                           |
| :--------: | :----------------------------------------------------------: |
| push_front |                  在容器的开头插入一个新元素                  |
| pop_front  |                    删除容器中的第一个元素                    |
|    sort    |     元素排序，值得注意的是 list 不支持 STL 算法中的 sort     |
|   remove   |                  删除和指定值相等的所有元素                  |
|   unique   | 删除所有和前一个元素相同的元素，使得元素不重复，使用之前需要sort |
|   merge    |             合并两个链表，并清空被合并的那个链表             |
|  reverse   |                         颠倒链表内容                         |
|   splice   | 在指定位置前面插入另一链表中的一个或多个元素，并在该链表中删除这些元素 |

​	一个 *list* 的成员函数使用实例如下：

```cpp
#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

class A{
    private:
        int n;
    public:
        A(int n_){n = n_;}
        friend bool operator<(const A & a1, const A & a2);
        friend bool operator==(const A & a1, const A & a2);
        friend ostream& operator<<(ostream & o, const A & a2);
};

bool operator<(const A & a1, const A & a2){
    return a1.n < a2.n;
}

bool operator==(const A & a1, const A & a2){
    return a1.n == a2.n;
}

ostream& operator<<(ostream & o, const A & a2){
    o << a2.n;
    return o;
}

template <class T>
void printList(T start, T end){
    for(;start != end; ++start){
        cout << *start << ',';
    }
    cout << endl;
}

int main(){
    list<A> lst1, lst2;
    lst1.push_back(1); lst1.push_back(3);
    lst1.push_back(2); lst1.push_back(4);
    lst1.push_back(2);
    lst2.push_back(10); lst2.push_back(50);
    lst2.push_back(30); lst2.push_back(30);  
    lst2.push_back(40); lst2.push_back(40); 
    lst2.push_back(30); lst2.push_back(20);
    cout << "1) ";
    printList(lst1.begin(),lst1.end());
    cout << "2) ";
    printList(lst2.begin(),lst2.end());
    lst2.sort(); // 调用 sort 成员函数进行 lst2 排序
    cout << "3) ";
    printList(lst2.begin(),lst2.end());
    lst2.unique(); // 删除 lst2 中所有和前一个元素相等的元素
    cout << "4) ";
    printList(lst2.begin(),lst2.end());
    lst2.pop_front(); // 将 lst2 的第一个元素删除
    cout << "5) ";
    printList(lst2.begin(),lst2.end());
    lst1.remove(2); // 删除 lst1 中所有值为 2 的元素
    cout << "6) ";
    printList(lst1.begin(),lst1.end());
    lst2.merge(lst1); // 将 lst1 中的元素合并到 lst2 并将 lst1 清空
    cout << "7) ";
    printList(lst2.begin(),lst2.end());
    lst2.reverse(); // 颠倒 lst2
    cout << "8) ";
    printList(lst2.begin(),lst2.end());
    
    lst1.push_back(100); lst1.push_back(200); 
    lst1.push_back(300); lst1.push_back(400);
    cout<<"9) ";
    printList(lst1.begin(),lst1.end());
    // 找到列表中的指定元素
    list<A>::iterator p1,p2,p3;
    p1 = find(lst2.begin(),lst2.end(),4);
    p2 = find(lst1.begin(),lst1.end(),200);
    p3 = find(lst1.begin(),lst1.end(),400);
    lst2.splice(p1,lst1,p2,p3); // 将 lst1 中 [p2,p3) 区间内的元素插入到 lst2 中 p1 位置之前，并将这些元素从 lst1 中删除
    cout<<"10) ";
    printList(lst1.begin(),lst1.end());
    cout<<"11) ";
    printList(lst2.begin(),lst2.end());
    
    return 0;
}
```

