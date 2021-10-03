## LeetCode刷题笔记 数学问题

### 01 公倍数与公因数

​	公倍数(common multiple)是指在两个或两个以上的自然数中，如果它们有相同的倍数，这些倍数就是它们的公倍数。公倍数中最小的，就称为这些整数的最小公倍数（lowest common multiple，lcm）

​	公因数，亦称公约数。它是一个能同时整除若干整数的整数 。如果一个整数同时是几个整数的因数，称这个整数为它们的公因数；公因数中最大的称为最大公因数 （greatest common divisor，gcd）

​	利用辗转相除法，计算公式为`gcd(a,b) = gcd(b,a mod b)`我们可以很方便地求得两个数的最大公因数；将两个数相乘再除以最大公因数即可得到最小公倍数。

``` cpp
int gcd(int a, int b){
    if(b==0){
        return a;
    }
    return gcd(b, a % b);
}

int lcm(int a, int b){
    int gcdRes = gcd(a,b);
    return a*b / gcdRes;
}
```

### 02 质数问题

​	质数又称素数，指的是指在大于 1 的自然数中，除了 1 和它本身以外不再有其他因数的自然数。值得注意的是，每一个数都可以分解成质数的乘积。

#### [204 计数质数](https://leetcode-cn.com/problems/count-primes/)

给定一个数字 n，求小于 n 的质数的个数。

输入一个整数，输出也是一个整数，表示小于输入数的质数的个数。

> ```
> 输入：n = 10
> 输出：4
> 解释：小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7 。
> ```

**解析：**

​	埃拉托斯特尼筛法（Sieve of Eratosthenes，简称埃氏筛法）是非常常用的，判断一个整数是否是质数的方法。并且它可以在判断一个整数 n 时，同时判断所小于 n 的整数，因此非常适合这道题。其原理也十分易懂：从 1 到 n 遍历，假设当前遍历到 m，则把所有小于 n 的、且是 m 的倍数的整数标为和数；遍历完成后，没有被标为和数的数字即为质数。

​	一般情况下标记和数时从 2m 开始标记，此处可以进一步优化，对于一个质数 m，如果从 2m 开始标记其实是冗余的，应该直接从 m^2 开始标记，因为 2m, 3m, … 这些数一定在 m^2 之前就被其他数的倍数标记过了，例如 2 的所有倍数，3 的所有倍数等。

```cpp
class Solution {
public:
    int countPrimes(int n) {
        vector<bool> prime(n,true);
        int ans = 0;
        for(int i=2;i<n;++i){
            if(prime[i]){
                ++ans;
                if((long long)i*i < n){ // i^2 可能越界 用长整型表示
                    for(int j=i*i;j<n;j+=i){
                        prime[j] = false;
                    }
                }
            }
        }
        return ans;
    }
};
```

#### [172 阶乘后的零](https://leetcode-cn.com/problems/factorial-trailing-zeroes/)

给定一个非负整数，判断它的阶乘结果的结尾有几个 0。

输入一个非负整数，输出一个非负整数，表示输入的阶乘结果的结尾有几个 0。

> ```
> 输入：n = 5
> 输出：1
> 解释：5! = 120 ，有一个尾随 0
> ```

**解析：**

​	**唯一分解定理**：任何一个大于1的自然数 N，如果 N 不为质数，那么 N 可以唯一分解成有限个质数的乘积。例如：`42 = 2×3×7, 75 = 3×5×5`。

​	每个尾部的 0 由 2 × 5 = 10 而来，因此可以把阶乘的每一个元素拆成质数相乘，统计有多少个 2 和 5 数对。明显的，质因子 2 的数量远多于质因子 5 的数量，因为**每 4 个数字**算作额外的因子 2，但是只有**每 25 个**数字算作额外的因子 5，因此可以进一步优化只统计阶乘结果里有多少个质因子 5。

