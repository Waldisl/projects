
#pragma once
#include <string>
#include <fstream>
#include "Form.hpp"

using std::exception;
using std::cout;
using std::endl;
using std::ostream;
using std::string;

class ShrubberyCreationForm: public Form
{
	private:
		ShrubberyCreationForm();
		string const target;
		static string tree;
	
	public:
		static string const &name;
		ShrubberyCreationForm(string const &target);
		ShrubberyCreationForm(ShrubberyCreationForm const &second);
		ShrubberyCreationForm &operator=(ShrubberyCreationForm const &second);
		~ShrubberyCreationForm();

		void execute(Bureaucrat const & executor) const;

		class FileOpen: public exception
		{
			public:
				virtual const char* what() const throw();
		};
};