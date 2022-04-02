#pragma once

#include "Traits.hpp"


namespace ft
{
	template < class Iterator >
	class reverse_iterator
	{
		protected:
			Iterator _it;
			typedef iterator_traits< Iterator > traits;

		public:
			typedef Iterator							iterator_type;
			typedef typename traits::iterator_category	iterator_category;
			typedef typename traits::value_type			value_type;
			typedef typename traits::difference_type	difference_type;
			typedef typename traits::reference			reference;
			typedef typename traits::pointer			pointer;

			reverse_iterator() : _it(Iterator()) {}

			explicit reverse_iterator(iterator_type it) : _it(it) {}

			reverse_iterator(const reverse_iterator& it) : _it(it._it) {}

			template < typename T >
			reverse_iterator(const reverse_iterator< T >& it) : _it(it.base()) {}

			iterator_type base() const { return _it; }

			reference operator*() const
			{
				Iterator tmp = _it;
				return *(--tmp);
			}

			pointer operator->() const
			{
				Iterator tmp = _it;
				--tmp;
				return to_pointer(tmp);
			}

			reverse_iterator& operator++()
			{
				--_it;
				return *this;
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				--_it;
				return tmp;
			}

			reverse_iterator& operator--()
			{
				++_it;
				return *this;
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				++_it;
				return tmp;
			}

			reverse_iterator operator+(difference_type n) const {return reverse_iterator(_it - n);}

			reverse_iterator& operator+=(difference_type n) 
			{
				_it -= n;
				return *this;
			}

			reverse_iterator operator-(difference_type n) const {return reverse_iterator(_it + n);}

			reverse_iterator& operator-=(difference_type n)
			{
				_it += n;
				return *this;
			}

			reference operator[](difference_type n) const { return *(*this + n); }

		private:
			template < typename T > static T* to_pointer(T* p) { return p; }

			template < typename T > static pointer to_pointer(T t) {return t.operator->();}
};

	template < typename IteratorL, typename IteratorR >
	bool operator==(const reverse_iterator< IteratorL >& lhs, const reverse_iterator< IteratorR >& rhs)
	{return lhs.base() == rhs.base();}

	template < typename IteratorL, typename IteratorR >
	bool operator<(const reverse_iterator< IteratorL >& lhs, const reverse_iterator< IteratorR >& rhs)
	{return rhs.base() < lhs.base();}

	template < typename IteratorL, typename IteratorR >
	bool operator!=(const reverse_iterator< IteratorL >& lhs, const reverse_iterator< IteratorR >& rhs)
	{return !(lhs == rhs);}

	template < typename IteratorL, typename IteratorR >
	bool operator>(const reverse_iterator< IteratorL >& lhs, const reverse_iterator< IteratorR >& rhs)
	{return rhs < lhs;}

	template < typename IteratorL, typename IteratorR >
	bool operator<=(const reverse_iterator< IteratorL >& lhs, const reverse_iterator< IteratorR >& rhs)
	{return !(rhs < lhs);}

	template < typename IteratorL, typename IteratorR >
	bool operator>=(const reverse_iterator< IteratorL >& lhs, const reverse_iterator< IteratorR >& rhs)
	{return !(lhs < rhs);}
}
