#pragma once

#include "Equal.hpp"
#include "Lexicographical_compare.hpp"
#include "Reverse_iterator.hpp"
#include "Standard_iterator.hpp"
#include <cmath>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <stdexcept>

namespace ft 
{
	template < class T, class Alloc = std::allocator< T > > 
	class vector 
	{
		public:
				typedef T&				reference;
				typedef const T&		const_reference;
				typedef T*				pointer;
				typedef const T*		const_pointer;
				typedef std::size_t		size_type;

				typedef standard_iterator< pointer, vector >		iterator;
				typedef standard_iterator< const_pointer, vector >	const_iterator;
				typedef reverse_iterator< const_iterator >			const_reverse_iterator;
				typedef reverse_iterator< iterator >				reverse_iterator;

		protected:
				Alloc		_alloc;
				size_type	_size;
				size_type	_capacity;
				pointer		_c;

		public:
				explicit vector(const Alloc& alloc = Alloc());
				explicit vector(size_type n, const T& v = T(), const Alloc& alloc = Alloc());
				vector(const vector< T, Alloc >& other);
				vector(iterator first, iterator last, const Alloc& alloc = Alloc());

				virtual ~vector();

				vector< T, Alloc >& operator=(const vector< T, Alloc >& other);

				// Iterators
				iterator				begin() {return iterator(_c);}; //начало массива
				const_iterator			begin() const {return const_iterator(_c);};
				iterator				end() {return iterator(_c + _size);}; //конец массива
				const_iterator			end() const {return const_iterator(_c + _size);};
				reverse_iterator		rbegin() {return reverse_iterator(end());}
				const_reverse_iterator	rbegin() const {return const_reverse_iterator(end());}
				reverse_iterator		rend() {return reverse_iterator(begin());}
				const_reverse_iterator	rend() const {return const_reverse_iterator(begin());}

				// Capacity
				size_type	size() const {return _size ;} //размер
				size_type	max_size() const {return _alloc.max_size();}; //макс размер
				size_type	capacity() const {return _capacity;}; //размер емкости хранилища
				bool		empty() const {return _size ? false : true;}; //пустой или нет
				void		resize(size_type n, T val = T());
				void		reserve(size_type n);

				// Element Access
				reference		operator[](const size_type i) {return _c[i];}; //доступ к i элементу
				const_reference	operator[](const size_type i) const {return _c[i];};
				reference		front() {return _c[0];}; //доступ к 1 элементу
				const_reference	front() const {return _c[0];};
				reference		back() {return _c[_size - 1];}; //доступ к последнему элементу
				const_reference	back() const {return _c[_size - 1];};
				reference		at(size_type n) //доступ к n элементу с проврекой на муссор
				{
					std::stringstream ss;
					ss << "vector::_M_range_check: __n (which is " << n << ") >= this->size() (which is " << _size << ")";
					if (n >= _size)
						throw std::out_of_range(ss.rdbuf()->str());
					return _c[n];
				};
				const_reference at(size_type n) const
				{
					std::stringstream ss;
					ss << "vector::_M_range_check: __n (which is " << n << ") >= this->size() (which is " << _size << ")";
					if (n >= _size)
						throw std::out_of_range(ss.rdbuf()->str());
					return _c[n];
				};

				// Modifiers
				void assign(iterator first, iterator last);
				void assign(size_type n, const T& val);
				void push_back(const T& val);
				void pop_back();

				iterator insert(iterator position, const T& val);
				void     insert(iterator position, size_type n, const T& val);
				void     insert(iterator position, iterator first, iterator last);
				iterator erase(iterator position);
				iterator erase(iterator first, iterator last);
				void     swap(vector& x);
				void     clear();

