## C++ 标准模板库 STL 顺序容器
|  容器  | 数据结构 | 顺序性 | 重复性 |   支持迭代器   |
| :----: | :------: | :----: | :----: | :------------: |
| vector | 动态数组 |  无序  | 可重复 | 随机访问迭代器 |
| deque  | 双向队列 |  无序  | 可重复 | 随机访问迭代器 |
|  list  | 双向链表 |  无序  | 可重复 |   双向迭代器   |

### 动态数组 vector

​	*vector* `#include <vector> ` 动态数组：其元素在内存中是连续存放的，随机存取任何元素都可以在常数时间内完成，在该容器的尾部增删元素也几乎能够在常熟时间内完成具有较好的性能。

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



### 双向队列 deque

​	*deque* `#include <deque>` 双向队列：其元素在内存中是连续存放的，随机存取任何元素都可以在常数时间内完成，在该容器的两端增删元素也几乎能够在常熟时间内完成具有较好的性能。

### 双向链表 list
​	*list* `#include <list>` 双向链表：其元素在内存中是不连续存放的，不支持随机存取，在该容器的任何位置增删元素几乎都能够在常熟时间内完成具有较好的性能。
