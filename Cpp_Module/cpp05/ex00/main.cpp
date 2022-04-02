#include "Bureaucrat.hpp"

int main()
{
	Bureaucrat ivan("Ivan", 100);
	cout << endl;
	cout << "Name : " << ivan.getName() << "\tGrade : " << ivan.getGrade() << endl << endl;

	try
	{
		cout << "Ivan 0 " << endl << endl;
		Bureaucrat ivan("Ivan", 0);
	}
	catch(exception const &ex)
	{
		std::cerr << ex.what() << endl << endl;
	}

	try
	{
		cout << "Ivan 1" << endl << endl;
		Bureaucrat ivan("Ivan", 1);
		cout << ivan << endl << endl;
		ivan.decrement();
		cout << ivan << endl << endl;
		ivan.increment();
		cout << ivan << endl << endl;
		ivan.increment();
		cout << ivan << endl << endl;

	}
	catch(exception const &ex)
	{
		std::cerr << ex.what() << endl << endl;
	}

	try
	{
		cout << "Ivan 200" << endl << endl;
		Bureaucrat ivan("Ivan", 200);
	}
	catch(exception const &ex)
	{
		std::cerr << ex.what() << endl << endl;
	}

	try
	{
		cout << "Ivan 5" << endl << endl;
		Bureaucrat ivan("Ivan", 5);
		cout << ivan << endl << endl;
	}
	catch(exception const &ex)
	{
		std::cerr << ex.what() << endl << endl;
	}

	try
	{
		cout << "Ivan 147" << endl << endl;
		Bureaucrat ivan("Ivan", 147);
		cout << ivan << endl;
	}
	catch(std::exception const &ex)
	{
		std::cerr << ex.what() << endl;
	}
	cout << endl;
	return (0);
}
