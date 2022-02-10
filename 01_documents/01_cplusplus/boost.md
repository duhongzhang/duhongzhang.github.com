# boost

## 1. boost install

### 1.1. windows

- 下载源码
  - https://www.boost.org/
- 执行命令1
  - cd tools/build
  - ./bootstrap.bat
- 执行命令2
  - ./b2 --prefix={安装目的地} install
    - =前后不要加空格
### 1.2. linux
- yum安装
  - yum install -y boost{ver}-devel
- rpm安装
  - 下载所需rpm
  - rpm -ivh * #自动安装依赖顺序安装

## 2. ut test

### 2.1. 编码

```c++
//1. 定义主测试套件名字
#define BOOST_TEST_MODULE xxx

//2. 包含ut头文件
#include <boost/test/included/unit_test.hpp> //单header使用，不需要链接库
//#include <boost/test/unit_test.hpp> //需要链接库

//3. 待测试class头文件

//4. 测试部分（同一文件，可以定义多个测试套件）
BOOST_AUTO_TEST_SUITE (xxx)	//测试套件，开始 xxx->套件名

BOOST_AUTO_TEST_CASE (yyy)	//测试case yyy->用例名
{
    //5. 测试工具(宏)
}

BOOST_AUTO_TEST_SUITE ()	//测试套件，结束 

//5. 测试工具(宏)
BOOST_CHECK()	//判断()中bool值：断言失败，当前case会继续执行。
BOOST_REQUIRE()	//判断()中bool值：断言失败，当前case会中止执行。
```



