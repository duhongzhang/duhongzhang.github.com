## C++

### 1. UML

#### 1.1. 类间关系

[图像](../astah/class_uml.asta)

- **泛化(generalization)**：

  - 直线 空心箭头（继承）

- **实现(realization)**：

  - `虚线 空心箭头`（接口）

  

- **依赖(dependency)**：	   `弱依赖`

  - 虚线 ~~虚~~**实**箭头（参数，静态方法）



- **关联~~合~~(association)**：	`强依赖`
  - `直线` **直**`箭头`（有影响关系）	
- **聚合(aggregation)**：      `强关联`
  - **空菱形** ~~虚~~**直线 直箭头**（多个对象的集合，非同生命周期）
- **组合(composition)**：     `强聚合`
  - **实菱形** **直线** ~~虚~~**箭头**（完全归属，同生命周期）

#### 1.2. 特性

- 斜体类名 抽象类

- property 属性

- operation 方法

### 2. 八股文

#### 2.1. STL

##### 2.1.1. 项目中使用容器的实例：

- 将IP包进行拼接<data design>：
  - 外层：map<iphdr~~_udphdr~~，set，sort(){id_**src**}>
  - 内层：set<ip_package，sort(){ip.offset}>
- [实例](../eight_legged_essays/ip_assembly/ip_assembly.sln)：
  - **第二次**看，发现**第一次**有和源码理解不同的地方~~A~~ **B**。

#### 2.2. pair

- pair不接受构造型参数，c++17以下不能推导<>
- make_pair，可以自动推导<>

#### 2.3. struct：bool&仿函数

- opreator bool()
  - bool值，对象变量var(包括引用)或*ptr形式。
- bool opreator()(xxx)
  - 仿函数，bool operator()(xxx){} ：
    - 普通对象使用
  - 仿函数，bool operator()(xxx) const {} ：
    - const对象使用（声明&定义双+），inline，override：声明自己加。
    - 仿函数作为sort传递，调用的时候，会掉**默认构造**，如果构造重载要搞default。

#### 2.4. 错误、警告

- namespace内没有cout：
  - cout错误的放到了函数外，namespace中。

#### 2.5. constructor = default

- construct = default
  - 会初始化成员（ex. int -> 0）。
    - 调用的时候，必须带()
    - [实例](../eight_legged_essays/ip_assembly/constructor.sln)

#### 2.6. thread

- [创建](../eight_legged_essays/muti-thread/muti-thread.sln)
  - 传函数的方式：
    - 仿函数
    - 类成员
    - lambda
  - 传参数注意点
    - ref -> 变引用
    - unique_ptr的move和shared_ptr不可传引用