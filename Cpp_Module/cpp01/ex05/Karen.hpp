#pragma once 
#include <iostream>

class Karen
{
	public:
		Karen();
		~Karen();
		void complain(std::string level);
	private:
		void warning(void);
		void debug(void);
		void error(void);
		void info(void);
};