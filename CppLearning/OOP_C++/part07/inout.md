## C++ 输入输出流

### 输入输出流基本概念

**与输入输出流操作相关的类**：类的继承关系从上往下如下图所示

<img src="D:\01BasicLearning\TechnicalRoute\CppLearning\OOP_C++\part07\输入输出类.png" alt="输入输出类" style="zoom:50%;" />

* `istream`：用于输入的流类，`cin` 是该类的对象
* `ostream`：用于输出的流类，`cout cerr clog` 是该类的对象
* `ifstream`：用于从文件读取数据的类
* `ofstream`：用于向文件写入数据的类
* `iostream`：既能用于输入，又能用于输出的类
* `fstream`：既能从文件读取数据，又能向文件写入数据的类

**标准流对象**：

* `cin` 对应于标准输入流，用于从键盘读取数据，也可以被**重定向**为从文件中读取数据
* `cout` 对应于标准输出流，用于从屏幕输出数据，也可以被**重定向**为向文件写入数据
* `cerr` 对应于标准错误输出流，用于向屏幕输出出错信息

* `clog` 对应于标准错误输出流，用于向屏幕输出错误信息
* `cerr` 和 `clog` 的区别在于 `cerr` 不使用缓冲区，直接向显示器输出出错信息；而 `clog` 中的信息先会被存放到缓冲区，缓冲区满或者刷新时才输出到屏幕。

**istream 类的成员函数**：

* `istream & getline(char* buf, int bufSize);` ：从输入流中读取 `bufSize-1` 个字符到缓冲区 `buf` 或读到碰到 `\n` 为止
* `istream & getline(char* buf, int bufSize, char delim);` ：从输入流中读取 `bufSize-1` 个字符到缓冲区 `buf` 或读到碰到字符 `delim` 为止。如果一次读入的字符个数超过了 `bufSize-1` 不会影响本次读入，但是之后的读入都会失败。另外，可以用 `getline()` 的返回值判断输入是否结束 `if(!cin.getline())`。
* `bool eof();` 判断输入流是否结束
* `int peek();` 返回下一个字符，但不从输入流中去掉
* `istream & putback(char c);` 将字符 `c` 放回输入流
* `iostream & ignore(int nCount = 1, int delim = EOF);` 从流中删掉最多 `nCount` 个字符，遇到 EOF 时结束

**流操纵算子控制输出格式**：

```cpp
int main(){

    // 分别以十六进制、十进制、八进制先后输出 n
    int n = 141;
    cout << "1) " << hex << n << " ";
    cout << dec << n << " ";
    cout << oct << n <<endl;

    // 保留 5 位有效数字
    double x = 1234567.89, y = 12.34567;
    cout << "2) " << setprecision(5) << x << " " << y <<endl;

    // 保留小数点后 5 位 定点输出浮点数
    cout << "3) " << fixed << setprecision(5) << x << " " << y <<endl;

    // 科学计数法输出，且保留小数点后 5 位
    cout << "4) " << scientific << setprecision(5) << x << " " << y <<endl;

    // 非负数要显示正号，输出宽度为 12 字符， 宽度不足则用 * 号填补
    cout << "5) " << showpos << fixed << setw(12) << setfill('*') << 12.1 <<endl;

    // 非负数不显示正号，输出宽度为 12 字符， 左对齐 宽度不足则右边用填充字符填补
    cout << "6) " << noshowpos << setw(12) << left << 12.1 <<endl;

    // 输出宽度为 12 字符，右对齐 宽度不足则左边用填充字符填补
    cout << "7) " << setw(12) << right << 12.1 << endl;

    // 宽度不足时，符号和数值分列左右，中间用填充字符填补
    cout << "8) " << setw(12) << internal << -12.1 <<endl;
    cout << "9) " << 12.1 <<endl;

    return 0;
}
```

### 文件读写

#### 创建文件

​	调用头文件 `#include <fstream>`  中的函数`ofstream outFile("data.txt", ios::out|ios::binary);`  创建文件，其中第一个参数表示要创建的文件的名字 `data.txt`；`ios::out` 表示文件打开方式，`out` 表示输出内容到该文件，删除原有文件内容，`app` 表示输出内容到该文件，保留原有内容，从尾部追加；`ios::binary` 表示以二进制文件格式打开文件。

