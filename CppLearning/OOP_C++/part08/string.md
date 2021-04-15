## C++ string类

### string 的初始化

​	使用 string 类要导入头文件 `#include <string>`，string 类是模板类 `typedef basic_string<char> string;`  从 `basic_string` 类模板实例化生成的。string 类有多种构造函数，string 对象的几种初始化方式如下

```cpp
string s1("Hello");
string month = "March";
string s2(8,'x'); // 生成具有8个x字符的字符串
// string 对象不能用字符(char)进行初始化，但是可以用字符对string 对象进行赋值
string error1 = 'c';
string error2('c');
// string 对象不能用数值进行初始化
string error1 = 22;
string error2(8);
```

### string 的基础操作

**获取长度** `length()`：

​	string 对象的长度用成员函数 `length()` 读取，`string s("hello"); cout << s.length();`

**流读取** `getline()`：

​	string 类支持流读取运算符，`string str; cin >> str;`。同时支持 `getline()` 函数，从流读取中读取一整行到指定的 string 对象，`getline(cin, str);`

**赋值** `=`：

​	string 类支持 `=` 运算符进行赋值，`string s1("cat"), s2;`

**复制** `assign()`：

​	string 对象使用 `assign()` 成员函数进行复制，`string s1("cat"), s3; s3.assign(s1);`，使用 `assign()` 函数除了可以完整复制，也可以指定起始位置和子串长度进行**部分复制**，`s3.assign(s1,1,3);` 从 s1 中下标为1的字符开始复制3个字符的子串给 s3。除此之外也可以对单个字符进行复制 `s2[5] = s1[3] = 'a';`

**随机访问** `at()`：

​	string 对象可以使用 `at()` 成员函数逐个访问对象中的字符，也可以使用**下标运算符** `[]` 进行随机访问，区别在于 `at()` 成员函数会做范围检查，如果超出范围会抛出 `out_of_range` 异常，而下标运算符不做范围检查。`string str("Hello"); sout<< str.at(1) << str[2];`

**连接** `append()`：

​	string 对象的连接可以使用 `append()` 成员函数连接字符串，`string s1("hello"), s2("world"); s1.append(s2);`；和 `assign()` 函数类似 `append()` 函数也可以通过指定起始位置和长度进行**部分连接**，`s2.append(s1,3,s1.size());` 从 s1 中下标为3开始将s1.size() 个字符连接到 s2 字符串，如果字符串内没有足够字符，则复制到字符串最后一个字符。除了 `append()` 函数也可以使用**连接运算符** `+` 连接字符串，`s1 += s2;`。

**取子串** `substr()`：

​	string 对象使用 `substr()` 成员函数取子串，`string s1("hello"), s2; s2 = s1.substr(0,4);` 返回 s1 从下标0开始的4个字符组成的子串给 s2。

**交换** `swap()`：

​	string 对象使用 `swap()` 成员函数交换两个 string 对象的值，`string s1("hello"), s2("world"); s1.swap(s2);`

**替换** `replace()`：

​	string 对象使用 `replace()` 成员函数替换字符串，`string s1("hello"); s1.replace(2,3,"1234");` 将 s1 中从下标 2 开始的3个字符串用 "1234" 替换；也可以使用·	`s1.replace(2,3,"1234",1,2);` 指定用于替换字符串的子串，即用 "1234" 下标 1 开始的两个字符进行替换。

**插入** `insert()`：

​	string 对象使用 `insert()` 成员函数插入其他字符串，`string s1("hello"), s2("world"); s1.insert(4,s2);` 将 s2 插入到 s1 下标为4的位置；`s1.insert(2,s2,0,3);` 将 s2 从下标0开始的3个字符插入到 s1 下标为2的位置；

**删除子串** `erase()`：

​	string 对象使用 `erase()` 成员函数删除子串，`string s1("hello"); s1.erase(2);` 将 s1 中从下标 2 开始（包含下标2的字符）之后的字符删除。

  ### string 的比较操作

