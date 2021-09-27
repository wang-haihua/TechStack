## LeetCode刷题笔记 动态规划

### 01 一维动态规划

#### [70 爬楼梯](https://leetcode-cn.com/problems/climbing-stairs/)

给定 n 节台阶，每次可以走一步或走两步，求一共有多少种方式可以走完这些台阶。

输入是一个数字，表示台阶数量；输出是爬台阶的总方式。

> ```
> 输入： 2
> 输出： 2
> 解释： 有两种方法可以爬到楼顶。
> 1.  1 阶 + 1 阶
> 2.  2 阶
> ```

**解析:**

​	这是十分经典的斐波那契数列题。

​	设置状态：定义一个数组 dp，`dp[i]` 表示走到第 i 阶的方法数

​	状态转移方程：因为我们每次可以走一步或者两步，所以第 i 阶可以从第 i-1 或 i-2 阶到达。换句话说，走到第 i 阶的方法数即为走到第 i-1 阶的方法数加上走到第 i-2 阶的方法数。这样我们就得到了状态转移方程`dp[i] = dp[i-1] + dp[i-2]`。

​	初始情况：当阶数小于等于1时，方法数为1

```cpp
class Solution {
public:
    int climbStairs(int n) {
        if(n<2) return n;
        vector<int> dp(n+1);
        dp[0] = dp[1] = 1;
        for(int i=2;i<=n;++i){
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }
};
```

#### [198 打家劫舍](https://leetcode-cn.com/problems/house-robber/)

假如你是一个劫匪，并且决定抢劫一条街上的房子，每个房子内的钱财数量各不相同。如果你抢了两栋相邻的房子，则会触发警报机关。求在不触发机关的情况下最多可以抢劫多少钱。

输入是一个一维数组，表示每个房子的钱财数量；输出是劫匪可以最多抢劫的钱财数量。

> 输入：[1,2,3,1]
> 输出：4
> 解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。偷窃到的最高金额 = 1 + 3 = 4 。

**解析:**

​	设置状态：定义一个数组 dp，`dp[i]` 表示抢劫到第 i 个房子时，可以抢劫的最大数量。
​	状态转移方程：我们考虑 `dp[i]`，此时可以抢劫的最大数量有两种可能，一种是我们选择不抢劫这个房子，此时累计的金额即为`dp[i-1]`；另一种是我们选择抢劫这个房子，那么此前累计的最大金额只能是 `dp[i-2]`，因为我们不能够抢劫第 i-1 个房子，否则会触发警报机关。因此本题的状态转移方程为 `dp[i] = max(dp[i-1],nums[i-1] + dp[i-2])`。

​	初始情况：第一个房子的抢劫最大数量 `dp[1] = nums[0]`

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()){
            return 0;
        }
        int len = nums.size();
        vector<int> dp(len+1,0);
        dp[1] = nums[0];
        for(int i=2;i<=len;++i){
            dp[i] = max(dp[i-1],dp[i-2]+nums[i-1]);
        }
        return dp[len];
    }
};
```

#### [213 打家劫舍 II](https://leetcode-cn.com/problems/house-robber-ii/)

假如你是一个劫匪，并且决定抢劫一条街上的房子，这条街所有的房屋都 **围成一圈** ，这意味着第一个房屋和最后一个房屋是紧挨着的。如果你抢了两栋相邻的房子，则会触发警报机关。求在不触发机关的情况下最多可以抢劫多少钱。

输入是一个一维数组，表示每个房子的钱财数量；输出是劫匪可以最多抢劫的钱财数量。

> ```
> 输入：nums = [2,3,2]
> 输出：3
> 解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）, 因为他们是相邻的。
> ```

**解析:**

​	本题与198题的主要区别是输入的一维数组是一个环形数组，所以要分别考虑抢第一个房子和不抢第一个房子的情况。抢第一个房子，那么就不能抢最后一个房子，则可抢的范围为`nums[0]~nums[len-2]`；不抢第一个房子，那么就可以抢最后一个房子，则可抢的范围为`nums[1]~nums[len-1]`。

​	基于上述两种情况使用与198题相同的动态规划方法解决本问题

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int len = nums.size();
        if(len < 1) return 0;
        vector<int> nums1,nums2;
        for(int i=0;i<len;++i){
            if(i==0){
                nums1.push_back(nums[i]);
            }else if(i==len-1){
                nums2.push_back(nums[i]);
            }else{
                nums1.push_back(nums[i]);
                nums2.push_back(nums[i]);
            }
        }
        return max(robRange(nums1),robRange(nums2));
    }

    int robRange(vector<int>& nums){
        int len = nums.size();
        if(len < 1) return 0;
        vector<int> dp(len+1,0);
        dp[1] = nums[0];
        for(int i=2;i<=len;++i){
            dp[i] = max(dp[i-1],dp[i-2]+nums[i-1]);
        }
        return dp[len];
    }
};
```

​	上述解法较为直观，先分情况在计算最大抢劫价值；也可以通过划分区间的方式划分情况如下

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int len = nums.size();
        if(len == 1) return nums[0];
        return max(robRange(nums,0,len-1),robRange(nums,1,len));
    }

    int robRange(vector<int>& nums, int start, int end){
        int len = end - start;
        if(len < 1) return 0;
        vector<int> dp(len+1,0);
        dp[1] = nums[start];
        for(int i=2;i<=len;++i){
            dp[i] = max(dp[i-1],dp[i-2]+nums[i+start-1]);
        }
        return dp[len];
    }
};
```

#### [413 等差数列划分](https://leetcode-cn.com/problems/arithmetic-slices/)

给定一个数组，求这个数组中连续且等差的子数组一共有多少个。

输入是一个一维数组，输出是满足等差条件的连续字数组个数。

> ```
> 输入：nums = [1,2,3,4]
> 输出：3
> 解释：nums 中有三个子等差数组：[1, 2, 3]、[2, 3, 4] 和 [1,2,3,4] 自身。
> ```

**解析:**

​	这道题略微特殊，因为要求是等差数列，可以很自然的想到子数组必定满足 `num[i] - num[i-1] = num[i-1] - num[i-2]`。然而由于我们对于 dp 数组的定义通常为以 i 结尾的，满足某些条件的子数组数量，而等差子数组可以在任意一个位置终结，因此此题在最后需要对 dp 数组求和。

```cpp
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int len = nums.size();
        int res = 0;
        if(len < 3){
            return res;
        }
        vector<int> dp(len,0);
        for(int i = 2;i<len;++i){
            if(nums[i]-nums[i-1] == nums[i-1] - nums[i-2]){
                dp[i] = dp[i-1] + 1;
                res += dp[i];
            }
        }
        return res;
    }
};
```

#### [53 最大子序和](https://leetcode-cn.com/problems/maximum-subarray/)

给定一个数组，找出一个具有最大和的连续子数组，并返回其最大和。

输入一个数组，输出一个整数，为连续子数组的最大和

> ```
> 输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
> 输出：6
> 解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
> ```

**解析:**

​	设置状态：使用一维数组`dp[i]`表示以第 i 个元素结尾的子序列的最大和

​	状态转移方程：我们考虑 `dp[i]`，此时构成最大和的子序列有两种可能，一种是我们选择不将第 i 个元素加入子序列，因为要构成连续的子序列，所以自己单独构成新的子序列此时最大和即为自身`nums[i-1]`；另一种是我们选择将第 i 个元素加入子序列，那么构成子序列的最大和为`dp[i-1]+nums[i-1]`。所以本题的状态转移方程为 `dp[i] = max(nums[i-1],nums[i-1] + dp[i-1])`。

​	初始情况：只有一个元素，`dp[1]=nums[0]`

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len = nums.size();
        if(len < 1) return 0;
        vector<int> dp(len+1,0);
        dp[1] = nums[0];
        int ans = nums[0];
        for(int i=2;i<=len;++i){
            dp[i] = max(nums[i-1],dp[i-1]+nums[i-1]);
            ans = max(ans,dp[i]);
        }
        return ans;
    }
};
```

### 02 二维动态规划

#### [64 最小路径和](https://leetcode-cn.com/problems/minimum-path-sum/)

给定一个 m × n 大小的非负整数矩阵，求从左上角开始到右下角结束的、经过的数字的和最小的路径。每次只能向右或者向下移动。

输入是一个二维数组，输出是最优路径的数字和。

