#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(string const &name, int grade) : name(name), grade(grade)
{
	if (this->grade < HIGH)
		throw Bureaucrat::GradeTooHighException();
	else if (this->grade > LOW)
		throw Bureaucrat::GradeTooLowException();
}

Bureaucrat::Bureaucrat(Bureaucrat const &second) : name(second.name), grade(second.grade)
{
	if (this->grade < HIGH)
		throw Bureaucrat::GradeTooHighException();
	else if (this->grade > LOW)
		throw Bureaucrat::GradeTooLowException();
}

Bureaucrat::~Bureaucrat()
{
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &second)
{
	this->grade = second.grade;
	if (this->grade < HIGH)
		throw Bureaucrat::GradeTooHighException();
	else if (this->grade > LOW)
		throw Bureaucrat::GradeTooLowException();
	return *this;
}

string const &Bureaucrat::getName(void) const
{
	return this->name;
}

int Bureaucrat::getGrade(void) const
{
	return this->grade;
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Error: Grade < 1";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Error: Grade > 150";
}

void Bureaucrat::increment(void)
{
	this->grade--;
	if (this->grade < HIGH)
		throw Bureaucrat::GradeTooHighException();
}

void Bureaucrat::decrement(void)
{
	this->grade++;
	if (this->grade > LOW)
		throw Bureaucrat::GradeTooLowException();
}

void Bureaucrat::signForm(Form &form) const
{
	if (form.getSigned())
	{
		cout << "[" << this->name << "] cannot sign [" << form.getName() << "] because [" << form.formSigned() << "]" << endl;
	}
	else if (form.getSign() < this->grade)
	{
		cout << " { " << this->name << " } cannot sign { " << form.getName() << " } because [" << form.gradeLOW() << "]" << endl;
	}
	else
	{
		form.beSigned(*this);
	}
}

void Bureaucrat::executeForm(Form const &form) const
{
	if (!form.getSigned())
	{
		cout << "[" << this->name << "] cannot execute [" << form.getName() << "] because [no " << form.formSigned() << "]" << endl;
	}
	else if (form.getExecute() < this->grade)
	{
		cout << " { " << this->name << " } cannot execute { " << form.getName() << " } because [" << form.gradeLOW() << "]" << endl;
	}
	else
	{
		form.execute(*this);
	}
}

ostream &operator<<(ostream &cout, Bureaucrat const &bur)
{
	cout << "Name [" << bur.getName() << "] "<< "grade [" << bur.getGrade() << "]";
	return cout;
}
