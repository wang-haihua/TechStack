## LeetCode刷题笔记 字符串

​	字符串可以看成是字符组成的数组。由于字符串是程序里经常需要处理的数据类型，因此有很多针对字符串处理的题目。

### 01 字符串比较

#### [242 有效的字母异位词](https://leetcode-cn.com/problems/valid-anagram/)

判断两个字符串包含的字符是否完全相同。

输入两个字符串，输出一个布尔值，表示两个字符串是否满足条件。

> ```
> 输入: s = "anagram", t = "nagaram"
> 输出: true
> ```

**解析：**

​	可以利用哈希表或者数组统计两个数组中每个数字出现的频次，若频次相同，则说明它们包含的字符完全相同。

​	为了降低空间复杂度，我们可以仅采用一个哈希表或数组记录 S 中字符的频次，然后减去 T 中对应字符出现的频次，如果最终该频次为 0 则该字符在 S 和 T 中个数相等，如果最终S和T所有字符频次都想等那么他们是异位词。这种方式避免了单独再开辟一个空间取存储 T 中字符的频次。

```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.length()!=t.length()) return false;
        unordered_map<char,int> s_cnt;
        for(int i=0;i<s.length();++i){
            ++s_cnt[s[i]];
            --s_cnt[t[i]];
        }

        for(const auto [h_key,h_val]: s_cnt){
            if(h_val){
                return false;
            }
        }
        return true;
    }
};
```

#### [205 同构字符串](https://leetcode-cn.com/problems/isomorphic-strings/)

判断两个字符串是否同构。同构的定义是，可以通过把一个字符串的某些相同的字符转换成另一些相同的字符，使得两个字符串相同，且两种不同的字符不能够被转换成同一种字符。

输入两个字符串，输出一个布尔值，表示两个字符串是否满足条件。

> ```
> 输入：s = "egg", t = "add"
> 输出：true
> 输入：s = "foo", t = "bar"
> 输出：false
> ```

**解析：**

​	本题可以通过哈希表记录两个字符串每种字符第一次出现的位置，如果两个字符串中相同位置的字符与它们第一次出现的位置一样，那么这两个字符串同构。如果他们第一次出现的位置一样，那么说明当前两个字符的对应关系是正确的；如果不一样，说明当前两个字符的对应关系是错误的，不满足异构。

```cpp
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if(s.length()!=t.length()) return false;
        unordered_map<char,int> s_first_in;
        unordered_map<char,int> t_first_in;
        for(int i=1;i<s.length();++i){
            if(s_first_in.find(s[i]) == s_first_in.end()){
                s_first_in[s[i]] = i;
            }
            if(t_first_in.find(t[i]) == t_first_in.end()){
                t_first_in[t[i]] = i;
            }
        }
        for(int i=0;i<s.length();++i){
            if(s_first_in[s[i]] != t_first_in[t[i]]){
                return false;
            }
        }
        return true;
    }
};
```

#### [125 验证回文串](https://leetcode-cn.com/problems/valid-palindrome/)

给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。

输入一个字符串，输出一个布尔值表示该字符串是否为回文串

> ```
> 输入: "A man, a plan, a canal: Panama"
> 输出: true
> 解释："amanaplanacanalpanama" 是回文串
> ```

**解析：**

​	**回文串一般都可以采用双指针从两头向中间检验，或者采用中心扩展法从中间向两头验证是否为回文串。**

