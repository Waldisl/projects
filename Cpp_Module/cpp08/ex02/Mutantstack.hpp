#pragma once
#include <iostream>
#include <stack>
// #include <vector>
// #include <iterator>
// using std::vector;
using std::cout;
using std::endl;
using std::deque;
using std::string;
using std::stack;

template<typename T>
class MutantStack : public stack<T>
{
public:

	MutantStack(void) {}
	MutantStack(const MutantStack<T> & second);
	MutantStack<T> & operator=(const MutantStack<T> & second);
	virtual ~MutantStack(void) {}


	typedef typename deque<T>::iterator iterator;
	typedef typename deque<T>::const_iterator citer;
	typedef typename deque<T>::reverse_iterator riter;
	typedef typename deque<T>::const_reverse_iterator criter;

	iterator	begin(void) { return this->c.begin();}
	iterator	end(void) { return this->c.end(); }
	citer		begin(void) const { return this->c.begin();}
	citer		end(void) const { return this->c.end(); }
	riter		rbegin(void) { return this->c.rbegin();}
	riter		rend(void) { return this->c.rend(); }
	criter		rbegin(void) const { return this->c.rbegin();}
	criter		rend(void) const { return this->c.rend(); }
};

// template<typename T>
// class MutantStack : public stack<T, vector<T> >
// {
// public:

// 	MutantStack(void) {}
// 	MutantStack(const MutantStack<T> & second);
// 	MutantStack<T> & operator=(const MutantStack<T> & second);
// 	virtual ~MutantStack(void) {}


// 	typedef typename vector<T>::iterator iterator;
// 	typedef typename vector<T>::const_iterator citer;
// 	typedef typename vector<T>::reverse_iterator riter;
// 	typedef typename vector<T>::const_reverse_iterator criter;

// 	iterator	begin(void) { return this->c.begin();}
// 	iterator	end(void) { return this->c.end(); }
// 	citer		begin(void) const { return this->c.begin();}
// 	citer		end(void) const { return this->c.end(); }
// 	riter		rbegin(void) { return this->c.rbegin();}
// 	riter		rend(void) { return this->c.rend(); }
// 	criter		rbegin(void) const { return this->c.rbegin();}
// 	criter		rend(void) const { return this->c.rend(); }
// };