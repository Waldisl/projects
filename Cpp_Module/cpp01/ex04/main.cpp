#include "ClassReplace.hpp"

int	main(int argc, char **argv)
{
	if (argc == 4)
		Replace::replace(argv[1], argv[2], argv[3]);
	else
	{
		std::cerr << "Error: " << argc - 1 
		<< " arguments entered."<< std::endl;
		std::cout << "Enter filename, s1, s2." << std::endl;
	}
	return (0);
}