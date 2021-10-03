## LeetCode刷题笔记 分治策略

​	分治问题由**分**（divide）和**治**（conquer）两部分组成，通过把原问题分为子问题，再将子问题进行处理合并，从而实现对原问题的求解。

#### [241 为运算表达式设计优先级](https://leetcode-cn.com/problems/different-ways-to-add-parentheses/)

给定一个只包含加、减和乘法的数学表达式，求通过加括号可以得到多少种不同的结果。

输入是一个字符串，表示数学表达式；输出是一个数组，存储所有不同的加括号结果。

> ```
> 输入: "2-1-1"
> 输出: [0, 2]
> 解释: 
> ((2-1)-1) = 0 
> (2-(1-1)) = 2
> ```

**解析：**

​	利用分治思想，我们可以把加括号转化为：对于每个运算符号，先执行处理两侧的数学表达式，再处理此运算符号。例如`2-1-1`，先将第一个减号的两侧划分为两个部分即`2, 1-1`，分别计算得到结果为 2；第二个减号的两侧划分为两个部分即`2-1, 1`，分别计算得到的结果是 0。注意边界情况，即字符串内无运算符号，只有数字。

```cpp
class Solution {
public:
    vector<int> diffWaysToCompute(string expression) {
        vector<int> ways;
        for(int i=0;i<expression.length();++i){
            char c = expression[i];
            if( c == '+' || c == '-' || c == '*'){
                vector<int> lsh = diffWaysToCompute(expression.substr(0,i));
                vector<int> rsh = diffWaysToCompute(expression.substr(i+1));
                for(const int& l: lsh){
                    for(const int& r: rsh){
                        switch(c){
                            case '+': ways.push_back(l+r); break;
                            case '-': ways.push_back(l-r); break;
                            case '*': ways.push_back(l*r); break;
                        }
                    }
                }
            }
        }
        if(ways.empty()){
            ways.push_back(stio(expression));
        }
        return ways;
    }
};
```

​	`stoi()`方法是 C++11的新特性，更多字符串与其他类型的相互转化如下

```cpp
// #include <string>
// 其他类型转字符串
string to_string(int _Val);
string to_string(unsigned int _Val);
string to_string(long _Val);
string to_string(unsigned long _Val);
string to_string(long long _Val);
string to_string(unsigned long long _Val);
string to_string(float _Val);
string to_string(double _Val);
string to_string(long double _Val);

// 字符串转其他类型
double stod(const string& _Str, size_t *_Idx = nullptr);
float stof(const string& _Str, size_t *_Idx = nullptr);
int stoi(const string& _Str, size_t *_Idx = nullptr, int _Base = 10);
long stol(const string& _Str, size_t *_Idx = nullptr, int _Base = 10);
long double stold(const string& _Str, size_t *_Idx = nullptr);
unsigned long stoul(const string& _Str, size_t *_Idx = nullptr, int _Base = 10);
long long stoll(const string& _Str, size_t *_Idx = nullptr, int _Base = 10);
unsigned long long stoull(const string& _Str, size_t *_Idx = nullptr, int _Base = 10);
```

