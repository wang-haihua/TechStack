## 二叉搜索树 BST

### 什么是二叉搜索树

​	二叉搜索树（又称：二叉查找树，二叉排序树，Binary Search Tree, BST）是一种特殊的二叉树：对于每个父节点，其左子节点的值小于等于父结点的值，其右子节点的值大于等于父结点的值。

​	因此对于一个二叉搜索树，我们可以在 O(nlogn) 的时间内查找一个值是否存在：从根节点开始，若当前节点的值大于查找值则向左下走，若当前节点的值小于查找值则向右下走。

​	同时因为二叉查找树是有序的，对其中序遍历的结果即为排好序的数组。

​	一个二叉搜索树实例`[15,6,23,4,7,null,71,null,5,null,null,null,null,50,null]`如下图所示：

![BST](/home/wang/Desktop/TechStack/ALGLearning/LeetCode_Cpp/LeetCodeNote/Tree/img/BST/BST.png)

​	二叉搜索树除了创建二叉树之外的基本操作有三种：（1）搜索（2）插入 （3）删除

### BST 的节点属性

​	和普通二叉树一样，二叉搜索树的每个节点**至少**有 3 个属性：左孩子，右孩子和数据值，它然节点还可以包含其他潜在的属性。 二叉搜索树节点的结构体声明可以如下：

```cpp
struct Node {
	T data; // T 代表模板类
	Node* left;
	Node* right;
};
```

​	二叉搜索树的节点放置规则是：任何节点的数据值一定大于其左子树中的每个节点的数据值，并小于其右子树中的每个节点的数据值。所以，在遍历二叉搜索树时，一直往左走可以得到最小元素，一直往右走可以得到最大元素。

### BST 的中序遍历

​	我们再来复习一遍二叉搜索树的特性：左子树上所有结点的值均小于它的根结点的值，右子树上所有结点的值均大于它的根结点的值。

​	依据这一特性我们可以推出二叉搜索树的另一个重要特性：**二叉搜索树的中序遍历序列是一个递增序列**。

​	二叉搜索树的中序遍历实现和普通二叉树一样，也有递归和非递归的实现方式。但是无论 BST 的高度如何，中序遍历的时间复杂度都是`O(N)`。

​	**（1）递归实现方式：**先遍历左节点，再遍历父结点，最后遍历右节点

```cpp
void inorder(Node* root) {
    inorder(root->left);
    visit(root);
    inorder(root->right);
}
```

​	（2）**非递归实现方式：**

​	二叉树中序遍历是从左子树的最左边的叶子节点开始处理，是**自下而上的递归**。

​	节点访问过程：由于是自下而上的访问，使用迭代实现中序遍历需要一个额外的指针来访问节点，从根节点一层层向左访问到左子树的最左边的叶子节点并逐个入栈，再开始向上迭代处理节点值。完成访问之后，栈中保存的是从根节点到最左边的叶子节点路径上的所有节点，他们都是左节点。

​	节点处理过程：直接取栈顶元素将其值加入结果集，然后查看它是否具有右节点。如果有右节点则使用指针从该节点开始进行和根节点一样的访问过程，将从该节点开始到以该节点为根节点的子树的最左叶子节点路径上的所有节点入栈。完成访问之后再重复处理过程，最终完成所有节点的访问和处理。

​	实现代码如下：

```cpp
vector<int> inorderTraversal(TreeNode* root) {
	vector<int> ans;
	if(!root){
	    return ans;
	}
	stack<TreeNode*> s;
	TreeNode* cur = root;
	while(cur || !s.empty()){
        if(cur){
            // 从根节点到最左叶子节点的访问过程
            s.push(cur);
            cur = cur->left;
        }else{
            // 自下而上 左中右的节点处理过程
            cur = s.top();
            s.pop();
            ans.push_back(cur->val);
            cur = cur->right;
        }
	}
	return ans;
}
```

### BST 搜索

​	二叉搜索树，最为基础的操作当然就是**搜索**了。

​	二叉树搜索过程中使用根结点 root 和目标值 target 进行比较，不同情况处理如下：

- 若 target 小于根结点键值，只需在左子树中继续搜索
- 如果 target 大于根结点的键值，在右子树中进行继续搜索
- 若两者比较结果是相等，搜索完成，返回指向此结点的指针。

![搜索](/home/wang/Desktop/TechStack/ALGLearning/LeetCode_Cpp/LeetCodeNote/Tree/img/BST/搜索.gif)

