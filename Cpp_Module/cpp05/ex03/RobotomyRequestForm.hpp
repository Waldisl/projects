#pragma once
#include "Form.hpp"
#include <cstdlib>

using std::exception;
using std::cout;
using std::endl;
using std::ostream;
using std::string;

class RobotomyRequestForm: public Form
{
	private:
		RobotomyRequestForm();
		string const target;
	public:
		static string const &name;
		RobotomyRequestForm(string const &target);
		RobotomyRequestForm(RobotomyRequestForm const &second);
		RobotomyRequestForm &operator=(RobotomyRequestForm const &second);
		~RobotomyRequestForm();
	
		void execute(Bureaucrat const & executor) const;
};
