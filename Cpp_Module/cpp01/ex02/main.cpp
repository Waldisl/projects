#include <iostream>
#include <string>

int main() 
{
	std::string str = "HI THIS IS BRAIN";
	std::string str1 = "Hello";
	std::string &stringREF = str;
	std::string *stringPTR = &str;
	std::cout << "Adress str:" << "\t\t" << &str << std::endl;
	std::cout << "Adress stringREF:" << "\t" << &stringREF << std::endl;
	std::cout << "Adress stringPTR:" << "\t" << stringPTR << std::endl;
	std::cout << "Reference:" << "\t\t" << stringREF << std::endl;
	std::cout << "Pointer:" << "\t\t" << *stringPTR << std::endl;
	stringPTR = &str1;
	std::cout << "Pointer:" << "\t\t" << *stringPTR << std::endl;
	const std::string &r = str + " " + str1;
	std::cout << "Reference:" << "\t\t" << r << std::endl;
	std::cout << "Adress str1:" << "\t\t" << &str1 << std::endl;
	std::cout << "Adress r:" << "\t\t" << &r << std::endl;
	return 0;
}

	// int a = 10;
	// int b = 5;
	// int *p;
	// p = &a;
	// std::cout << *p << std::endl;
	// p = &b;
	// std::cout << *p << std::endl;
	// int &r = a;
	// std::cout << r << std::endl;
	// int &r = b;
	// std::cout << r << std::endl;