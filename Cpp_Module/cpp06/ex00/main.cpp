#include "Scalar.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		cout << "Error : argument not 2" << endl;
	}
	else
	{
		bool	flag_c = 0;
		bool	flag_n = 0;
		double	temp;
		char 	*c_str;
		string str = string(av[1]);
		Scalar Scalar;
		
		if (str.length() == 1 && !std::isdigit(str[0]))
		{
			flag_c = true;
		}
		else if (std::isdigit(str[0]) || ((str[0] == '-' || str[0] == '+') && std::isdigit(str[1])) || \
				(str == "nan" || str == "nanf" || str == "inf" || str == "-inff" || str == "+inff" || str == "+inf" || str == "-inf"))
		{
			temp = strtod(av[1], &c_str);
			if (!((c_str[0] != 'f' && c_str[0] != '\0') || (c_str[0] == 'f' && c_str[1] != '\0') || \
					(c_str[0] == '.' && c_str[1] == 'f' && c_str[2] != '\0')))
			{
				flag_n =true;
			}
		}
		
		if (!flag_c && !flag_n)
		{
			cout << "Error : bad argument" << endl;
		}
		else
		{
			if (flag_c)
				temp = static_cast<double>(str[0]);
			
			try
			{
				char c = Scalar.char_convert(temp);
				cout << "char :\t'" << c << "'" << endl;
			}
			catch (string &ex)
			{
				cout << "char :\t" << ex << endl;
			}

			try
			{
				int i = Scalar.int_convert(temp);
				cout << "int :\t" << i << endl;
			}
			catch (string &ex)
			{
				cout << "int :\t" << ex << endl;
			}

			float fl = Scalar.float_convert(temp);
			if (fl - static_cast<int>(fl) == 0)
				cout << "float :\t" << fl << ".0f" << endl;
			else
				cout << "float :\t" << fl << "f" << endl;

			double db = Scalar.double_convert(temp);
			if (db - static_cast<int>(db) == 0)
				cout << "double : " << db << ".0" << endl;
			else
				cout << "double : " << db << endl;
		}
	}
	return (0);
}