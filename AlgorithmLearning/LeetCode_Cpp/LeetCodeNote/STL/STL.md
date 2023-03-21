## LeetCode刷题笔记 数据结构

### STL 容器

​	容器是可容纳各种数据类型（基本数据类型、对象等）的通用**数据结构**，都是**类模板**，分为三种类型：

* **顺序容器**：*vector, deque, list*  
* **关联容器**：*set, multiset, map, multimap* 
* **容器适配器**：*stack, queue, priority_queue*

**顺序容器**：

​	顺序容器是**非排序的**，而且其元素的插入位置与元素自身的值无关，数组便于查找，链表便于操作。

* *vector* `#include <vector>` 一维动态数组：其元素在内存中是**连续存放**的，随机存取任何元素都可以在常数时间内完成，在该容器的**尾部**增删元素也几乎能够在常熟时间内完成具有较好的性能。
* *deque* `#include <deque>` 双向队列：其元素在内存中是**连续存放**的，随机存取任何元素都可以在常数时间内完成，在该容器的**两端**增删元素也几乎能够在常熟时间内完成具有较好的性能。
* *list* `#include <list>` 双向链表：其元素在内存中是**不连续存放**的，不支持随机存取，在该容器的**任何位置**增删元素几乎都能够在常熟时间内完成具有较好的性能。

**关联容器**：

​	关联容器的元素是**排序的**，插入元素需要根据相应的排序规则来确定插入位置的，在查找时具有较好的性能。关联容器通常使用**平衡二叉树**实现，其插入和检索的时间都是 $O(log(N))$ 。

* *set/multiset* `#include <set>` 集合：*set* 集合中**不允许**存在相同的元素，*multiset* 集合中**允许**存在相同的元素。
* *map/multimap* `#include <map>` 键值对集合：*map* 和 *set* 的不同在于前者存放的元素有且仅有两个成员变量 `(first,second)`，一个名为 `first`，另一个名为 `second` ，`first` 的值用来对整体元素进行从小到大的排序，并可以通过 `first` 快速检索元素。和 *multiset* 类似 *multimap* 和 *map* 的区别中**允许**存在相同 `first` 值的元素。

**容器适配器**：

* *stack* `#include <stack>` 栈：栈是项都有限序列，并满足序列中被删除、检索和修改的项都只能是**最近插入**序列的项，即栈顶的项。满足**后进先出**规则
* *queue* `#include <queue>` 队列：（**入队**）插入只允许在尾部进行，（**出队**）删除、检索和修改只允许在头部进行。满足**先进先出**规则
* *priority_queue* `#include <queue>` 优先级队列：优先级最高的元素总是第一个出队列