​	本题可以采用双指针的策略，从字符串首尾两端逐个字符检验。但是本题中给出的字符串有许多非字母字符，可以用一个新字符串保存原字符串中的所有字母小写形式，然后对其使用双指针方法验证。

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        // 筛选出字母内容
        string sgood;
        for (char ch: s) {
            if (isalnum(ch)) {
                sgood += tolower(ch);
            }
        }
        // 双指针验证回文串
        int n = sgood.size();
        int left = 0, right = n - 1;
        while (left < right) {
           if (sgood[left] != sgood[right]) {
                return false;
            }
            ++left;
            --right;
        }
        return true;
    }
};
```

#### [680 验证回文字符串 Ⅱ](https://leetcode-cn.com/problems/valid-palindrome-ii/)

给定一个非空字符串 `s`，**最多**删除一个字符。判断是否能成为回文字符串。

输入一个字符串，输出一个布尔值表示该字符串是否能通过删除操作构成回文串

> ```
> 输入: s = "abca"
> 输出: true
> 解释: 你可以删除c字符。
> ```

**解析：**

​	本题采用双指针的方法检验回文串，两个指针分别指向字符串的头和尾，逐一比较两个指针指向的元素。当出现两个指针指向的字符不想等的情况时分别检验将头指针指向的元素删除和将尾指针指向的元素删除两种情况下继续比较字符，是否仍然可以构成回文串。

```cpp
class Solution {
public:
    bool subPalindrome(string s, int head, int tail){
        for(;head<tail;++head,--tail){
            if(s[head]!=s[tail]){
                return false;
            }
        }
        return true;
    }

    bool validPalindrome(string s) {
        int head = 0, tail = s.size()-1;
        while(head<tail){
            if(s[head]==s[tail]){
                ++head;
                --tail;
            }else{
                if( subPalindrome(s,head,tail-1)||subPalindrome(s,head+1,tail)){
                    return true;
                }else{
                    return false;
                }
            }
        }
        return true;
    }
};
```

#### [647 回文子串](https://leetcode-cn.com/problems/palindromic-substrings/)

给定一个字符串，求其有多少个回文子字符串。回文的定义是左右对称。

输入是一个字符串，输出一个整数，表示回文子字符串的数量。

> ```
> 输入：s = "aaa"
> 输出：6
> 解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa"
> ```

**解析：**

​	本题采用中心扩展法，可以从字符串的每个位置开始，向左向右延长，判断存在多少以当前位置为中轴的回文
子字符串。中心扩展法：枚举每一个可能的回文中心，然后用两个指针分别向左右两边拓展，当两个指针指向的元素相同的时候就拓展，否则停止拓展。枚举过程中要区分子串的长度为偶数情况和奇数情况。

```cpp
class Solution {
public:
    int countCurSub(string s, int lsh, int rsh){
        int count = 0;
        while(lsh>=0 && rsh<s.length() && s[lsh]==s[rsh]){
            --lsh;
            ++rsh;
            ++count;
        }
        return count;
    }

    int countSubstrings(string s) {
        int ans = 0;
        for(int i=0;i<s.length();++i){
            // 长度为奇数的回文子串
            ans += countCurSub(s,i,i);
            // 长度为偶数的回文子串
            ans += countCurSub(s,i,i+1);
        }
        return ans;
    }
};
```

#### [696 计数二进制子串](https://leetcode-cn.com/problems/count-binary-substrings/)

给定一个 0-1 字符串，求有多少非空子字符串的 0 和 1 数量相同。

输入是一个字符串，输出一个整数，表示满足条件的子字符串的数量。

> 输入: "00110011"
> 输出: 6
> 解释: 有6个子串具有相同数量的连续1和0：“0011”，“01”，“1100”，“10”，“0011” 和 “01”。

**解析：**

​	从左往右遍历数组，记录和当前位置数字相同且连续的长度，以及其之前连续的不同数字的长度。举例来说，对于 00110 的最后一位，我们记录的相同数字长度是 1，因为只有一个连续 0；我们记录的不同数字长度是 2，因为在 0 之前有两个连续的 1。若不同数字的连续长度大于等于当前数字的连续长度，则说明存在一个且只存在一个以当前数字结尾的满足条件的子字符串。

```cpp
class Solution {
public:
    int countBinarySubstrings(string s) {
        int pre = 0, cur = 1, count = 0;
        for (int i = 1; i < s.length(); ++i) {
            if (s[i] == s[i-1]) {
                ++cur;
            } else {
                pre = cur;
                cur = 1;
            }
            if (pre >= cur) {
                ++count;
            }
        }
        return count;
    }
};
```