> ```
> 输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
> 输出：7
> 解释：因为路径 1→3→1→1→1 的总和最小。
> ```

**解析:**

​	设置状态：使用一个二维的 dp 数组，其中 `dp[i][j]` 表示从左上角开始到 (i, j) 位置的最
优路径的数字和。

​	状态转移方程：因为每次只能向下或者向右移动，我们可以很容易得到状态转移方程 `dp[i][j] =
min(dp[i-1][j], dp[i][j-1]) + grid[i][j]`，其中 grid 表示原数组。

​	 边界条件：只有一格`dp[0][0] = grid[0][0]`；第一行的元素只能由前一个元素向右移动得到即`dp[0][j] = dp[0][j-1]+grid[0][j]`；第一列的元素只能由上一个元素向下移动得到即`dp[i][0] = dp[i-1][0]+grid[i][0]`

```cpp
class Solution {
public:
    int minPathSum_old(vector<vector<int>>& grid) {
        int ans = 0;
        if(grid.empty()||grid[0].empty()){
            return ans;
        }
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m,vector<int>(n));
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
                if(i==0&&j==0){
                    dp[i][j] = grid[0][0];
                }else if(i==0){
                    dp[i][j] = dp[i][j-1] + grid[i][j];
                }else if(j==0){
                    dp[i][j] = dp[i-1][j] + grid[i][j];
                }else{
                     dp[i][j] = min(dp[i][j-1],dp[i-1][j]) + grid[i][j];
                }
            }
        }
        return dp[m-1][n-1];
    }
};
```

​	因为 dp 矩阵的每一个值只和左边和上面的值相关，我们可以使用空间压缩将 dp 数组压缩为一维。对于第 i 行，在遍历到第 j 列的时候，因为第 j-1 列已经更新过了，所以 `dp[j-1]` 代表 `dp[i][j-1]`的值；而 `dp[j]` 待更新，当前存储的值是在第 i-1 行的时候计算的，所以代表 `dp[i-1][j]`的值。

#### [542 01矩阵](https://leetcode-cn.com/problems/01-matrix/)

给定一个由 0 和 1 组成的二维矩阵，求每个位置到最近的 0 的距离。

输入是一个二维 0-1 数组，输出是一个同样大小的非负整数数组，表示每个位置到最近的 0的距离。

> ```
> 输入：mat = [[0,0,0],[0,1,0],[1,1,1]]
> 输出：[[0,0,0],[0,1,0],[1,2,1]]
> ```

**解析:**

​	本题涉及到四个方向上的最近搜索，如果使用递归的方法进行搜索在二维数组中将造成极大的时间复杂度。使用动态规划进行存储化，可以使得递归搜索不会重复遍历相同位置；另一种更简单的方法是，从左上到右下进行一次动态搜索，再从右下到左上进行一次动态搜索，这样两次动态搜索即可完成四个方向上的查找。

​	设置状态：使用一个二维数组 `dp[i][j]` 表示位置为 (i,j) 的元素与0的距离

​	状态转移方程：值为0的元素到0的距离为0；从左上到右下进行动态搜索，那么`dp[i][j]` 可以从`dp[i-1][j]`、`dp[i][j-1]`和自身三个状态中转移得到`dp[i][j]=min(dp[i][j],min(dp[i-1][j],dp[i][j-1])) + 1`； 从右下到左上进行动态搜索的状态转移方程可以类比得到`dp[i][j]=min(dp[i][j],min(dp[i+1][j],dp[i][j+1])) + 1`

​	边界情况：当`d[i][j]`处于矩阵的边界上时其状态转移受到限制，例如，从左上到右下进行动态搜索时处于第一行的元素状态仅能从自身和前一个状态转移得到，而第一列的元素状态仅能从自身和上一个状态转移得到。

```cpp
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        if(mat.empty()||mat.empty()){
            return {};
        }
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dp(m, vector<int>(n,INT_MAX-1)); // INT_MAX会在特殊用例中报错
        // 从左上到右下进行动态搜索
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
                if(mat[i][j]==0){
                    dp[i][j] = 0;
                }else{
                    // 区分边界情况
                    if(j>0){
                        dp[i][j] = min(dp[i][j], dp[i][j-1]+1);
                    }
                    if(i>0){
                        dp[i][j] = min(dp[i][j], dp[i-1][j]+1);
                    }
                }
            }
        }
        // 从右下到左上进行动态搜索
        for(int i=m-1;i>=0;--i){
            for(int j=n-1;j>=0;--j){
                if(mat[i][j]){
                    if(j<n-1){
                        dp[i][j] = min(dp[i][j], dp[i][j+1]+1);
                    }
                    if(i<m-1){
                        dp[i][j] = min(dp[i][j], dp[i+1][j]+1);
                    }
                }
            }
        }
        return dp;
    }
};
```

#### [221 最大正方形](https://leetcode-cn.com/problems/maximal-square/)

给定一个二维的 0-1 矩阵，求全由 1 构成的最大正方形面积。

输入是一个二维 0-1 数组，输出是最大正方形面积。

> 输入：matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
> 输出：4

**解析:**

​	对于**在矩阵内搜索正方形或长方形的题型**，一种常见的做法是定义一个二维 dp 数组，其中`dp[i][j] `表示满足题目条件的、以 (i, j) 为右下角的正方形或者长方形的属性。对于本题，则表示以 (i, j) 为右下角的全由 1 构成的最大正方形面积。

​	设置状态：定义一个二维 dp 数组，其中`dp[i][j] `表示以 (i, j) 为右下角的全由 1 构成的最大正方形面积

​	状态转移方程：如果当前位置是 0，那么 `dp[i][j]` 即为 0；如果当前位置是 1，我们假设 `dp[i][j] = k^2` ，其充分条件为 `dp[i-1][j-1]`、`dp[i][j-1] `和 `dp[i-1][j] `的值必须都不小于 `(k − 1)^2` ，否则 (i, j) 位置不可以构成一个边长为 k 的正方形。同理，如果这三个值中的最小值为 k − 1，则 (i, j) 位置一定且最大可以构成一个边长为 k 的正方形。所以状态转移方程为`dp[i][j] = min(dp[i-1][j-1], min(dp[i][j-1], dp[i-1][j])) + 1`

​	初始情况：仅有一个方格构成正方形`dp[0][0] = 1`

```cpp
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if(matrix.empty()||matrix[0].empty()){
            return 0;
        }
        int m = matrix.size(), n = matrix[0].size();
        int maxSize = 0;
        vector<vector<int>> dp(m+1,vector<int>(n+1));
        for(int i=1;i<=m;++i){
            for(int j=1;j<=n;++j){
                if(matrix[i-1][j-1] == '1'){
                	dp[i][j] = min(min(dp[i][j-1],dp[i-1][j]),dp[i-1][j-1]) + 1;
                }
                maxSize = max(dp[i][j],maxSize);
            }
        }
        return maxSize * maxSize;
    }
};
```

### 03 分割型动态规划

​	对于分割类型题，动态规划的状态转移方程通常并不依赖相邻的位置，而是依赖于满足分割条件的位置。

#### [279 完全平方数](https://leetcode-cn.com/problems/perfect-squares/)

给定一个正整数，求其最少可以由几个完全平方数相加构成。

输入是给定的正整数，输出也是一个正整数，表示输入的数字最少可以由几个完全平方数相加构成。

> ```
> 输入：n = 12
> 输出：3 
> 解释：12 = 4 + 4 + 4
> ```

**解析：**

​	设置状态：定义一个一维矩阵 dp，其中 `dp[i]` 表示数字 i 最少可以由几个完全平方数相加构成

​	状态转移方程：在本题中，位置 i 只依赖 `i - k^2` 的位置，如 i - 1、i - 4、i - 9 等等，才能满足完全平方分割的条件。因此数字 i 可以取的最小值为 `dp[i] = 1 + min(dp[i-1], dp[i-4], dp[i-9], ....... )`

​	初始情况：0 无法由任一个完全平方数相加构成，即`dp[0]=0`

```cpp
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1,INT_MAX);
        dp[0] = 0;
        for(int i=1;i<=n;++i){
            for(int j=1;i-j*j>=0;++j){
                dp[i] = min(dp[i],dp[i-j*j]+1);
            }
        }
        return dp[n];
    }
};
```

#### [343 整数拆分](https://leetcode-cn.com/problems/integer-break/)

