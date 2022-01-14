#include <iostream>

using namespace std;
/*
　　一、只能用于良性转换，这样的转换风险较低，一般不会发生什么意外，例如：

    1. 原有的自动类型转换，例如 short 转 int、int 转 double、向上转型等；
    2. void 指针和具体类型指针之间的转换，例如void *转int *、char *转void *等；
    3. 有转换构造函数或者类型转换函数的类与其它类型之间的转换。

　　二、需要注意的是，static_cast 不能用于无关类型之间的转换，因为这些转换都是有风险的，例如：

    1. 两个具体类型指针之间的转换，例如int *转double *、Student *转int *等。
    2. int 和指针之间的转换。将一个具体的地址赋值给指针变量是非常危险的，因为该地址上的内存可能没有分配，也可能没有读写权限，恰好是可用内存反而是小概率事件。

　　三、static_cast 也不能用来去掉表达式的 const 修饰和 volatile 修饰。换句话说，不能将 const/volatile 类型转换为非 const/volatile 类型。
　　四、static_cast 是“静态转换”的意思，也就是在编译期间转换，转换失败的话会抛出一个编译错误。
*/
namespace staticc {
    struct A {
        int a;
        int b;
    };
    struct B {
        int a;
        int b;
    };
    
    void test() {
        A a = { 1, 2 };
        //1. 不能进行类类型的转换
        //B* b = static_cast<B*>(&a);

        unsigned char b = 1;
        unsigned char c;
        short d = 0x0303;
        c = static_cast<unsigned char>(d);
        cout << b << "," << c << "," << d << endl;
    }
}

/*
    reinterpret 是“重新解释”的意思，顾名思义，reinterpret_cast 这种转换仅仅是对二进制位的重新解释，不会借助已有的转换规则对数据进行调整，非常简单粗暴，所以风险很高。
　　reinterpret_cast 可以认为是 static_cast 的一种补充，一些 static_cast 不能完成的转换，就可以用 reinterpret_cast 来完成，
    例如两个具体类型指针之间的转换、int 和指针之间的转换(有些编译器只允许 　　int 转指针,不允许反过来)。
    在使用reinterpret_cast强制转换过程仅仅只是比特位的拷贝。

    1. 将A*转换为int*，使用指针直接访问 private 成员刺穿了一个类的封装性
    2. 用途：
        改变指针或引用的类型
        将指针或引用转换为一个足够长度的整形
        将整型转换为指针或引用类型
*/
namespace reinterpretc {
    struct A {
        int a;
        int b;
    };
    struct B {
        int a;
        int b;
    };

    void test() {
        A a = { 1, 2 };
        //1. 可以进行结构体类型的转换
        B* b = reinterpret_cast<B*>(&a);
        cout << a.a << a.b << endl;

        unsigned char c = 1;
        unsigned char d;
        short e = 0x0303;
        d = reinterpret_cast<unsigned char>(&e);
        //d = reinterpret_cast<unsigned char>(e);
        //cout << c << "," << d << "," << e << endl;
    }
}

int main()
{
    staticc::test();


    return 0;
}