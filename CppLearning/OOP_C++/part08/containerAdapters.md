## C++ 标准模板库 STL 容器适配器

|      容器      |     数据结构      |       时间复杂度        | 顺序性 | 重复性 |
| :------------: | :---------------: | :---------------------: | :----: | :----: |
|     stack      |   deque / list    | 顶部插入、顶部删除 O(1) |  无序  | 可重复 |
|     queue      |   deque / list    | 尾部插入、头部删除 O(1) |  无序  | 可重复 |
| priority_queue | vector + max-heap |   插入、删除 O(log2n)   |  有序  | 可重复 |

​	容器适配器和容器的主要差别在于，容器适配器**没有迭代器**，所以STL中的算法无法直接在容器适配器中使用。

### 栈 stack

​	*stack* 类模板定义中有2个模板参数如下：

```cpp
template <typename T, typename Container = deque<T> >
class stack { …… };
```

​	两个参数分别表示栈中元素类型和实现栈的数据结构`Container`，栈可用 `vector, list, deque` 来实现，缺省情况下用deque实现；一般情况下推荐使用`deque`实现，因为用 vector 实现存在是容量大小有限制和扩容耗时的缺陷；而使用`list`实现则会导致整体性能较差。

​	stack 是后进先出的数据结构，只能插入，删除，访问栈顶的元素。所以，stack上主要可以进行如下操作：

* `push`：插入元素
* `pop`：弹出元素
* `top`：返回栈顶元素的引用
* `empty`：判断容器适配器是否为空
* `size`：回适配器中元素个数

### 队列 queue

​	*queue* 和 *stack* 基本相似，其类模板定义中也有相同的2个模板参数如下：

```cpp
template <typename T, typename Container = deque<T> >
class queue { …… };
```

​	两个参数分别表示栈中元素类型和实现栈的数据结构`Container`，栈可用 `vector, list, deque` 来实现，缺省情况下用deque实现；一般情况下推荐使用`deque`实现，因为用 vector 实现存在是容量大小有限制和扩容耗时的缺陷；而使用`list`实现则会导致整体性能较差。

​	queue 是先进先出的数据结构，可以在队头和队尾操作元素。所以，queue 上主要可以进行如下操作：

* `push`：从队尾插入元素
* `pop`：弹出队头元素
* `top`：返回队头元素的引用
* `back`：返回队尾元素的引用
* `empty`：判断容器适配器是否为空
* `size`：回适配器中元素个数

### 优先队列 priority_queue

​	*priority_queue* 类模板定义中有3个模板参数如下：

```cpp
template <typename T, typename Container = vector<T>, typename Compare = less<T> >
class priority_queue { …… };
```

​	priority_queue 通常使用 `vector` 实现，其内部元素处理规则通常用堆排序（heap）技术实现，保证最大的元素总是在最前面。即执行pop操作时，删除的是最大的元素；执行top操作时，返回的是最大元素的常引用。默认的元素比较器是使用`<`运算符进行比较的 `less<T>`。

​	和 queue 相似 priority_queue 可以进行如下操作： 

* `push`：从队尾插入元素
* `pop`：弹出队头元素
* `top`：返回队头元素的引用
* `empty`：判断容器适配器是否为空
* `size`：回适配器中元素个数

​    一个 priority_queue 使用示例如下：

```cpp
include <queue>
#include <iostream>
using namespace std;
int main()
{
    priority_queue<double> pq1;
    pq1.push(3.2); pq1.push(9.8); pq1.push(9.8); pq1.push(5.4);
    while( !pq1.empty() ) {
    	cout << pq1.top() << " ";
    	pq1.pop();
    } 
    cout << endl;
    
    priority_queue<double,vector<double>,greater<double> > pq2;
    pq2.push(3.2); pq2.push(9.8); pq2.push(9.8); pq2.push(5.4);
    while( !pq2.empty() ) {
        cout << pq2.top() << " ";
        pq2.pop();
    }
    return 0;
}
```

