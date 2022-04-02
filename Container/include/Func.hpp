#pragma once

#include "Map.hpp"
#include "Stack.hpp"
#include "Vector.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <vector>

//Определить пространство имен во время компиляции
#ifndef FT
#define FT std
#endif

using std::string;
using std::cout;
using std::endl;

const string CLR = "\033[0m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BOLDWHITE = "\033[1m\033[37m\033[31m";

template < typename T >
void print_vector(FT::vector< T >& vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (i == 0)
			cout << GREEN + "[";
		cout << vec[i];
		if (i != vec.size() - 1)
			cout << ", ";
		else
			cout << "]" + CLR << endl;
	}
}

template < typename T, typename C >
void print_stack(FT::stack< T, C > st)
{
	for (size_t i = 0; st.size(); i++)
	{
		if (i == 0)
			cout << GREEN + " Last In <-[";
		T item = st.top();
		cout << item;
		if (st.size() != 1)
			cout << ", ";
		else
			cout << "]<- First In" + CLR << endl;
		st.pop();
	}
}

template < typename T >
void print_stack(FT::stack< T > st)
{
	for (size_t i = 0; st.size(); i++)
	{
		if (i == 0)
			cout << GREEN + " Last In <-[";
		T item = st.top();
		cout << item;
		if (st.size() != 1)
			cout << ", ";
		else
			cout << "]<- First In" + CLR << endl;
		st.pop();
	}
}

double chrono(void (*f)(), string const& str)
{
	clock_t t;
	t = clock();
	f();
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC;
	cout << GREEN << str << " time =  " << time_taken * 1000 << " ms"<< CLR << endl;
	return time_taken;
}

void perf_vector_insert()
{
	FT::vector< int > nblist;
	for (int i = 0; i < 10000; i++)
	{
		nblist.insert(nblist.end(), i);
	}
}

void perf_vector_push_back()
{
	FT::vector< int > nblist;
	for (int i = 0; i < 10000; i++)
	{
		nblist.push_back(i);
	}
}

void perf_vector_clear()
{
	FT::vector< int > nblist;
	for (int i = 0; i < 10000; i++)
	{
		nblist.push_back(i);
	}
	nblist.clear();
}

void perf_map_insert()
{
	FT::map< int, int > nbmap;
	for (int i = 0; i < 10000; i++)
	{
		nbmap.insert(FT::pair< int, int >(i, i + 1));
	}
}

void perf_map_clear()
{
	FT::map< int, int > nbmap;
	for (int i = 0; i < 10000; i++)
	{
		nbmap.insert(FT::pair< int, int >(i, i + 1));
	}
	nbmap.clear();
}

// template<class Key, class Compare, class Alloc>
// void    print_set(ft::set<Key, Compare, Alloc> s, string name_set)
// {
// 	cout << "print " << name_set << ": ";
// 	if (s.size() == 0)
// 	{
// 		cout << "<null>" << endl;
// 		return ;
// 	}
// 	bool	is_first = true;
// 	for (typename ft::set<Key, Compare, Alloc>::const_iterator it = s.begin(); it != s.end(); it++)
// 	{
// 		if (!is_first)
// 			cout << ", ";
// 		else
// 			is_first = false;
// 		cout << "{" << *it << "}";
// 	}
// 	cout << endl;
// }