​	搜索过程的代码实现如下：

```cpp
Node* find(Node* t, T target) {
	if (t == NULL) return NULL;
	if (target < t->data) return find(t->left, target);
	if (target > t->data) return find(t->right, target);
	return t;
}
```

​	除了快速搜索目标值，二叉搜索树中还可以快速查找最大值和最小值。

**查找最大值和最小值**

​	二叉搜索树的节点放置规则是：任何节点的数据值一定大于其左子树中的每个节点的数据值，并小于其右子树中的每个节点的数据值。所以，在遍历二叉搜索树时，一直往左走就可以得到最小元素，一直往右走就可以得到最大元素。

​	查找最大值和最小值的代码实现如下：

```cpp
// 查找最小值
Node* findMin(Node* t) {
	if (t == NULL || t->left == NULL) return t;
	return findMin(t->left);
}

// 查找最大值
Node* findMax(Node* t) {
	if (t == NULL || t->right == NULL) return t;
	return findMax(t->right);
}
```

​	二叉搜索树的搜索时间复杂度与其自身高度 **h** 相关，通常为`O(h)`。但值得注意的是：在普通的 BST 中其自身高度 **h** 可能和元素 O(**N**) 一样高，即向右倾斜或向左倾斜的情况。

### BST 插入

​	二叉搜索树中插入新元素时，从根节点开始寻找插入位置，遇到数据值较大的节点就向左，遇到数据值较小的节点就向右。重复上述步骤一直到尾端，最终完成插入位置的寻找，然后插入新节点。

​	我们还是使用递归实现二叉搜索树的插入操作：

- 遇到数据值较大的节点就向左递归
- 遇到数据值较小的节点就向右递归
- 到达尾端，新建节点并插入

​    向上述二叉搜索树插入`9, 60`两个值的过程如下图：

![插入](/home/wang/Desktop/TechStack/ALGLearning/LeetCode_Cpp/LeetCodeNote/Tree/img/BST/插入.gif)

​	代码实现如下：

```cpp
Node* insert(Node* t, T x) {
	if (t == NULL) {
        t = new Node;
        t->data = x;
        t->left = t->right = NULL;
	} else if (x < t->data) {
        t->left = insert(t->left, x);
	} else if (x > t->data) {
        t->right = insert(t->right, x);
	}
	return t;
}
```

​	二叉搜索树插入的时间复杂度也是 `O(h)` ，其中 h 是 BST 的高度。同样的这个 **h** 在普通 BST 中可以和 O(**N**) 一样高，即向右倾斜或向左倾斜的情况。

### BST 删除的三种情况

​	二叉搜索树的删除操作还是通过与搜索操作相似先找到要删除的节点：

- 如果找不到目标节点，什么都不做。
- 如果找到了目标节点，这时需要考虑三个可能的删除情况：
  - 目标节点是叶子节点
  - 目标节点有一个子节点
  - 目标节点有两个子节点

#### 1 目标节点是叶子节点

​	第一种情况是最简单的，目标节点是当前二叉搜索树的叶子节点之一。

​	要删除叶子顶点很容易，我们只需要找到这个节点并将其删除就可以了，下图展示了删除上述二叉搜索树叶子节点`5`的过程。

![删除1](/home/wang/Desktop/TechStack/ALGLearning/LeetCode_Cpp/LeetCodeNote/Tree/img/BST/删除1.gif)

#### 2 目标节点有一个子节点

​	第二种情况也不是那么难：目标节点是当前二叉搜索树的非叶子节点，但是它只有一个子节点。

​	删除这个节点时我们只需要将该节点的唯一的子节点与该节点的父节点连接即可，下图展示了删除上述二叉搜索树中只有一个子节点`71`的过程。

![删除2](/home/wang/Desktop/TechStack/ALGLearning/LeetCode_Cpp/LeetCodeNote/Tree/img/BST/删除2.gif)

#### 3 目标节点有两个子节点

​	第三种情况是三者中最复杂的：目标节点是当前二叉搜索树中具有两个叶子节点的非叶子节点。

​	删除该节点需要进行如下步骤：

- 搜索二叉搜索树找到该节点
- 找到以该节点为根节点的右子树中的最小结点`findMin()`
- 使用右子树中的最小节点替代该节点
- 然后依据上述三种删除情况，**递归调整**其右子树的放置情况

