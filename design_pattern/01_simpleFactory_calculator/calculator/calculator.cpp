#include <iostream>
#include <exception>

/**
* 改良点：
* 1. 没有直接使用函数，使用的类【java就没有独立函数】。
* 2. 异常系处理，使用catch throw。
* 3. 活字印刷术，曹操变需求：
*    使用继承和多态：
*/

class Calculator {
	double operator_left;
	double operator_right;
public:
	Calculator() = default;
	double calc(double operator_left, double operator_right, std::string opreator_sign) {
		double result = 0;

		switch (opreator_sign[0]) {
		case '+':
			result = operator_left + operator_right;
			break;
		case '-':
			result = operator_left - operator_right;
			break;
		case '*':
			result = operator_left * operator_right;
			break;
		case '/':
			if (operator_right > -0.000001 && operator_right < 0.000001) {
				throw std::exception("除数为0.");
				//std::cout << "除数为0." << std::endl;
			}
			result = operator_left / operator_right;
			break;
		default:
			throw std::exception("不支持的操作符.");
			//std::cout << "不支持的操作数." << std::endl;
			break;
		}

		return result;
	}
};

int main_ori()
{
	using namespace std;
	double left, right;
	std::string opreator_sign;

	Calculator calcor;
	
	while (cin >> left >> opreator_sign >> right) {
		try {
			double result = calcor.calc(left, right, opreator_sign);
			std::cout << "运算结果为：" << result << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	return 0;
}
