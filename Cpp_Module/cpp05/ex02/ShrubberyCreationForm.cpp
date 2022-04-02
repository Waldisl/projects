#include "ShrubberyCreationForm.hpp"

string const &ShrubberyCreationForm::name = string("ShrubberyCreationForm");

string ShrubberyCreationForm::tree = "                                             \n" \
"               #                 \n" \
"              ***                \n" \
"             *****               \n" \
"            *****~~              \n" \
"             **~~~               \n" \
"            *~~~***              \n" \
"           ~~~******             \n" \
"          ~~*********            \n" \
"         *************           \n" \
"          ***********            \n" \
"         *************           \n" \
"        ***************          \n" \
"       *@***************         \n" \
"      ***@************@**        \n" \
"     *@****************@**       \n" \
"       @****************         \n" \
"      *******************        \n" \
"     *****@***************       \n" \
"    ***********************      \n" \
"   ********@****************     \n" \
"  *****************@*********    \n" \
" *****************************   \n" \
"            |||||                \n" \
"            |||||   _8_8_        \n" \
"            |||||  |  |  |_8_    \n" \
"            |||||  |__|__|___|;  \n"; \


ShrubberyCreationForm::ShrubberyCreationForm(string const &target):
	Form(ShrubberyCreationForm::name, 145, 137), target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &second):
	Form(second), target(second.target) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &second)
{
	(void)second;
	return *this;
}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
	Form::execute(executor);
	std::ofstream out_file;
	string file = (this->target + "_shrubbery");

	out_file.open(&file[0], std::ios::trunc);
	if (!out_file.is_open())
		throw ShrubberyCreationForm::FileOpen();
	out_file << this->tree;
	out_file.close();
	cout << "[" << executor.getName() << "]  execute the form with target: [" << this-> target << "]" << endl;
}
const char* ShrubberyCreationForm::FileOpen::what() const throw()
{
	return "Cannot open file";
}