				Alloc get_allocator() const {return _alloc;}; 
	};

/******************** Ctors & Dtors *******************************************/
/*Создает пустой контейнер без элементов.*/
	template < class T, class Alloc >
	vector< T, Alloc >::vector(const Alloc& alloc)
	{
		_alloc = alloc;
		_size = 0;
		_capacity = 0;
		_c = NULL;
	}
/*Создает контейнер с n элементами. Каждый элемент является копией val .*/
	template < class T, class Alloc >
	vector< T, Alloc >::vector(size_type n, const T& v, const Alloc& alloc)
	{
		_alloc = alloc;
		_size = n;
		_capacity = n;
		_c = _alloc.allocate(_capacity);
		for (size_type i = 0; i < _capacity; i++) 
		{
			_alloc.construct(&_c[i], v);
		}
	}
/*Создает контейнер с копией каждого из элементов x в том же порядке.*/
	template < class T, class Alloc >
	vector< T, Alloc >::vector(const vector< T, Alloc >& other)
	{
		_alloc = other.get_allocator();
		_size = 0;
		_capacity = 0;
		_c = NULL;
		*this = other;
	}
/*Создает контейнер с количеством элементов, равным диапазону [first,last) , 
причем каждый элемент создается из соответствующего элемента в этом диапазоне в том же порядке.*/
	template < class T, class Alloc >
	vector< T, Alloc >::vector(iterator first, iterator last, const Alloc& alloc) 
	{
		_alloc = alloc;
		_size = 0;
		_capacity = last - first;
		_c = NULL;
		this->assign(first, last);
	}
/*Это уничтожает все элементы контейнера и освобождает всю емкость хранилища , выделенную вектором с помощью его распределителя .*/
	template < class T, class Alloc > 
	vector< T, Alloc >::~vector()
	{
		this->clear();
		_alloc.deallocate(_c, _capacity);
	}

/************************ Operators *******************************************/
	template < class T, class Alloc >
	vector< T, Alloc >& vector< T, Alloc >::operator=(const vector< T, Alloc >& other)
	{
		if (_c)
		{
			this->clear();
			_alloc.deallocate(_c, _capacity);
		}
		_size = other.size();
		_capacity = other.capacity();
		_c = _alloc.allocate(_capacity);
		for (size_type i = 0; i < _capacity; i++)
		{
			_alloc.construct(&_c[i], other[i]); //Создает объект элемента в месте, указанном _c(для того чтобы объект в который присваимаем был в месте присваимого)
		}
		return *this;
	}

/**************** Capacity ****************************************************/
	template < class T, class Alloc >
	void vector< T, Alloc >::resize(size_type n, T val) //Изменяет размер контейнера так, чтобы он содержал n элементов (если больше чем раньше вставляем val) 
	{
		if (n < _size) 
		{
			for (size_type i = _size; i > n; i--) 
			{
				this->pop_back();
			}
		} 
		else if (n > _size) 
		{
			for (size_type i = _size; i < n; i++)
			{
				this->push_back(val);
			}
		}
	}

	template < class T, class Alloc >
	void vector< T, Alloc >::reserve(size_type n) //запрос на увеличение емкости
	{
		if (n > max_size())
			{throw std::length_error("vector::reserve");}
		else if (n <= _capacity)
			{return;} 
		else 
		{
			pointer tmp = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++) 
			{
				_alloc.construct(&tmp[i], _c[i]);
			}
			if (_c) 
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_c[i]); //удаляем объект элемента
				_alloc.deallocate(_c, _capacity);
			}
			_c = tmp;
			_capacity = n;
		}
	}

