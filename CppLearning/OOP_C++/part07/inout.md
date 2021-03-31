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