​	对于一个数的阶乘，就如之前分析的，5 的因子一定是每隔 5 个数出现一次，也就是下边的样子。`n! = 1 * 2 * 3 * 4 * (1 * 5) * ... * (2 * 5) * ... * (3 * 5) *... * n`。因为每隔 5 个数出现一个 5，所以计算出现了多少个 5，我们只需要用 n/5 就可以算出来。

但还没有结束，继续分析。`... * (1 * 5) * ... * (1 * 5 * 5) * ... * (2 * 5 * 5) * ... * (3 * 5 * 5) * ... * n`。每隔 25 个数字，出现的是两个 5，所以除了每隔 5 个数算作一个 5，每隔 25 个数，还需要多算一个 5。也就是我们需要再加上 n / 25 个 5。

​	同理还会有每隔 5 * 5 * 5 = 125 个数字，会出现 3 个 5，所以还需要再加上 n / 125 。

​	综上，规律就是每隔 5 个数，出现一个 5，每隔 25 个数，出现 2 个 5，每隔 125 个数，出现 3 个 5... 以此类推。最终 5 的个数就是 `n / 5 + n / 25 + n / 125 ...`

```cpp
class Solution {
public:
    int trailingZeroes(int n) {
        if(n==0){
            return 0;
        }
        int a = n / 5;
        return a + trailingZeroes(a);
    }
};
```

### 03 进制转换问题

#### [504 七进制数](https://leetcode-cn.com/problems/base-7/)

给定一个十进制整数，求它在七进制下的表示。

输入一个整数，输出一个字符串，表示其七进制。

> ```
> 输入: num = 100
> 输出: "202"
> 解释：100 的七进制表示法来源于 100 = 2 * 49 + 0 * 7 + 2 * 1。
> ```

**解析：**

​	**进制转换类型的题**，通常是利用除法和取模（mod）来进行计算，同时也要注意一些细节，如负数和零。如果输出是数字类型而非字符串，则也需要考虑是否会超出整数上下界。	

```cpp
class Solution {
public:
    string convertToBase7(int num) {
        if(num == 0) return "0";
        bool isNegatibe = num < 0;
        num = abs(num);
        string ans;
        while(num){
            int a = num / 7;
            int b = num % 7;
            ans = to_string(b) + ans;
            num = a;
        }
        if(isNegatibe){
            return "-"+ans;
        }
        return ans;
    }
};
```

#### [168 Excel表列名称](https://leetcode-cn.com/problems/excel-sheet-column-title/)

给你一个整数 `columnNumber` ，返回它在 Excel 表中相对应的列名称。

输入一个整数，输出一个字符串表示Excel 表中相对应的列名称

> ```
> 输入：columnNumber = 28
> 输出："AB"
> ```

**解析：**

​	本题是进制转换题型的变种题，和504七进制转换题十分相似，可以视为26进制转换，但是需要注意的是输入的整数是从 1 开始而不是 0，所以要将输入减1。

```cpp
class Solution {
public:
    string convertToTitle(int columnNumber) {
        string ans;
        while(columnNumber){
            int a = (columnNumber-1) / 26;
            int b = (columnNumber-1) % 26;
            columnNumber = a;
            char c = b + 'A';
            ans = c + ans;
        }
        return ans;
    }
};
```

#### [202 快乐数](https://leetcode-cn.com/problems/happy-number/)

输入一个整数，判断它是否是快乐数，快乐数是指将该数替换为它每个位置上的数字的平方和，如果该数进过上述过程最终变为 1,则称为快乐数

> ```
> 输入：19
> 输出：true
> 解释：
> 1^2 + 9^2 = 82
> 8^2 + 2^2 = 68
> 6^2 + 8^2 = 100
> 1^2 + 0^2 + 0^2 = 1
> ```

**解析：**

​	本题有两个需要注意的地方，和504七进制转换题一样要能够转换出十进制每一位上的数值获取下一个数值。另一个点是，不是快乐数的数可能是 **无限循环** 但始终变不到 1，看到无限循环就能想到成环，而环路检测最常用的方法就是弗洛伊德判圈算法，可以使用快慢指针实现。

