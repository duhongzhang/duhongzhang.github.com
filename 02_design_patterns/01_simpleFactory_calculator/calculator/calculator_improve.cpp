#include <iostream>
#include <exception>

/**
* 改良点：
* 1. 没有直接使用函数，使用的类【java就没有独立函数】。
* 2. 异常系处理，使用catch throw。
* 3. 活字印刷术，曹操变需求：
*    使用继承和多态(to复用，扩展)
*        开发原则：1.单一职责原则
*                  2.开闭原则
*        设计模式：
*				   1.工厂模式(to使用方便)
* 
* ? const引用参数，只能调用const方法？:
*		const对象，只能访问const函数，是一种重载形式。
*		const修饰的成员函数不能修改任何的成员变量，也不能调用非const函数，且只能被const对象修改调用。
* ? *ptr_cls = a 使用的是等号赋值，还是指针指向。
*		因为ptr_cls未赋值，所以行为未知
* ? 纯虚接口的~要为虚
*       不然无法析构多态对象
* ? 应对data变化，模板参数(所有使用的地方，哪怕作为参数使用，也要使用template声明)
*		对象方法的模板参数定义和类的模板参数定义相同，都是限定作用域。
*    )
*/
template<typename T>
class CalcData {
public:
	virtual T get() const = 0;
	virtual ~CalcData() = default;
};

template<typename T>
class CalcLeft : public CalcData<T> {
	T data;
public:
	CalcLeft(T data) : data(data) {};

	virtual T get() const override {
		return this->data;
	}
};

template<typename T>
class CalcRight : public CalcData<T> {
	T data;
public:
	CalcRight(T data) : data(data) {};
	virtual T get() const override {
		return this->data;
	}
};

template<typename T>
class CalcOperate {
public:
	virtual T calc(const CalcData<T>& operator_left, const CalcData<T>& operator_right) = 0;
	virtual ~CalcOperate() = default;
};

template<typename T>
class Plus : public CalcOperate<T> {
public:
	T calc(const CalcData<T>& operator_left, const CalcData<T>& operator_right) override {
		double result = 0;

		result = operator_left.get() + operator_right.get();

		return result;
	}
};

template<typename T>
class Minute : public CalcOperate<T> {
public:
	double calc(const CalcData<T>& operator_left, const CalcData<T>& operator_right) override {
		double result = 0;

		result = operator_left.get() - operator_right.get();

		return result;
	}
};

template<typename T>
class Multi : public CalcOperate<T> {
public:
	T calc(const CalcData<T>& operator_left, const CalcData<T>& operator_right) override {
		T result = 0;

		result = operator_left.get() * operator_right.get();

		return result;
	}
};

template<typename T>
class Divide : public CalcOperate<T> {
public:
	T calc(const CalcData<T>& operator_left, const CalcData<T>& operator_right) override {
		double result = 0;

		if (operator_left.get() > -0.000001 && operator_right.get() < 0.000001) {
			throw std::exception("除数为0.");
			//std::cout << "除数为0." << std::endl;
		}

		result = operator_left.get() / operator_right.get();

		return result;
	}
	Divide() { std::cout << "real C" << std::endl; }

	~Divide() { std::cout << "real ~" << std::endl; }
};

class Factory {
public:
	template<typename T>
	static CalcOperate<T>* createCalcOperate(std::string opreatorSign) {
		CalcOperate<T>* calcor = nullptr;

		switch (opreatorSign[0]) {
		case '+':
			calcor = new Plus<T>();
			break;
		case '-':
			calcor = new Minute<T>();
			break;
		case '*':
			calcor = new Multi<T>();
			break;
		case '/':
			calcor = new Divide<T>();
			break;
		default:
			throw std::exception("不支持的操作符.");
			break;
		}

		return calcor;
	}
};

int main_improve()
{
	using namespace std;
	double left, right;
	std::string opreator_sign;
	double result = 0;

	std::cout << "请按照此格式输出数据：数字1 空格 操作符 空格 数字2，例如: 1 + 2" << std::endl;

	while (cin >> left >> opreator_sign >> right) {

		try {
			std::unique_ptr<CalcOperate<double>> oper(Factory::createCalcOperate<double>(opreator_sign));
			CalcLeft<double> oleft(left);
			CalcRight<double> oright(right);

			result = oper->calc(oleft, oright);

			std::cout << "运算结果为：" << result << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	return 0;
}
