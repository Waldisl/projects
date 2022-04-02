#pragma once
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

using std::exception;
using std::cout;
using std::endl;
using std::ostream;
using std::string;

class Intern
{
	public:
		Intern();
		Intern(Intern const &second);
		Intern &operator=(Intern const &);
		~Intern();

		Form *makeForm(string const &formName, string const &formTarget);

		class NotKnownForm : public exception
		{
			public:
				const char *what() const throw();
		};
};