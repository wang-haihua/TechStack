## LeetCode刷题笔记 位运算

### 01 位运算基础

​	位运算是算法题里比较特殊的一种类型，它们利用二进制位运算的特性进行一些奇妙的优化和计算。常用的位运算符号包括：“∧” 按位异或、“&” 按位与、“|” 按位或、“∼” 取反、“<<” 算术左移和 “>>” 算术右移。以下是一些常见的位运算特性：

|     异或      |      与      |        或        |
| :-----------: | :----------: | :--------------: |
| x ^ 0000 = x  | x & 0000 = 0 |  x \| 0000 = x   |
| x ^ 1111 = ~x | x & 1111 = x | x \| 1111 = 1111 |
|   x ^ x = 0   |  x & x = x   |    x \| x = x    |

​	除此之外， n & (n - 1) 可以**去除** n 的位级表示中最低的那一位，例如对于二进制表示 11110100，减去 1 得到 11110011，这两个数按位**与**得到 11110000。

​	n & (-n) 可以**仅保留** n 的位级表示中最低的那一位，例如对于二进制表示 11110100，取负得到 00001100，这两个数按位与得到 00000100。

​	回顾一下移位操作，移位操作是一种基本操作，是一种直接对二进制数据的位运算操作，移位运算又包含了逻辑移位（logical shift）和算术移位（arithmetic shift）两种。

* 逻辑移位：移出去的位丢弃，空缺位（vacant bit）用 0 填充。
* 算术移位：移出去的位丢弃，空缺位（vacant bit）用“符号位”来填充，所以一般用在右移运算中。

​    无符号数，不管是左移还是右移都是逻辑移位；有符号数，做左移运算是逻辑移位，而做右移运算是算术移位。

#### [461 汉明距离](https://leetcode-cn.com/problems/hamming-distance/)

给定两个十进制数字，求它们二进制表示的汉明距离（Hamming distance，即不同位的个数）。

输入是两个十进制整数，输出是一个十进制整数，表示两个输入数字的汉明距离。

> 输入：x = 1, y = 4
> 输出：2
> 解释：1   (0 0 0 1)；4   (0 1 0 0)

**解析：**

​	求二进制数不同位的个数，直接使用将俩个数进行按位异或操作，不同位的结果就是 1，所以最终统计异或结果中的 1 的个数即可。

​	计算二进制数 1 的个数的方法：不断将二进制数算数右移，将其与 1 进行与运算，如果末位是 1 则加入计数。

```cpp
class Solution {
public:
    int hammingDistance(int x, int y) {
        // 异或运算
        int diff = x^y;
        int ans = 0;
        while(diff){
            // 与运算 判断末位是否为 1
            ans += diff & 1;
            // 算术右移动 将已经被统计的 1 移出
            diff = diff>>1;
        }
        return ans;
    }
};
```

#### [190 颠倒二进制位](https://leetcode-cn.com/problems/reverse-bits/)

给定一个十进制整数，输出它在二进制下的翻转结果。

输入和输出都是十进制整数。

> 输入：n = 00000010100101000001111010011100
>
> 输出：964176192 (00111001011110000010100101000000)
>
> 解释：将 n 的二进制串倒转

**解析：**

​	使用算术左移和右移，可以很轻易地实现二进制的翻转。保存结果的二进制串每次向左移动一位腾出末位，然后将 n 与 1 取出 n 的末位并放入结果腾出的末位，放入之后 n 向右移动一位将已放入的位移出。

​	一个简单的示例：

|                |  1   |  2   |  3   |  4   |  5   |
| :------------: | :--: | :--: | :--: | :--: | :--: |
| ans (算术左移) | 0000 | 0000 | 0001 | 0010 | 0101 |
|  n (算术右移)  | 1010 | 0101 | 0010 | 0001 | 0000 |

```cpp
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        // 无符号32位整型
        uint32_t ans = 0;
        for(int i=0;i<32;++i){
            // 每次先将结果左移一位腾出位置
            ans <<= 1;
            // 将 n 当前的最后一位放到上一步ans腾出的位置（末位）
            ans += n&1;
            // 将已经放入结果的位移出
            n >>= 1;
        }
        return ans;
    }
};
```

#### [476 数字的补数](https://leetcode-cn.com/problems/number-complement/)

给你一个 **正** 整数 `num` ，输出它的补数。补数是对该数的二进制表示取反。

输入一个整数，输出一个整数表示原整数的补数

> ```
> 输入：num = 5
> 输出：2
> 解释：5 的二进制表示为 101（没有前导零位），其补数为 010。所以你需要输出 2 。
> ```

**解析：**

