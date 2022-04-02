#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

class Replace
{
	public:
		Replace();
		~Replace();
		static int replace(std::string const filename, std::string const s1, std::string const s2);
	private:
		static int	Error(std::string error);
		static std::string replace2(std::string const str, std::string const s1, std::string const s2);
};
