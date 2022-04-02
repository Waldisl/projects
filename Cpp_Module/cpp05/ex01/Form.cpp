#include "Form.hpp"

Form::Form(string const &name, int const sign, int const execute) : name(name), execute(execute), bool_sign(false), sign(sign)
{
	if (sign < HIGH || execute < HIGH)
		throw Bureaucrat::GradeTooHighException();
	else if (sign > LOW || execute > LOW)
		throw Bureaucrat::GradeTooLowException();
}

Form::Form(Form const &second) : name(second.name), execute(second.execute), bool_sign(second.bool_sign), sign(second.sign)
{
	if (sign < HIGH || execute < HIGH)
		throw Bureaucrat::GradeTooHighException();
	else if (sign > LOW || execute > LOW)
		throw Bureaucrat::GradeTooLowException();
}

Form::~Form()
{
}

Form &Form::operator=(Form const &second)
{
	this->bool_sign = second.bool_sign;
	return *this;
}

string const &Form::getName(void) const
{
	return this->name;
}

int Form::getSign(void) const
{
	return this->sign;
}

int Form::getExecute(void) const
{
	return this->execute;
}

bool Form::getSigned(void) const
{
	return this->bool_sign;
}

void Form::beSigned(Bureaucrat const &bureaucrat)
{
	if (this->bool_sign)
		return ;
	if (bureaucrat.getGrade() > this->sign)
		throw Bureaucrat::GradeTooLowException();
	this->bool_sign = true;
	cout <<  "[" << this->name << "]: " << "signed ["  << bureaucrat.getName() << "]" << endl;
}

const char* Form::formSigned() {return "form signed";}

const char* Form::gradeLOW() {return "grade LOW";}

ostream &operator<<(ostream &cout, Form const &form)
{
	cout << "Name [" << form.getName() << "]  [" << ((form.getSigned()) ? "Signed" : "Unsigned")
		<< "] sign [" << form.getSign() << "]  execute [" << form.getExecute() << "]";
	return cout;
}