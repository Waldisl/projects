#include "Karen.hpp"

Karen::Karen() 
{
}

Karen::~Karen()
{
}

void Karen::warning(void)
{
	std::cout << "[ WARNING ]\n" << "I think I deserve to have some extra bacon for free.\n"
	<< "I’ve been coming here for years and you just started working here last month." << std::endl;
}

void Karen::debug(void)
{
	std::cout << "[ DEBUG ]" << '\n' << "I love to get extra bacon for my 7XL-double-cheese-triple-"
	<< "pickle-special-ketchup burger.\nI just love it!" << std::endl;
}

void Karen::error(void)
{
	std::cout << "[ ERROR ]" << '\n' << "This is unacceptable, I want to speak to the manager now." << std::endl;
}

void Karen::info(void)
{
	std::cout << "[ INFO ]" << '\n' << "I cannot believe adding extra bacon cost more money.\n"
	<< "You don’t put enough!\nIf you did I would not have to ask for it!" << std::endl;
}

void Karen::complain(std::string level)
{

	std::string str[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	void	(Karen::*arr_func[])(void) =
	{&Karen::debug, &Karen::info, &Karen::warning, &Karen::error};
	for (size_t i = 0; i < 4; i++)
	{
		if (level == str[i])
			(this->*arr_func[i])();
	}
}
void Karen::filter_switch(void)
{
	switch(_num)
	{
		case 0:
			complain("DEBUG");
			std::cout << std::endl;
		case 1:
			complain("INFO");
			std::cout << std::endl;
		case 2:
			complain("WARNING");
			std::cout << std::endl;
		case 3:
			complain("ERROR");
			std::cout << std::endl;
			break ;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
			break;
	}
}
void Karen::filter(std::string av)
{
	std::string str[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	for (int num = 0; num < 4; num++)
	{
		if (str[num] == av)
		{
			Karen::_num = num;
			break ;
		}
		else
			Karen::_num = -1;
		
	}
	filter_switch();
}

	// std::string str[] = 
	// {"debug", 
	// 	"info", 
	// 	"warning", 
	// 	"error" 
	// };
	// // switch (level)
	// // {
	// // 	case str[0]:
	// // 		Karen::debug();
	// // 		break ;
	// // 	case str[1]:
	// // 		Karen::info();
	// // 		break ;
	// // 	case str[2]:
	// // 		Karen::warning();
	// // 		break ;
	// // 	case str[3]:
	// // 		Karen::error();
	// // 		break ;
	// // }