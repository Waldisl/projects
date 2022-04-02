#include "Karen.hpp"

Karen::Karen() 
{
}

Karen::~Karen()
{
}

void Karen::warning(void)
{
	std::cout << "WARNING: " << "I think I deserve to have some extra bacon for free. "
	<< "I’ve been coming here for years and you just started working here last month." << std::endl;
}

void Karen::debug(void)
{
	std::cout << "DEBUG:" << '\t' << "I love to get extra bacon for my 7XL-double-cheese-triple-"
	<< "pickle-special-ketchup burger. I just love it!" << std::endl;
}

void Karen::error(void)
{
	std::cout << "ERROR:" << '\t' << "This is unacceptable, I want to speak to the manager now." << std::endl;
}

void Karen::info(void)
{
	std::cout << "INFO:" << '\t' << "I cannot believe adding extra bacon cost more money. "
	<< "You don’t put enough! If you did I would not have to ask for it!" << std::endl;
}

void Karen::complain(std::string level)
{

	std::string str[] = {"warning", "debug", "error", "info"};
	void	(Karen::*arr_func[])(void) =
	{&Karen::warning, &Karen::debug, &Karen::error, &Karen::info};
	for (size_t i = 0; i < 4; i++)
	{
		if (level == str[i])
			(this->*arr_func[i])();
	}
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