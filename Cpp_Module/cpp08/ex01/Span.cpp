#include "Span.hpp"
#include <algorithm>

Span::Span(unsigned int len) : _arr(), _len(len) {}

Span::Span(const Span& second) : _arr(second._arr), _len(second._len) {}

Span & Span::operator=(const Span& second)
{
	this->_arr = second._arr;
	this->_len = second._len;
	return *this;
}

Span::~Span(void) {}


void	Span::addNumber(int num)
{
	if (this->_arr.size() == this->_len)
		throw string("Error: length");
	_arr.push_back(num);
}

size_t		Span::shortestSpan(void)
{
	if (this->_arr.size() == 0 || this->_arr.size() == 1)
		throw string("Error: range");
	vector<int> temp(_arr);
	std::sort(temp.begin(), temp.end());
	vector<int>::iterator begin = temp.begin();
	vector<int>::iterator end = temp.end();
	size_t	min = static_cast<size_t>(*(begin + 1)) - *begin;
	while (begin + 1 != end)
	{
		if (static_cast<size_t>(*(begin + 1)) - *(begin) < min)
			min = *(begin + 1) - *(begin);
		++begin;
	}
	return min;
}

size_t	Span::longestSpan(void)
{
	if (this->_arr.size() == 0 || this->_arr.size() == 1)
		throw string("Error: range");
	vector<int> temp(_arr);
	std::sort(temp.begin(), temp.end());
	vector<int>::iterator begin = temp.begin();
	vector<int>::iterator end = temp.end();
	return static_cast<size_t>(*(end - 1)) - *(begin);
}
