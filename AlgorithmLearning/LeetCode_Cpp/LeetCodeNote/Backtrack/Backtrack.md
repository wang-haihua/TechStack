## LeetCode刷题笔记 回溯算法

### 回溯算法简介

递归 回溯 DFS 的区别

#### 递归是一种算法结构，DFS是一种搜索（方法）工具，回溯是一种算法思想。
**1.在函数中调用函数本身来解决子问题以达到解决原问题的方法就叫递归**

​	对于一个可以分解的问题，子问题与原问题处理过程完全相同，区别只在于数据规模，可以用递归来解。。

**2.回溯就是通过不同的尝试来搜索问题的解。**

​	有点类似于穷举（搜索全部解空间），但是和穷举不同的是回溯会“剪枝”，对已经知道错误的结果没必要再枚举接下来的答案了。

**3.回溯搜索是深度优先搜索（DFS）的一种情况**

​	对于某一个搜索树来说（搜索树是起记录路径和状态判断的作用），回溯和DFS，其主要的区别是，回溯法在求解过程中不保留完整的树结构（剪枝），而深度优先搜索则记下完整的搜索树。
​	为了减少存储空间，在深度优先搜索中，用标志的方法记录访问过的状态，这种处理方法使得深度优先搜索法与回溯法没什么区别了。



### 回溯算法的代码模板

```cpp
result = []
void backtrack(路径, 选择列表):
    if 满足结束条件:
        result.add(路径)
        return

    for 选择 in 选择列表:
        做选择
        backtrack(路径, 选择列表)
        撤销选择
```



[如何理解回溯和递归以及DFS](https://leetcode-cn.com/circle/discuss/8uubaL/view/kg2lF1/)

[DFS 、动态规划、回溯法、递归之间的关系是什么？](https://www.zhihu.com/question/266403334?sort=created)

[回溯法套路模板 刷通leetcode](https://zhuanlan.zhihu.com/p/112926891)



[C++ 总结了回溯问题类型 带你搞懂回溯算法(大量例题)](https://leetcode-cn.com/problems/subsets/solution/c-zong-jie-liao-hui-su-wen-ti-lei-xing-dai-ni-gao-/)