给定一个正整数 *n*，将其拆分为**至少**两个正整数的和，并使这些整数的乘积最大化。

输入是给定的正整数，输出也是一个正整数，表示输入的数字拆分获得的最大乘积。

> ```
> 输入: 10
> 输出: 36
> 解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。
> ```

**解析：**

​	本题和279题相似，位置 i 依赖于 i - j 的位置

​	设置状态：定义一个一维矩阵 dp，其中 `dp[i]` 表示数字 i 拆分可以获得的最大乘积

​	状态转移方程：将 i 拆分分为两种情况，第一种是仅拆分为两个数即 i 和 i - j，不再拆分为更多正整数，这种情况的乘积为 `j*(i-j)`；第二种是拆分出第一个正整数 j 后，将 i - j 继续拆分为多个正整数，这种情况乘积为`j*dp[i-j]`。所以在拆分的第一个数 j 固定的情况下状态转移方程为`dp[i] = max(j*(i-j),j*dp[i-j])`。由于 *j* 的取值范围是 1 到 i - 1，需要遍历所有的 *j* 得到 `dp[i]` 的最大值，因此可以得到状态转移方程`dp[i] = max(dp[i],max(j*(i-j),j*dp[i-j]))`。

​	初始情况：0 不是正整数，1 是最小的正整数，0 和 1 都不能拆分，因此 `dp[0] = dp[1] = 0`

```cpp
class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n+1,0);
        for(int i=2;i<=n;++i){
            for(int j=1;j<i;++j){
                dp[i] = max(dp[i],max(j*(i-j),j*dp[i-j]));
            }
        }
        return dp[n];
    }
};
```

#### [91 解码方法](https://leetcode-cn.com/problems/decode-ways/)

已知字母 A-Z 可以表示成数字 1-26。给定一个数字串，求有多少种不同的字符串等价于这个数字串。

输入是一个由数字组成的字符串，输出是满足条件的解码方式总数。

> ```
> 输入：s = "226"
> 输出：3
> 解释：它可以解码为 "BZ" (2 26), "VF" (22 6), 或者 "BBF" (2 2 6) 
> ```

**解析：**

​	本题的特殊情况较多因为只有 1-26 可以表示字母，所以对于一些特殊情况，比如数字 0 或者当相邻两数字大于 26 时，需要有不同的状态转移方程。本人对此题还存在一些疑惑，仅贴出代码，欢迎解惑。

```cpp
class Solution {
public:
    int numDecodings(string s) {
        int n = s.length();
        if(n==0){
            return 0;
        }
        int prev = s[0] - '0';
        if(!prev){
            return 0;
        }
        if(n==1){
            return 1;
        }
        vector<int> dp(n+1,1);
        for(int i=2;i<=n;++i){
            int cur = s[i-1] - '0';
            if((prev==0 || prev>2) && cur == 0){
                return 0;
            }
            if((prev < 2 && prev>0) || prev == 2 && cur < 7){
                if(cur){
                    dp[i] = dp[i-2] + dp[i-1];
                }else{
                    dp[i] = dp[i-2];
                }
            }else{
                dp[i] = dp[i-1];
            }
            prev = cur;
        }
        return dp[n];
    }
};
```

#### [139 单词拆分](https://leetcode-cn.com/problems/word-break/)

给定一个字符串和一个字符串集合，求是否存在一种分割方式，使得原字符串分割后的子字符串都可以在集合内找到。

> 输入: s = "applepenapple", wordDict = ["apple", "pen"]
> 输出: true
> 解释: 返回 true 因为 "applepenapple" 可以被拆分成 "apple pen apple"；注意你可以重复使用字典中的单词。

**解析：**

​	本题类似于完全平方数分割问题，这道题的分割条件由集合内的字符串决定，因此在考虑每个分割位置时，需要遍历字符串集合，以确定当前位置是否可以成功分割。

​	设置状态：用一个一维数组 `dp[i]` 表示开头到以 i 位置结束的子串是否能够在集合中找到

​	状态转移方程：如果开头到以 j 结尾的子串都能在集合中找到，且从 j 到 i 的子串也能够在集合中找到那么 `dp[i] = true`

​	初始情况：字符串和集合都为空时为真，`dp[0]=true`

```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordDictSet;
        for(const auto w: wordDict){
            wordDictSet.insert(w);
        }
        int n = s.length();
        vector<bool> dp(n+1,false);
        dp[0] = true;
        for(int i=1;i<=n;++i){
            for(int j=0;j<i;++j){
                // 分割类型动态规划：dp[i] = s[0]到s[j-1]为true && s[j]到s[i-j]子串在字典中
                if(dp[j] && wordDictSet.find(s.substr(j,i-j)) != wordDictSet.end()){
                    dp[i] = true;
                    // dp[i] 表示的是 s[0]到s[i-1]的子串中单词是否出现在字典中
                    break;
                }
            }
        }
        return dp[n];
    }
};
```

### 04 子序列问题

​	对于子序列问题，第一种动态规划方法是，定义一个 `dp` 数组，其中 `dp[i] `表示以 i 结尾的子序列的性质。在处理好每个位置后，统计一遍各个位置的结果即可得到题目要求的结果。第二种动态规划方法是，定义一个 `dp `数组，其中 `dp[i]` 表示到位置 i 为止的子序列的性质，**并不必须以 i 结尾**。这样 `dp` 数组的最后一位结果即为题目所求，不需要再对每个位置进行统计。

#### [300 最长递增子序列](https://leetcode-cn.com/problems/longest-increasing-subsequence/)

给定一个未排序的整数数组，求最长的递增子序列。

输入是一个一维数组，输出是一个正整数，表示最长递增子序列的长度。

>```
>输入：nums = [10,9,2,5,3,7,101,18]
>输出：4
>解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
>```

**解析:**

​	设置状态：使用一个一维数组`dp[i]` 可以表示以 i 结尾的、最长子序列长度。

​	状态转移方程：对于每一个位置 i，如果其之前的某个位置 j 所对应的数字小于位置 i 所对应的数字，则可以获得一个以 i 结尾的、长度为 `dp[j] + 1` 的子序列，即`dp[i] = max(dp[i],dp[j]+1)`。为了遍历所有情况，我们需要 i 和 j 进行两层循环，并记录最大值。