**关系运算符比大小**：string 对象可以关系运算符比较大小 `==, >, >=, <, <=, !=` 返回值都是 bool 类型，成立返回 true，否则返回 false

```cpp
string s1("hello"),s2("hello"),s3("hell");
bool b = (s1 == s2);
cout << b << endl;
b = (s1 == s3);
cout << b << endl;
b = (s1 > s3);
cout << b << endl;
```

`compare()`**函数比大小**：string 对象也可以`compare()` 成员函数比较大小 ，大于返回值为 1，等于返回值为 0，小于返回值为 -1；和 `assign(), append()`函数类似，`compare()`函数也可以指定起始位置和长度进行**部分比较**，`s1.compare(1,2,s3,0,3);` s1 从以开始的2个字符构成的子串和 s3 从0开始的3个字符构成的子串进行比较。

### string 的查找操作

​	示例 `string s1("hello, world");`

* `find()`：`s1.find("lo");` 在 s1 中从前向后查找 `"lo"` 第一次出现的地方，如果找到返回对应的位置即 `l` 的位置下标；如果没有找到则返回一个静态常量 `string::npos` 。除此之外，`find()` 成员函数也可以指定查找的起始位置，`s1.find("ll",3);`表示从 s1 下标为3的位置开始从前向后查找。
* `rfind()`：`s1.rfind("lo");` 在 s1 中从后向前查找 `"lo"` 第一次出现的地方，如果找到返回对应的位置即 `l` 的位置下标；如果没有找到则返回一个静态常量 `string::npos` 
* `find_first_of()`：`s1.find_first_of("abcd");` 在 s1 中从前向后查找 `"abdc"` 中**任何一个**字符第一次出现的地方，如果找到返回被找到字母的位置；如果没有找到则返回一个静态常量 `string::npos` 

* `find_last_not_of()`：`s1.find_last_not_of("abcd");` 在 s1 中从后向前查找**不在** `"abdc"` 中**任何一个**字符第一次出现的地方，如果找到返回被找到字母的位置；如果没有找到则返回一个静态常量 `string::npos` 

### string 的C语言转换

​	C++ 是兼容 C 语言的，但是 C 语言中没有 string 类，所以要使用一些方法将 string 对象转换为 C 语言支持的 `char *` 字符串。

* `c_str()`：返回一个以 `\0` 结尾的 C 字符串，即 `c_str()` 函数返回一个指向正规 C 字符串的指针, 内容与原始string串相同。例如 `string s1("hello world"); s1.c_str();` ，`s1.c_str();` 返回传统的 `const char *` 类型字符串，且该字符串以 `\0` 结尾。
* `data()`：与 `c_str()` 方法类似，但是返回的是 `char *` 类型字符串，而非 `const` 类型，在修改时会导致原始字符转被更改。

### 字符串流处理

​	除了标准流和文件流输入输出外，还可以从 string 进行输入输出。类似 istream 和 ostream 进行标准流输入输出，也可以用 istringstream 和 ostringstream 进行字符串上的输入输出，也称为内存输入输出。使用字符串流处理需要导入以下头文件 `<string> <iostream> <sstream>`。

```cpp
// 使用 istringstream 进行字符串输入
string input("Input test 123 4.7 A");
istringstream inputString(input); // 声明istringstream对象
int i; double d; char c;
inputString >> str1 >> str2 >> i >> d >> c; // 使用istringstream对象进行字符串输入
cout << str1 << str2 << endl;
cout << i << ' ' << d << ' ' << c << endl;

// 使用 ostringstream 进行字符串输出
ostringstream outputString;
int a = 10;
outputString << "This" << a << "ok" << endl;
cout << outputString.str(); // 取出ostringstream的字符串
```

### Reference

[C++string类总结](https://www.cnblogs.com/X-Do-Better/p/8628492.html)