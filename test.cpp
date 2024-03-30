#include "pch.h"
#include "C:\Users\i.kupa\source\repos\ProjectString\String.cpp"

TEST(testConstruct, firstConstruct)
{
	String test1constr("string1");
	ASSERT_EQ(1, test1constr.countRef()) << "countRef is not equal to 1";
	ASSERT_STREQ("string1", test1constr.data()) << "strings don't match";
}

TEST(test_case_name, test_name)
{
	//String test2constr("string1", 4);
	//ASSERT_EQ(1, test2constr.countRef()) << "countRef is not equal to 1";
	//ASSERT_STREQ("stri", test2constr.data()) << "strings don't match";

	//String test3constr(5, 'a');
	//ASSERT_EQ(1, test3constr.countRef()) << "countRef is not equal to 1";
	//ASSERT_STREQ("aaaaa", test3constr.data()) << "strings don't match";

	//String test4constr("string1");
	//String test4copy(test4constr);
	//ASSERT_EQ(2, test4copy.countRef()) << "countRef is not equal to 2";
	//ASSERT_STREQ("string1", test4copy.data()) << "strings don't match";
	//test4copy += '2';
	//ASSERT_EQ(1, test4copy.countRef()) << "countRef is not equal to 1";
	//ASSERT_STREQ("string12", test4copy.data()) << "strings don't match";

	//String test5constr("QQQQQstring1QQQQQQQQ");
	//String test5copy(test5constr, 5, 7);
	//ASSERT_EQ(1, test5copy.countRef()) << "countRef is not equal to 1";
	//ASSERT_STREQ("string1", test5copy.data()) << "strings don't match";
	//test5copy += '2';
	//ASSERT_EQ(1, test5copy.countRef()) << "countRef is not equal to 1";
	//ASSERT_STREQ("string12", test5copy.data()) << "strings don't match";
}

TEST(substring_test, empty)
{
	String testSubstring;
	ASSERT_STREQ("", testSubstring.data());
}