```cpp
class Solution {
public:
    int getNext(int num){
        int nextNum = 0;
        while(num){
            int b = num % 10;
            num = num / 10;
            nextNum += b*b;
        }
        return nextNum;
    }

    bool isHappy(int n) {
        int slow = n;
        int fast = getNext(n);
        while(fast!=1 && fast!=slow){
            slow = getNext(slow);
            fast = getNext(getNext(fast));
        }
        return fast == 1;
    }
};
```

### 04 数字字符串求和问题

#### [415 字符串相加](https://leetcode-cn.com/problems/add-strings/)

给定两个由数字组成的字符串，求它们相加的结果。

输入是两个字符串，输出是一个整数，表示输入的数字和。

> ```
> 输入：num1 = "11", num2 = "123"
> 输出："134"
> ```

**解析：**

​	因为相加运算是从后往前进行的，所以可以先翻转字符串也可以从字符串尾部开始，再逐位计算。这种类型的题考察的是细节，如进位、位数差等等。

​	从字符串尾部开始计算和，如果扫描超出其中一个字符串长度则用0值代替，如果两个字符串计算完毕要检查是否还存在进位。字符串的数值计算通过与字符`'0'`比较得到。

```cpp
class Solution {
public:
    string addStrings(string num1, string num2) {
        int tail1 = num1.length()-1, tail2 = num2.length()-1;
        string ans = "";
        int addbit = 0;
        while(tail1>=0 || tail2>=0 || addbit!=0){
            int x = 0, y = 0;
            if(tail1 >= 0){
                x = num1[tail1--] - '0';
            }
            if(tail2 >=0 ){
                y = num2[tail2--] - '0';
            }
            int add = x + y + addbit;
            // 记录当前位计算结果
            ans.push_back(add % 10 + '0');
            // 记录进位情况
            if(add < 10){
                addbit = 0;
            }else{
                addbit = 1;
            }
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};
```

#### [67 二进制求和](https://leetcode-cn.com/problems/add-binary/)

给你两个二进制字符串，返回它们的和（用二进制表示）

输入是两个字符串，输出是一个字符串，表示输入的二进制数字和。

>```
>输入: a = "1010", b = "1011"
>输出: "10101"
>```

**解析：**

​	本题和字符串相加类似，从尾部开始逐位运算，要注意进位和两个字符串位数差的情况。

```cpp
class Solution {
public:
    string addBinary(string a, string b) {
        int taila = a.length()-1, tailb = b.length()-1;
        string ans;
        int addbit = 0;
        while(taila>=0 || tailb>=0 || addbit){
            int x = 0, y = 0;
            if(taila >= 0){
                x = a[taila--] - '0';
            }
            if(tailb >= 0){
                y = b[tailb--] - '0';
            }
            int add = x + y + addbit;
            char c = add % 2 + '0';
            ans = c + ans;
            if(add < 2){
                addbit = 0;
            }else{
                addbit = 1;
            }
        }
        return ans;
    }
};
```

### 05 众数问题

#### [169 多数元素](https://leetcode-cn.com/problems/majority-element/)

给定一个大小为 *n* 的数组，找到其中的多数元素。多数元素是指在数组中出现次数 **大于** n / 2 的元素。

输入一个一维数组，输出一个整数，表示数组中个数占多数的元素。

> ```
> 输入：[3,2,3]
> 输出：3
> ```

**解析：**

