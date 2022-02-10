#include "String.h"

int main1() {
	testString tStr(__FILE__);

	std::cout << tStr() << std::endl;

	return 0;
}