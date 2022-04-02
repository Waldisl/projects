#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	Bureaucrat Bro1("Bro1", 3);
	cout << Bro1 << endl;
	Bureaucrat Bro2("Bro2", 37);
	cout << Bro2 << endl << endl;
	
	Form *Shrubbery = new ShrubberyCreationForm("Shrubbery");
	cout << *Shrubbery << endl;
	Shrubbery->beSigned(Bro1);
	Shrubbery->execute(Bro2);
	cout << endl << endl;
	
    Form *Robotomy = new RobotomyRequestForm("Robot");
	cout << *Robotomy << endl;
	Robotomy->beSigned(Bro1);
	Robotomy->execute(Bro2);
	Bro1.executeForm(*Robotomy);
	Bro2.executeForm(*Robotomy);
	cout << endl << endl;

	Form *Pardon = new PresidentialPardonForm("Pardon");
	cout << *Pardon << endl;
	Bro1.signForm(*Pardon);
	Pardon->execute(Bro1);
	cout << endl << endl;

	try
	{
		Bureaucrat Bro("Bro", 99);
		cout << Bro << endl;
		ShrubberyCreationForm tree = ShrubberyCreationForm("hrubbery");
		cout << tree << endl;
		tree.execute(Bro);
	}
	catch(exception const &ex)
	{
		std::cerr << ex.what() << endl;
	}

	cout << endl;
	try
	{
		Bureaucrat Bro("Bro", 99);
		cout << Bro << endl;
		ShrubberyCreationForm tree = ShrubberyCreationForm("hrubbery");
		cout << tree << endl;
		Bro.executeForm(tree);
	}
	catch(exception const &ex)
	{
		std::cerr << ex.what() << endl;
	}

	cout << endl;
	try
	{
		Bureaucrat Bro("Bro", 99);
		cout << Bro << endl;
		ShrubberyCreationForm tree = ShrubberyCreationForm("hrubbery");
		cout << tree << endl;
		Bro.executeForm(tree);
	}
	catch(exception const &ex)
	{
		std::cerr << ex.what() << endl;
	}


	cout << endl;
	try
	{
		RobotomyRequestForm Request = RobotomyRequestForm("Request");
		cout << Request << endl;
		Request.execute(Bro1);
	}
	catch(exception const &ex)
	{
		std::cerr << ex.what() << endl;
	}

	cout << endl;
	try
	{
		PresidentialPardonForm Presidential = PresidentialPardonForm("Presidential");
		cout << Presidential << endl;
		Presidential.execute(Bro1);
	}
	catch(exception const &ex)
	{
		std::cerr << ex.what() << endl;
	}

	delete Shrubbery;
	delete Robotomy;
	delete Pardon;
	return (0);
}

