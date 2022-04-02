#pragma once
#include <iostream>
#include <string>

#define HIGH 1
#define LOW 150

using std::exception;
using std::cout;
using std::endl;
using std::ostream;
using std::string;

class Bureaucrat;
#include "Form.hpp"

class Bureaucrat 
{
	private:
		Bureaucrat();
		string const		name;
		int 				grade;
	public:
		Bureaucrat(string const &name, int grade);
		Bureaucrat(Bureaucrat const &second);
		Bureaucrat &operator=(Bureaucrat const &second);
		~Bureaucrat();

		string const &getName(void) const;
		int getGrade(void) const;

		class GradeTooHighException : public exception
		{
			public:
				virtual const char* what() const throw();
		};

		class GradeTooLowException : public exception
		{
			public:
				virtual const char* what() const throw();
		};

		void increment(void);
		void decrement(void);
		void signForm(Form &form) const;
		void executeForm(Form const &base) const;
};

ostream &operator<<(ostream &cout, Bureaucrat const &bur);