​	采用哈希表是一种最为直接的方法，统计数组中每个元素出现的次数，然后找出频次最高的元素即可。

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int,int> counts;
        for(const auto elem:nums){
            if(counts.find(elem) != counts.end()){
                counts[elem]++;
            }else{
                counts.insert(make_pair(elem,1));
            }
        }
        int ans = 0;
        int max = INT_MIN;
        for(const auto count: counts){
            if(count.second > max){
                ans = count.first;
                max = count.second;
            }
        }
        return ans;
    }
};
```

​	本题也可以采用**摩尔投票法**更加简洁的解决。摩尔投票法的基本原理是：在数组中找到两个不相同的元素并删除它们，不断重复此过程，直到数组中元素都相同，那么剩下的元素就是主要元素。

​	这种找主要元素的方法是怎么得以实现的呢？该投票法，遇到相同的元素则票数加 1，遇到不同的元素则票数减 1，当该元素的票数为 0 时更换投票主要元素。在主要元素个数大于 n / 2 的情况下，相当于每个主要元素和其他元素两两相互抵消，抵消到最后肯定还剩余至少 1 个多数元素。

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int major = nums[0];
        int count = 0;
        for(int i=0;i<nums.size();++i){
            if(major == nums[i]){
                ++count;
            }else if(count == 0){
                major = nums[i];
            }else{
                --count;
            }
        }
        return major;
    }
};
```

#### [229 求众数 II](https://leetcode-cn.com/problems/majority-element-ii/)

给定一个大小为 *n* 的整数数组，找出其中所有出现超过 `n / 3` 次的元素。

输入一个一维数组，输出一个一维数组包含所有频次超过 n/3 的元素

> ```
> 输入：[1,1,1,3,3,2,2,2]
> 输出：[1,2]
> ```

**解析：**

​	本题是**摩尔投票法**的进阶用法，摩尔投票法的核心是通过**抵消**和**计票**选出多数，可以推出规律：如果至多选一个代表，那他的票数至少要超过一半 1/2 的票数；如果至多选两个代表，那他们的票数至少要超过 1/3 的票数；类推可知，如果至多选 m 个代表，那他们的票数至少要超过 1 / (m+1)  的票数。

​	回到本题，求频次超过 n/3 的元素，那么最多只有两个，要注意多个主要元素时的抵消情况：（1）A同B不同，A++，B不变；（2）A不同B同，A不变，B++；（3）AB均不同，A--，B--；。

```cpp
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> res;        
        const int len = nums.size();		
        int major1, major2;        
        int count1 = 0, count2 = 0;        
        for(int i = 0; i < len; i++) {
            // 存在元素相同
            if(nums[i] == major1){
                ++count1;
            }
            else if(nums[i] == major2){
                ++count2;
            }
            // 替换主要元素
            else if(count1 == 0) {
				major1 = nums[i];
				count1 = 1;
			}
            else if(count2 == 0) {
				major2 = nums[i];
				count2 = 1;
			}
            // 与major1和major2都不同时才抵消，如果只有一个不同的情况是另一个计数增加，不要想成了让不同的那一个去抵消，这里容易出错
            else {
				count1--;
				count2--;
			}
        }
        // 检验结果中元素数目是否超过三分之一
        count1 = 0, count2 = 0;
        for(auto &num : nums) {
            if(num == major1) count1++;
            else if(num == major2) count2++;
        }

        if(count1 > len / 3) res.push_back(major1);
        if(count2 > len / 3) res.push_back(major2);
        return res;
    }
};
```

### 06 中位数问题

#### [462 最少移动次数使数组元素相等 II](https://leetcode-cn.com/problems/minimum-moves-to-equal-array-elements-ii/)

给定一个非空整数数组，找到使所有数组元素相等所需的最小移动数，其中每次移动可将选定的一个元素加1或减1。 您可以假设数组的长度最多为10000。

输入一个数组，输出一个整数表示最少移动的步数。

> 输入: [1,2,3]
>
> 输出: 2
>
> 解释：只有两个动作是必要的（记得每一步仅可使其中一个元素加1或减1）： [1,2,3]  =>  [2,2,3]  =>  [2,2,2]

**解析：**

​	本题的关键是找数组的中位数。