​	看到二进制位取返就可以想到异或运算`x^1111 = ~x`，所以本题可以采用异或运算。本题的关键点在于怎样让参与异或运算的 `1` 所占位置与 num 二进制有效表示位置一致，一种方法是通过算术左移将 1 移动到有效位，同时怎么判断是否已经移到完整区间呢？可以采用与运算，如果 num 的最大有效位被覆盖，进行与运算的结果为0。

|    变量     | 二进制表示 |
| :---------: | :--------: |
|     num     |  00000101  |
|    mask     |  11111000  |
|    ~mask    |  00000111  |
| ~mask ^ num |  00000010  |

```cpp
class Solution {
public:
    int findComplement(int num) {
        // 注意mask要用无符号，不然无法算术左移  -1 = 0xFFFFFFFF
        unsigned mask = -1; 
        while(mask & num){
            mask <<=1;
        }
        return ~mask^num;
    }
};
```

#### [136 只出现一次的数字](https://leetcode-cn.com/problems/single-number/)

给定一个整数数组，这个数组里只有一个数字出现了一次，其余数字出现了两次，求这个只出现一次的数字。

输入是一个一维整数数组，输出是该数组内的一个整数。

> ```
> 输入: [4,1,2,1,2]
> 输出: 4
> ```

**解析：**

​	本题可以利用异或运算的特性快速找出唯一出现一次的数字，应为`x^x=0, x^0=x`。所以在数组中出现两次的所有数字按位异或的结果是 0，出现一次的数字与0按位异或运算的结果是其本身。例如`[4,1,2,1,2]`，进行异或运算有`4^1^2^1^2 = 4^0 = 4`。

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        // 将数组中所有元素逐个按位异或运算
        for(int i=0;i<nums.size();++i){
            ans = ans^nums[i];
        }
        return ans;
    }
};
```

#### [268 丢失的数字](https://leetcode-cn.com/problems/missing-number/)

给定一个包含 `[0, n]` 中 `n` 个数的数组 `nums` ，找出 `[0, n]` 这个范围内没有出现在数组中的那个数。

输入一个数组，输出一个整数表示数组中没有出现的数。

> 输入：nums = [3,0,1]
> 输出：2
> 解释：n = 3，因为有 3 个数字，所以所有的数字都在范围 [0,3] 内。2 是丢失的数字，因为它没有出现在 nums 中。

**解析：**

​	本题是[136 只出现一次的数字](https://leetcode-cn.com/problems/single-number/)的变种题，如果将 0 到 n 的所有数字都添加到 nums 中是不是就直接转换成了136题一样的题。例如`nums = [3,0,1]`，其长度为3那么添加0到3的所有元素构成`nums = [3,0,1,0,1,2,3]`，这样一看是不是就是找只出现一次的数字了。

​	当然，我们不需要真的需要取重新构造 nums，在遍历 nums 时元素对应的索引就是要添加的元素。利用异或运算的特性`x^x=0, x^0=x`，将**元素与索引**进行按位异或运算最终就可以得到只出现一次的那个数了，例如`3^1^0^2^1^2^3 = 2`。当然，别忘了要将`nums.size()`这个元素加入异或运算。

```cpp
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        // 将nums.size()作为第一个参与异或运算的元素，当然将它放在最后参与效果是一样的
        int ans = nums.size();
        for(int i=0;i<nums.size();++i){
            // 元素与索引进行按位异或运算
            ans ^= (nums[i]^i);
        }
        return ans;
    }
};
```

#### [260 只出现一次的数字 III](https://leetcode-cn.com/problems/single-number-iii/)

给定一个整数数组 `nums`，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两个元素。

输入一个一维数组，输出一个一维数组包含只出现一次的那两个元素

> ```
> 输入：nums = [1,2,1,3,2,5]
> 输出：[3,5]
> 解释：[5, 3] 也是有效的答案。
> ```

**解析：**

​	本题是[136 只出现一次的数字](https://leetcode-cn.com/problems/single-number/)题的扩展，本题也可以使用异或运算解决，但是要考虑**分组**的情况。

​	首先，遍历数组的所有元素，逐一进行异或运算的到只出现一次的那两个元素的异或运算结果，例如`1^2^1^3^2^5 = 3^5 `

​	只出现一次的那两个元素肯定不一样，所以他们的异或运算结果二进制表示中**至少包含一个1**。而整个数组就可以根据这个为1的二进制位进行划分，将数组中元素该位为0的划分为一组，该位为1的划分为另一组。采用这种策略就能将只出现一次的那两个元素划分到不同的组中。例如对数组`1,2,1,3,2,5`进行划分，`3^5=(110)`，根据第二位进行划分有：第一组：`1(001), 1(001), 5(101)`；第二组：`2(010), 2(010), 3(011)`

​	然后在两组中分别进行如[136 只出现一次的数字](https://leetcode-cn.com/problems/single-number/)题的异或运算，分别得出只出现一次的那两个元素

​	另一个难点在于怎么找到只出现一次的那两个元素的异或运算结果中1的位置，可以采用与[476 数字的补数](https://leetcode-cn.com/problems/number-complement/)相似的方法。用`mask = 0001`不断的算术左移，直到`mask & num != 0`，那么mask中1的位置就是该划分位。

​	根据mask划分元素也可以直接使用按位与运算，结果为0的一组，不为0的一组。

```cpp
    vector<int> singleNumber(vector<int>& nums) {
        int res = 0;
        // 计算只出现一次的那两个元素的异或运算结果
        for(const auto num: nums){
            res ^= num;
        }
        // 找划分位
        int mask = 1;
        while(!(mask & res)){
            mask <<= 1;
        }
        // 分组异或运算
        int a = 0, b = 0;
        for(const auto num: nums){
            if(mask&num){
                a^=num;
            }else{
                b^=num;
            }
        }
        return vector<int>{a,b};
    }
