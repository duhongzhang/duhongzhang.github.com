## docker command

## 0. 实践

- 后台运行容器
  - docker run -tid xxx ：
    - centos跑完没退出，hello-world跑完退出了
    - 如果TAG=latest可以省略，其他不可以[:TAG]
  - docker start xxx :
    -  centos跑起来了
- docker exec -ti xxx[不能是image名]  /bin/bash
  
  - 连接启动中的容器
- 使用`docker push`镜像时，出现`denied: requested access to the resource is denied`
  - docker login
  - image要以username开始：username/image:version
- 上传完整image
  
  - 先commit，再push。
- 构建boost环境
  - yum install -y vim iptables
  
  - yum install -y automake autoconf libtool git
  
  - yum install -y epel-release rpm-build cmake3
  
  - yum install -y gcc gcc-c++ gdb
  
  - yum install -y boost-devel
  
    - > automake autoconf生成config的工具，以便以make install方式安装软件
  
    - > libtool将lib依赖关系写入lib.la，不必更改LD_LIBARY_PATH
- 添加ll命令
  - vim ~/.bashrc
    - aslias ll='ls -l'
  - source ~/.bashrc

### 1. 启动

#### 1.1. run

- 重点，使用run image会返回，容器的id。
  - run的是类image，生成的是实例id。
  - start的是实例id。

**docker run ：**创建一个新的容器并运行一个命令

- ```shell
  $docker run [OPTIONS] IMAGE [COMMAND] [ARG...]
  ```

##### 1.1.1. **option**

- [ ] **-a stdin:** 指定标准输入输出内容类型，可选 STDIN/STDOUT/STDERR 三项；

- [x] **-d:** 后台运行容器，并返回容器ID；

- [x] **-i:** 以交互模式运行容器，通常与 -t 同时使用；

  - 阻塞交互式，exit或ctrl+d退出

- [ ] **-P:** 随机端口映射，容器内部端口**随机**映射到主机的端口

- [x] **-p:** 指定端口映射，格式为：主机(宿主)端口:容器端口 

  - [ ] 实例，访问nginx：docker run --name nginx-test -p 8888:80  -p 9999:80 -d nginx

- [x] **-t:** 为容器重新分配一个伪输入终端，通常与 -i 同时使用；

  - 类似ssh，切换到容器运行环境

- [x] **--name="nginx-lb":** 为容器指定一个名称；

- [ ] **--dns 8.8.8.8:** 指定容器使用的DNS服务器，默认和宿主一致；

- [ ] **--dns-search example.com:** 指定容器DNS搜索域名，默认和宿主一致；

- [ ] **-h "mars":** 指定容器的hostname；

- [ ] **-e username="ritchie":** 设置环境变量；

  - [ ] ```
    $ docker run -itd --name mysql-test -p 3306:3306 -e MYSQL_ROOT_PASSWORD=123456 mysql
    ```

- [ ] **--env-file=[]:** 从指定文件读入环境变量；

- [ ] **--cpuset="0-2" or --cpuset="0,1,2":** 绑定容器到指定CPU运行；

- [ ] **-m :**设置容器使用内存最大值；

- [ ] **--net="bridge":** 指定容器的网络连接类型，支持 bridge/host/none/container: 四种类型；

- [ ] **--link=[]:** 添加链接到另一个容器；

- [ ] **--expose=[]:** 开放一个端口或一组端口；

- [x] **--volume , -v:** 绑定一个卷，映射文件夹，主机(宿主)文件夹:容器文件夹 

### 2. 查看

#### 2.1. ps

- **docker ps :** 列出容器

```shell
#CONTAINER ID: 容器ID
#IMAGE: 使用的镜像
#COMMAND: 启动容器时运行的命令
#CREATED: 容器的创建时间
#PORTS: 容器的端口信息和使用的连接类型（tcp\udp）。
#NAMES: 自动分配的容器名称。
#STATUS: 容器状态
#7种状态： created（已创建） restarting（重启中） running（运行中） removing（迁移中） paused（暂停） exited（停止） dead（死亡）
[root@localhost ~]# docker ps
CONTAINER ID IMAGE  COMMAND  CREATED          STATUS          PORTS     NAMES
ebde105d0b72 ubuntu "bash"   30 minutes ago   Up 14 seconds             love1
```

```shell
docker ps [OPTIONS]
```

