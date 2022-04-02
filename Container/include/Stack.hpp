#pragma once

#include "Vector.hpp"

namespace ft 
{
	template < class T, class container_type = vector< T > > 
	class stack
	{
		public:
				typedef std::size_t size_type;

				explicit stack(const container_type& container = container_type()) : _c(container) {} //explicit избежать неявного контейнера

				stack(const stack< T, container_type >& cont) : _c(cont._c) {}

				const stack< T, container_type >& operator=(const stack< T, container_type >& other)
				{
					if (this != &other)
						_c = other._c;
					return *this;
				}
				virtual ~stack() {}

				bool empty() const { return _c.empty(); } //пусто или нет

				size_type size() const { return _c.size(); } //размер стека

				T& top() { return _c.back(); } //верхний элемент

				const T& top() const { return _c._back(); } //верхний элемент(если пользовательский тип)

				void push(const T& val) { _c.push_back(val); } //добавить элемент

				void pop() { _c.pop_back(); } //удалить элемент

				template < class A, class B >
				friend bool operator==(const stack< A, B >& lhs, const stack< A, B >& rhs);

				template < class A, class B >
				friend bool operator!=(const stack< A, B >& lhs, const stack< A, B >& rhs);

				template < class A, class B >
				friend bool operator<(const stack< A, B >& lhs, const stack< A, B >& rhs);

				template < class A, class B >
				friend bool operator<=(const stack< A, B >& lhs, const stack< A, B >& rhs);

				template < class A, class B >
				friend bool operator>(const stack< A, B >& lhs, const stack< A, B >& rhs);

				template < class A, class B >
				friend bool operator>=(const stack< A, B >& lhs, const stack< A, B >& rhs);
				//A = T, B = container_type
				// операторы являются функциями-членами, а функция-член принимает неявный первый параметр,
				// а это означает, что мои операторы теперь принимают три параметра, и это может быть исправлено как функция, не являющаяся членом.(friend)

		private:
				container_type _c;
};

template < class A, class B >
bool operator==(const stack< A, B >& lhs, const stack< A, B >& rhs) {return (lhs._c == rhs._c);}

template < class A, class B >
bool operator!=(const stack< A, B >& lhs, const stack< A, B >& rhs) {return !(lhs == rhs);}

template < class A, class B >
bool operator<(const stack< A, B >& lhs, const stack< A, B >& rhs) {return (lhs._c < rhs._c);}

template < class A, class B >
bool operator<=(const stack< A, B >& lhs, const stack< A, B >& rhs) {return !(lhs > rhs);}

template < class A, class B >
bool operator>(const stack< A, B >& lhs, const stack< A, B >& rhs) {return rhs < lhs;}

template < class A, class B >
bool operator>=(const stack< A, B >& lhs, const stack< A, B >& rhs) {return !(lhs < rhs);}
}
