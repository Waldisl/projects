#include "Mutantstack.hpp"


template <typename T>
MutantStack<T>::MutantStack(const MutantStack<T> & second) : stack<T>(second) 
{
}

template <typename T>
MutantStack<T> & MutantStack<T>:: operator=(const MutantStack<T> & second)
	{
		this->c = second.c;
		return *this;
	}