​    下图展示了删除上述二叉搜索树具有两个叶子节点`6`的过程。
![删除3](/home/wang/Desktop/TechStack/ALGLearning/LeetCode_Cpp/LeetCodeNote/Tree/img/BST/删除3.gif)

​	二叉搜索树删除操作的代码实现如下：

```cpp
Node* remove(Node* t, T x) {
	Node* temp;
    // 搜索目标节点
	if (t == NULL) return NULL;
	else if (x < t->data) t->left = remove(t->left, x);
	else if (x > t->data) t->right = remove(t->right, x);
    // 情况 3
	else if (t->left && t->right) {
		temp = findMin(t->right);
        t->data = temp->data;
        t->right = remove(t->right, t->data);
    } else {
        temp = t;
        // 情况 2
        if (t->left == NULL) t = t->right;
        else if (t->right == NULL) t = t->left;
        // 情况 1
        delete temp;
    }
	return t;
}
```

​	二叉搜索树删除操作的时间复杂度也是 `O(h)` ，其中 h 是 BST 的高度，即使是第三种最复杂的情况时间复杂度也不会超过 `O(h)` 。同样的这个 **h** 在普通 BST 中可以和 O(**N**) 一样高，即向右倾斜或向左倾斜的情况。

## 平衡二叉搜索树

​	在二叉搜索树 BST 的介绍过程中，我们不断提到了操作的时间复杂度，其中除了中序遍历之外，大部分操作的时间复杂度都是 O(**h**) ，即与 BST 自身的高度相关。

​	而普通二叉搜索树可能会出现向右倾斜或向左倾斜的情况，即导致其高度为 `N-1`，从而使得二叉搜索树操作出现最坏情况时间复杂度为 O(**N**) 。

​	为了降低二叉搜索树操作的时间复杂度，我们将讨论**平衡二叉搜索树**的概念，以使得 `h = O(logN)`。

 	二叉树的极度平衡和极度不平衡状态如下图所示：

<img src="/home/wang/Desktop/TechStack/ALGLearning/LeetCode_Cpp/LeetCodeNote/Tree/img/BST/平衡BST.png" alt="平衡BST" style="zoom:80%;" />

​	树形结构是否平衡并没有绝对的衡量标准，它指的是没有任何一个节点深度过大。不同的平衡条件，可以实现不同的树形操作效率，也会带来不同的实现复杂度。

​	用的最多的平衡标准是：**其左子树和右子树均为平衡二叉树，且左子树和右子树的高度差的绝对值不超过 1**。这使得含有 N 个结点的平衡二叉树的最大深度为 `O(logN)`。

​	基于平衡二叉树的概念，已经有多种实现平衡二叉搜索树的数据结构，例如 `AVL-Tree, RB-Tree, B/B+ Tree`等，他们比一般的二叉搜索树复杂，但是能够保证高效的查找、插入和删除等操作。

## 自平衡二叉搜索树 AVL

### 什么是 AVL

​	AVL-Tree，是由两位俄罗斯（苏联）发明家 *Georgy Adelson-Velskii* 和 *Evgenii Landis* 在 1962 年提出的。

​	AVL-Tree 使用的平衡标准就是：**二叉搜索树所有非叶子节点的左子树和右子树均为平衡二叉树，且左子树和右子树的高度差的绝对值不超过 1**。该平衡条件就是为了确保整颗二叉搜索树的深度为`O(logN)`。

​	自平衡二叉搜索树 AVL 是带了自平衡功能的二叉搜索树。当对其进行插入或删除操作后破坏了平衡条件时，它能够进行调整，使整颗树的高度平衡为 `O(logN)`。

![AVL](/home/wang/Desktop/TechStack/ALGLearning/LeetCode_Cpp/LeetCodeNote/Tree/img/BST/AVL.png)

### 树的旋转

​	由于 AVL-Tree 的平衡条件，对其进行插入和删除操作后可能破坏整颗树的平衡，平衡被破坏后 AVL 能够自行进行调整恢复平衡。首先，找到平衡被破坏中的各个非叶子节点中深度最深的那一个。

​	由于二叉树最多有两个子节点，而平衡被破坏即为该节点的左右子树的高度相差 2。因此，以插入操作为例可以将平衡被破坏分为如下四种情况：

1. 插入左子节点的左子树  **LL**
2. 插入右子节点的右子树  **RR**
3. 插入左子节点的右子树  **LR**
4. 插入右子节点的左子树  **RL**

​    情况 1 和 2 又可以称为**外侧插入**，使用单旋转操作调整恢复平衡；情况 3 和 4 称为**内侧插入**，使用双旋转操作调整恢复平衡。

