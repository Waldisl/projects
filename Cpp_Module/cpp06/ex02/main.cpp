#include <iostream>
#include <ctime>
// #include <unistd.h>

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "Base.hpp"

Base *generate(void)
{
	std::srand(std::time(NULL));
	int random = rand() % 1000;

	if (random > 800)
		return new A;
	else if (random > 400)
		return new B;
	return new C;
}

void identify(Base *p)
{
	cout << endl << "Identify pointer :";
	if (dynamic_cast<A*>(p) != nullptr)
		cout << "\tpointer A" << endl;
	else if (dynamic_cast<B*>(p) != nullptr)
		cout << "\tpointer B" << endl;
	else if (dynamic_cast<C*>(p) != nullptr)
		cout << "\tpointer C" << endl;
	else
		cout << "Error : identify" << endl;
}

void identify(Base &p)
{
	cout  << "Identify link :\t";
	// A type_a;
	// B type_b;
	// C type_c;
	// if (type_a == dynamic_cast<A&>(p);)
	// 	cout << "\tlink A" << endl;
	// else if (type_b == dynamic_cast<B&>(p);)
	// 	cout << "\tlink B" << endl;
	// else if (type_c == dynamic_cast<C&>(p);)
	// 	cout << "\tlink C" << endl;
	try
	{
		A type_a = dynamic_cast<A&>(p);
		cout << "\tlink A" << endl;
	}
	catch(const exception& ex) {}

	try
	{
		B type_b = dynamic_cast<B&>(p);
		cout << "\tlink B" << endl;
	}
	catch(const exception& ex) {}
	try
	{
		C type_c = dynamic_cast<C&>(p);
		cout << "\tlink C" << endl;
	}
	catch(const exception& ex) {}
}

int		main()
{
	Base	*test1 = generate();
	Base	*test2 = generate();
	
	cout << endl << "Test1";
	identify(test1);
	identify(*test1);
	// usleep(1000000);

	cout << endl << "Test2";
	identify(test2);
	identify(*test2);

	delete test1;
	delete test2;
	return (0);
}