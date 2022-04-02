#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main()
{
	try
	{
		cout << "===================================================" << endl << endl;
		Intern  someRandomIntern;
		Form*   rrf;

		rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		cout << *rrf << endl;
		delete rrf;
	}
	catch(exception const &ex)
	{
		std::cerr << ex.what() << endl;
	}
	
	
	try
	{
		cout << "===================================================" << endl << endl;
		Intern  someRandomIntern;
		Form*   rrf;

		rrf = someRandomIntern.makeForm("Robot request", "Dom");
		cout << *rrf << endl;
		delete rrf;
	}
	catch(exception const &ex)
	{
		std::cerr << "Error : "<< ex.what() << endl;
	}

	try
	{
		cout << "===================================================" << endl << endl;
		Intern  someRandomIntern;
		Form*   rrf;

		rrf = someRandomIntern.makeForm("shrubbery creation", "DOM");
		cout << *rrf << endl;
		delete rrf;
	}
	catch(exception const &ex)
	{
		std::cerr << "Error : "<< ex.what() << endl;
	}
	
	try
	{
		cout << "===================================================" << endl << endl;
		Intern  someRandomIntern;
		Form*   rrf;

		rrf = someRandomIntern.makeForm("ShrubbeaasryCreationt", "LOv");
		cout << *rrf << endl;
		delete rrf;
	}
	catch(exception const &ex)
	{
		std::cerr << "Error : "<< ex.what() << endl;
	}

	try
	{
		cout << "===================================================" << endl << endl;
		Intern  someRandomIntern;
		Form*   rrf;

		rrf = someRandomIntern.makeForm("presidential pardon", "RONE");
		cout << *rrf << endl;
		delete rrf;
	}
	catch(exception const &ex)
	{
		std::cerr << "Error : "<< ex.what() << endl;
	}

	try
	{
		cout << "===================================================" << endl << endl;
		Intern  someRandomIntern;
		Form*   rrf;

		rrf = someRandomIntern.makeForm("someRandomIntern", "Ofr");
		cout << *rrf << endl;
		delete rrf;
	}
	catch(exception const &ex)
	{
		std::cerr << "Error : "<< ex.what() << endl;
	}
	
	try
	{
		cout << "===================================================" << endl << endl;
		Intern  someRandomIntern;
		Form*   rrf;

		rrf = someRandomIntern.makeForm("pResIdentidsal pArdon", "rick");
		cout << *rrf << endl;
		delete rrf;
	}
	catch(exception const &ex)
	{
		std::cerr << "Error : "<< ex.what() << endl;
	}
	
	try
	{
		cout << "===================================================" << endl << endl;
		Intern  someRandomIntern;
		Form*   rrf;

		rrf = someRandomIntern.makeForm("sdlfsdvk sdlmvm f", "allme");
		cout << *rrf << endl;
		delete rrf;
	}
	catch(exception const &ex)
	{
		std::cerr << "Error : "<< ex.what() << endl;
	}

	return (0);
}