​	初始情况：`dp[0] = 0, dp[1] = 1`

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = nums.size();
        // 将所有位置初始化为 1, 因为len>=1,所以最短递增子序列就是 1 
        vector<int> dp(len,1); 
        int ans = 1;
        // i 控制每一个记录位置
        for(int i=1;i<len;++i){ 
            // j 扫描 i 之前的子序列
            for(int j=0;j<i;++j){ 
                // 如果出现递增情况，判断是否增加的子序列长度
                if(nums[i]>nums[j]){ 
                    dp[i] = max(dp[i],dp[j]+1);
                }
            }
            // 完成一个位置的记录之后，判断是否是较大长度
            ans = max(ans,dp[i]);
        }
        return ans;
    }
};
```

#### [646 最长数对链](https://leetcode-cn.com/problems/maximum-length-of-pair-chain/)

给出 `n` 个数对，在每一个数对中，第一个数字总是比第二个数字小。对于数对`(a,b),(c,d)`如果 b < c则这两个数对可以构成数对链

输入一个数对集合，输出一个整数表示能够形成的最长数对链的长度。

> ```
> 输入：[[1,2], [2,3], [3,4]]
> 输出：2
> 解释：最长的数对链是 [1,2] -> [3,4]
> ```

**解析:**

​	本题和300题本质上是一样的，不同在于递增序列由数对构成。另外需要考虑数对出现的次序并不影响它是否能够加入数对链，所以在使用类似于300题的动态规划方法计算最长数对链长度之前需要对其进行排序，简化元素选择。本题中以区间（数对）结尾排序。

```cpp
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        int len = pairs.size();
        if(len < 1) return 0; 
        sort(pairs.begin(),pairs.end(),[](vector<int> a, vector<int> b){ return a[1]<b[1];});
        vector<int> dp(len,1);
        int ans = 1;
        for(int i=1;i<len;++i){
            for(int j=0;j<i;++j){
                if(pairs[j][1]<pairs[i][0]){
                    dp[i] = max(dp[i],dp[j]+1);
                }
            }
            ans = max(ans,dp[i]);
        }
        return ans;
    }
};
```

#### [376 摆动序列](https://leetcode-cn.com/problems/wiggle-subsequence/)

如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为**摆动序列**。给你一个整数数组 `nums` ，返回 `nums` 中作为 **摆动序列** 的 **最长子序列的长度** 。

输入是一个一维数组，输出是一个正整数，表示作为摆动序列的最长子序列的长度。

> 输入：nums = [1,17,5,10,13,15,10,5,16,8]
> 输出：7
> 解释：这个序列包含几个长度为 7 摆动序列。其中一个是 [1, 17, 10, 13, 10, 16, 8] ，各元素之间的差值为 (16, -7, 3, -3, 6, -8) 。

**解析:**

​	本题和递增子序列的差别在于摆动序列的元素选择取决于前一个被选元素的大小，既可以上升也可以下降。

​	设置状态：使用一个二维数组`dp[i][j]`表示前 i 个元素中的某一个为结尾的最长摆动序列长度，其中 j 取值为 0 和 1分别表示上升摆动序列和下降摆动序列。上升摆动序列是指最后一个元素是呈上升趋势的摆动序列，下降摆动序列同理。`d[i][0]`表示以前 i 个元素中的某一个为结尾的最长的上升摆动序列的长度；`dp[i][1]`以前 i 个元素中的某一个为结尾的最长的下降摆动序列的长度。

​	状态转移方程：考虑第 i 个元素，如果`nums[i] > nums[i-1]`，则该元素可以加入下降摆动序列形成上升摆动序列`dp[i][0] = max(dp[i-1][0],dp[i-1][1] + 1)`，但是该元素加入上升摆动序列并不会形成下降摆动序列`dp[i][1] = dp[i-1][1]`；如果`nums[i] < nums[i-1]`，则该元素可以加入上升摆动序列形成下降摆动序列`dp[i][1] = max(dp[i-1][1],dp[i-1][0] + 1)`，如果该元素加入下降摆动序列并不会形成上升摆动序列所以`dp[i][0] = dp[i-1][0]`；如果`nums[i] == nums[i-1]`那么可以直接跳过该元素`dp[i][0] = dp[i-1][0], dp[i][1] = dp[i-1][1]`。

​	初始情况：当只有一个元素时，该元素既是上升摆动序列也是下降摆动序列，`dp[0][j] = 1;`

```cpp
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int len = nums.size();
        if(len < 2) return len;
        vector<vector<int>> dp(len,vector<int>(2,1));
        int ans = 1;
        for(int i=1;i<len;++i){
            if(nums[i] < nums[i-1]){
                dp[i][0] = dp[i-1][0];
                dp[i][1] = max(dp[i-1][1],dp[i-1][0] + 1);
            }else if(nums[i] > nums[i-1]){
                dp[i][0] = max(dp[i-1][0],dp[i-1][1] + 1);
                dp[i][1] = dp[i-1][1];
            }else{
                dp[i][0] = dp[i-1][0];
                dp[i][1] = dp[i-1][1];
            }
            ans = max(ans,max(dp[i][0],dp[i][1]));
        }
        return ans;
    }
};
```

​	本题也可以采用贪心策略解决，使用极值构成最长摆动序列。

#### [1143 最长公共子序列](https://leetcode-cn.com/problems/longest-common-subsequence/)

给定两个字符串，求它们最长的公共子序列长度。

输入是两个字符串，输出是一个整数，表示它们满足题目条件的长度。

>```
>输入：text1 = "abcde", text2 = "ace" 
>输出：3  
>解释：最长公共子序列是 "ace" ，它的长度为 3 。
>```

**解析:**

​	设置状态：建立一个二维数组 `dp`，其中 `dp[i][j]` 表示到第一个字符串位置 i 为止、到第二个字符串位置 j 为止、最长的公共子序列长度。

​	状态转移方程：从1开始计算字符串位置，那么当`text1` 的第 i 个字符与 `text2` 的第 j 个字符相等时，其最长公共子串长度为前一状态加1，即 `dp[i][j] = dp[i-1][j-1] + 1`；如果不相等，`dp[i][j]` 不会比`dp[i-1][j]` 和`dp[i][j-1]` 两者之中任何一个小，也不会比两者都大，即 `dp[i][j] = max(dp[i-1][j],dp[i][j-1])`

​	初始情况：任一个字符串为空串则最长公共子序列的长度都为0，即`dp[0][j] = dp[i][0] = 0`

```cpp
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int len1 = text1.length(), len2 = text2.length();
        // 创建len+1行len2+1列的二维数组 dp，其中 dp[i][j] 表示 text1[0:i] 和 text2[0:j] 的最长公共子序列的长度
        vector<vector<int>> dp(len1+1,vector<int>(len2+1));
        for(int i=1;i<=len1;++i){
            for(int j=1;j<=len2;++j){
                // 相等情况
                if(text1[i-1]==text2[j-1]){
                    dp[i][j] = dp[i-1][j-1] + 1;
                // 不等情况
                }else{
                    dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }
        return dp[len1][len2];
    }
};
```

#### [583 两个字符串的删除操作](https://leetcode-cn.com/problems/delete-operation-for-two-strings/)

给定两个字符串，求它们通过删除操作变成相同的最小步骤。

输入是两个字符串，输出是一个整数，表示它们通过删除操作变成相同的最小步骤数。

> ```
> 输入: "sea", "eat"
> 输出: 2
> 解释: 第一步将"sea"变为"ea"，第二步将"eat"变为"ea"
> ```

**解析:**

​	本题是最长公共子序列的一种变种题，可以直接求出最长公共子序列后用较长一个字符串的长度减去最长公共子序列的长度。

```cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length(), n = word2.length();
        vector<vector<int>> dp(m+1,vector<int>(n+1));
        for(int i=1;i<=m;++i){
            for(int j=1;j<=n;++j){
                if(word1[i-1] == word2[j-1]){
                    dp[i][j] = dp[i-1][j-1] + 1;
                }else{
                    dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }
        int LCS = dp[m][n];
        return m+n-2*LCS;
    }
};
```



### 05 背包问题

​	背包问题：有 N 个物品和容量为 W 的背包，每个物品都有自己的体积 w 和价值 v，求拿哪些物品可以使得背包所装下物品的总价值最大。如果限定每种物品只能选择 0 个或 1 个，则问题称为 0-1 背包问题；如果不限定每种物品的数量，则问题称为完全背包问题。

​	0-1 背包问题，我们可以定义一个二维数组 `dp` 存储最大价值，其中 `dp[i][j]` 表示前 i 件物品体积不超过 j 的情况下能达到的最大价值。在我们遍历到第 i 件物品时，在当前背包总容量为 j 的情况下，分为两种情况：（1）如果我们不将物品 i 放入背包，即当前背包容量不足或这放入当前物品无法达到最大价值，那么 `dp[i][j]= dp[i-1][j]`，即前 i 个物品的最大价值等于只取前 i -1 个物品时的最大价值；（2）如果我们将物品 i 放入背包，假设第 i 件物品体积为 w，价值为 v，那么我们得到 `dp[i][j] = dp[i-1][j-w] + v`。

```cpp
int knapsack(vector<int> weights, vector<int> values, int N, int W) {
	vector<vector<int>> dp(N+1,vector<int>(W+1));
    // 放置第i个物品
    for(int i=1;i<=N;++i){
        // 第 i 个物品的体积w和价值v
        int w = weights[i-1], v = values[i-1];
        // 遍历容量
        for(int j=1;j<=W;++j){
            if(j>=w){
                dp[i][j] = max(dp[i-1][j],dp[i-1][j-w]+v);
            }else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[N][W];
}
```

​	在完全背包问题中，一个物品可以拿多次。这里直接给出完全背包问题的状态转移方程`dp[i][j] = max(dp[i-1][j], dp[i][j-w] + v)`，其与 0-1 背包问题的差别**仅仅**是把状态转移方程中的第二个 i-1 变成了 i。

```cpp
int knapsack(vector<int> weights, vector<int> values, int N, int W) {
	vector<vector<int>> dp(N+1,vector<int>(W+1));
    // 放置第i个物品
    for(int i=1;i<=N;++i){
        // 第 i 个物品的体积w和价值v
        int w = weights[i-1], v = values[i-1];
        // 遍历容量
        for(int j=1;j<=W;++j){
            if(j>=w){
                dp[i][j] = max(dp[i-1][j],dp[i][j-w]+v);
            }else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[N][W];
}
```

#### [416 分割等和子集](https://leetcode-cn.com/problems/partition-equal-subset-sum/)

给定一个正整数数组，求是否可以把这个数组分成和相等的两部分。

输入是一个一维正整数数组，输出时一个布尔值，表示是否可以满足题目要求。

> ```
> 输入：nums = [1,5,11,5]
> 输出：true
> 解释：数组可以分割成 [1, 5, 5] 和 [11] 。
> ```

**解析:**

​	本题等价于 0-1 背包问题，设所有数字和为 sum，我们的目标是选取一部分物品，使得它们的总和为 target = sum/2，及用部分物品填满容量为target的背包。同时本题不需要考虑价值，因此我们只需要通过一个布尔值矩阵来表示状态转移矩阵。

​	设置状态： `dp[i][j]` 表示 nums 的前 i 个整数是否能够组合成和为 j

​	状态转移方程：(01背包问题的子问题都很简单只用区分选择当前物品或者不选择当前物品的情况)

* 不选择 `nums[i]`：`nums[i]` 大于于当前容量 j 时，容量不够不选择该物品，`dp[i][j] = dp[i-1][j]`

* 选择 `nums[i]`：

  > * `nums[i]` 恰好等于当前容量 j，即`nums[i]==j`时，只放该物品就可以填满容量为 j 的背包，`dp[i][j] =true`
  > * `nums[i]` 小于当前容量 j，即`nums[i]<j`时，只放该物品不够填满容量为 j 的背包，检测放入该物品后`dp[i-1][j-nums[i]]`的情况下是否可以填满背包
  >
  > 总的说，当容量足够时，物品nums[i] 可选可不选（在有价值的情况下就需要选择价值较大的情况），则`dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i]]`

​    初始情况：容量为0的时候，不选择任何物品，`dp[i][0] = true`；只有一个物品的时候，当容量为`j == nums[0]`时恰好满足，即`dp[0][nums[0]] = true`

​	示例的状态转移矩阵根据上述状态转移方程可以得到如下表格：

|          |   0   |   1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  10  |  11  |
| :------: | :---: | :---: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| [0] = 1  | **T** | **T** |  F   |  F   |  F   |  F   |  F   |  F   |  F   |  F   |  F   |  F   |
| [1] = 5  | **T** |   T   |  F   |  F   |  F   |  T   |  T   |  F   |  F   |  F   |  F   |  F   |
| [2] = 11 | **T** |   T   |  F   |  F   |  F   |  T   |  T   |  F   |  F   |  F   |  F   |  T   |
| [3] = 5  | **T** |   T   |  F   |  F   |  F   |  T   |  T   |  F   |  F   |  F   |  T   |  T   |

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(),nums.end(),0);
        auto maxPos = max_element(nums.begin(),nums.end());
        int target = sum/2, len = nums.size();
        // 注意特殊情况，和为奇数或者元素个数小与2都无法进行有效分割，而元素值大于target直接导致越界
        if(len<2 || sum&1 || *maxPos > target){
            return false;
        }
        vector<vector<bool>> dp(len,vector<bool>(target+1,false));
        // 初始情况容量为0
        for(int i=0;i<len;++i){
            dp[i][0] = true;
        }
        // 初始情况物品只有一个
        dp[0][nums[0]] = true;
        for(int i=1;i<len;++i){
            for(int j=1;j<=target;++j){
                // 背包容量大于当前扫描物品，可选可不选
                if(j >= nums[i]){
                    dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i]];
                // 背包容量小于当前扫描物品，没法选
                }else{
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[len-1][target];
    }
};
```

#### [494 目标和](https://leetcode-cn.com/problems/target-sum/)

给定义一个整数数组 `nums` 和一个整数 `target` 。向数组中的每个整数前添加 `'+'` 或 `'-'` ，然后串联起所有整数，可以构造一个 **表达式**，返回可以完成表达式构造的、运算结果等于 `target` 的不同 **表达式** 的数目。

输入一个一维数组和整数，输出一个整数表示构造表达式结果为target的方法数

> 输入：nums = [1,1,1,1,1], target = 3
> 输出：5
> 解释：一共有 5 种方法让最终目标和为 3 。
> -1 + 1 + 1 + 1 + 1 = 3
> +1 - 1 + 1 + 1 + 1 = 3
> +1 + 1 - 1 + 1 + 1 = 3
> +1 + 1 + 1 - 1 + 1 = 3
> +1 + 1 + 1 + 1 - 1 = 3

**解析：**

​	本题可以转化为 01 背包问题，假设数组元素总和为 sum，添加 `'+'`的元素和为 x，那么添加 `'-'`的元素和为 `sum - x`。由此可以得到 `x - (sum - x) = target`，即为`x = (target + sum) / 2`，那么本题就可以转化为使用 `nums`中的N个物品装满容量为 x 的背包，**共有多少种方法**，可以看出这时一个组合问题。

​	设置状态：使用一个二维数组 `dp[i][j]` 表示数组 nums 中从开头到以 i 位置结尾的所有物品装满容量为 j 的背包的方法数。

​	状态转移方程：考虑第 i 个元素，如果当前背包容量 `j<nums[i]`，则不能放入第 i 个元素 `dp[i][j] = dp[i-1][j]`；如果当前背包容量`j >= nums[i]`，不放入第 i 个元素的方法数为`dp[i][j] = dp[i-1][j]`，放入第 i 个元素的方法数为`dp[i][j] = dp[i-1][j-nums[i]]`，那么总的方法数为这两中情况之和即`dp[i][j] = dp[i-1][j] + dp[i-1][j-nums[i]]` 

​	边界情况：如果`(target + sum)`不为偶数是无解情况，如果 `abs(target) > sum` 也是无解情况，没有任何构造方式能够满足题目条件。当数组为空，背包容量为0时`dp[0][0] == 1`

```cpp
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int len = nums.size();
        int sum = accumulate(nums.begin(),nums.end(),0);
        if((target+sum)&1 || abs(target)>sum){
            return 0;
        }
        int weight = (target + sum)/2;
        vector<vector<int>> dp(len+1,vector<int>(weight+1));
        dp[0][0] = 1;
        for(int i=1;i<=len;++i){
            for(int j=0;j<=weight;++j){
                dp[i][j] = dp[i-1][j];
                if(j>=nums[i-1]){
                    dp[i][j] = dp[i-1][j] + dp[i-1][j-nums[i-1]];
                }
            }
        }
        return dp[len][weight];
    }
};
```

#### [474 一和零](https://leetcode-cn.com/problems/ones-and-zeroes/)

​	给定 m 个数字 0 和 n 个数字 1，以及一些由 0-1 构成的字符串，求利用这些数字最多可以构成多少个给定的字符串，字符串只可以构成一次。

​	输入两个整数 m 和 n，表示 0 和 1 的数量，以及一个一维字符串数组，表示待构成的字符串；输出是一个整数，表示最多可以生成的字符串个数。

> 输入：strs = ["10", "0001", "111001", "1", "0"], m = 5, n = 3
> 输出：4
> 解释：最多有 5 个 0 和 3 个 1 的最大子集是 {"10","0001","1","0"} ，因此答案是 4 。其他满足题意但较小的子集包括 {"0001","1"} 和 {"10","1","0"} 。{"111001"} 不满足题意，因为它含 4 个 1 ，大于 n 的值 3 。

**解析：**

​	本题也是一个01背包问题，而其特点在于它有两个背包，一个装0，另一个装1。

​	设置状态：`dp[i][j][k]` 表示装0背包容量为 j，装1背包容量为k的情况下，能够装入前 i 个物品中的几个

​	状态转移方程：仍旧划为装入当前物品和不装入当前物品两个子问题，不装入则`dp[i][j][k]=dp[i-1][j][k]`，装入则`dp[i][j][k]=max(dp[i-1][j][k],dp[i-1][j-w0[i]][k-w1[i]] + 1)`，其中w0表示物品中0的体积，w1表示物品中1的体积。

```cpp
class Solution {
public:

    // 计算每个str中0和1的数量
    pair<int,int> countWeight(string str){
        int count0 = 0, count1 = 0;
        for(int i=0;i<str.length();++i){
            if(str[i] == '0'){
                ++count0;
            }else{
                ++count1;
            }
        }
        return make_pair(count0,count1);
    }

    int findMaxForm(vector<string>& strs, int m, int n) {
        int len = strs.size();
        // 用一个三维数组表示在前 i 个字符串中，使用 j 个 0 和 k 个 1 的情况下最多可以得到的字符串数量
        vector<vector<vector<int>>> dp(len+1,vector<vector<int>>(m+1,vector<int>(n+1)));
        for(int i=1;i<=len;++i){
            auto count = countWeight(strs[i-1]);
            // j 和 k 都从零开始，因为str存在'0'或'1'这种只有一种元素构成的情况
            for(int j=0;j<=m;++j){
                for(int k=0;k<=n;++k){
                    if(j >= count.first && k >= count.second){
                        dp[i][j][k] = max(dp[i-1][j][k],dp[i-1][j-count.first][k-count.second] + 1);
                    }else{
                        dp[i][j][k] = dp[i-1][j][k];
                    }
                }
            }
        }
        return dp[len][m][n];
    }
};
```

#### [322 零钱兑换](https://leetcode-cn.com/problems/coin-change/)

​	给定一些硬币的面额，求最少可以用多少颗硬币组成给定的金额。

​	输入一个一维整数数组，表示硬币的面额；以及一个整数，表示给定的金额。输出一个整数，表示满足条件的最少的硬币数量。若不存在解，则返回-1。	

> ```
> 输入：coins = [1, 2, 5], amount = 11
> 输出：3 
> 解释：11 = 5 + 5 + 1
> ```

**解析：**

​	因为每个硬币可以用无限多次，这道题本质上是完全背包问题。完全背包问题还是没搞懂，记录一下，以后仔细琢磨。

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int Max = amount + 1;
        vector<int> dp(amount + 1, Max);
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (int j = 0; j < (int)coins.size(); ++j) {
                if (coins[j] <= i) {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
```

### 06 字符串编辑问题

#### [72 编辑距离](https://leetcode-cn.com/problems/edit-distance/)

​	给定两个字符串，已知你可以删除、替换和插入任意字符串的任意字符，求最少编辑几步可以将两个字符串变成相同。

​	输入是两个字符串，输出是一个整数，表示最少的步骤。

> 输入：word1 = "horse", word2 = "ros"
> 输出：3
> 解释：
> horse -> rorse (将 'h' 替换为 'r')
> rorse -> rose (删除 'r')
> rose -> ros (删除 'e')

**解析：**

​	本题与最长公共子序列类似，两个字符串的对比所以需要使用一个二维数组来设置状态 `dp[i][j]`

​	设置状态：`dp[i][j]` 表示将第一个字符串到位置 i 为止，和第二个字符串到位置 j 为止，最多需要几步编辑。

​	状态转移方程：当第 i 位和第 j 位对应的字符相同时，`dp[i][j]` 等于 `dp[i-1][j-1]`；当二者对应的字符不同时，修改的消耗是 `dp[i-1][j-1]+1`，插入 i 位置/删除 j 位置的消耗是 `dp[i][j-1] + 1`，插入 j 位置/删除 i 位置的消耗是 `dp[i-1][j] + 1`，所以在不同的情况下状态转移方程`dp[i][j] = min(dp[i-1][j-1],dp[i-1][j],dp[i][j-1])`。

​	边界情况：word1为空串时，需要插入字符与word2一致，即`dp[0][j] = j`；同理，word2为空串是`dp[i][0] = i`

```cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length(), n = word2.length();
        vector<vector<int>> dp(m+1,vector<int>(n+1));
        // 边界条件 word2为空串
        for(int i=0;i<=m;++i){
            dp[i][0] = i;
        }
        // 边界条件 word1为空串
        for(int j=0;j<=n;++j){
            dp[0][j] = j;
        }
        for(int i=1;i<=m;++i){
            for(int j=1;j<=n;++j){
                // 状态转移，相等情况不编辑，不等情况选择编辑次数最少的编辑
                if(word1[i-1] == word2[j-1]){
                    dp[i][j] = dp[i-1][j-1];
                }else{
                    dp[i][j] = min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1])) + 1;
                }
            }
        }
        return dp[m][n];
    }
};
```

#### [650 只有两个键的键盘](https://leetcode-cn.com/problems/2-keys-keyboard/)

​	给定一个字母 A，已知你可以每次选择复制全部字符，或者粘贴之前复制的字符，求最少需要几次操作可以把字符串延展到指定长度。

​	输入是一个正整数，代表指定长度；输出是一个整数，表示最少操作次数。

> 输入：3
> 输出：3
> 解释：
> 最初, 只有一个字符 'A'。
> 第 1 步, 使用 Copy All 操作。
> 第 2 步, 使用 Paste 操作来获得 'AA'。
> 第 3 步, 使用 Paste 操作来获得 'AAA'。

**解析：**

​	不同于以往通过加减实现的动态规划，这里需要乘除法来计算位置，因为粘贴操作是倍数增加的。

​	设置状态：使用一个一维数组 `dp[i]`，其中位置 i 表示延展到长度 i 的最少操作次数。

​	状态转移方程：对于每个位置 j，如果 j 可以被 i 整除，那么长度 i 就可以由长度 j 操作得到，其操作次数等价于把一个长度为 1 的 A 延展到长度为 i/j。例如3由1操作得到`A A A`，6由2操作得到`AA AA AA`因此可以得到递推公式 `dp[i] = dp[j] + dp[i/j]`。

```cpp
class Solution {
public:
    int minSteps(int n) {
        vector<int> dp(n+1);
        for(int i=2;i<=n;++i){
            dp[i] = i;
            for(int j=2;j<=i;++j){
                if(i%j==0){
                    dp[i] = dp[j] + dp[i/j];
                    break;
                }
            }
        }
        return dp[n];
    }
};
```

#### [10 正则表达式匹配](https://leetcode-cn.com/problems/regular-expression-matching/)

​	给定一个字符串和一个正则表达式（regular expression, regex），求该字符串是否可以被匹配，其中`'.'` 匹配任意单个字符；`'*'` 匹配零个或多个前面的那一个元素。

​	输入是一个待匹配字符串和一个用字符串表示的正则表达式，输出是一个布尔值，表示是否可以匹配成功。

> 输入：s = "aab" p = "c*a*b"
> 输出：true
> 解释：因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。

**解析：**

​	两个字符串进行匹配，且字符具有特殊含义，本题动态规划的特点在于多种情况下的不同状态转移方程。

​	设置状态：使用一个布尔类型的二维数组 dp，其中 `dp[i][j]` 表示以 i 截止的字符串是否可以被以 j 截止的正则表达式匹配。

​	状态转移方程：根据正则表达式的不同情况，即字符、星号，点号，分情况讨论来更新 dp 数组

* 相等情况：即`s[i-1] == p[j-1] || p[j-1] == '.'`的情况，这种情况下`dp[i][j] == dp[i-1][j-1]`，即与前 i-1 个子串匹配情况一致

* 不相等情况：

  > * `s[i-1] != p[j-1] && p[j-1] != '*'` ，直接不匹配情况`dp[i][j] = false`
  > * `p[j-1] == '*'`：如果匹配0次则`dp[i][j-2] == true` 则 `dp[i][j] = true`；如果匹配多次则需要验证`'*'`前一个字符相等情况即`s[i-1] == p[j-1] || p[j-1] == '.'`，相等则`dp[i][j] = dp[i-1][j]`，否则不匹配

​    初始情况：空串匹配非空正则表达式，`dp[0][0]=true`，当`p[j-1]=='*'`是可以匹配0次匹配空串即`dp[0][j] =dp[0][j-2]`；非空串匹配空正则表达式，`dp[0][0]=true`，其他情况都无法成功匹配。

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m+1,vector<bool>(n+1,false));
        dp[0][0] = true;
        for(int j=1;j<=n;++j){
            if(p[j-1] == '*'){
                dp[0][j] = dp[0][j-2];
            }
        }

        for(int i=1;i<=m;++i){
            auto chs = s[i-1]; 
            for(int j=1;j<=n;++j){
                auto chp = p[j-1];
                if(chs == chp || chp == '.'){
                    dp[i][j] = dp[i-1][j-1];
                }else if(chp ==  '*'){
                    if(j>1){
                        if(dp[i][j-2]){
                            dp[i][j] = true;
                        }else{
                            auto prechp = p[j-2];
                            if(prechp==chs || prechp =='.'){
                                dp[i][j] = dp[i-1][j];
                            } 
                        }
                    }
                }
            }
        }
        return dp[m][n];
    }
};
```

