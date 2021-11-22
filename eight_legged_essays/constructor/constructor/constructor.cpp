#include <iostream>

/**
* 1.default: 估计是以内存形式在最上层直接清空的[反汇编 构造之前有个清0动作]。
* 2.具体实现要看汇编（估计不同的编译器实现也不一样）才行，太费劲，先记最上层吧，变量被初始化。
*     VS编译器在进入下层构造之前，内存已经被初始化了，汇编有xorps       xmm0,xmm0。
* 3.()形式调用，初始化。
* https://stackoverflow.com/questions/13576055/how-is-default-different-from-for-default-constructor-and-destructor
* https://github.com/cplusplus/draft/blob/master/papers/n4659.pdf
*/
namespace condef {
    class Mii {
    public:
        Mii() {
            std::cout << "Mii() " << i << "," << j << std::endl;
        };
        int i;
        int j;
    };

    class Mi {
    public:
        Mi() = default;
        Mii ii;
        int i;
        int j;
    };

    class Mn {
    public:
        Mn() {
            std::cout << "Mn() " << i << "," << j << std::endl;
        };
        Mii ii;
        int i;
        int j;
    };

    class A {
    public:
        A() {
            std::cout << "A() " << i << "," << j << std::endl;
        }
        Mi mi;
        Mn mn;
        int i;
        int j;
    };

    class B {
    public:
        B() = default;
        Mi mi;
        Mn mn;
        int i;
        int j;
    };

    int test()
    {
        for (int i = 0; i < 1; ++i) {
            A* pa = new A();
            B* pb = new B();
            std::cout << "A(){      } " << pa->i << "," << pa->j << "," << pa->mi.i << "," << pa->mi.j << "," << pa->mn.i << "," << pa->mn.j << std::endl;
            std::cout << "B()=default " << pb->i << "," << pb->j << "," << pb->mi.i << "," << pb->mi.j << "," << pb->mn.i << "," << pb->mn.j << std::endl;
            delete pa;
            delete pb;
        }

        return 0;
    }
}

namespace kuohao {
#include <iostream>

    using namespace std;
    class A
    {
    public:
        int x;
        A() {}
    };

    class B
    {
    public:
        int x;
        B() = default;
    };


    int test()
    {
        int x = 5;
        new(&x)A(); // Call for empty constructor, which does nothing
        cout << x << endl;
        new(&x)B; // Call for default constructor
        cout << x << endl;
        new(&x)B(); // Call for default constructor + Value initialization
        cout << x << endl;
        return 0;
    }
}

int main() {
    condef::test();
    kuohao::test();

    return 0;
}