**[更多关于C++ STL的内容请移步到此博文](https://blog.csdn.net/qq_41773806/category_9754474.html)**

### 01 数组

#### [448 找到所有数组中消失的数字](https://leetcode-cn.com/problems/find-all-numbers-disappeared-in-an-array/)

给定一个长度为 n 的数组，其中包含范围为 1 到 n 的整数，有些整数重复了多次，有些整数没有出现，求 1 到 n 中没有出现过的整数。

输入是一个一维整数数组，输出也是一个一维整数数组，表示输入数组内没出现过的数字。

> ```
> 输入：nums = [4,3,2,7,8,2,3,1]
> 输出：[5,6]
> ```

**解析：**

​	利用数组这种数据结构建立长度为 n 的标记数组，每一个标记表示对应位置的元素是否出现过。然后遍历一遍 nums 根据其元素情况修改标记数组对应元素。完成一遍遍历之后，标记数组中就已经记录了 nums 中所有元素出现情况，最后在遍历一遍标记数组就可以得到没出现的元素了。

| 数组 | [1,2,3,4,5,6,7,8] |
| :--: | :---------------: |
| nums | [4,3,2,7,8,2,3,1] |
| mask | [T,T,T,T,F,F,T,T] |

```cpp
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int len = nums.size();
        // 记录nums中元素存在情况
        vector<bool> mask(len,true);
        for(const auto num: nums){
            mask[num-1] = false;
        }
        // 找出不存在的元素
        vector<int> ans;
        for(int i=0;i<len;++i){
            if(mask[i]){
                ans.push_back(i+1);
            }
        }
        return ans;
    }
};
```

​	进一步地，可以直接对原数组进行标记：把重复出现的数字在原数组出现的位置设为负数，最后仍然为正数的位置即为没有出现过的数。

#### [48 旋转图像](https://leetcode-cn.com/problems/rotate-image/)

给定一个 n × n 的矩阵，在尽量不创建额外储存空间的情况下，求它顺时针旋转 90 度的结果，且必须在原矩阵上修改（in-place）。

输入和输出都是一个二维整数矩阵。

> ```
> 输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
> 输出：[[7,4,1],[8,5,2],[9,6,3]]
> ```

**解析：**

​	本题可以每次只考虑矩阵一圈中的 4 个间隔90度的元素的旋转情况，设置两层循环：外层循环用于一圈一圈的遍历矩阵，内循环用于旋转一圈上的元素。

​	旋转公式主要与遍历的当前圈层相关，例如，矩阵长度`len = n + 1`，则第 i 圈中与`[i][j]`参与旋转的其他3个元素分别为`[j][n-j], [n-i][n-j], [n-j][i]` 他们的旋转公式为：

```cpp
// 以下图示例中的 2,8,15,9 为例
temp = matrix[j][n-i]; // 8
matrix[j][n-i] = matrix[i][j]; // 2
matrix[i][j] = matrix[n-j][i]; // 9
matrix[n-j][i] = matrix[n-i][n-j]; // 15
matrix[n-i][n-j] = temp;
// 经过上述旋转得到 9,2,8,15
```

<img src="/home/wang/Desktop/TechStack/ALGLearning/LeetCode_Cpp/LeetCodeNote/STL/img/48.png" alt="48" style="zoom:50%;" />

```cpp
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size() - 1;
        for(int i=0;i<=n/2;++i){
            // 子矩阵的第一个元素是[i][n-i],最后一个元素是[n-i][n-i]
            for(int j=i;j<n-i;++j){
                int tmp = matrix[j][n-i];
                matrix[j][n-i] = matrix[i][j];
                matrix[i][j] = matrix[n-j][i];
                matrix[n-j][i] = matrix[n-i][n-j];
                matrix[n-i][n-j] = tmp;
            }
        }
    }
};
```

#### [240 搜索二维矩阵 II](https://leetcode-cn.com/problems/search-a-2d-matrix-ii/)

给定一个二维矩阵，已知每行和每列都是增序的，尝试设计一个快速搜索一个数字是否在矩阵中存在的算法。

输入是一个二维整数矩阵，和一个待搜索整数。输出是一个布尔值，表示这个整数是否存在于矩阵中。

> 输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
> 输出：true

**解析：**

本题可以利用矩阵中元素的增序快速缩减搜索空间，每一行是增序的，每一列是增序的。

那么我们从矩阵的右上角开始查找：

* 如果当前值大于目标值那么就直接排除了当前列，向左移动一位
* 如果当前值小于搜索值，由于我们已经搜索了当前行当前值右侧的所有元素，其左侧的值均小于当前值，因此可以直接排除当前行，向下移动一位
* 如果最终移动到左下角时仍没有找到目标值，则说明待搜索值不存在于矩阵中

```cpp
class Solution {
public:
    bool searchMatrix_2(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()||matrix[0].empty()){
            return false;
        }
        int m = matrix.size(), n = matrix[0].size();
        int i = 0, j = n-1;
        while(i<m && j>=0){
            if(matrix[i][j] == target){
                return true;
            }else if(matrix[i][j] > target){
                // 大于目标值向左移动一步
                --j;
            }else{
                // 小于目标值向下移动一步
                ++i;
            }
        }
        return false;
    }
};
```

#### [769 最多能完成排序的块](https://leetcode-cn.com/problems/max-chunks-to-make-sorted/)

给定一个含有 0 到 n 整数的数组，每个整数只出现一次，求这个数组最多可以分割成多少个子数组，使得对每个子数组进行增序排序后，原数组也是增序的。

输入一个一维整数数组，输出一个整数，表示最多的分割数。

> 输入: arr = [1,0,2,3,4]
> 输出: 4
> 解释: 可以把它分成两块，例如 [1, 0], [2, 3, 4]。然而，分成 [1, 0], [2], [3], [4] 可以得到最多的块数。

**解析：**

从左往右遍历，同时记录当前的最大值，每当当前最大值等于数组位置时，我们可以多一次分割。

为什么可以通过这个算法解决问题呢？

如果当前最大值大于数组位置，则说明右边一定有小于数组位置的数字，需要把它也加入待排序的子数组；又因为数组只包含不重复的 0 到 n，所以当前最大值一定不会小于数组位置。所以每当当前最大值等于数组位置时，假设为 p，我们可以成功完成一次分割，并且其与上一次分割位置 q 之间的值一定是 q + 1 到 p 的所有数字。

```cpp
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int cur_max = INT_MIN;
        int ans = 0;
        for(int i=0;i<arr.size();++i){
            cur_max = max(cur_max,arr[i]);
            if(cur_max == i){
                ++ans;
            }
        }
        return ans;
    }
};
```