- [x] **-a :**显示所有的容器，包括未运行的。
- [ ] **-f :**根据条件过滤显示的内容。
  - docker ps --filter"name=test-nginx"
- [ ] **--format :**指定返回值的模板文件。
- [ ] **-l :**显示最近创建的容器。
- [ ] **-n :**列出最近创建的n个容器。
- [x] **--no-trunc :**不截断输出。
- [ ] **-q :**静默模式，只显示容器编号。
- [ ] **-s :**显示总的文件大小。

#### 2.2. top

```shell
$docker top [OPTIONS] CONTAINER [ps OPTIONS]
```

- 容器运行时不一定有/bin/bash终端来交互执行top命令
- 容器不一定有top命令，可以使用docker top来实现查看container中正在运行的进程。

### 3. 启停重启

**docker start** :启动一个或多个已经被停止的容器

**docker stop** :停止一个运行中的容器

**docker restart** :重启容器

```shell
#CONTAINER也可以是name
$docker start [OPTIONS] CONTAINER [CONTAINER...]
$docker stop [OPTIONS] CONTAINER [CONTAINER...]
$docker restart [OPTIONS] CONTAINER [CONTAINER...]
```

### 4. 连接容器

**docker attach :**连接到正在运行中的容器。

```
$docker attach [OPTIONS] CONTAINER
```

- --sig-proxy=false来确保CTRL-D或CTRL-C不会关闭容器

**docker exec ：**在运行的容器中执行命令

```
$docker exec [OPTIONS] CONTAINER COMMAND [ARG...]
```

- [ ] **-d :**分离模式: 在后台运行

- [x] **-i :**即使没有附加也保持STDIN 打开

- [x] **-t :**分配一个伪终端

```
docker exec -it mynginx /bin/sh
```

### 5. 拷贝数据

```shell
#从源 -> 目的
docker cp [OPTIONS] SRC_PATH CONTAINER:DEST_PATH
docker cp [OPTIONS] CONTAINER:SRC_PATH DEST_PATH
```

### 6.检查容器变化

```shell
#查看容器变化
docker diff [OPTIONS] CONTAINER
```

### 7.仓库操作

- **OFFICIAL**：官方
- **verify**：认证

#### 7.1. login/logout

- **docker login/logout** 命令

```shell
#默认server为hub.docker.com
$docker login [OPTIONS] [SERVER]
$docker logout [OPTIONS] [SERVER]
```

```shell
#登录hub.docker.com
$docker login -u 用户名 -p 密码
#登出hub.docker.com
$docker logout
```

#### 7.2. pull

- **docker pull :** 从镜像仓库中拉取或者更新指定镜像

```shell
$docker pull [OPTIONS] NAME[:TAG|@DIGEST]
```

**-a :**拉取所有 tagged 镜像

**--disable-content-trust :**忽略镜像的校验,默认开启

**无参**：拉取最新

#### 7.3. push

- **docker push :** 将本地的镜像上传到镜像仓库,要先登陆到镜像仓库

```shell
$docker push [OPTIONS] NAME[:TAG]
#上传本地镜像myapache:v1到镜像仓库中。
docker push myapache:v1
```

**--disable-content-trust :**忽略镜像的校验,默认开启

#### 7.4. search

- **docker search :** 从Docker Hub查找镜像

```shell
$docker search [OPTIONS] TERM
```

- **--automated :**只列出 automated build类型的镜像；
- **--no-trunc :**显示完整的镜像描述；
- **-f <过滤条件>:**列出收藏数不小于指定值的镜像。

#### 7.5. commit

- **docker commit**：保存本地镜像变化

  ```
  $docker commit [option] id new-image-name[:tag]
  ```

- -m : 添加说明信息
- -a : 添加作者信息

### 8. 查看容器元数据

- **docker inspect :** 获取容器/镜像的元数据。inspect(检查，查看，观察)

```
docker inspect [OPTIONS] NAME|ID [NAME|ID...]
```

- [ ] **-f :**指定返回值的模板文件

- [ ] **-s :**显示总的文件大小

- [ ] **--type :**为指定类型返回JSON

### 9. 修改容器别名

```php
docker rename 镜像ID <new_container>       //修改容器别名
```

- 同run时，--name，可以替代container-id使用。

### 10. 修改镜像名

```shell
$docker tag SOURCE_IMAGE[:TAG] TARGET_IMAGE[:TAG]
```

- 给image起别名