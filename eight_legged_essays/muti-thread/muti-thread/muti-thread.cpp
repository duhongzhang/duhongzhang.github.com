#include <iostream>
#include <thread>
#include <array>

using namespace std;
/**
* 1. 传递参数(可变参，run的)的方式不对：“invoke”: 未找到匹配的重载函数
*   1.1. 普通函数：      函数名，参数列表
*   1.1. 类的成员函数：  &类名::函数名（固定形式），this（调用成员函数的对象），参数列表(如是引用，需要转义，加ref())
*   1.2. lamda表达式：   如果需要具名的话，需要使用functionnal或者函数指针定义，auto不行；lambda调用()[]{}();
*   1.3. 仿函数：        类名(), 相当于类对象  => CL cl => 调用方式1：CL()//匿名对象？不用加括号  2：cl(此处用法与普通函数同) //普通对象，区别于成员函数
*   1.4  智能指针：      move(unique)，做参数;shared_ptr不需要，但是shared_ptr引用不增加计数。
*
*/

namespace class_member_function {
    class thread_wrapper {
        thread t;
        int id;
    public:
        thread_wrapper(int& id): id(id), t(std::thread(&thread_wrapper::run, this, ref(id))) {
            cout << "thread_wrapper(" << id << ")" << ",硬件支持的并发线程数=" << t.hardware_concurrency() << " , &id=" << &id << endl;
            if (id % 2) t.detach();
        }

        void run(int& id);

        ~thread_wrapper() {
            if(t.joinable()) t.join();
            cout << "~thread_wrapper(" << id << ")" << endl;
        }
    };

    void thread_wrapper::run(int& id) {
        cout << "thread start[" << id << "] " << this_thread::get_id() << " , &id=" << &id << endl;
        this_thread::sleep_for(chrono::seconds(id));
    }
}

namespace class_function {
    struct run {
        void operator()(int& id);
    };

    void run::operator()(int& id){
        cout << "thread start[" << id << "] " << this_thread::get_id() << " , &id=" << &id << endl;
        this_thread::sleep_for(chrono::seconds(id));
    }

    class thread_wrapper {
        thread t;
        int id;
    public:
        thread_wrapper(int& id) : id(id), t(std::thread(
            [](int& id) {cout << "thread start[" << id << "] " << this_thread::get_id() << " , &id=" << &id << endl;
            this_thread::sleep_for(chrono::seconds(id)); }
            , ref(id))) {
            cout << "thread_wrapper(" << id << ")" << ",硬件支持的并发线程数=" << t.hardware_concurrency() << " , &id=" << &id << endl;
            if (id % 2) t.detach();
        }

        ~thread_wrapper() {
            if (t.joinable()) t.join();
            cout << "~thread_wrapper(" << id << ")" << endl;
        }
    };
}

namespace lambda_function {
    struct run {
        void operator()(int& id);
    };

    void run::operator()(int& id) {
        cout << "thread start[" << id << "] " << this_thread::get_id() << " , &id=" << &id << endl;
        this_thread::sleep_for(chrono::seconds(id));
    }

    class thread_wrapper {
        thread t;
        int id;
    public:
        thread_wrapper(int& id) : id(id), t(std::thread(run(), ref(id))) {
            cout << "thread_wrapper(" << id << ")" << ",硬件支持的并发线程数=" << t.hardware_concurrency() << " , &id=" << &id << endl;
            if (id % 2) t.detach();
        }

        ~thread_wrapper() {
            if (t.joinable()) t.join();
            cout << "~thread_wrapper(" << id << ")" << endl;
        }
    };
}

namespace uniptr_arg {
    struct run {
        void operator()(unique_ptr<int> id);
    };

    void run::operator()(unique_ptr<int> id) {
        cout << "thread start[" << *id << "] " << this_thread::get_id() << " , &id=" << id.get() << endl;
        this_thread::sleep_for(chrono::seconds(*id));
    }

    class thread_wrapper {
        int id;
        thread t;
    public:
        thread_wrapper(unique_ptr<int> id) :
            id(*id), 
            t(std::thread(run(), move(id))) {
            cout << "thread_wrapper(" << id << ")" << ",硬件支持的并发线程数=" << t.hardware_concurrency() << " , &id=" << id.get() << endl;
            //if (this->id % 2) t.detach();
        }