​	除了 直接创建  `ofstream`  对象 `outFile` 也可以先创建对象，再用 `open` 函数打开该文件，形如 `ofstream fout; fout.open("data.txt", ios::out|ios::binary)` 。判断文件是否打开可以直接使用被重载的 `!` 运算符，`if(!fout){}` 进行判断。

#### 文件的读写指针

​	文件的读写指针并不是真正意义上的指针，它用来表示文件操作的当前位置，该指针在那里，读写操作就在哪里进行。对于输入文件，有一个读指针；对于输出文件，有一个写指针；对于输入输出文件，有一个读写指针。

​	输出文件，写指针：`tellp()/seekp()`

```cpp
ofstream fout("test.out", ios::app); 
long location = fout.tellp(); // 获取写指针的位置
location = 10;  // location 可以为负值
fout.seekp(location); // 将写指针移动到第10个字节处
fout.seekp(location, ios::beg); // 从文件头开始移动location个字节
fout.seekp(location, ios::cur); // 从当前位置开始移动location个字节
fout.seekp(location, ios::end); // 从文件尾开始移动location个字节
```

​	输入文件，读指针：`tellg()/seekg()`

```cpp
ifstream fin("test.in", ios::ate); // 打开文件并将读指针定位到文件末尾 
long location = fin.tellg(); // 获取写指针的位置
location = 10;  // location 可以为负值
fin.seekg(location); // 将读指针移动到第10个字节处
fin.seekg(location, ios::beg); // 从文件头开始移动location个字节
fin.seekg(location, ios::cur); // 从当前位置开始移动location个字节
fin.seekg(location, ios::end); // 从文件尾开始移动location个字节
```

**字符文件读写**：实践示例 将文件 `in.txt` 里面的整数排序后，输出到 `out.txt`

```cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){

    vector<int> v;
    ifstream srcFile("in.txt", ios::in);
    ofstream destFile("out.txt", ios::out);
    int x;
    while (srcFile >> x)
    {
        v.push_back(x);
    }
    sort(v.begin(), v.end());
    for(int i=0; i< v.size(); i++){
        destFile << v[i] << " ";
    }
   destFile.close();
   srcFile.close();

    return 0;
}
```

#### 二进制文件读写

**二进制读文件**：

​	二进制读文件可以使用 `ifstream` 和 `fstream` 的成员函数 `istream& read(char* s, long n);`，`read` 函数的作用是将文件读指针指向的地方的 n 个字节内容，读入到内存地址 s，然后将文件读指针向后移动 n 个字节；如果文件使用 `ios::in` 的方式打开文件，文件的读指针开始指向文件开头。

**二进制写文件**：

​	二进制写文件可以使用 `ofstream` 和 `fstream` 的成员函数 `istream& write(const char* s, long n);`，`write` 函数的作用是将内存地址 s 处的 n 个字节内容，写入到文件中写指针指向的位置，然后将文件写指针向后移动 n 个字节；如果文件使用 `ios::out` 的方式打开文件，文件的写指针开始指向文件开头；`ios::app` 方式打开文件时，文件写指针最开始指向文件尾部。

```cpp
#include<iostream>
#include<fstream>
int main(){
    ofstream fout("data.dat", ios::out|ios::binary);
    int x=120;
    fout.write((const char *)(&x), sizeof(int));
    fout.close();
    ifstream fin("data.dat", ios::in|ios::binary);
    int y;
    fin.read((char *)(&y), sizeof(int));
    fin.close();
    cout << y << endl;
    return 0;
}
```

**文件读写实例-文件拷贝**：将 `ori.dat` 拷贝到 `dest.dat` ，如果目标文件存在就将其原始文件覆盖。

```cpp
#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char* argv[]){
	if(argc != 3){
        cout << "file name missing1" << endl;
        return 0;
    }
    // 读取二进制文件
    ifstream inFile(argv[1], ios::binary|ios::in);
    if(!inFile){
        cout << "Source file open error." << endl;
        return 0;
    }
	// 写入二进制文件
    ofstream outFile(argv[2], ios::binary|ios::out);
    if(!outFile){
        cout << "New file open error." << endl;
        inFile.close();
        return 0;
    }
    // 拷贝文件
    char c;
    while(inFile.get(c)){ // 每次从源文件读取一个字符
        outFile.put(c); // 每次写入一个字符到目标文件
    }
    outFile.close();
    inFile.close();
    return 0;
}
```

