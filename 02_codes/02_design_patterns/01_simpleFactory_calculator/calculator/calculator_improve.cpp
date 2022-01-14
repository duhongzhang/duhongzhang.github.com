#include <iostream>
#include <exception>

/**
* �����㣺
* 1. û��ֱ��ʹ�ú�����ʹ�õ��ࡾjava��û�ж�����������
* 2. �쳣ϵ����ʹ��catch throw��
* 3. ����ӡˢ�����ܲٱ�����
*    ʹ�ü̳кͶ�̬(to���ã���չ)
*        ����ԭ��1.��һְ��ԭ��
*                  2.����ԭ��
*        ���ģʽ��
*				   1.����ģʽ(toʹ�÷���)
* 
* ? const���ò�����ֻ�ܵ���const������:
*		const����ֻ�ܷ���const��������һ��������ʽ��
*		const���εĳ�Ա���������޸��κεĳ�Ա������Ҳ���ܵ��÷�const��������ֻ�ܱ�const�����޸ĵ��á�
* ? *ptr_cls = a ʹ�õ��ǵȺŸ�ֵ������ָ��ָ��
*		��Ϊptr_clsδ��ֵ��������Ϊδ֪
* ? ����ӿڵ�~ҪΪ��
*       ��Ȼ�޷�������̬����
* ? Ӧ��data�仯��ģ�����(����ʹ�õĵط���������Ϊ����ʹ�ã�ҲҪʹ��template����)
*		���󷽷���ģ�������������ģ�����������ͬ�������޶�������
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
			throw std::exception("����Ϊ0.");
			//std::cout << "����Ϊ0." << std::endl;
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
			throw std::exception("��֧�ֵĲ�����.");
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

	std::cout << "�밴�մ˸�ʽ������ݣ�����1 �ո� ������ �ո� ����2������: 1 + 2" << std::endl;

	while (cin >> left >> opreator_sign >> right) {

		try {
			std::unique_ptr<CalcOperate<double>> oper(Factory::createCalcOperate<double>(opreator_sign));
			CalcLeft<double> oleft(left);
			CalcRight<double> oright(right);

			result = oper->calc(oleft, oright);

			std::cout << "������Ϊ��" << result << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	return 0;
}
