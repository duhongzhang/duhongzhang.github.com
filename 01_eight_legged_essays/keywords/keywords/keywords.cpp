#include <iostream>

/**
*   符合doxgen规则
    1. explict： 说明单个需要赋值的构造函数，声明处单独使用，不可以在定义处使用。
    2. default： 声明，放在末尾，不可以在定义处使用，普通函数也可以使用。
    3. const:    声明+定义，{明示不改变成员} 仿函数后的const指明了这个函数【不会修改该类的任何成员数据的值】，称为常量成员函数。
                 const类型参数，和函数const声明都能实现重载。
                 const类，只能调用const方法；
                 非const类，在没有非const方法时，会调用const方法，有时，则调用非const方法。
    4. static:   声明，{不传this提高效率} 未使用类的成员变量，在类的声明处使用。
                 static函数不能声明为const类型。
*/
namespace keywords {
    void normal_function(std::string name, int age = 18) {

    }

    class Demo11 {
    public:
        explicit Demo11(int a);
    };
    //explicit Demo11::Demo11(int a){}
    Demo11::Demo11(int a) {}

    class Demo12 {
    public:
        Demo12(int a);
    };
    //explicit Demo12::Demo12(int a){}
    Demo12::Demo12(int a) {}


    class Demo21 {
    public:
        explicit Demo21(int a, double b = 2.0);
    };
    //explicit Demo21::Demo21(int a, double b = 2.0) {}
    Demo21::Demo21(int a, double b) {}
    class Demo22 {
    public:
        Demo22(int a, double b = 2.0);
    };
    //explicit Demo22::Demo22(int a, double b = 2.0) {}
    Demo22::Demo22(int a, double b) {}

    class constCls {
    public:
        //void print() {
        //    std::cout << "this is print()." << std::endl;
        //}

        void print() const {
            std::cout << "this is print() const." << std::endl;
        }
    };

    void test() {
        //Demo1 demo1 = 5;
        Demo11 demo11(5);
        Demo12 demo12 = 5;

        Demo21 demo21(5);
        Demo22 demo22 = 5;

        normal_function("");

        constCls con1;
        const constCls con2;
        con1.print();
        con2.print();
    }
}

/**
    1. weak_ptr的lock，指向计数
*/
namespace smartptr {
    void observe(std::weak_ptr<int> weak)
    {
        if (auto observe = weak.lock()) {
            std::cout << "\tobserve() able to lock weak_ptr<>, value=" << *observe << "\n";
        }
        else {
            std::cout << "\tobserve() unable to lock weak_ptr<>\n";
        }
    }

    template<class T>
    void test() {
        std::shared_ptr<T> sp = std::make_shared<T>();
        std::weak_ptr<T> wp = sp;
        std::cout << "sp.use_count() = " << sp.use_count() << "\n";
        std::cout << "wp.use_count() = " << wp.lock().use_count() << "\n";

        wp.reset();
    }
}
/**
    1. ""和匿名string不能用来初始化引用，包括参数位置。
    2. ""可以隐式转换为const引用
*/
namespace reference {
    class String {
        std::string str;
    public:
        String(char* chs) { std::cout << "char *" << std::endl; str = chs; }
        String(std::string& _str) { std::cout << "refer &" << std::endl; str = _str; }
        String(const std::string& _str) { std::cout << "const refer &" << std::endl; str = _str; }
    };

    void test() {
        const char* p = "123";
        String str(const_cast<char*>(p));
        String str1(std::string("123"));
        String str2("123");
        String str3(str);
    }
}

int main()
{
    reference::test();

    smartptr::test<int>();

    keywords::test();

    return 0;
}
