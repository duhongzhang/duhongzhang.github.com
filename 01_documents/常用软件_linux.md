# 工作软件

## 1. docker

### 1.1. 概念

- [参考](https://www.w3cschool.cn/docker/docker-architecture.html)

- 一个application形式的小型的linux运行环境，可以将开发环境【db，lib，工具链】打包在一起，从而屏蔽环境安装作业，在linux上下载使用，实现即下即用【**体积小/统一线上线下**】。

- > Docker 是世界领先的软件容器平台。**开发人员使用 Docker 来消除与同事的代码协作时 “我机器上可以工作” 的问题**。运营商使用 Docker 在独立的容器中并行运行和管理应用程序，以获得更好的计算密度。企业使用 Docker 构建灵活的软件传送管道，可以更快，更安全地运行新功能，并且对于 Linux 和 Windows Server 应用程序都可适配。

- > Docker **自动执行设置和配置开发环境**的重复任务，以便开发人员可以专注于重要的事情：构建出优秀的软件。

- > Docker 我们可以专注于代码的编写, 忽略其他软件复杂的安装, 配置. 同时可以**统一线上, 线下环境, 不受服务版本差异的影响**。

- 实际应用中，还可以一机多配，一台物理主机，搭建多份docker环境。

- docker使用api，将远程仓库中的镜像，安装到本地主机。

### 1.2. [安装](https://docs.docker.com/)

- centos8安装docker错误：
  - 因为安装了podman-docker
  - 使用yum erase podman buildah
- 安装：
  - yum install -y yum-utils device-mapper-persistent-data lvm2
  - sudo yum-config-manager --add-repo http://mirrors.aliyun.com/docker-ce/linux/centos/docker-ce.repo
  - yum install -y docker-ce（社区版）
- 配置：
  - 启动 systemctl start docker
  - 开机启动 systemctl enable docker
- 验证
  - docker run hello-world
- 默认安装文件及镜像下载位置（卸载后删除）
  - /var/lib/docker

### 1.3. [使用](../03_tools/02_docker/docker_cmd.md)

## 2. Jenkins

### 2.1. 概念

- [参考](https://www.w3cschool.cn/jenkins/jenkins-5h3228n2.html)

- 自动化部署环境，编译，发布代码。

- > Jenkins是一个独立的开源**自动化服务器**，可用于自动化各种任务，如**构建，测试和部署软件**。Jenkins可以通过本机系统包**Docker安装**，甚至可以通过安装Java Runtime Environment的**任何机器独立运行**。

### 2.2. 安装

- [centos](http://mirrors.jenkins-ci.org/redhat/)
- yum install jenkins超时，使用阿里源：
  - wget -O /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-8.repo
  - 查看源：yum repolist
- 访问：
  - localhost:8080
  - 外部访问，需要开启8080端口：
    - 关闭firewalld
    - firewall-cmd --query-port 8080
    - firewall-cmd --add-port  8080 --per    =>  firewall-cmd --reload

### 2.3. 使用

#### 2.3.1. pipeline

- [pipeline](../03_tools/03_jenkins/pipeline/pipeline.md)（流水线）：集成CI和发布CD的插件套装，通过生成Jenkinsfile实现。

- 报错：Invalid agent type "docker" specified. Must be one of [any, label, none]

  - [解决](https://segmentfault.com/a/1190000023275456?utm_source=tag-newest)：安装docker plugins和docker pipeline

- 报错：Got permission denied while trying to connect to the Docker daemon socket at unix:///var/run/docker.sock: Get "http://%2Fvar%2Frun%2Fdocker.sock/v1.24/containers/python:3.5.1/json": dial unix /var/run/docker.sock: connect: permission denied

  - [解决](https://blog.csdn.net/qq_26878363/article/details/110479644)  chmod 777 /var/run/docker.sock

- 报错：Caused: org.kohsuke.github.HttpException: Server returned HTTP response code: -1, message: 'null' for URL: https://api.github.com/rate_limit
  - 解决 安装github plugins
    - [GitHub Authentication plugin](https://plugins.jenkins.io/github-oauth)
    - [GitHub Integration Plugin](https://plugins.jenkins.io/github-pullrequest)
    - [GitHub Pipeline for Blue Ocean](https://plugins.jenkins.io/blueocean-github-pipeline)
    - [Pipeline: GitHub Groovy Libraries](https://plugins.jenkins.io/pipeline-github-lib)
    - [GitHub API Plugin](https://plugins.jenkins.io/github-api)
    - [GitHub plugin](https://plugins.jenkins.io/github)
    - [Pipeline: GitHub Groovy Libraries](https://plugins.jenkins.io/pipeline-github-lib)

  

## 3. wmware

### 3.1. 网络连接

- 桥接(Bridge)
  - 为客户机操作系统提供**直接访问外部以太网络**的权限，客户机在外部网络上**必须有自己的IP地址**。
- 网络地址转换(NAT)<default>
  - 为客户机操作系统提供**使用主机IP地址**访问主机拨号连接或外部**以太网络连接**的权限。
- 仅使用主机模式(HostOnly)
  - 将客户机操作系统连接到主机上的专用**虚拟网络**。

## 3. yum

- [参考](https://blog.51cto.com/xiaocao13140/2105528)

### 3.1. repo

> repo文件是Fedora中**yum源（软件仓库）的配置文件**，通常一个repo文件定义了一个或者多个软件仓库的细节内容，例如我们将从**哪里下载**需要安装或者升级的软件包，repo文件中的设置内容将**被yum读取和应用**！

### 3.2. **epel**


> 如果既想获得 **RHEL(redhat enterprise linux)** 的高质量、高性能、高可靠性，又需要方便易用(关键是免费)的软件包更新功能，那么 Fedora Project 推出的 EPEL(Extra Packages for Enterprise Linux)正好适合你。EPEL是由 Fedora 社区打造，为 RHEL 及衍生发行版如 CentOS、Scientific Linux 等提供高质量软件包的项目。

### 3.3. 命令

- 安装
  -  install

- 卸载
  - remove/erase
- 列出版本
  - list xx --showduplicates(可以tab联想输入)
- 列出依赖
  - deplist xx

## 4. firewalld

### 4.1. 概念

- 维护内外通信的**端口**oc状态和**转发**规则。

### 4.2. 应用

- firewalld-cmd 
- 参数 --add/--remove/--query，输入部分，即可查看所有命令的list
- --perment 保存
- --reload生效保存值

## 5. vim

### 5.1. 快捷键

- 跳到指定行
  - ESC退出编辑模式
    - 行号 gg/G
    - ：行号
- 设定tab
  - ：set tabstop=4
- 显示行号
  - ：set nu
- 缩进
  - ESC退出编辑模式
  - `<<` 向左
  - `>>` 向右
  - `==` 自动
  - v选择多行
- 多行注释
  - ESC退出编辑模式
  - `ctrl+v`，进入列模式
  - 添加注释：`I` -> `//`  -> ESC生效
  - 删除注释：d

- 撤回上步操作
  - u

### 5.2. 本地设置

- 在**配置文件**中添加：
  - /etc/vimrc 或 /etc/vim/vimrc

```shell
"self defined settings
"1. set linenumber
set number
"2. mark editting line
set cursorline
"3. light the syntax
syntax on
"4. bottom show cmd/insert mode
set showmode
"5. show the input command
set showcmd
"6. show mouse
set mouse=a
"7. charset utf-8
set encoding=utf-8
"8. 256bits colors
set t_Co=256
"9. set tab match the languages
filetype indent on
"10. auto add tab in new lines
set autoindent
"11. tab = 4 spaces
set tabstop=4
"12. << = >> 's spaces step
set shiftwidth=4
"13. tab to spaces
set expandtab
"14. tab to spaces
set softtabstop=4
"15. show the state bar
set laststatus=2
"16. show the cousor's position
set ruler
"17. {} () [] match lights
set showmatch
"18. lights the search result
set hlsearch
"19. show search result
set incsearch
"20. save undo opration in files
set undofile
```

## 6. cmake

### 6.1. CMakeLists.txt（大小写如此）

```cmake
## 1. 三要素
 #VERSION大写
 #3.x x必须
cmake_minimum_required(VERSION 3.0)
project(projectName)
add_executable(exeName xx.cpp)

## 2. 指定编译器
set(CMAKE_CXX_STANDARD 11)

## 3. 指定CPack(大小写如此)
set(CPACK_GENERATOR "RPM")
include(CPack)
```

