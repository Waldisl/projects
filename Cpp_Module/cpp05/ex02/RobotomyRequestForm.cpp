#include "RobotomyRequestForm.hpp"
string const &RobotomyRequestForm::name = string("RobotomyRequestForm");

RobotomyRequestForm::RobotomyRequestForm(string const &target) : 
	Form(RobotomyRequestForm::name, 72, 45), target(target) {}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &second):
	Form(second), target(second.target) {}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm &RobotomyRequestForm::operator=(RobotomyRequestForm const &second)
{
	(void)second;
	return *this;
}

void RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
	Form::execute(executor);
	
	if ((rand() % 2) == 0)
		cout << this->target << " has been robotomized successfully 50% of the time" << endl;
	else
		cout << this->target << " failure" << endl;
}