```cpp
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int len = nums.size();
        int mid = nums[len/2];
        int ans = 0;
        for(int i=0;i<len;++i){
            ans += abs(nums[i]-mid);
        }
        return ans;
    }
};
```

### 07 数字处理问题

#### [238 除自身以外数组的乘积](https://leetcode-cn.com/problems/product-of-array-except-self/)

给定一个长度为 n 的整数数组 nums，其中 n > 1，返回输出数组 output ，其中 output[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。

输入一个数组，输出一个数组，其中每个元素数值为除本身之外所有元素的乘积

> ```
> 输入: [1,2,3,4]
> 输出: [24,12,8,6]
> ```

**解析：**

​	本题与135题分糖果相似，可以先从左到右计算当前元素左侧所有元素的乘积，然后从右到左计算当前元素右侧所有元素的乘积，再将两个元素乘积相乘得到最终结果。

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int len = nums.size();
        vector<int> output(len,1);
        vector<int> L(len,1);
        vector<int> R(len,1);
        for(int i=1;i<len;++i){
            L[i] = L[i-1] * nums[i-1];
        }
        for(int i=len-2;i>=0;--i){
            R[i] = R[i+1] * nums[i+1];
            output[i] = L[i]*R[i];
        }
        output[len-1] = L[len-1];
        return output;
    }
};
```

​	进一步优化空间复杂的，在从左和从右扫描中，用一个全局变量记录 i 之前或 i 之后所有元素的乘积

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int len = nums.size();
        vector<int> output(len,1);
        int product = nums[0];
        for(int i=1;i<len;++i){  
            output[i] = product;
            product *= nums[i]; // 记录从开头到当前位置中所有元素的乘积
        }
        product = nums[len-1];
        for(int i=len-2;i>=0;--i){
            output[i] *= product;
            product *= nums[i];// 记录从结尾到当前位置中所有元素的乘积
        }
        return output;
    }
};
```

#### [326 3的幂](https://leetcode-cn.com/problems/power-of-three/)

判断一个数字是否是 3 的次方。

输入一个整数，输出一个布尔值。

> Input: n = 27
> Output: true

**解析：**

​	第一种方式是使用对数函数以3为底的对数函数，如果 n 是 3 的次方那么其值应该为整数。math库中提供了以 e 为底的`log()`和以10为底的`log10()`，根据换底公式有`log3(n) = log10(n)/log10(3)`。
$$
log_a^b = log_c^b / log_c^a
$$

```cpp
class Solution {
public:
    bool isPowerOfThree(int n) {
        if(n == 0) return false;
        double m = log10(n) / log10(3);
        // fmod(double x, double y) 用于计算浮点数取模
        return fmod(m,1) == 0; 
    }
};
```

​	另一中方式因为在 int 范围内 3 的最大次方是 3^19 = 1162261467，如果 n 是 3 的整数次方，那么 1162261467 除以 n 的余数一定是零；反之亦然。

```cpp
class Solution {
public:
    bool isPowerOfThree(int n) {
        return n > 0 && 1162261467 % n == 0;
    }
};
```

### 08 随机数问题

#### [384 打乱数组](https://leetcode-cn.com/problems/shuffle-an-array/)

给定一个数组，要求实现两个指令函数。第一个函数 `shuﬄe()` 可以随机打乱这个数组，第二个函数 `reset()` 可以恢复原来的顺序。

输入是一个存有整数数字的数组，和一个包含指令函数名称的数组。输出是一个二维数组，表示每个指令生成的数组。

> 输入: ["Solution", "shuffle", "reset", "shuffle"] [[[1, 2, 3]], [], [], []]
>
> 输出: [null, [3, 1, 2], [1, 2, 3], [1, 3, 2]]
>
> 解释:
> Solution solution = new Solution([1, 2, 3]);
> solution.shuffle();    // 打乱数组 [1,2,3] 并返回结果。任何 [1,2,3]的排列返回的概率应该相同。例如，返回 [3, 1, 2]
> solution.reset();      // 重设数组到它的初始状态 [1, 2, 3] 。返回 [1, 2, 3]
> solution.shuffle();    // 随机返回数组 [1, 2, 3] 打乱后的结果。例如，返回 [1, 3, 2]