        ~thread_wrapper() {
            if (t.joinable()) t.join();
            cout << "~thread_wrapper(" << id << ")" << endl;
        }
    };
}

namespace shrptr_arg {
    struct run {
        void operator()(shared_ptr<int> id);
    };

    void run::operator()(shared_ptr<int> id) {
        cout << "thread start[" << *id << "] " << this_thread::get_id() << " , &id=" << id.get() << " , count=" << id.use_count() << endl;
        this_thread::sleep_for(chrono::seconds(*id));
    }

    class thread_wrapper {
        shared_ptr<int> id;
        thread t;
    public:
        thread_wrapper(shared_ptr<int> id) :
            id(id),
            t(std::thread(run(), id)) {
            cout << "thread_wrapper(" << *id << ")" << ",硬件支持的并发线程数=" << t.hardware_concurrency() << " , &id=" << id.get() << " , count=" << id.use_count() << endl;
            //if (this->id % 2) t.detach();
        }

        ~thread_wrapper() {
            if (t.joinable()) t.join();
            cout << "~thread_wrapper(" << *id << ")" << " , count=" << id.use_count() << endl;
        }
    };
}

namespace shrptr_inyong_arg {
    struct run {
        void operator()(shared_ptr<int>& id);
    };

    void run::operator()(shared_ptr<int>& id) {
        cout << "thread start[" << *id << "] " << this_thread::get_id() << " , &id=" << id.get() << " , count=" << id.use_count() << endl;
        this_thread::sleep_for(chrono::seconds(*id));
    }

    class thread_wrapper {
        shared_ptr<int> &id;
        thread t;
    public:
        thread_wrapper(shared_ptr<int>& id) :
            id(id),
            t(std::thread(run(), ref(id))) {
            cout << "thread_wrapper(" << *id << ")" << ",硬件支持的并发线程数=" << t.hardware_concurrency() << " , &id=" << id.get() << " , count=" << id.use_count() << endl;
            //if (this->id % 2) t.detach();
        }

        ~thread_wrapper() {
            if (t.joinable()) t.join();
            cout << "~thread_wrapper(" << *id << ")" << " , count=" << id.use_count() << endl;
        }
    };
}

int main()
{
    cout << "main thread start " << this_thread::get_id() << endl;

    array<int, 11> arr = { 0,1,2,3,4,5,6,7,8,9,10 };

    cout << "================================================类的成员函数================================================" << endl;
    class_member_function::thread_wrapper tw1(arr[1]);
    class_member_function::thread_wrapper tw2(arr[2]);
    
    cout << "================================================仿函数================================================" << endl;
    class_function::thread_wrapper tw3(arr[3]);
    class_function::thread_wrapper tw4(arr[4]);
    
    cout << "================================================lamda表达式================================================" << endl;
    lambda_function::thread_wrapper tw5(arr[5]);
    lambda_function::thread_wrapper tw6(arr[6]);

    for (auto const& i : arr) {
        cout << i << " , ";
    }
    cout << endl;

    cout << "================================================unique_ptr做参数================================================" << endl;
    unique_ptr<int> p7(new int(7));
    uniptr_arg::thread_wrapper tw7(move(p7));
    unique_ptr<int> p8(new int(8));
    uniptr_arg::thread_wrapper tw8(move(p8));

    cout << "================================================shared_ptr做参数================================================" << endl;
    shared_ptr<int> p9(new int(9));
    shrptr_arg::thread_wrapper tw9(p9);
    p9.reset();
    shared_ptr<int> p10(new int(10));
    shrptr_arg::thread_wrapper tw10(move(p10));

    cout << "================================================shared_ptr引用做参数================================================" << endl;
    shared_ptr<int> p11(new int(11));
    shrptr_inyong_arg::thread_wrapper tw11(p11);

    //使用引用，导致程序崩溃，因为计数不增加。
    shared_ptr<int> p12(new int(12));
    shrptr_inyong_arg::thread_wrapper tw12(p12);
    p12.reset();

    return 0;
}
