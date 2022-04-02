#pragma once
#include <iostream>

class Fixed
{
	private:
		int fix_point = 0;
		static const int bit = 8;

	public:
		Fixed();
		Fixed(Fixed const &second);
		Fixed	&operator=(Fixed const &second);
		~Fixed();

		int		getRawBits(void) const;
		void	setRawBits(int const raw);

};
