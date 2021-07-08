#include <iostream>
#include "String.h"

int main()
{
	MySpace::String str;
	MySpace::String str2("Hello,World!");
	MySpace::String str3 = "Game";
	MySpace::String str4(str3); // str4.pString = str3.pString;

	str2 = str3; // str2.pString = str3.pString;

	std::cout << str2 << std::endl;
	std::cin >> str2;
	std::cout << str2 << std::endl;

	return 0;
}