```

​	这种统计频次的题目，如果对空间复杂度没有要求的话，使用哈希表解决往往有较高的效率。

```cpp
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unordered_map<int,int> hash;
        vector<int> ans;
        for(const auto num: nums){
            if(hash.find(num) == hash.end()){
                hash[num] = 1;
            }else{
                ++hash[num];
            }
        }
        for(const auto [h_num,h_cnt]:hash){
            if(h_cnt==1){
                ans.push_back(h_num);
            }
        }
        return ans;
    }
};
```

#### [693 交替位二进制数](https://leetcode-cn.com/problems/binary-number-with-alternating-bits/)

给定一个正整数，检查它的二进制表示是否总是 0、1 交替出现

输入一个整数，输出一个布尔类型表示二进制表示是否总是 0、1 交替出现

> ```
> 输入：n = 10
> 输出：true
> 解释：10 的二进制表示是：1010
> ```

**解析：**

​	一种简单的思路是不断使用算术右移将n的二进制表示末位移出，使用按位与运算获取末位是0还是1，并且比较第 i 个和第 i-1 个末位是否相同，如果相同则直接返回false，检查完成则返回true。

```cpp
class Solution {
public:
    bool hasAlternatingBits(int n) {
        // 记录第一个末位
        int pre = n & 1;
        n>>=1;
        while(n){
            // 比较第 i 个和第 i-1 个末位
            int now = n & 1;
            if(now == pre){
                return false;
            }else{
                // 更新前一个状态
                pre = now;
            }
            n >>= 1;
        }
        return true;
    }
};
```

### 02 二进制特性

​	利用二进制的一些特性，可以把位运算使用到更多问题上。例如，可以利用二进制和位运算输出一个数组的所有子集。假设有一个长度为 n 的数组，可以生成长度为 n 的所有二进制，1 表示选取该数字，0 表示不选取。这样就获得了 `2^n` 个子集。

#### [342 4的幂](https://leetcode-cn.com/problems/power-of-four/)

给定一个整数，判断它是否是 4 的次方。

输入是一个整数，输出是一个布尔值，表示判断结果。

> ```
> 输入：n = 16
> 输出：true
> ```

**解析：**

​	本题可以采用按位与运算简单实现判断数是否为4的幂。如果 n 是 4 的幂，那么 n 的二进制表示中有且仅有一个 1 ，且其位置必须为奇数位，例如`16 = (10000)`，从右向左且从1开始计数的话，16的二进制表示中 1 位于第5位。根据此规律可以将 n 和二进制`01010101010101010101010101010101`或者十六进制的`0x55555555`做按位与，如果得到的结果不为零，那么说明这个数**可能**是 4 的幂。

​	为什么说是可能呢？可以看出上述条件是充分条件而非充要条件，1 与`0x55555555`做按位与的结果也是非0的。

​	所以需要进一步考虑该数 n 也是 2 的幂，才能保证上述条件判断结果为该数是 4 的幂。如果 n 是 2 的幂，那么 n 的二进制表示中也有且仅有一个 1，假设其位置为 pos ；那么 n - 1 二进制表示由第 1 位到第 pos-1 位全部为 1构成。例如`16 = 10000; 15 = 01111 ` ，所以可以得出：如果 `n & (n - 1) == 0`，那么 n 是 2 的幂。

​	最终得到：如果`(n&(n-1))==0 && (n & 0x55555555)!=0`，那么n 是 4 的幂。

```cpp
class Solution {
public:
    bool isPowerOfFour(int n) {
        return n > 0 && !(n&(n-1)) && (n&0x55555555);
    }
};
```

​	当然，本题也可以采用类似求 [326. 3的幂 ](https://leetcode-cn.com/problems/power-of-three/)的方法直接使用对数函数的换底公式构造`log4(n)`，然后使用`fmod()`函数判断该值是否为整数，进而判断 n 是否是 4 的幂。

```cpp
class Solution {
public:
    bool isPowerOfFour(int n) {
        return fmod(log10(n)/log10(4),1) == 0;
    }
};
```

#### [318 最大单词长度乘积](https://leetcode-cn.com/problems/maximum-product-of-word-lengths/)

给定多个字母串，求其中任意两个字母串的长度乘积的最大值，且这两个字母串不能含有相同字母。

输入一个包含多个字母串的一维数组，输出一个整数，表示长度乘积的最大值。

> ```
> 输入: ["a","ab","abc","d","cd","bcd","abcd"]
> 输出: 4 
> 解释: 这两个单词为 "ab", "cd"。
> ```

**解析：**

​	怎样快速判断两个字母串是否含有重复数字呢？可以为每个字母串建立一个长度为 26 的二进制数字 mask，用于表示从右到左每个位置表示是否存在`a-z`对应的字母。例如`abc:111, abd:1011`，如果两个字母串含有重复数字，那它们的二进制表示的按位与不为 0，例如`abc,adbe`存在相同的字母，将它们按位与的结果是`1011!=0`。

​	怎么实现对字符串的编号记录呢？也可以通过位运算实现：首先将 mask 置为 0，然后遍历字符串的所有字符，每一次遍历中计算当前字符串所处的位置，然后使用算术左移，将标识 1 移动到指定位置，移动完成后将其与mask按位与运算，将位置记录在mask中。

​	为了求长度乘积的最大值，可以建立一个哈希表记录字符串与其自身的长度。在计算长度乘积最大值时，遍历哈希表将不存在相同字母的字符串长度相乘并取最大值。

```cpp
class Solution {
public:
    int maxProduct(vector<string>& words) {
        unordered_map<int,int> hash;
        int ans = 0;
        for(const auto& word: words){
            int mask = 0;
            int wordLen = word.length();
            // 为当前字符串编码
            for(const auto c:word){
                // 考虑字符串中每一个字符时，将 1 左移 (c-'a') 位
                int cPos = 1 << (c-'a');
                // 与mask按位与，将当前字符的位置保存到mask中，如果当前字符已经存在不影响mask
                mask = mask | cPos;
            }
            // 更新mask对应的长度时要考虑到：字符串中元素重复出现的情况，这种情况下字符串长度不一致 
            hash[mask] = max(hash[mask],wordLen);
            // 遍历所有已经记录的字符串，如果有不存在相同字符 （mask & h_mask）== 0 的字符串计算当前长度乘积
            for(const auto& [h_mask,h_len]: hash){
                if(!(mask & h_mask)){
                    ans = max(ans,wordLen*h_len);
                }
            }
        }
        return ans;
    }
};
```

#### [338 比特位计数](https://leetcode-cn.com/problems/counting-bits/)

给定一个非负整数 n，求从 0 到 n 的所有数字的二进制表达中，分别有多少个 1。

输入是一个非负整数 n，输出是长度为 n + 1 的非负整数数组，每个位置 m 表示 m 的二进制里有多少个 1。

> 输入：n = 5
> 输出：[0,1,1,2,1,2]
> 解释：0 --> 0, 1 --> 1, 2 --> 10, 3 --> 11, 4 --> 100, 5 --> 101

**解析：**

​	本题如果使用双层循环逐个统计每个数二进制表示中1的个数会出现超时的情况。为了优化可以考虑使用动态规划来解题。

​	设置状态：使用一个一维数组`dp[i]`表示第 i 个数的二进制表示中 1 的个数

​	状态转移方程：对于第 i 个数字，如果该数为奇数即其二进制表示的末位为1，那么该数二进制表示中 1 的个数直接与前一个偶数相关为`dp[i]=dp[i-1]+1`；如果该数为偶数即其二进制表示的末位为0，那么该数二进制表示中 1 的个数与其算术右移一位结果相同，因为其算术右移一位将末位0移出后与对应数的二进制表示一致，即`dp[i]=dp[i>>1]`

​	边界条件：当 n = 0时，`dp[0]=0`

```cpp
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> dp(n+1,0);
        for(int i=1;i<=n;++i){
            if(i&1){
                dp[i] = dp[i-1] + 1;
            }else{
                dp[i] = dp[i>>1];
            }
        }
        return dp;
    }
};
```


