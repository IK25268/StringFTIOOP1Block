#include "pch.h"
#include "D:\prog\VS\StringFTIOOP1Block\String.cpp"

TEST(testConstruct, Construct0)
{
	String test0constr;
	ASSERT_EQ(1, test0constr.countRef()) << "countRef is not equal to 1";
	ASSERT_STREQ("", test0constr.data()) << "strings don't match";
}
TEST(testConstruct, Construct1)
{
	String test1constr("string1");
	ASSERT_EQ(1, test1constr.countRef()) << "countRef is not equal to 1";
	ASSERT_STREQ("string1", test1constr.data()) << "strings don't match";
}
TEST(testConstruct, Construct2)
{
	String test2constr("string16666666", 7);
	ASSERT_EQ(1, test2constr.countRef()) << "countRef is not equal to 1";
	ASSERT_STREQ("string1", test2constr.data()) << "strings don't match";
}
TEST(testConstruct, Construct3)
{
	String test3constr(7, 'a');
	ASSERT_EQ(1, test3constr.countRef()) << "countRef is not equal to 1";
	ASSERT_STREQ("aaaaaaa", test3constr.data()) << "strings don't match";
}
TEST(testConstruct, Construct4)
{
	String test4constrOrig("string1");
	String test4constr(test4constrOrig);
	ASSERT_EQ(2, test4constr.countRef()) << "countRef is not equal to 2";
	ASSERT_EQ(2, test4constrOrig.countRef()) << "countRef is not equal to 2";
	ASSERT_STREQ("string1", test4constr.data()) << "strings don't match";
}
TEST(testConstruct, Construct5)
{
	String test5constrOrig("66666666string166666666");
	String test5constr(test5constrOrig, 8, 7);
	ASSERT_EQ(1, test5constr.countRef()) << "countRef is not equal to 1";
	ASSERT_EQ(1, test5constrOrig.countRef()) << "countRef is not equal to 1";
	ASSERT_STREQ("string1", test5constr.data()) << "strings don't match";
}

TEST(testOperator, OperatorAT0)
{
	String testOperatorAT("string1");
	ASSERT_EQ('i', testOperatorAT[3]) << "symbols don't match";
}
TEST(testOperator, OperatorAT1)
{
	String testOperatorAT("string1");
	ASSERT_EQ('i', testOperatorAT.at(3)) << "symbols don't match";
}
TEST(testOperator, OperatorBack)
{
	String testOperatorAT("string1");
	ASSERT_EQ('1', testOperatorAT.back()) << "symbols don't match";
}
TEST(testOperator, OperatorFront)
{
	String testOperatorAT("string1");
	ASSERT_EQ('s', testOperatorAT.front()) << "symbols don't match";
}
TEST(testOperator, OperatorPLUS0)
{
	String testOperatorPLUS0("string1");
	String testOperator("vector2");
	testOperatorPLUS0 += testOperator;
	ASSERT_STREQ("string1vector2", testOperatorPLUS0.data()) << "strings don't match";
}
TEST(testOperator, OperatorPLUS1)
{
	String testOperatorPLUS1("string1");
	testOperatorPLUS1 += "vector2";
	ASSERT_STREQ("string1vector2", testOperatorPLUS1.data()) << "strings don't match";
}
TEST(testOperator, OperatorPLUS2)
{
	String testOperatorPLUS2("string1");
	testOperatorPLUS2 += '2';
	ASSERT_STREQ("string12", testOperatorPLUS2.data()) << "strings don't match";
}
TEST(testOperator, OperatorEQ0)
{
	String testOperatorEQ0("string1");
	String testOperator("vector2");
	testOperatorEQ0 = testOperator;
	ASSERT_EQ(2, testOperator.countRef()) << "countRef is not equal to 2";
	ASSERT_EQ(2, testOperatorEQ0.countRef()) << "countRef is not equal to 2";
	ASSERT_STREQ("vector2", testOperatorEQ0.data()) << "strings don't match";
}
TEST(testOperator, OperatorEQ1)
{
	String testOperatorEQ0("string1");
	testOperatorEQ0 = "vector2";
	ASSERT_EQ(1, testOperatorEQ0.countRef()) << "countRef is not equal to 2";
	ASSERT_STREQ("vector2", testOperatorEQ0.data()) << "strings don't match";
}

TEST(testInsert, Insert0)
{
	String testInsert0("string1");
	String testInsert("vector25");
	testInsert0.insert(3, testInsert);
	ASSERT_STREQ("strvector25ing1", testInsert0.data()) << "strings don't match";
}
TEST(testInsert, Insert1)
{
	String testInsert0("string1");
	testInsert0.insert(3, "vector25");
	ASSERT_STREQ("strvector25ing1", testInsert0.data()) << "strings don't match";
}
TEST(testErase, Erase0)
{
	String testErase0("strvector2ing1");
	testErase0.erase(3, 7);
	ASSERT_STREQ("string1", testErase0.data()) << "strings don't match";
}
TEST(testReplace, Replace0)
{
	String testReplace0("str7777777777ing1");
	String testReplace("vector2");
	testReplace0.replace(3, 10, testReplace);
	ASSERT_STREQ("strvector2ing1", testReplace0.data()) << "strings don't match";
}
TEST(testReplace, Replace1)
{
	String testReplace1("str7777777777ing1");
	testReplace1.replace(3, 10, "vector2");
	ASSERT_STREQ("strvector2ing1", testReplace1.data()) << "strings don't match";
}
TEST(testReplace, Replace2)
{
	String testReplace2("str7777777777ing1");
	testReplace2.replace(3, 10, 7, 'v');
	ASSERT_STREQ("strvvvvvvving1", testReplace2.data()) << "strings don't match";
}
TEST(testFind, Find0)
{
	String testFind0("vector2str7777777777ing1");
	String testFind("7777777777");
	ASSERT_EQ(10, testFind0.find(testFind, 7)) << "strings don't match";
}
TEST(testFind, Find1)
{
	String testFind1("vector2str7777777777ing1");
	ASSERT_EQ(10, testFind1.find("7777777777", 7)) << "strings don't match";
}
TEST(testFind, Find2)
{
	String testFind2("vector2str7ing1");
	ASSERT_EQ(10, testFind2.find("7", 7)) << "symbols don't match";
}

TEST(testOtherFunc, Substr)
{
	String testSubstr("vecstring1tor2");
	testSubstr.substr(3, 7);
	ASSERT_STREQ("string1", testSubstr.data()) << "strings don't match";
}
TEST(testOtherFunc, Compare)
{
	String testCompare0("aaaaaa");
	String testCompare1("bbbbbb");
	String testCompare11("bbbbbb");
	String testCompare2("cccccc");
	ASSERT_EQ(0, testCompare1.compare(testCompare11)) << "strings don't match";
	ASSERT_EQ(1, testCompare1.compare(testCompare0)) << "strings don't match";
	ASSERT_EQ(-1, testCompare1.compare(testCompare2)) << "strings don't match";
}
TEST(testOtherFunc, Swap)
{
	String testSwap0("aaaaaa");
	String testSwap1("bbbbbb");
	testSwap0.swap(testSwap1);
	ASSERT_STREQ("aaaaaa", testSwap1.data()) << "strings don't match";
	ASSERT_STREQ("bbbbbb", testSwap0.data()) << "strings don't match";
}
