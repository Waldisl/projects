#pragma once 

#include "Traits.hpp"
#include "Pair.hpp"
#include "RB_Tree.hpp"
#include "Type_traits.hpp"

namespace ft
{
	template < typename Iterator, typename node_pointer, typename Container >
	class reverse_map_iterator
	{
		protected:
			typedef iterator_traits< Iterator >	traits;
			node_pointer						_ptr;
			bool _key_comp(node_pointer ptr1, node_pointer ptr2)
			{return ptr1->_data->first < ptr2->_data->first;}

		public:
			typedef Iterator							iterator_type;
			typedef typename traits::iterator_category	iterator_category;
			typedef typename traits::value_type			value_type;
			typedef typename traits::difference_type	difference_type;
			typedef typename traits::reference			reference;
			typedef typename traits::pointer			pointer;

			reverse_map_iterator() : _ptr() {}

			reverse_map_iterator(const node_pointer& ptr) : _ptr(ptr) {}

			template < typename T >
			reverse_map_iterator(const reverse_map_iterator<T, node_pointer, typename enable_if< is_same< T, 
			typename Container::pointer >::value,Container >::type >& ptr) : _ptr(ptr.base()) {}

			const node_pointer& base() const { return _ptr; }

			reference operator*() const { return *(_ptr->_data); }

			pointer operator->() const { return _ptr->_data; }

			reverse_map_iterator operator++()
			{
				node_pointer last_node = _ptr->_tree->max_node(_ptr->_tree->root);
				if (_ptr == _ptr->_tree->NIL)
				{
					_ptr = last_node;
					return (_ptr);
				}
				if (!_ptr->left->nil_node)
				{
					_ptr = _ptr->left;
					if (_ptr == last_node)
						return reverse_map_iterator(_ptr);
					while ((_ptr != last_node) && !_ptr->left->nil_node)
						_ptr = _ptr->left;
				}
				else
				{
					if (!_key_comp(_ptr, _ptr->parent))
						_ptr = _ptr->parent;
					else
					{
						while (!_ptr->parent->nil_node && _key_comp(_ptr, _ptr->parent))
						{
							_ptr = _ptr->parent;
						}
						_ptr = _ptr->parent;
					}
				}
				return reverse_map_iterator(_ptr);
			}

			reverse_map_iterator operator++(int)
			{
				node_pointer tmp = _ptr;
				if (_ptr == _ptr->_tree->NIL)
				{
					_ptr = _ptr->_tree->max_node(_ptr->_tree->root);
					return (tmp);
				}
				if (!_ptr->left->nil_node)
				{
					_ptr = _ptr->left;
					if (_ptr == _ptr->_tree->max_node(_ptr->_tree->root))
						return reverse_map_iterator(_ptr);
					while (!_ptr->right->nil_node)
						_ptr = _ptr->right;
				}
				else
				{
					if (!_key_comp(_ptr, _ptr->parent))
						_ptr = _ptr->parent;
					else
					{
						while (!_ptr->parent->nil_node && _key_comp(_ptr, _ptr->parent))
						{
							_ptr = _ptr->parent;
						}
						_ptr = _ptr->parent;
					}
				}
				return reverse_map_iterator(tmp);
			}

			reverse_map_iterator operator--()
			{
				node_pointer last_node = _ptr->_tree->min_node(_ptr->_tree->root);
				if (_ptr == _ptr->_tree->NIL)
				{
					_ptr = last_node;
					return (_ptr);
				}
				if (_ptr == _ptr->_tree->NIL)
					_ptr->parent = last_node;
				if (_ptr == last_node)
				{
					_ptr = _ptr->parent;
				} 
				else if (!_ptr->left->nil_node)
				{
					_ptr = _ptr->left;
					if (_ptr == last_node) 
						return reverse_map_iterator(_ptr);
					while (!_ptr->right->nil_node)
						_ptr = _ptr->right;
				}
				else
				{
					if (!_key_comp(_ptr, _ptr->parent))
					{
						_ptr = _ptr->parent;
					}
					else
					{
						while (_key_comp(_ptr, _ptr->parent)) 
						{
							_ptr = _ptr->parent;
						}
						_ptr = _ptr->parent;
					}
				}
				return reverse_map_iterator(_ptr);
			}

			reverse_map_iterator operator--(int)
			{
				node_pointer last_node = _ptr->_tree->min_node(_ptr->_tree->root);
				node_pointer tmp = _ptr;
				if (_ptr == _ptr->_tree->NIL)
				{
					_ptr = _ptr->_tree->min_node(_ptr->_tree->root);
					return (tmp);
				}
				if (_ptr == last_node)
				{
					_ptr = _ptr->parent;
				}
				else if (!_ptr->right->nil_node)
				{
					_ptr = _ptr->right;
					if (_ptr == last_node)
						return reverse_map_iterator(_ptr);
					while (!_ptr->left->nil_node)
						_ptr = _ptr->left;
				}
				else
				{
					if (_key_comp(_ptr, _ptr->parent))
					{
						_ptr = _ptr->parent;
					}
					else
					{
						while (!_ptr->parent->nil_node && !_key_comp(_ptr, _ptr->parent))
						{
							_ptr = _ptr->parent;
						}
						_ptr = _ptr->parent;
					}
				}
				return reverse_map_iterator(tmp);
			}
	};

	template < typename IteratorL, typename IteratorR, typename node_pointer, typename Container >
	bool operator==( const reverse_map_iterator< IteratorL, node_pointer, Container >& lhs,
	const reverse_map_iterator< IteratorR, node_pointer, Container >& rhs) {return lhs.base() == rhs.base();}

	template < typename Iterator, typename node_pointer, typename Container >
	bool operator==( const reverse_map_iterator< Iterator, node_pointer, Container >& lhs,
	const reverse_map_iterator< Iterator, node_pointer, Container >& rhs) {return lhs.base() == rhs.base();}

	template < typename IteratorL, typename IteratorR, typename node_pointer,typename Container >
	bool operator!=( const reverse_map_iterator< IteratorL, node_pointer, Container >& lhs,
	const reverse_map_iterator< IteratorR, node_pointer, Container >& rhs) { return lhs.base() != rhs.base();}

	template < typename Iterator, typename node_pointer, typename Container >
	bool operator!=( const reverse_map_iterator< Iterator, node_pointer, Container >& lhs,
	const reverse_map_iterator< Iterator, node_pointer, Container >& rhs) { return lhs.base() != rhs.base();}
}