### 07 股票交易问题

​	股票交易类问题通常可以用动态规划来解决。对于稍微复杂一些的股票交易类问题，比如需要冷却时间或者交易费用，则可以用通过动态规划实现的状态机来解决。

|                             题目                             |                特点                |
| :----------------------------------------------------------: | :--------------------------------: |
| [121 买卖股票的最佳时机](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/) |            只能买卖一次            |
| [122 买卖股票的最佳时机 II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/) |            可以买卖多次            |
| [714 买卖股票的最佳时机含手续费](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/) |    可以买卖多次，每次都有手续费    |
| [123 买卖股票的最佳时机 III](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/) |            最多买卖两次            |
| [188 买卖股票的最佳时机 IV](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv/) |           最多买卖 k 次            |
| [309 最佳买卖股票时机含冷冻期](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/) | 可以买卖多次，但是卖出有一天冷冻期 |

#### [121 买卖股票的最佳时机](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/)

​	给定一段时间内每天的股票价格，已知你只可以买卖各一次，求最大的收益。

​	输入一个一维整数数组，表示每天的股票价格；输出一个整数，表示最大的收益。

> 输入：[7,1,5,3,6,4]
> 输出：5
> 解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5

**解析：**

​	求最大利润本质是也是一个优化问题，所以可以采用动态规划的思路解决。

