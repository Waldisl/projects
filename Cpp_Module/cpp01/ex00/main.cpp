#include "Zombie.hpp"

int main() 
{
	Zombie *zombie_Ivan(newZombie("Ivan"));
	zombie_Ivan->announce();
	Zombie zombie_James("James");
	zombie_James.announce();
	randomChump("Oleg");
	randomChump("Kevin");
	randomChump("Mark");
	delete zombie_Ivan;
	return 0;
}