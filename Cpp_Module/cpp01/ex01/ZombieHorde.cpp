#include "Zombie.hpp"

Zombie *zombieHorde(int N, std::string name)
{
	if (N > 0)
	{
		Zombie *Zombie_N = new Zombie[N];
		for (int i = 0; i < N; i++)
		{
			std::string name_z = name + " " + std::to_string(i + 1);
			Zombie_N[i].SetName(name_z);
		}
		return Zombie_N;
	}
	else
		return NULL;
}