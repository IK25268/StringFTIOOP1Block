#include <iostream>
#include "String.hpp"
using namespace std;

int main()
{
	String test1("qwertyuiop");
	String test2("QWERTYUIOP");
	String test3(test2);
	test3 = test1;
	return 0;
}