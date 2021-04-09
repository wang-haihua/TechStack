### 双指针 Two Pointer

#### 什么是双指针

​	**双指针的用途：**双指针主要用于单循环遍历线性表数据结构，两个指针指向不同的元素，从而协同完成任务（通常双指针分别指向元素比较，或者两元素联合与某一条件比较）

​	**双指针的特点：**不管数据输入是字符串、数组还是链表，使用一般方法的遍历方法时间复杂度度在*O(n^3)*和*O(n^2)*使用双指针对其进行遍历的平均时间复杂度为*O(nlogn)*，最好的情况下时间复杂度为*O(n)*

​	**两种特殊形式的双指针**

> * 碰撞指针*Opposite directional*：两个指针指向同一线性表，但是遍历方向相反，一个指针指向开头，另一个指向末尾，它们相向移动直到相遇或满足其他特殊条件为止
> * 快慢指针*Equi-directional*：两个指针指向同一线性表，遍历方向相同，且两个指针起点可以相同，也可以不同形成一个滑动窗口，两个指针以不同的策略移动，直到两个指针的值相等或满足其他特殊条件为止

#### 一般双指针常见问题

**27. 移除元素**

>**题目：**一个数组 *nums* 和一个值 *val*，移除所有数值等于 *val* 的元素，并返回移除后数组的新长度（不考虑数组新长度后面的元素）
>
>**样例：**Input:  nums = [3,2,2,3], val = 3     Output: 2
>
>**解答：**用双指针方法解决，一个指针用于每步迭代判断该指针所指向的值和val是否一样，另一个指针记录其前面值与val不一样的个数。如果第一个指针当前值和val不一致了，此时需要把该值存储在第二个指针所指向的位置上，同时两指针都需要向右移动；如果第一个指针当前值和val一致，该指针需要继续向右移动，第二个指针则不改变位置，当第一个指针遍历完当前数组时结束循环。其过程如下图所示：
>
><img src="D:\01BasicLearning\02DataStructure\TwoPointer\移动元素.gif" alt="移动元素" style="zoom:100%;" />
>
>**代码：**
>
>```python
>class Solution {
>public:
>    int removeElement(vector<int>& nums, int val){
>        int pointer1 = 0, pointer2 = 0;
>        int nums_len = nums.size();
>        while(pointer1 < nums_len){
>            if(nums[pointer1] == val){
>                nums[pointer2] = val;
>                ++pointer2;
>            }
>            ++pointer1;
>        }
>        return pointer2;
>    }
>};
>```

**88. 合并两个有序数组**

>**题目：**两个有序整数数组 *nums1* 和 *nums2*，请你将 *nums2* 合并到 *nums1* 中*，*使 *nums1* 成为一个有序数组。
>
>**样例：**Input: nums1 = [1,2,3,0,0,0], m = 3 ；nums2 = [2,5,6], n = 3    Output: [1,2,2,3,5,6]
>
>**解答：**因为这两个数组已经排好序，所以可以把两个指针分别放在两个数组的末尾，即nums1 的m-1 位和nums2 的n-1 位。每次将较大的那个数字复制到nums1的后边，然后向前移动一位。因为还要要定位nums1的末尾，所以还需要第三个指针，以便复制。
>
>需要考虑两种特殊情况，一种是nums1元素为空，这种情况下直接将nums2中元素位置不变的移入nums1中即可；另一种则是nums1非空但是大部分元素大于nums2中的元素导致先于nums2遍历完，要考虑将nums2剩下的元素覆盖到nums1中。
>
>**代码：**
>
>```python
>class Solution{
>public:
>    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n){
>        int tail1 = m-1, tail2 = n-1, tail = m+n-1;
>        if(0 == tail1){
>            nums1 = nums2;
>        }
>        while(tail2 >= 0){
>            if(tail1 < 0){
>                nums1[tail--] = nums2[tail2--];
>                continue;
>            }
>            if(nums1[tail1] < nums2[tail2]){
>                nums1[tail--] = nums2[tail2--];
>            }else{
>                nums1[tail--] = nums1[tail1--];
>            }
>        }
>        for(int i =0; i< m+n; i++){
>            cout<<nums1[i]<<' ';
>        }
>        cout<<endl;
>    }
>};
>```

