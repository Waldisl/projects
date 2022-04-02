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

class Form;
#include "Bureaucrat.hpp"

class Form 
{
	private:
		Form();
		string const		&name;
		int const			_execute;
		bool 				bool_sign;
		int const			sign;
	public:
		Form(string const &name, int const sign, int const _execute);
		Form(Form const &second);
		Form &operator=(Form const &second);
		virtual ~Form();

		string const &getName(void) const;
		int getSign(void) const;
		int getExecute(void) const;
		bool getSigned(void) const;
		void beSigned(Bureaucrat const &bureaucrat);
		string gradeLOW(void) const;
		string formSigned(void) const;
		virtual void execute(Bureaucrat const & executor) const = 0;

		friend class Bureaucrat;

		class FormSigned: public exception
		{
			public:
				virtual const char* what() const throw();
		};
		
		class FormUnsigned: public exception
		{
			public:
				virtual const char* what() const throw();
		};

};

ostream &operator<<(ostream &cout, Form const &form);