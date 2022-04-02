#pragma once
#include <iostream>
#include <string>

#include "Form.hpp"

using std::exception;
using std::cout;
using std::endl;
using std::ostream;
using std::string;

class PresidentialPardonForm: public Form
{
	private:
		PresidentialPardonForm();
		string const target;
	public:
		static string const &name;
		PresidentialPardonForm(std::string const &target);
		PresidentialPardonForm(PresidentialPardonForm const &second);
		PresidentialPardonForm &operator=(PresidentialPardonForm const &second);
		~PresidentialPardonForm();

		void execute(Bureaucrat const & executor) const;
};