#pragma once
#include <cstdlib>

using std::exception;
using std::cout;
using std::endl;
using std::string;

template<typename T>
class Array
{
	private:
		unsigned int	len;
		T				*arr;

	public:
		Array() : len(0), arr(NULL) {}
		Array(unsigned int n) : len(n), arr(new T[n]()) {}
		
		Array& operator=(Array<T> const &second)
		{
			if (this->len > 0)
				delete[] this->arr;
			if (second.len > 0)
			{
				this->arr = new T[second.len]();
				for (unsigned int i = 0; i < second.len; i++)
					this->arr[i] = second.arr[i];
				this->len = second.len;
			}
			else
			{
				this->len = 0;
				this->arr = NULL;
			}
			return *this;
		}

		Array(Array<T> const &second)
		{
			if (second.len > 0)
			{
				this->arr = new T[second.len]();
				for (unsigned int i = 0; i < second.len; i++)
					this->arr[i] = second.arr[i];
				this->len = second.len;
			}
			else
			{
				this->len = 0;
				this->arr = NULL;
			}
		}

		~Array()
		{
			if (this->len > 0)
				delete[] this->arr;
		}

		T &operator[](unsigned int i)
		{
			if (i >= this->len)
				throw IError();
			return this->arr[i];
		}

		unsigned int size() const { return this->len; }

		class IError: public exception
		{
			public:
				virtual const char* what() const throw() { return "Error : idnex."; }
		};
};
