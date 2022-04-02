#include "PresidentialPardonForm.hpp"

string const &PresidentialPardonForm::name = string("PresidentialPardonForm");

PresidentialPardonForm::PresidentialPardonForm(string const &target):
	Form(PresidentialPardonForm::name, 25, 5), target(target) {}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &second):
	Form(second), target(second.target) {}

PresidentialPardonForm::~PresidentialPardonForm() {}

PresidentialPardonForm &PresidentialPardonForm::operator=(PresidentialPardonForm const &second)
{
	(void)second;
	return *this;
}

void PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
	Form::execute(executor);
	cout << "[" << this->target << "] has been pardoned by Zafod Beeblebrox!" << endl;
}