#### 1 LL 单旋转

​	上述 AVL-Tree 中的节点`20`，我们进行外侧插入，在其左子节点`11`的左子树插入新的节点`5`。这就破坏了整颗树的平衡，处于不平衡状态的节点有`41, 20`，而`20`的深度更大。

​	为了调整平衡状态，需要将以`6`为根节点的子树提高一层，将以`29`为根节点的子树下降一层，进行如下单向右旋步骤：

- 深度最大的不平衡状态的节点 node，即`20`
- node 的左孩子代替 node，即用`11`代替`20`，`41->left = 11`
- node 左孩子的右子树变为 node 的左子树，即将`20->left = 15`
- 将 node 作为其原始左孩子的右子树，即将`11->right = 20`

![AVL-LL](/home/wang/Desktop/TechStack/ALGLearning/LeetCode_Cpp/LeetCodeNote/Tree/img/BST/AVL-LL.gif)

​	AVL-Tree LL型调整操作的代码实现如下：（[代码来源](https://zhuanlan.zhihu.com/p/56066942)，如有侵权请告知）

```cpp
//LL型调整函数
//返回:新父节点
Node LL_rotate(Node node){
    //node为离操作结点最近的失衡的结点
    Node parent=NULL,son;
    //获取失衡结点的父节点
    parent=node->parent;
    //获取失衡结点的左孩子
    son=node->lchild;
    //设置son结点右孩子的父指针
    if (son->rchild!=NULL)  son->rchild->parent=node;
    //失衡结点的左孩子变更为son的右孩子
    node->lchild=son->rchild;
    //更新失衡结点的高度信息
    update_depth(node);
    //失衡结点变成son的右孩子
    son->rchild=node;
    //设置son的父结点为原失衡结点的父结点
    son->parent=parent;
    //如果失衡结点不是根结点，则开始更新父节点
    if (parent!=NULL){
        //如果父节点的左孩子是失衡结点，指向现在更新后的新孩子son
        if (parent->lchild==node){
            parent->lchild=son;
        }else{
             //父节点的右孩子是失衡结点
              parent->rchild=son;
        }
     }
    //设置失衡结点的父亲
    node->parent=son;
    //更新son结点的高度信息
    update_depth(son);
    return son;
}
```

#### 2 RR 单旋转

​	上述 AVL-Tree 中的节点`65`，我们进行外侧插入，在其左子节点`91`的右子树插入新的节点`100`。这就破坏了整颗树的平衡，处于不平衡状态的节点有`41, 65`，而`65`的深度更大。

​	为了调整平衡状态，需要将以`99`为根节点的子树提高一层，将以`50`为根节点的子树下降一层，进行如下单向左旋步骤：

- 深度最大的不平衡状态的节点 node，即`65`
- node 的右孩子代替 node，即用`91`代替`65`，`41->right = 91`
- node 右孩子的左子树变为 node 的右子树，即将`65->right = 72`
- 将 node 作为其原始右孩子的左子树，即将`91->left = 65`

![AVL-RR](/home/wang/Desktop/TechStack/ALGLearning/LeetCode_Cpp/LeetCodeNote/Tree/img/BST/AVL-RR.gif)

​	AVL-Tree RR型调整操作的代码实现如下：（[代码来源](https://zhuanlan.zhihu.com/p/56066942)，如有侵权请告知）

```cpp
/RR型调整函数
//返回新父节点
Node RR_rotate(Node node){
    //node为离操作结点最近的失衡的结点
    Node parent=NULL,son;
    //获取失衡结点的父节点
    parent=node->parent;
    //获取失衡结点的右孩子
    son=node->rchild;
    //设置son结点左孩子的父指针
    if (son->lchild!=NULL){
          son->lchild->parent=node;
    }
    //失衡结点的右孩子变更为son的左孩子
    node->rchild=son->lchild;
    //更新失衡结点的高度信息
    update_depth(node);
    //失衡结点变成son的左孩子
    son->lchild=node;
    //设置son的父结点为原失衡结点的父结点
    son->parent=parent;
    //如果失衡结点不是根结点，则开始更新父节点
    if (parent!=NULL){
        //如果父节点的左孩子是失衡结点，指向现在更新后的新孩子son
        if (parent->lchild==node){
            parent->lchild=son;
        }else{
            //父节点的右孩子是失衡结点
            parent->rchild=son;
        } 
    }
    //设置失衡结点的父亲
    node->parent=son;
    //更新son结点的高度信息
    update_depth(son);
    return son;
}
```

#### 3 LR 双旋转

​	上述 AVL-Tree 中的节点`20`，我们进行内侧插入，在其左子节点`11`的**右子树**插入新的节点`14`。这就破坏了整颗树的平衡，处于不平衡状态的节点有`41, 20`，而`20`的深度更大。

​	这种情况我们无法直接使用 LL 或者 RR 的单旋转完整调整，因为旋转之后仍然是不平衡的。为了调整平衡状态，需要将以`15`作为跳转子树的新根节点，这使得`11`必将成为`15`的左子节点，而`20`则将称为`15`的右子节点，这样就恢复了平衡状态。

​	这一过程需要进行两次单旋转，首先进行 RR 单向左旋转让`11`成为`15`的左孩子；然后进行 LL 单向右旋转让`20`成为`15`的右孩子。

![AVL-LR](/home/wang/Desktop/TechStack/ALGLearning/LeetCode_Cpp/LeetCodeNote/Tree/img/BST/AVL-LR.gif)

​	AVL-Tree LR型调整操作的代码实现如下：（[代码来源](https://zhuanlan.zhihu.com/p/56066942)，如有侵权请告知）

```cpp
//LR型，先左旋转，再右旋转
//返回：新父节点
Node LR_rotate(Node node){
    RR_rotate(node->lchild);
    return LL_rotate(node);
}
```

#### 4 RL 双旋转

​	上述 AVL-Tree 中的节点`65`，我们进行内侧插入，在其右子节点`91`的**左子树**插入新的节点`73`。这就破坏了整颗树的平衡，处于不平衡状态的节点有`41, 65`，而`65`的深度更大。

​	这种情况我们无法直接使用 LL 或者 RR 的单旋转完整调整，因为旋转之后仍然是不平衡的。为了调整平衡状态，需要将以`72`作为跳转子树的新根节点，这使得`91`必将成为`72`的右子节点，而`65`则将称为`72`的左子节点，这样就恢复了平衡状态。

​	这一过程需要进行两次单旋转，首先进行 LL 单向右旋转让`91`成为`72`的右孩子；然后进行 RR 单向左旋转让`65`成为`72`的右孩子。

![AVL-RL](/home/wang/Desktop/TechStack/ALGLearning/LeetCode_Cpp/LeetCodeNote/Tree/img/BST/AVL-RL.gif)

​	AVL-Tree RL型调整操作的代码实现如下：（[代码来源](https://zhuanlan.zhihu.com/p/56066942)，如有侵权请告知）

```cpp
//RL型，先右旋转，再左旋转
//返回:新父节点
Node RL_rotate(Node node){
    LL_rotate(node->rchild);
    return RR_rotate(node);
}
```

### AVL 插入与删除

#### 1 AVL 插入

​	介绍完树的旋转，其实就已经介绍完了 AVL-Tree 的核心步骤。

​	AVL-Tree 插入的总体步骤如下：

1. 和普通二叉搜索树插入过程一样，BST 插入
2. 从插入点向上走遍历 AVL-Tree 直到回到根节点。每遍历一个节点，我们更新处于不平衡状态节点的高度和平衡因子：
   - 如果存在不平衡状态的节点，停止在不平衡的第一个节点即深度最大的不平衡状态节点，其平衡因子为`+2 或 -2`
   - 使用四个树旋转案例中的一个来跳转二叉树，使其重新达到平衡状态

#### 2 AVL 删除

​	AVL 删除和 AVL 插入本质上是相似的方法，核心还是在于使用树旋转调整平衡状态。

​	AVL-Tree 删除的总体步骤如下：

1. 和普通二叉搜索树删除过程一样，使用三个删除案例中的一个进行 BST 删除
2. 在 AVL-Tree 中从删除点向上走直到回到根节点。每遍历一个节点，我们更新处于不平衡状态节点的高度和平衡因子：
   - 如果存在不平衡状态的节点，停止在不平衡的第一个节点即深度最大的不平衡状态节点，其平衡因子为`+2 或 -2`
   - 使用四个树旋转案例中的一个来跳转二叉树，使其重新达到平衡状态

**总结**

​	BST 插入和删除操作与AVL 的插入和删除操作相比的主要区别在于：可能会多次触发四种可能的需要重新平衡情况中的一种，但时间复杂度不会超过 `h = O(logN)`。