​	设置状态：用两个动态规划数组`buy[i]` 表示第 i 天持股时的现金数，`sell[i]`表示第 i 天不持股时的现金数

​	状态转移方程：第 i 天持股 `buy[i] = max(buy[i-1],-prices[i])`，如果第 i-1 天不持股则花费`-prices[i]`的现金**买入**股票，如果第i-1天持股，则保持不变；第 i 天不持股 `sell[i] = max(sell[i-1],buy[i-1]+prices[i])`，如果第 i-1 天也不持股那么情况不变，如果第 i-1 天持股则需要将其**卖出**产生收益`buy[i-1]+prices[i]`。

​	初始情况：第 1 天不持股`sell[0] = 0`；第 1 天持股`buy[0] = -prices[0]`

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if(len<2) return 0;
        vector<int> sell(len);
        vector<int> buy(len);
        sell[0] = 0;
        buy[0] = -prices[0];
        for(int i=1;i<len;++i){
            buy[i] = max(buy[i-1],-prices[i]);
            sell[i] = max(sell[i-1],buy[i-1]+prices[i]);
        }
        return sell[len-1];
    }   
}
```

​	本题也可以用更直接的方法解决，遍历一遍数组，在每一个位置 i 时，记录 i 位置之前所有价格中的最低价格，然后将当前的价格作为售出价格，查看当前收益是不是最大收益，一遍遍历完成后就可以得到最大收益。

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int sell = 0, buy = INT_MAX;
        for(int i=0;i<prices.size();++i){
            buy = min(buy,prices[i]);
            sell = max(sell,prices[i]-buy);
        }
        return sell;
    }
};
```

