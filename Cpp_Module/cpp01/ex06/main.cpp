#include "Karen.hpp"

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		Karen a;
		a.filter(av[1]);
	}
	else 
	{
		std::cerr << "Error: " << ac - 1 << " arguments entered."<< std::endl;
		std::cout << "Enter DUBUG, INFO, WARNING or ERROR." << std::endl;
	}
	return 0;
}