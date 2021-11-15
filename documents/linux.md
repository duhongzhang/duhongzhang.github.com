# 概念收纳

### 0. 命令

- ps - report a snapshot of the current processes
  - 

## 1. 进程

- 僵尸，孤儿进程都涉及到父子关系：linux的子进程是由父进程来创建和管理的，所以涉及到:
  - 丢失 -> 僵尸
  - 托管 -> 孤儿

### 僵尸进程<defunct>

1. 子进程先退出，父进程没有收尸(wait/waitpid)，资源被释放(虚拟内存、文件描述符)，但是PCB中残留了进程信息(`父进程获取后进行善后`)，占用了有限的进程数量；
    直到父进程退出，子进程由init收尸(`init进程在循环wait`)。

    *除init外的所有进程退出exit后，都会留下一个僵尸进程，等待父进程处理*
    
    杀死父进程，即可快速处理僵尸进程。
    
2. 收尸方式：
```c
//1. 注册子进程结束信号处理函数
signal(SIGCHLD);

//2.1. [信号处理函数内]收尸函数，阻塞形式，多子进程同时退出时，可能会导致部分进程未被收尸处理。
pid=wait(&status)

//2.2. [信号处理函数内]收尸函数，可以不阻塞(opt=WNOHANG)，接收所有子进程-1.
while ((pid=waitpid(-1, &status, WNOHANG)) > 0)

//2.x. 获取进程退出状态信息的宏函数：man waitpid进行查询
```

- 父进程先退出，确保init收尸。

### 孤儿进程<ppid init>

1. 父进程先退出，子进程变成孤儿进程，被init进程收养，即父进程变为init进程。

### 守护进程

- [参考](https://blog.csdn.net/mijichui2153/article/details/81394387)

1. 守护进程是**后台运行的**、**系统启动时**就存在的、**不与任何终端**关联的，用于处理一些系统级别任务的**特殊进程**。
2. 实现一个守护进程，其实就是将普通进程按照上述特性改造为守护进程的过程。
3. 

## 2. 同步异步

### 1. 进程：

- 互相阻塞，互相等待？
- 父进程和子进程是异步的，所以不知道其什么时候结束？