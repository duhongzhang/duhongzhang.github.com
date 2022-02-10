#define BOOST_TEST_MODULE "stringtest1"
#include <boost/test/included/unit_test.hpp> //单header使用
//#include <boost/test/unit_test.hpp> //需结合库使用
#include "String.h"

BOOST_AUTO_TEST_SUITE (stringtest1)

BOOST_AUTO_TEST_CASE (test1)
{
	testString tStr("abc");
	BOOST_WARN(tStr.size() == 0);

	testString tStr1("someString");
	BOOST_REQUIRE_EQUAL('x', tStr1[0]);

	testString tStr2("a");
	BOOST_CHECK(tStr2.isEmpty());
}

BOOST_AUTO_TEST_CASE(test2)
{
	testString tStr("a");
	BOOST_CHECK(tStr.isEmpty());

	testString tStr1("someString");
	BOOST_REQUIRE_EQUAL('x', tStr1[0]);
}

BOOST_AUTO_TEST_SUITE_END (stringtest1)



BOOST_AUTO_TEST_SUITE(stringtest2)

BOOST_AUTO_TEST_CASE(test1)
{
	testString tStr("abc");
	BOOST_WARN(tStr.size() == 0);

	testString tStr1("someString");
	BOOST_REQUIRE_EQUAL('x', tStr1[0]);

	testString tStr2("a");
	BOOST_CHECK(tStr2.isEmpty());
}

BOOST_AUTO_TEST_CASE(test2)
{
	testString tStr("a");
	BOOST_CHECK(tStr.isEmpty());

	testString tStr1("someString");
	BOOST_REQUIRE_EQUAL('x', tStr1[0]);
}

BOOST_AUTO_TEST_SUITE_END(stringtest2)

