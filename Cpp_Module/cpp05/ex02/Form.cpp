#include "Form.hpp"

Form::Form(string const &name, int const sign, int const _execute) : name(name), _execute(_execute), bool_sign(false), sign(sign)
{
	if (sign < HIGH || _execute < HIGH)
		throw Bureaucrat::GradeTooHighException();
	else if (sign > LOW || _execute > LOW)
		throw Bureaucrat::GradeTooLowException();
}

Form::Form(Form const &second) : name(second.name), _execute(second._execute), bool_sign(second.bool_sign), sign(second.sign)
{
	if (sign < HIGH || _execute < HIGH)
		throw Bureaucrat::GradeTooHighException();
	else if (sign > LOW || _execute > LOW)
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
	return this->_execute;
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

string Form::formSigned() const {return "form signed";}

string Form::gradeLOW() const {return "grade LOW";}

void Form::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > this->_execute)
		throw Bureaucrat::GradeTooLowException();
	if (!this->bool_sign)
		throw Form::FormUnsigned();
	cout << executor.getName() << " executes " << this->name << endl;
}

const char* Form::FormSigned::what() const throw()
{
	return "Form already signed";
}

const char* Form::FormUnsigned::what() const throw()
{
	return "The form is not executed because it is not signed";
}

ostream &operator<<(ostream &cout, Form const &form)
{
	cout << "Name [" << form.getName() << "]  [" << ((form.getSigned()) ? "Signed" : "Unsigned")
		<< "] sign [" << form.getSign() << "]  execute [" << form.getExecute() << "]";
	return cout;
}