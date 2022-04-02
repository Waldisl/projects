#include "Intern.hpp"

Intern::Intern() {}

Intern::Intern(Intern const &second)
{
	*this = second;
}

Intern &Intern::operator=(Intern const &)
{
	return *this;
}

Intern::~Intern() {}

Form* makeFormShrubbery(string const& target)
{
	return new ShrubberyCreationForm(target);
}

Form* makeFormRobotomy(string const& target)
{
	return new RobotomyRequestForm(target);
}

Form* makeFormPresidential(string const& target)
{
	return new PresidentialPardonForm(target);
}

const char* Intern::NotKnownForm::what() const throw()
{
	return ("Intern cannot create the form");
}

typedef Form *(*func)(const string &target);

Form*	Intern::makeForm(string const &name, string const &target)
{
	const string type[3] = 
	{	"shrubbery creation", "robotomy request", "presidential pardon" };
	static func makeFormFuncts[3] = 
	{	makeFormShrubbery, makeFormRobotomy, makeFormPresidential };

	for (int i = 0; i < 3; i++) 
	{
		if (name == type[i])
		{
			cout << "Intern creates [" << name << "]" << endl;
			return makeFormFuncts[i](target);
		}
	}
	throw Intern::NotKnownForm();
}
