#include <iostream>

template<typename T>
class A
{
public:
	A()
	{
		std::cout << "A " << typeid(T).name() << std::endl;
	}
};

template <typename T>
using B = A<T>;

/**
* 1. typedef 不可以应用于模板，但是可以应用于特化后的模板。
* 2. 
*/
//template <typename T>
//typedef D = A<T>;

typedef A<int> C;

int main()
{
	A<int> a;
	B<int> b; // OK, B is an alias of class A.
	C<int> c; // Syntax Error, C cannot be recognized as a type.
	return 0;
}