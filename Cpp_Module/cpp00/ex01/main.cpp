#include "ClassPhoneBook_Contact.hpp"

int		main(void)
{
	PhoneBook	PhoneBook;
	std::string	command;

	std::cout << "Hello, this is the phone book." << std::endl;

	while(1)
	{
		std::cout << "PhoneBook > ";
		if (!(std::getline(std::cin, command)))
		{
			std::cout << std::endl;
			break ;
		}
		if (command.empty())
			continue ;
		if (!command.compare("EXIT"))
		{
			std::cout << "All contacts have been deleted." << std::endl;
			return (0);
		}
		else if (!command.compare("ADD"))
		{
			if (ft_add(&PhoneBook))
				return 0;;
		}
		else if (!command.compare("SEARCH"))
		{
			if (ft_search(&PhoneBook))
				return 0;
		}
		else
			std::cout << "Please use ADD,SEARCH or EXIT." << std::endl;
	}
	return 0;
}
