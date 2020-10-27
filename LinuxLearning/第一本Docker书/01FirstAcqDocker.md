### 初识Docker

#### Docker的特点

* **易构建**：提供一个简单、轻量的建模方式，不需要模拟层`(emulation layer)`和管理层`(hypervisor layer)`的额外开销。
* **职责分离**：类似前后端分离逻辑，开发人员关注容器中运行的程序，运维人员关注容器的管理。
* **高效性**：高效的开发生命周期，使用容器程序从开发、测试到部署、上线的周期将大大缩短。
* **容器互联**：可以面向微服务架构，一个容器运行一个应用程序或进程，服务由一系列互联的容器提供，实现分布式的应用程序部署。

#### Docker的组件

* **Docker客户端和服务器**`(C/S)`：客户端负责发送请求，服务器负责提供服务完成工作并返回结果；Docker架构由**多个客户端 + 一个守护进程 + 多个容器**组成。
* **Docker镜像`(image)`**：镜像是Docker创建容器的基础，它具有轻量、易分享、存储和更新等特点。
* **Docker容器`(container)`**：容器是基于镜像启动的，容器中可以运行一个或多个进程；镜像是Docker生命周期中的**构建**和**打包**阶段，而容器则是Docker生命周期中的**启动**和**执行**阶段。
* **Docker仓库`(registry/Docker Hub)`**：类似Github，Registry用来保存用户构建的镜像，分为共有和私有两种，是获取/保存各种镜像的远程仓库。

#### Docker镜像基础操作

* 搜索镜像命令`docker serach image_name`
  * `--filter`选项可以用来过滤搜索结果，例如`docker serach "is-official=true" image_name`过滤出仅为官方提供的镜像。
* 下载镜像命令`docker pull image_name`
* 查询镜像命令`docker images`
* 删除镜像命令`docker rmi image_name`

#### Docker容器基础操作

* 创建容器命令`docker run -i -t -d --name=container_name image_name`
  * `-i`:表示容器可交互，提供bash交互方式
  * `-d`:表示容器可后台运行
  * `-t`:表示为容器分配一个伪输入终端
* 查看容器命令`docker ps`：查看正在运行的容器；该命令类似`ls`命令，可以使用选项`-a`来查看所有状态的容器。
* 启动容器命令`docker start container_name/id`
* 停止容器命令`docker stop container_name/id`
* 重启容器命令`docker restart container_name/id`
* 删除容器命令`docker rm container_name/id`
* 进入容器命令`docker exec -it container_name/id /bim/bash`
* 退出容器命令`exit`

