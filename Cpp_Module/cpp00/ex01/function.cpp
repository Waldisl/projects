#include "ClassPhoneBook_Contact.hpp"

int		ft_add(PhoneBook *PhoneBook)
{
	int			i = PhoneBook->Getnext();
	int			step = 1;
	std::string	str;

	while (step <= 5)
	{
		std::cout << "Enter ";
		if (step == 1)
			std::cout << "first name";
		else if (step == 2)
			std::cout << "last name";
		else if (step == 3)
			std::cout << "nickname";
		else if (step == 4)
			std::cout << "phone number";
		else if (step == 5)
			std::cout << "darkest secret";
		std::cout << " contact ";
		std::cout << (i + 1);
		std::cout << ": ";
		if (!(std::getline(std::cin, str)))
		{
			std::cout << std::endl;
			return 1;
		}
		PhoneBook->SetContactStep(i, step, str);
		step++;
	}
	PhoneBook->SetContactFull(i);
	if (i == 7)
		(PhoneBook->Setnext(0));
	else
		(PhoneBook->Setnext(i + 1));
	return 0;
}

void	print_long(PhoneBook *PhoneBook, int i, int step)
{
	std::string	temp;

	{
		temp = PhoneBook->GetContactStep(i, step);
		temp.resize(9);
		temp.append(".");
		std::cout << temp;
	}
}

void	print_short(PhoneBook *PhoneBook, int i)
{
	int			step;

	std::cout << std::setw(10);
	std::cout << (i + 1);
	std::cout << "|";
	step = 1;
	std::cout << std::setw(10);
	if (PhoneBook->GetContactStep(i, step).length() > 10)
		print_long(PhoneBook, i, step);
	else
		std::cout << PhoneBook->GetContactStep(i, step);
	std::cout << "|";
	step = 2;
	std::cout << std::setw(10);
	if (PhoneBook->GetContactStep(i, step).length() > 10)
		print_long(PhoneBook, i, step);
	else
		std::cout << PhoneBook->GetContactStep(i, step);
	std::cout << "|";
	step = 3;
	std::cout << std::setw(10);
	if (PhoneBook->GetContactStep(i, step).length() > 10)
		print_long(PhoneBook, i, step);
	else
		std::cout << PhoneBook->GetContactStep(i, step);
	std::cout << std::endl;
}

void	print_contacts(PhoneBook *PhoneBook)
{
	std::cout << "     index|first name| last name|  nickname" << std::endl;
	std::cout << "----------|----------|----------|----------" << std::endl;

	int		i = 0;

	while (i <= 7)
	{
		if (PhoneBook->GetContactFull(i))
		{
			print_short(PhoneBook, i);
		}
		i++;
	}
	std::cout << "-------------------------------------------" << std::endl;
}

bool	num_index(std::string index)
{
	char	num;

	num = index.at(0);
	if (num >= 49 && num <= 56)
		return true;
	else
		return false;
}

void	print_contact(PhoneBook *PhoneBook, int i)
{
	std::cout << "First name:\t" << PhoneBook->GetContactStep(i, 1) << std::endl;
	std::cout << "Last name:\t" << PhoneBook->GetContactStep(i, 2) << std::endl;
	std::cout << "Nickname:\t" << PhoneBook->GetContactStep(i, 3) << std::endl;
	std::cout << "Phone number:\t" << PhoneBook->GetContactStep(i, 4) << std::endl;
	std::cout << "Darkest secret:\t" << PhoneBook->GetContactStep(i, 5) << std::endl;
}

int		ft_search(PhoneBook *PhoneBook)
{
	print_contacts(PhoneBook);

	std::string	in;
	int			i;
	while (1)
	{
		std::cout << "Enter index: ";
		if (!(std::getline(std::cin, in)))
			return 1;
		if (in.length() != 1 || !num_index(in))
		{
			std::cout << "Enter Index value should be 1 - 8." << std::endl;
			continue ;
		}
		i = (int)in.at(0) - 49;
		if (PhoneBook->GetContactFull(i))
		{
			print_contact(PhoneBook, i);
			break ;
		}
		else
		{
			std::cout << "Contact is not full." << std::endl;
			continue ;
		}
	}
	return 0;
}
