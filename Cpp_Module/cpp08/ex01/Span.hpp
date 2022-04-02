#pragma once
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;

class Span
{
	private:
		vector<int> _arr;
		unsigned int _len;

	public:
		Span(unsigned int len);
		Span(const Span& second);
		Span & operator=(const Span& second);
		~Span(void);

		void		addNumber(int num);
		size_t		shortestSpan(void);
		size_t		longestSpan(void);
		template <typename T> void	addNumber(T begin, T end)
		{
			for (; begin != end; ++begin)
			{
				if (this->_arr.size() == _len)
					throw string("Error: length");
				_arr.push_back(*begin);
			}
		}
};
