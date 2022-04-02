#pragma once

#include "Equal.hpp"
#include "Lexicographical_compare.hpp"
#include "Map_iterator.hpp"
#include "Pair.hpp"
#include "RB_Tree.hpp"
#include "Reverse_map_iterator.hpp"
#include "Stack.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>

namespace ft
{
	template <  typename Key, typename T, typename Compare = std::less< Key >, typename Alloc = std::allocator< ft::pair< const Key, T > > >
	class map
	{
		public:
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair< const key_type, mapped_type >	value_type;
			typedef Compare									key_compare;
			typedef Alloc									allocator_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef value_type*								pointer;
			typedef const value_type*						const_pointer;
			typedef std::ptrdiff_t							difference_type;
			typedef std::size_t								size_type;

		class value_compare
		{
			friend class map;

			protected:
				Compare comp;
				value_compare(Compare c) : comp(c) {}
			public:
				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;
				bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first);}
		};

		private:
			typedef typename RBTree< key_type, mapped_type, Alloc, value_type >::Node	node;
			typedef typename RBTree< key_type, mapped_type, Alloc, value_type >::Node*	node_pointer;
			RBTree< key_type, mapped_type, Alloc, value_type >							tree;
			size_type																	_size;
			key_compare																	_comp;
			allocator_type																_alloc;

			bool is_key_equal(const value_type& k1, const value_type& k2) const // сравнение элемнетов в lower_bound
			{
				value_compare value_comp(_comp);
				return !value_comp(k1, k2) && !value_comp(k2, k1);
			}

		public:
			typedef map_iterator< pointer, node_pointer, map >					iterator;
			typedef map_iterator< const_pointer, node_pointer, map >			const_iterator;
			typedef reverse_map_iterator< const_pointer, node_pointer, map >	const_reverse_iterator;
			typedef reverse_map_iterator< pointer, node_pointer, map >			reverse_iterator;

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: tree(), _size(0), _comp(comp), _alloc(alloc) {}

			template < class InputIterator >
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : tree(), _size(0), _comp(comp), _alloc(alloc) 
			{insert(first, last);}

			map(const map& rhs) { *this = rhs; };

			~map() {}

			map& operator=(map const& rhs)
			{
				if (this != &rhs)
				{
					tree = rhs.tree;
					_alloc = rhs._alloc;
					_comp = rhs._comp;
					_size = rhs._size;
				}
				return *this;
			}

			mapped_type& operator[](key_type const& k)
			{
				ft::pair< iterator, bool > tmp = insert(ft::make_pair(k, T()));
				return tmp.first.base()->_data->second;
			}

			iterator begin()
			{
				node_pointer node = tree.min_node(tree.root);
				return iterator(node);
			}

			const_iterator begin() const
			{
				node_pointer node = tree.min_node(tree.root);
				return const_iterator(node);
			};

			iterator end() { return iterator(tree.NIL); }
			const_iterator end() const { return const_iterator(tree.NIL); }

			reverse_iterator rbegin()
			{
				node_pointer node = tree.max_node(tree.root);
				return reverse_iterator(node);
			}

			const_reverse_iterator rbegin() const
			{
				node_pointer node = tree.min_node(tree.root);
				return const_reverse_iterator(node);
			}

			reverse_iterator rend() { return reverse_iterator(tree.NIL); }
			const_reverse_iterator rend() const { return const_reverse_iterator(tree.NIL);}

			bool empty() const { return _size > 0 ? false : true; } // пустая map или нет

			size_type size() const { return _size; }; 

			size_type max_size() const {return std::numeric_limits< long >::max() / sizeof(node);} // маскимально возможный размер map

			ft::pair< iterator, bool > insert(const value_type& val) // вставляем элемент пары first, second
			{
				node_pointer n = find(val.first).base();
				ft::pair< node_pointer, bool > ret;
				if (n == tree.NIL)
				{
					ret = tree.insert_key(val.first, val.second);
					if (ret.second)
						_size++;
				}
				else 
				{
					ret = ft::make_pair(n, false);
				}
				return ft::make_pair(iterator(ret.first), ret.second); //  Типы шаблонов могут быть неявно выведены из аргументов, переданных в make_pair.
			}

			iterator insert(iterator position, const value_type& val) // Функция оптимизирует время вставки, если position указывает на элемент, 
			{															// который будет предшествовать вставляемому элементу. Position это подсказка
				node_pointer n = find(val.first).base();
				ft::pair< node_pointer, bool > ret;
				if (n == tree.NIL)
				{
					(void)position;
					ret = tree.insert_key(val.first, val.second);
					if (ret.second)
						_size++;
				}
				else
				{
					ret = ft::make_pair(n, false);
				}
				return iterator(ret.first);
				}

			template < typename InputIterator >
			void insert(InputIterator start, InputIterator end) // Вставка диапазона элементов
			{
				while (start != end)
				{
					tree.insert_key(start->first, start->second);
					_size++;
					++start;
				}
			}

			void erase(iterator position) // удаляет указанный элемент
			{
				tree.erase_key(position->first);
				_size--;
			}

			size_type erase(const key_type& k) // удаление по ключу
			{
				if (tree.erase_key(k))
				{
					_size--;
					return 1;
				}
				return 0;
			}

			void erase(iterator first, iterator last) // удаление диапазона элементов
			{
				ft::stack< node_pointer > store;
				while (first != last)
				{
					store.push(first.base());
					++first;
				}
				while (!store.empty())
				{
					tree.erase_key(store.top()->_data->first);
					_size--;
					store.pop();
				}
			}

			void swap(map& x)
			{
				std::swap(tree.root, x.tree.root);
				std::swap(tree.NIL, x.tree.NIL);
				std::swap(_size, x._size);
				std::swap(tree.root->_tree, x.tree.root->_tree);
			}

			void clear() { erase(begin(), end()); } // удаление всех элементов карты

			key_compare key_comp() const { return _comp; } // Возвращает копию объекта сравнения , используемого контейнером для сравнения ключей .

			value_compare value_comp() const { return value_compare(_comp); } // Возвращает объект сравнения, который можно использовать для сравнения двух элементов, чтобы узнать, идет ли ключ первого перед вторым.

			iterator find(const key_type& k) { return iterator(tree.find_key(k)); } // Ищет в контейнере элемент с ключом , эквивалентным k , и возвращает ему итератор, если он найден, 
																					// в противном случае он возвращает итератор для map::end .

			const_iterator find(const key_type& k) const {return const_iterator(tree.find_key(k));}

			size_type count(const key_type& k) const {return tree.find_key(k) == end().base() ? 0 : 1;} // Ищет в контейнере элементы с ключом, эквивалентным k , и возвращает количество совпадений. 0 или 1

			iterator lower_bound(const key_type& k) // Вернуть итератор к нижней границе
														// Возвращает итератор, указывающий на первый элемент в контейнере, ключ которого не считается предшествующим k (т. е. он либо эквивалентен, либо идет после).
			{
				iterator		it = begin();
				value_type		tmp(k, T());
				value_compare	value_comp(_comp);

				for (; it != end(); ++it)
				{
					if (is_key_equal(*it, tmp) || value_comp(tmp, *it.base()->_data)) 
						return it;
				}
				return it;
			}
			const_iterator lower_bound(const key_type& k) const
			{
				const_iterator it = begin();
				value_type tmp(k, T());
				value_compare value_comp(_comp);

				for (; it != end(); ++it)
				{
					if (is_key_equal(*it, tmp) || value_comp(tmp, it.base()->_data))
						return it;
				}
				return it;
			};

			iterator upper_bound(const key_type& k) // Возвращает итератор, указывающий на первый элемент в контейнере, чей ключ считается поледующим k 
			{
				iterator it = begin();
				value_type tmp(k, T());
				value_compare value_comp(_comp);

				for (; it != end(); ++it)
				{
					if (value_comp(tmp, *it))
						return it;
				}
				return it;
			}

			const_iterator upper_bound(const key_type& k) const
			{
				const_iterator it = begin();
				value_type tmp(k, T());
				value_compare value_comp(_comp);

				for (; it != end(); ++it)
				{
					if (value_comp(tmp, *it))
						return it;
				}
				return it;
			}

			ft::pair< const_iterator, const_iterator > equal_range(const key_type& k) const // Возвращает границы диапазона, включающего все элементы в контейнере, имеющие ключ , эквивалентный k .
			{
				const_iterator it1 = lower_bound(k);
				const_iterator it2 = upper_bound(k);
				return ft::make_pair(it1, it2);
			}

			ft::pair< iterator, iterator > equal_range(const key_type& k)
			{
				iterator it1 = lower_bound(k);
				iterator it2 = upper_bound(k);
				return ft::make_pair(it1, it2);
			}

			allocator_type get_allocator() const { return _alloc; } // Возвращает копию объекта распределителя

		template < typename _Key, typename _T, typename _Compare, typename _Alloc >
		friend bool operator==(const map< _Key, _T, _Compare, _Alloc >&, const map< _Key, _T, _Compare, _Alloc >&);

		template < typename _Key, typename _T, typename _Compare, typename _Alloc >
		friend bool operator<(const map< _Key, _T, _Compare, _Alloc >&, const map< _Key, _T, _Compare, _Alloc >&);
	};

	template < typename Key, typename T, typename Compare, typename Alloc >
	bool operator==(map< Key, T, Compare, Alloc >& x, map< Key, T, Compare, Alloc >& y)
	{return ft::equal(x.begin(), x.end(), y.begin());}

	template < typename Key, typename T, typename Compare, typename Alloc >
	bool operator!=(map< Key, T, Compare, Alloc >& x, map< Key, T, Compare, Alloc >& y)
	{return !(x == y);}

	template < typename Key, typename T, typename Compare, typename Alloc >
	bool operator<(map< Key, T, Compare, Alloc >& x, map< Key, T, Compare, Alloc >& y)
	{return ft::lexicographical_compare(x.begin(), x.end(), y.begin());}

	template < typename Key, typename T, typename Compare, typename Alloc >
	bool operator<=(map< Key, T, Compare, Alloc >& x, map< Key, T, Compare, Alloc >& y)
	{return !(y < x);}

	template < typename Key, typename T, typename Compare, typename Alloc >
	bool operator>(map< Key, T, Compare, Alloc >& x, map< Key, T, Compare, Alloc >& y)
	{return y < x;}

	template < typename Key, typename T, typename Compare, typename Alloc >
	bool operator>=(map< Key, T, Compare, Alloc >& x, map< Key, T, Compare, Alloc >& y)
	{return !(x < y);}

	template < typename _Key, typename _T, typename _Compare, typename _Alloc >
	void swap(map< _Key, _T, _Compare, _Alloc >& x, map< _Key, _T, _Compare, _Alloc >& y)
	{x.swap(y);}

}
