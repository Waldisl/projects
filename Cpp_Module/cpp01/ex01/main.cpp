#include "Zombie.hpp"

int main(void)
{
	int N = 30;
	
	Zombie *Horda = zombieHorde(N, "Zombie");
	if (Horda == NULL)
		return 1;
	for (int i = 0; i < N; i++)
		Horda[i].announce();
	delete[] Horda;
	return 0;
}