#### [122 买卖股票的最佳时机 II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/)

​	给定一段时间内每天的股票价格，已知你只可以多次买卖一支股票，求最大的收益。

​	输入一个一维整数数组，表示每天的股票价格；输出一个整数，表示最大的收益。

> 输入：[7,1,5,3,6,4]
> 输出：5
> 解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5-1 = 4 。随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3 = 3 。

**解析：**

​	本题和上一题的区别在于可以多次买卖，也可以采用动态规划的思路来解决。

​	设置状态：除了用两个数组分别表示股票持股与不持股情况，也可以使用一个二维数组`dp[i][j]`来表示，其中 i 表示交易的时间，j 表示交易状态即买入或卖出 ，0 表示买入状态、1表示卖出状态；`dp[i][0]`表示第 i 天持股时的现金数，`dp[i][1]` 表示第 i 天不持股时的现金数。**值得注意的是`dp[i][0]`，表示的是第i天，买入股票的状态，并不是说一定要第i天买入股票，`dp[i][1]`亦同**

​	状态转移方程：本题的状态转移方程和上一题的唯一区别在于第 i 天持股的情况，如果第 i-1 天也持股那么保持一致，如果第 i-1 天不持股由于可以进行多次交易，那么就需要在已获得收益的基础上花费`-prices[i]`的现金买入股票即`dp[i][0] = max(dp[i-1][0],dp[i-1][1] - prices[i])`。

​	初始情况：第 1 天持股`dp[0][0] = -prices[0]`，第 1 天不持股`dp[0][1] = 0`

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if(len<2) return 0;
        vector<vector<int>> dp(len,vector<int>(2));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for(int i=1;i<len;++i){
            dp[i][0] = max(dp[i-1][0],dp[i-1][1] - prices[i]);
            dp[i][1] = max(dp[i-1][1],dp[i-1][0] + prices[i]);
        }
        return dp[len-1][1];
    }
};
```

​	本题可以采用贪心策略，由于不限制交易次数，只要今天股价比昨天高，就交易。

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int sum = 0;
        for(int i=1;i<prices.size();++i){
            if(prices[i]>prices[i-1]){
                sum+=(prices[i]-prices[i-1]);
            }
        }
        return sum;
    }
};
```

#### [714 买卖股票的最佳时机含手续费](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/)

​	给定一段时间内每天的股票价格，已知每次交易都需要扣除`fee`的手续费，且每次只能拥有一支股票，求最大的收益。

​	输入一个一维整数数组，表示每天的股票价格；输出一个整数，表示最大的收益。

> 输入：prices = [1, 3, 2, 8, 4, 9], fee = 2
> 输出：8
> 解释：能够达到的最大利润 ((8 - 1) - 2) + ((9 - 4) - 2) = 8

**解析：**

​	本题本质上和122可多次交易并没有什么差别，主要的问题是需要考虑过多次数的交易可能会产生大量手续费，直接导致总的收益不如交易次数较少的利润。

​	设置状态：使用一个二维数组`dp[i][j]`来表示，其中 i 表示交易的时间，j 表示交易状态即买入或卖出 ，0 表示买入状态、1表示卖出状态；`dp[i][0]`表示第 i 天持股时的现金数，`dp[i][1]` 表示第 i 天不持股时的现金数。

​	状态转移方程：本题与122题状态转移方程的主要区别在于第 i 天不持股的情况，如果第 i-1 天也不持股那么保持一致，如果第 i-1 天持股，那么就需要将其卖出产生`buy[i-1]+prices[i]`的收益，同时需要从收益中扣除`fee`的手续费。得到第 i 天不持股情况的状态转移方程`dp[i][1] = max(dp[i-1][1],dp[i-1][0] + prices[i] - fee)`

