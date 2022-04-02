#include "ClassReplace.hpp"

Replace::Replace()
{
}

Replace::~Replace()
{
}

int		Replace::Error(std::string error)
{
	std::cerr << "Error: " << error << std::endl;
	return EXIT_FAILURE;
}

std::string Replace::replace2(std::string const str, std::string const s1, std::string const s2)
{
	std::stringstream str_out;
	size_t g;

	for (size_t i = 0; i < str.length(); i++)
	{
		g = 0;
		while (str[i + g] == s1[g] && g < s1.length())
			g++;
		if (g == s1.length())
		{
			str_out << s2;
			i += (g - 1);
		}
		else
			str_out << str[i];
	}
	return (str_out.str());
}

int Replace::replace(std::string const filename, std::string const s1, std::string const s2)
{
	std::ifstream file_in;
	std::ofstream file_out;
	std::string str;

	if (filename.length() == 0)
		return Error("Argument filename is empty.");
	else if (s1.length() == 0)
		return Error("Argument s1 is empty.");
	else if (s2.length() == 0)
		return Error("Argument s2 is empty.");
	file_in.open(filename);
	if (!file_in.is_open())
		return Error("no input file.");
	file_out.open(filename + ".replace", std::ios_base::trunc);
	if (!file_out.is_open())
		return Error("no output file.");
	while (std::getline(file_in, str))
	{
		if (!file_in.eof())
			str += "\n";
		file_out << Replace::replace2(str, s1, s2);
	}
	file_in.close();
	file_out.close();
	return 0;
}
