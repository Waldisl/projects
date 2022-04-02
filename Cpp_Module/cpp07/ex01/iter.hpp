#pragma once

using std::exception;
using std::cout;
using std::endl;
using std::string;

template<typename T>
void iter(T *array, size_t len, void (*function)(T const &iter))
{
	if (!array || !len || !function)
		return ;
	for (size_t i = 0; i < len; i++)
		(*function)(array[i]);
}

template<typename T>
void print(T const &arr) { cout << "\tArray element: " << arr << endl; }