**解析：**

​	本题可以采用经典的 Fisher-Yates 洗牌算法，原理是通过随机交换位置来实现随机打乱，有正向和反向两种写法。在每次迭代中，生成一个范围在当前下标到数组末尾元素下标之间的随机整数。接下来，将当前元素和随机选出的下标所指的元素互相交换，这一步模拟了每次从 “帽子” 里面摸一个元素的过程，其中选取下标范围的依据在于每个被摸出的元素都不可能再被摸出来了。此外还有一个需要注意的细节，**当前元素是可以和它本身互相交换**的 ，否则生成最后的排列组合的概率就不对了。

​	注意 reset 函数以及类的构造函数的实现细节，使用成员变量保存原数组。

```cpp
class Solution {
private:
    vector<int> origin;

public:
    Solution(vector<int>& nums) {
        origin = nums;
    }
    
    vector<int> reset() {
        return origin;
    }
    
    vector<int> shuffle() {
        // 反向洗牌
        if(origin.empty()) return {};
        vector<int> shuffleNum(origin);
        for(int i=shuffleNum.size()-1;i>=0;--i){
            int pos = rand()%(i+1);
            swap(shuffleNum[i],shuffleNum[pos]);
        }
        // 正向洗牌
        /*
        int len = shuffleNum.size();
        for(int i=0;i<len;++i){
            int pos = rand()%(len-i);
            swap(shuffleNum[i],shuffleNum[i+pos]);
        }
        */
        return shuffleNum;
    }
};
```

#### [528 按权重随机选择](https://leetcode-cn.com/problems/random-pick-with-weight/)

给定一个数组，数组每个位置的值表示该位置的权重，要求按照权重的概率去随机采样。

输入是一维正整数数组，表示权重；和一个包含指令字符串的一维数组，表示运行几次随机采样。输出是一维整数数组，表示随机采样的整数在数组中的位置。

> 输入: weights = [1,3], actions: ["pickIndex","pickIndex","pickIndex"]
>
> 输出: [0,1,1]
>
> 解释：在这个样例中，每次选择的位置都是不确定的，但选择第 0 个位置的期望为 1/4，选择第 1个位置的期望为 3/4。

**解析：**

​	进一步读懂题目。假设有数组w: [1, 2, 3, 4], 那么这个数组的的和为 1 + 2 + 3 + 4 = 10。对应的得到 index {0,1,2,3} 的概率为 {1/10, 2/10, 3/10, 4/10}。现在要返回 {0,1,2,3} 中的随意一个index，但是要保证pickIndex()函数所得到这个index的概率是根据以上的权重来的。

​	首先，求出前缀和表。paritial_sum()就是求前缀和，w[0] = W[0], w[1] = W[0] + W[1]...如此推算

​	然后，求出前缀和表后最后一位数所包含的就是所有数字的和。用以上的例子 w.back() 最终会包含 1 + 2 + 3 + 4 = 10
​	接着，求出一个随机数，rand() % w.back(); 假设 w.back() = 10, 那么这里产生的数字是 0-9。如果我们继续用以上的例子的话那么其每个数字所对应取到的index便为，0 ：代表取到 index 0；1，2: 代表取到 index 1；3，4，5: 代表取到 index 2；6，7, 8, 9: 代表取到 index 3
​	最后，用以上的例子产生的前缀和表 [1, 3, 6, 10], 可以发现我们用得到的数字调用 upper_bound() 会刚好使其指向我们的 index 位置。0 的 upper_bound 会指向 index 0, 因为第一个比 0 大的数是 w[0] = 1；1, 2 的 upper_bound 会指向 index 1, 因为第一个比 1 或者 2 大的数是 w[1] = 3；3, 4, 5 的 upper_bound 会指向 index 2, 因为第一个比 {3, 4, 5} 大的数是 w[2] = 6；6, 7, 8, 9 的 upper_bound 会指向 index 3, 因为第一个比 {6，7, 8, 9} 大的数是 w[3] = 10;