#### 碰撞指针常见问题

**167. Two Sum**

> **题目：**在一个增序的整数数组里找到两个数，使它们的和为给定值，已知有且只有一对解。
>
> **样例：**Input: numbers = [2,7,11,15], target = 9     Output: [1,2]  //输出一对解在数组中的坐标
>
> **解答：**因为数组已经排好序，我们可以采用碰撞指针来寻找这两个数字，一个指向数组开头head，一个指向数组末尾tail。判断这两个指针指向的元素之和TwoSum与target值的关系，如果大于target则将tail向左移动，如果小于target则将head向右移动，如果与target值相等则head和tail指向的元素为所找的一对解。
>
> ​	在本题中采用碰撞指针的搜索空间如下图所示，*head < tail*为该矩阵的上三角，可以看出该搜索空间的大小是*O(n^2)*数量级的，那么碰撞指针是怎么缩减搜索空间实现*O(n)*时间复杂度的呢？
>
> <img src="D:\01BasicLearning\02DataStructure\TwoPointer\twosum.png" alt="twosum" style="zoom:50%;" />
>
> ​	碰撞指针缩减搜索空间的关键在于它每一次移动指针都直接排除了一行或一列的搜索空间，例如当`TwoSum = numbers[head]+numbers[tail] < target`这时就将`head++`，因为tail已经对应的是最大值无需再去搜索本行中其他解，这样就直接排除了当前一行的搜索空间；同理，`TwoSum = numbers[head]+numbers[tail] > target`时就将`tail--`，此时head对应的是当前最小值也无需去搜索本列中其他解，这样就直接排除了head当前一列的搜索空间。完整过程如下图所示：
>
> <img src="D:\01BasicLearning\02DataStructure\TwoPointer\TwoSum.gif" alt="TwoSum" style="zoom: 25%;" />
>
> **代码：**
>
> ```python
> class Solution:
>     def twoSum(self, numbers: List[int], target: int) -> List[int]:
>         head = 0
>         tail = len(numbers) - 1
>         theSum = 0
>         while(head<tail):
>             theSum = numbers[head]+numbers[tail]
>             if(target == theSum):
>                 break
>             if theSum > target:
>                 tail -= 1
>             else:
>                 head += 1
>         return [head+1,tail+1]
> ```

**345. 反转字符串中的元音字母**

>**题目：**编写一个函数，以字符串作为输入，反转该字符串中的元音字母。
>
>**样例：**Input: "hello"    Output: "holle" 
>
>**解答：**反转字符串中的字符，需要用两个指针，使用碰撞指针，一个指针head从开头向左遍历找到一个元音字母时暂停，另一个指针tail从末尾向右遍历找到一个元音字母时将其指向的元素与head指向的元素交换；完成一对交换之后重复上述操作，继续找下一对可交换的元音字母，直到两指针相遇停止。
>
>**代码：**
>
>```python
>class Solution:
>    def reverseVowels(self, s: str) -> str:
>        if(s == "") : return ""
>        head = 0
>        tail = len(s) - 1
>        vowel_list = ['a','e','i','o','u','A','E','I','O','U']
>        s_list = list(s)
>        while(head < tail):
>            if(s_list[head] in vowel_list and s_list[tail] in vowel_list):
>                    temp = s_list[head]
>                    s_list[head] = s_list[tail]
>                    s_list[tail] = temp
>                    head += 1
>                    tail -= 1
>            if(s_list[head] not in vowel_list):
>                head += 1
>            if(s_list[tail] not in vowel_list):
>                tail -= 1
>        return "".join(s_list)
>```



#### 快慢指针常见问题
