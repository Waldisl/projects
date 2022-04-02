#include "Bureaucrat.hpp"

int main()
{
	cout << endl;
	try
	{
		cout << "Form1 (40, 0)" << endl << endl;
		Form F1("Form1", 40, 0);
		cout << F1 << endl << endl;
	}
	catch(exception & ex)
	{
		std::cerr << ex.what() << endl << endl;
	}

	try
	{
		cout << "Form2 (10, 40)" << endl << endl;
		Form F2("Form2", 10, 40);
		cout << F2 << endl << endl;
	}
	catch(exception & ex)
	{
		std::cerr << ex.what() << endl << endl;
	}

	try
	{
		cout << "Form3 (190, 90)" << endl << endl;
		Form F3("Form3", 190, 90);
		cout << F3 << endl << endl;
	}
	catch(exception & ex)
	{
	std::cerr << ex.what() << endl << endl;
	}

	try
	{
		cout << "Form4 (90, 250)" << endl << endl;
		Form F4("Form4", 90, 250);
		cout << F4 << endl << endl;
	}
	catch(exception & ex)
	{
		std::cerr << ex.what() << endl << endl;
	}


	Bureaucrat Ivan("Ivan", 11);
	cout << Ivan << endl;
	Form F5("Form5", 10, 4);
	cout << F5 << endl << endl;
	try
	{
		F5.beSigned(Ivan);
	}
	catch(exception & ex)
	{
		std::cerr << ex.what() << endl << endl;
	}
	Ivan.increment();
	try
	{
		F5.beSigned(Ivan);
	}
	catch(exception & ex)
	{
		std::cerr << ex.what() << endl << endl;
	}
	cout << F5 << endl << endl;

	return (0);
}
