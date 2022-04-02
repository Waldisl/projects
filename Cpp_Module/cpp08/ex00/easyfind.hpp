#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
// #include <string>

template<typename T, typename T1>
typename T::iterator	easyfind(T & cont, T1 & element)
{
	typename T::iterator begin = cont.begin();
	typename T::iterator end = cont.end();

	while (begin != end)
	{
		if (*begin == element)
			return begin;
		begin++;
	}
	// throw std::string("\tError: Notfound ");
	return end;
}

	// begin = std::find(begin, end, element);
	// if (begin != end)
	// 	return begin;
	// return end;