## 基本LINUX命令

### 命令分类

* 文件目录类命令
* 进程控制类命令
* 用户和权限管理类命令

### 文件目录类命令

**浏览目录命令**

* `ls`：list 显示目录文件
* `pwd`：print working directory 显示当前所在的工作目录

**目录操作命令**

* `cd`：change directory 切换目录
* `mkdir`：make directory 创建新目录
* `rmdir`：remove directory 删除空目录

**浏览文件命令**

* `cat`：concatenate and display files 链接文件并打印到标准输出设备上
* `more/less`：分页显示文件内容，使用space和enter换页换行
* `head/tail`：显示文件前几行的内容；显示文件后几行的内容（多用于日志文件）

**文件操作命令**

* `cp`：copy 将文件从一处复制到另一处 `cp param orpath depath`
* `rm`：remove 删除文件或目录
* `find`：寻找文件或目录
* `grep`：在文件中搜索匹配的字符并输出 `grep param deString depath`
* `tar`：tape archive 打包文件和压缩解压文件

### 进程控制类命令

**查看进程命令**

* `ps`：显示系统响应命令时的用户的进程信息
* `top`：动态监视系统任务的工具，相当于任务管理器

**控制进程命令**

* `kill`：向某个进程传送一个信号 `kill -signal PID`
* `killall`：使用进程的名称来杀死进程，区别于`kill`使用`ps`查看进程在使用`grep`查找进程过程
* `nice`：改变进程的优先级，使得系统分配资源更加公平
* `renice`：改变一个正在运行进程的优先级（nice值）

**进程的挂起和恢复**

* `Ctrl+Z`：挂起进程
* `jobs`：查看被挂起的进程列表
* `fg/bg`：将挂起进程恢复到前台/后台继续运行
* `Ctrl+C`：终止进程

### 用户和权限管理类命令

**用户管理命令**

* `useradd`：新建用户账号
* `passwd`：设置或修改用户的口令和口令属性
* `usermod`：user modify 修改用户的属性
* `userdel`：user delete 删除指定用户账号
* `su`：切换用户身份 exit退出超级用户

**用户组管理命令**

* `groupadd`：添加用户组
* `groupmod`：修改用户组属性
* `groupdel`：删除指定用户组

**文件权限命令**

* 权限：读取r、写入w、执行x
* `chmod`：修改文件的访问权限
* `chown`：change owner 改变文件所属的用户