```cpp
class Solution {
private:
    vector<int> sums;
public:
    Solution(vector<int>& w) {
        sums = w;
        partial_sum(sums.begin(),sums.end(),sums.begin()); 
    }
    
    int pickIndex() {
        int pos = (rand()%sums.back()) + 1;
        return lower_bound(sums.begin(), sums.end(), pos) - sums.begin();
    }
};
```

#### [382 链表随机节点](https://leetcode-cn.com/problems/linked-list-random-node/)

给定一个单向链表，要求设计一个算法，可以随机取得其中的一个数字。

输入是一个单向链表，输出是一个数字，表示链表里其中一个节点的值。

> // 初始化一个单链表 [1,2,3].
> ListNode head = new ListNode(1);
> head.next = new ListNode(2);
> head.next.next = new ListNode(3);
> Solution solution = new Solution(head);
>
> // getRandom()方法应随机返回1,2,3中的一个，保证每个元素被返回的概率相等。
> solution.getRandom();

**解析：**

​	不同于数组，在未遍历完链表前，无法知道链表的总长度。这里可以使用**水库采样**：遍历一次链表，在遍历到第 m 个节点时，有 1/m 的概率选择这个节点覆盖掉之前的节点选择。**采用水库算法满足每个点都有均等的概率被选择的随机性**。

​	水库采样，也称为蓄水池抽样算法。概算法常被用于大数据流中的随机抽样问题即：当内存无法加载全部数据时，如何从包含未知大小的数据流中随机选取k个数据，并且要保证每个数据被抽取到的概率相等。该算法每次只保留一个数，当遇到第 i 个数时，以 1/i的概率保留它，(i-1)/i的概率保留原来的数，采用这种方式始终保持每个数被保留的概率是 1/N。例如，{1,2,3} 三个数以数据流的形式读取：1到达时将其以概率为 1/1 保留；2到达时以概率 1/2 保留，1 以 `(2-1) / 2` 即 `1/2 * 1 = 1/2` 保留；3 到达时以概率 1/3 保留，1 以 `(3-1)/2 * 1/2 = 1/3` 保留，同理 2 也以1/3保留。可以看出水库抽样算法可以始终保持每个数被保留的概率都是 1/N。

```cpp
class Solution {
    ListNode* headNode;
public:
    Solution(ListNode* head) {
        headNode = head;
    }
    
    int getRandom() {
        int ans = headNode->val;
        ListNode* node = headNode->next;
        int i = 2;
        while(node){
            if(rand()%i == 0){
                ans = node->val;
            }
            ++i;
            node = node->next;
        }
        return ans;
    }
};
```

#### [470 用 Rand7() 实现 Rand10()](https://leetcode-cn.com/problems/implement-rand10-using-rand7/)

已有方法 `rand7` 可生成 1 到 7 范围内的均匀随机整数，试写一个方法 `rand10` 生成 1 到 10 范围内的均匀随机整数。

**解析：**

​	用现有范围随机数生成函数构造新的范围的随机数生成函数。这种问题分为两种情况：一种是缩小原有随机数生成函数的范围，另一种是扩展原有随机数生成函数的范围。

​	第一种缩小范围情况较为简单，只需要将范围之外的随机数丢弃即可。

​	第二种扩展范围的情况要用到一个公式，`(randM()-1) * M + randM()` 可以生成`1～M*M`范围内的等概率随机数。

```cpp
class Solution {
public:
    int rand10() {
        int num = (rand7()-1)*7+rand7();
        while(num>10){
            num = (rand7()-1)*7+rand7();
        }
        return num;
    }
};
```

