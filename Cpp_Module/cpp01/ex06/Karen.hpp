#pragma once 
#include <iostream>

class Karen
{
	public:
		Karen();
		~Karen();
		void complain(std::string level);
		void filter(std::string level);
		void filter_switch(void);
	private:
		void warning(void);
		void debug(void);
		void error(void);
		void info(void);
		int _num;
};