/**************** Modifiers ***************************************************/

	
	template < class T, class Alloc >
	void vector< T, Alloc >::assign(iterator first, iterator last) //заполняет вектор элементали от first до last(массив уже должен существовать)
	{
		if (_c == NULL) 
		{_c = _alloc.allocate(_capacity);} 
		else 
		{ this->clear();}
	for (; first != last; ++first) 
	{this->push_back(*first);}
	}

	template < class T, class Alloc >
	void vector< T, Alloc >::assign(size_type n, const T& val) //новое содержимое представляет собой n элементов, каждый из которых инициализирован копией val 
	{
		this->clear();
		for (size_type i = 0; i < n; i++) 
		{this->push_back(val);}
	}

	template < class T, class Alloc >
	void vector< T, Alloc >::push_back(const T& val) //добавляет элемент в конец вектора
	{
		
		if (_size == _capacity) 
		{
			if (_size == 0)
			{
				this->reserve(2);
			} 
			else 
			{
				this->reserve(_size * 2);
			}
		}
		_alloc.construct(&_c[_size], val);
		_size++;
	}

	template < class T, class Alloc > 
	void vector< T, Alloc >::pop_back() //удаляет последный элемент
	{
		if (_size)
		{
			_alloc.destroy(&_c[_size - 1]);
			_size--;
		}
	}

	template < class T, class Alloc >
	typename vector< T, Alloc >::iterator vector< T, Alloc >::insert(iterator position, const T& val) //Вектор расширяется путем вставки нового элемента(val) перед элементом в указанной позиции(position)
	{
		size_type n = position - this->begin();
		insert(position, 1, val);
		return iterator(&_c[n]);
	}

	template < class T, class Alloc >
	void vector< T, Alloc >::insert(iterator position, size_type n, const T& val) //Вектор расширяется путем вставки новых элементов(val) перед элементом в указанной позиции(position) кол-во элементов (n)
	{
		vector< T, Alloc > tmp(position, this->end());
		_size -= (this->end() - position);
		for (size_type i = 0; i < n; i++)
			{this->push_back(val);}
		for (iterator it = tmp.begin(); it != tmp.end(); ++it)
			{this->push_back(*it);}
	}

	template < class T, class Alloc >
	void vector< T, Alloc >::insert(iterator position, iterator first, iterator last) //Вектор расширяется путем вставки диапазона новых элементов перед элементом в указанной позиции
	{
		vector< T, Alloc > tmp(position, this->end());
		_size -= (this->end() - position);
		for (iterator it = first; it != last; ++it)
			{this->push_back(*it);}
		for (iterator it = tmp.begin(); it != tmp.end(); ++it)
			{this->push_back(*it);}
	}

	template < class T, class Alloc >
	typename vector< T, Alloc >::iterator vector< T, Alloc >::erase(iterator position) //Удаляет из вектора либо один элемент ( position )
	{
		for (iterator it = position; it != this->end(); ++it)
			{*it = *(it + 1);}
		_size--;
		return (position);
	}

	template < class T, class Alloc >
	typename vector< T, Alloc >::iterator vector< T, Alloc >::erase(iterator first, iterator last) //либо диапазон элементов ( [first,last) )
	{
		iterator tmp(last);
		while (last != this->end())
		{
			*first = *last;
			++first;
			++last;
		}
		this->_size -= (last - first);
		return (tmp);
	}

	// template < class T, class Alloc >
	// void vector< T, Alloc >::swap(vector& other) { std::swap(_c, other._c);}
	template < class T, class Alloc >
	void vector< T, Alloc >::swap(vector& other)
	{//Заменяет содержимое контейнера содержимым x , который является другим векторным объектом того же типа. Размеры могут отличаться.
		if (this == &other)
			return ;
		if (get_allocator() != other.get_allocator())
			throw std::runtime_error("this->_alloc != other._alloc");
		std::swap(this->_c, other._c);
		std::swap(this->_size, other._size);
		std::swap(this->_capacity, other._capacity);
	}

	template < class T, class Alloc > 
	void vector< T, Alloc >::clear() //Удаляет все элементы из вектора (которые уничтожаются), оставляя контейнер с размером 0 .
	{
		for (size_type i = 0; i < _size; i++)
			{_alloc.destroy(&_c[i]);}
		_size = 0;
	}

/**************** Relational operators ****************************************/

	template < class T, class Alloc >
	bool operator==(const vector< T, Alloc >& lhs, const vector< T, Alloc >& other)
	{return lhs.size() == other.size() && ft::equal(lhs.begin(), lhs.end(), other.begin());}

	template < class T, class Alloc >
	bool operator!=(const vector< T, Alloc >& lhs, const vector< T, Alloc >& other)
	{return !(lhs == other);}

	template < class T, class Alloc >
	bool operator<(const vector< T, Alloc >& lhs, const vector< T, Alloc >& other)
	{return ft::lexicographical_compare(lhs.begin(), lhs.end(), other.begin(), other.end());}

	template < class T, class Alloc >
	bool operator<=(const vector< T, Alloc >& lhs, const vector< T, Alloc >& other)
	{return !(lhs > other);}

	template < class T, class Alloc >
	bool operator>(const vector< T, Alloc >& lhs, const vector< T, Alloc >& other)
	{return other < lhs;}

	template < class T, class Alloc >
	bool operator>=(const vector< T, Alloc >& lhs, const vector< T, Alloc >& other)
	{return !(lhs < other);}

/**************** Non member functions ****************************************/

	template < class T, class Alloc >
	void swap(vector< T, Alloc >& x, vector< T, Alloc >& y) //Содержимое контейнера x заменяется содержимым контейнера y . Оба объекта-контейнера должны быть одного типа (одинаковые параметры шаблона), хотя размеры могут различаться.
	{x.swap(y);}

}

