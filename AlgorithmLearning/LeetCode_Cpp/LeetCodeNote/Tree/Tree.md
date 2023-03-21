## LeetCode刷题笔记 树

​	最为常见的树就是二叉树，这种树的每个节点最多有两个子节点，二叉树可以看成是单链表的升级版，因为他和链表的主要区别就是多了一个子节点的指针。

```cpp
 Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
```

