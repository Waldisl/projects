#include <iostream>

int main (int ac, char **av)
{
	int	i = 1;
	int k = 0;

	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	else
	{
		while (i < ac)
		{
			while (av[i][k])
			{
				if (av[i][k] >= 97 && av[i][k] <= 122)
					std::cout << (char)(av[i][k] - 32);
				else
					std::cout << av[i][k];
				k++;
			}
			k = 0;
			i++;
		}
		std::cout << std::endl;
	}
	return (0);
}