​	初始情况：第 1 天持股`dp[0][0] = -prices[0]`，第 1 天不持股`dp[0][1] = 0`

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int len = prices.size();
        if(len < 2) return 0;
        vector<vector<int>> dp(len,vector<int>(2));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for(int i=1;i<len;++i){
            dp[i][0] = max(dp[i-1][0],dp[i-1][1] - prices[i]);
            dp[i][1] = max(dp[i-1][1],dp[i-1][0] + prices[i] - fee);
        }
        return dp[len-1][1];
    }
};
```

#### [123 买卖股票的最佳时机 III](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/)

​	给定一段时间内每天的股票价格，已知你最多可以进行**两次**买卖一支股票，求最大的收益。

​	输入一个一维整数数组，表示每天的股票价格；输出一个整数，表示最大的收益。

> 输入：prices = [3,3,5,0,0,3,1,4]
> 输出：6
> 解释：在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 = 3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。随后，在第 7 天（股票价格 = 1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1 = 3 。

**解析：**

​	本题限制了交易次数**最多**为两次买卖，那么就要对这两次交易操作进行区分，所以一天的交易就不再是前两题中持股和不持股两种状态，而是要在此基础上区分第一次交易持股状态和第二次交易持股状态。

​	设置状态：使用一个二维数组`dp[i][j]`来表示，其中 i 表示交易的时间，j 为`0～3`表示交易状态。例如`dp[i][0]`表示第一次买入状态、`dp[i][1]`表示第一次卖出状态、`dp[i][2]`表示第二次买入状态、`dp[i][3]`表示第二次卖出状态。

​	状态转移方程：

> * 第一次交易的状态转移方程与121的单次交易一致，如果第一次第 i 天持股`dp[i][0] = max(dp[i-1][0],- prices[i])`，第 i-1 天不持股则需要花费`-prices[i]`的现金**买入**股票达成买入状态，如果第i-1天持股，则保持不变；
> * 如果第一次第 i 天不持股`dp[i][1] = max(dp[i-1][1],dp[i-1][0] + prices[i])`，第 i-1 天也不持股那么情况不变，如果第 i-1 天持股则需要将其**卖出**达成卖出状态并产生收益`prices[i]`。
> * 第二次交易的状态转移方程则与122的多次交易大致相同，如果第二次交易第 i 天持股`dp[i][2] = max(dp[i-1][2],dp[i-1][1] - prices[i])`，如果第 i-1 天也持股那么不进行操作，如果第 i-1 天不持股则需要在**第一次交易完成的基础上**花费`prices[i]`的现金买入股票达成持股或买入状态；
> * 如果第 i 天为卖不持股或卖出状态`dp[i][3] = max(dp[i-1][3],dp[i-1][2] + prices[i])`，如果第 i-1 天不持股第 i-1 天也不持股那么情况不变，如果第 i-1 天持股则需要将其**卖出**达成卖出状态并产生收益`prices[i]`。

​	初始情况：第 1 天持股`dp[0][0] = -prices[0], dp[0][1] = -prices[0]`，第 1 天不持股`dp[0][1] = 0, dp[0][3] = 0`

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if(len<2) return 0;
        vector<vector<int>> dp(len,vector<int>(4));
        dp[0][0] = -prices[0];
        dp[0][2] = -prices[0];
        dp[0][1] = 0;
        dp[0][3] = 0;
        for(int i=1;i<len;++i){
            dp[i][0] = max(dp[i-1][0],-prices[i]);
            dp[i][1] = max(dp[i-1][1],dp[i-1][0]+prices[i]);
            dp[i][2] = max(dp[i-1][2],dp[i-1][1]-prices[i]);
            dp[i][3] = max(dp[i-1][3],dp[i-1][2]+prices[i]);
        }
        return dp[len-1][3];
    }
};
```

#### [188 买卖股票的最佳时机 IV](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv/)

​	给定一段时间内每天的股票价格，已知你最多可以进行 **k 次**买卖一支股票，求最大的收益。

​	输入一个一维整数数组，表示每天的股票价格；输出一个整数，表示最大的收益。

> 输入：k = 2, prices = [3,2,6,5,0,3]
> 输出：7
> 解释：在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6) 的时候卖出, 这笔交易所能获得利润 = 6-2 = 4 。随后，在第 5 天 (股票价格 = 0) 的时候买入，在第 6 天 (股票价格 = 3) 的时候卖出, 这笔交易所能获得利润 = 3-0 = 3 。

**解析：**

​	本题限制了交易次数**最多**为 k 次，那么就要根据 k 值大小区分不同情况，如果 k 大于数组长度那么就可以类比122题相当于可以不限次数交易；如果 k 小于数组长度那么就可以类比为123题有限次数交易求最大利润。

​	设置状态：还是使用一个二维数组`dp[i][j]`来记录所剩余的现金，其中 i 表示交易的时间，j 为表示交易状态。类比123题本题的不同在于交易次数是变化的，交易状态难以表征，但是我们也可以总结出规律，可以使用**偶数表示买入状态，奇数表示卖出状态**。

​	状态转移方程：本题的状态转移方程可以直接类比123题，区别在于次数是变化的。

​	初始情况：即所有交易次数中第一天不持股时为0，持股则为`-prices[i]`

```cpp
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int len = prices.size();
        // 临界情况 k <= 0 || k >= len
        if(len < 2 || k <= 0) return 0;
        if(len <= k){
            return unlimitedTimes(prices);
        }
        // 一般情况 0 < k && k < len
        vector<vector<int>> dp(len,vector<int>(2*k));
        // 初始情况
        for(int i=0;i<2*k;++i){
            if(i&1){
                dp[0][i] = 0;
            }else{
                dp[0][i] = -prices[0];
            }
        }
        
        for(int i=1;i<len;++i){
            // 第一次买入状态
            dp[i][0] = max(dp[i-1][0],-prices[i]);
            for(int j=1;j<2*k;++j){
                if(j&1){
                    // 卖出状态转移方程
                    dp[i][j] = max(dp[i-1][j],dp[i-1][j-1]+prices[i]);
                }else{
                    // 买入状态转移方程
                    dp[i][j] = max(dp[i-1][j],dp[i-1][j-1]-prices[i]);
                }
            }
        }
        return dp[len-1][2*k-1];
    }

    // 可以进行多次交易的贪心实现
    int unlimitedTimes(vector<int>& prices){
        int len = prices.size();
        int sum = 0;
        for(int i=1;i<len;++i){
            if(prices[i]>prices[i-1]){
                sum += (prices[i] - prices[i-1]);
            }
        }
        return sum;
    }
};
```

#### [309 最佳买卖股票时机含冷冻期](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)

​	给定一段时间内每天的股票价格，已知每次卖出之后必须冷却一天，且每次只能拥有一支股票，求最大的收益。

​	输入一个一维整数数组，表示每天的股票价格；输出一个整数，表示最大的收益。

> ```
> 输入: [1,2,3,0,2]
> 输出: 3 
> 解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]
> ```

**解析：**

​	我们可以使用状态机来解决这类复杂的状态转移问题，通过建立多个状态以及它们的转移方式，我们可以很容易地推导出各个状态的转移方程。如图所示，我们可以建立四个状态来表示带有冷却的股票交易，以及它们的之间的转移方式。

<img src="/home/wang/Desktop/TechnicalRoute/ALGLearning/LeetCode_Cpp/LeetCode刷题笔记/img/309.png" alt="309" style="zoom:50%;" />

​	其中分为买入状态Buy、卖出状态Sell、买入后状态S1和卖出后状态S2（状态的划分本人也没有搞清楚，仅仅凭个人理解进行划分，如有错误感谢指正）

* 买入状态：即通过买入股票达到的买入状态
* 买入后状态：买入大于等于两天后的持股状态，一直没操作，保持持股
* 卖出状态：通过卖出持有的股票达到卖出状态，可以从买入状态直接操作卖出股票进入卖出状态，也可以在买入之后的持有多天后卖出股票进入卖出状态，这两个过程都会产生收益
* 卖出后状态：度过了冷冻期，大于等于两天前就卖出了股票，一直没操作，保持不持股

​    设置状态：使用一个二维数组`dp[i][j]`来表示，其中 i 表示交易的时间，j 为`0～3`表示交易状态。例如`dp[i][0]`表示买入状态、`dp[i][1]`表示不操作状态、`dp[i][2]`表示卖出状态、`dp[i][3]`表示卖出后状态。

​	状态转移方程：

> * 买入状态`dp[i][0] = dp[i-1][3] - prices[i]`，卖出后状态下所持有的现金中花费`prices[i]`买入股票达到买入状态。
> * 买入后状态`dp[i][1] = max(dp[i-1][0],dp[i-1][1])`，可以通过买入状态到达，也可以不操作，保持原先持股状态。
> * 卖出状态`dp[i][2] = max(dp[i-1][0],dp[i-1][1]) + prices[i]`，可以买入后第二天直接卖出股票到达卖出状态，也可以持有多天后再卖出股票达到卖出状态。
> * 卖出后状态`dp[i][3] = max(dp[i-1][2],dp[i-1][3])`，可以通过卖出状态到达，也可以不操作，保持原先不持股状态。

​    初始情况：第一天不持股时为`dp[0][2] = 0, dp[0][3] = 0`，持股则为`dp[0][0] = -prices[i], dp[0][1] = -prices[i]`

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if(len < 2) return 0;
        vector<vector<int>> dp(len,vector<int>(4));
        dp[0][0] = dp[0][1] = -prices[0];
        dp[0][2] = dp[0][3] = 0;
        for(int i=1;i<len;++i){
            dp[i][0] = dp[i-1][3] - prices[i];
            dp[i][1] = max(dp[i-1][0],dp[i-1][1]);
            dp[i][2] = max(dp[i-1][0],dp[i-1][1]) + prices[i];
            dp[i][3] = max(dp[i-1][2],dp[i-1][3]);
        }
        return max(dp[len-1][2],dp[len-1][3]);
    }
};
```

