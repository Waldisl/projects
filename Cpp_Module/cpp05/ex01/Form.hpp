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
		int const			execute;
		bool 				bool_sign;
		int const			sign;
	public:
		Form(string const &name, int const sign, int const execute);
		Form(Form const &second);
		Form &operator=(Form const &second);
		~Form();

		string const &getName(void) const;
		int getSign(void) const;
		int getExecute(void) const;
		bool getSigned(void) const;
		void beSigned(Bureaucrat const &bureaucrat);
		const char* gradeLOW();
		const char* formSigned();

		friend class Bureaucrat;
};

ostream &operator<<(ostream &cout, Form const &form);