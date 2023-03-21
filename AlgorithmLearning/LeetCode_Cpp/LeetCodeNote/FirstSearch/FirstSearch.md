## LeetCode刷题笔记 优先搜索

### 优先搜索

DFS（深度优先搜索）和 BFS（广度优先搜索）就像孪生兄弟，提到一个总是想起另一个。然而在实际使用中，我们用 DFS 的时候远远多于 BFS。那么，是不是 BFS 就没有什么用呢？

如果我们使用 DFS/BFS 只是为了遍历一棵树、一张图上的所有结点的话，那么 DFS 和 BFS 的能力没什么差别，我们当然更倾向于更方便写、空间复杂度更低的 DFS 遍历。不过，某些使用场景是 DFS 做不到的，只能使用 BFS 遍历。这就是本文要介绍的两个场景：「层序遍历」、「最短路径」。

[BFS 的使用场景：层序遍历、最短路径问题](https://mp.weixin.qq.com/s?__biz=MzA5ODk3ODA4OQ==&mid=2648167212&idx=1&sn=6af5ffe5b69075b21bb4743ddcee4e7c&chksm=88aa236abfddaa7cae70b42edb299d0a52d9f1cc4fc1fdba1116972fc0ca0275b8bfdf10851b&token=1607921395&lang=zh_CN#rd)

可以看到，「BFS 遍历」、「层序遍历」、「最短路径」实际上是递进的关系。在 BFS 遍历的基础上区分遍历的每一层，就得到了层序遍历。在层序遍历的基础上记录层数，就得到了最短路径。

BFS 遍历是一类很值得反复体会和练习的题目。一方面，BFS 遍历是一个经典的基础算法，需要重点掌握。另一方面，我们需要能根据题意分析出题目是要求最短路径，知道是要做 BFS 遍历。

本文讲解的只是两道非常典型的例题。LeetCode 中还有许多层序遍历和最短路径的题目

层序遍历的一些变种题目：

LeetCode 103. Binary Tree Zigzag Level Order Traversal 之字形层序遍历
LeetCode 199. Binary Tree Right Side View 找每一层的最右结点
LeetCode 515. Find Largest Value in Each Tree Row 计算每一层的最大值
LeetCode 637. Average of Levels in Binary Tree 计算每一层的平均值
对于最短路径问题，还有两道题目也是求网格结构中的最短路径，和我们讲解的距离岛屿的最远距离非常类似：

LeetCode 542. 01 Matrix
LeetCode 994. Rotting Oranges

还有一道在真正的图结构中求最短路径的问题：

LeetCode 310. Minimum Height Trees

作者：nettee
链接：https://leetcode-cn.com/problems/binary-tree-level-order-traversal/solution/bfs-de-shi-yong-chang-jing-zong-jie-ceng-xu-bian-l/
来源：力扣（LeetCode）



### 递归 回溯 DFS 的区别

#### 递归是一种算法结构，DFS是一种搜索（方法）工具，回溯是一种算法思想。
**1.在函数中调用函数本身来解决子问题以达到解决原问题的方法就叫递归**

​	对于一个可以分解的问题，子问题与原问题处理过程完全相同，区别只在于数据规模，可以用递归来解。。

**2.回溯就是通过不同的尝试来搜索问题的解。**

​	有点类似于穷举（搜索全部解空间），但是和穷举不同的是回溯会“剪枝”，对已经知道错误的结果没必要再枚举接下来的答案了。

**3.回溯搜索是深度优先搜索（DFS）的一种情况**

​	对于某一个搜索树来说（搜索树是起记录路径和状态判断的作用），回溯和DFS，其主要的区别是，回溯法在求解过程中不保留完整的树结构（剪枝），而深度优先搜索则记下完整的搜索树。
​	为了减少存储空间，在深度优先搜索中，用标志的方法记录访问过的状态，这种处理方法使得深度优先搜索法与回溯法没什么区别了。

[如何理解回溯和递归以及DFS](https://leetcode-cn.com/circle/discuss/8uubaL/view/kg2lF1/)

[DFS 、动态规划、回溯法、递归之间的关系是什么？](https://www.zhihu.com/question/266403334?sort=created)

