#pragma once

#include "Pair.hpp"
#include "Stack.hpp"

namespace ft
{
/*******************************************************************************

	[ свойства узлов ]
		1) Левое поддерево узла содержит только узлы с ключами < ключа узла.
		2) Правое поддерево узла содержит только узлы с ключами >= ключа узла.
		3) Каждое из левого и правого поддеревьев также должно быть бинарным деревом поиска.

	например:
		слева < узел <= справа

	[ свойства RB-дерева ]
	В дополнение к свойствам узлов должны выполняться следующие условия:
		1) Каждый узел либо красный, либо черный.
		2) Все узлы NIL (листья) считаются черными.
		3) Красный узел не имеет красного потомка.
		4) Каждый путь от данного узла к любому из его потомков NIL узлов идет через такое же количество черных узлов.

*******************************************************************************/

	template < typename K, typename V, typename Alloc, typename value_type >
	class RBTree
	{
	/* Node class */
		private:
			Alloc _alloc;

		public:
			class Node
			{
				private:
					Alloc _alloc;

				public:
				enum Color { BLACK, RED };
				Color								color;
				Node*								parent;
				Node*								left;
				Node*								right;
				bool								nil_node;
				value_type*							_data;
				RBTree< K, V, Alloc, value_type >*	_tree;

				Node(K const& key, V val = V()) : _alloc(), color(BLACK), parent(), left(), right(), nil_node(true)
				{
					_data = _alloc.allocate(1);
					_alloc.construct(_data, ft::pair< const K, V >(key, val));
					_tree = NULL;
				}

				Node(RBTree< K, V, Alloc, value_type >* tree, K const& key, V val = V())
					: _alloc(), color(BLACK), parent(), left(), right(), nil_node(true)
				{
					_data = _alloc.allocate(1);
					_alloc.construct(_data, ft::pair< const K, V >(key, val));
					_tree = tree;
				}

				Node(Node const& src) { *this = src; }

				~Node()
				{
					if (_data)
					{
						_alloc.destroy(_data);
						_alloc.deallocate(_data, 1);
					}
				}

				Node& operator=(Node const& rhs)
				{
					if (this != &rhs)
					{
						_data = _alloc.allocate(1);
						_alloc.construct(_data, ft::pair< const K, V >(rhs._data->first, rhs._data->second));
						color = rhs.color;
						parent = rhs.parent;
						left = rhs.left;
						right = rhs.right;
						nil_node = rhs.nil_node;
						_tree = rhs._tree;
					}
					return *this;
				}
			};

			Node  NIL_node;
			Node* NIL;
			Node* root;

			RBTree() : _alloc(), NIL_node(K(), V()), NIL(&NIL_node), root(NIL)
			{
				NIL->color = Node::BLACK;
				NIL->parent = NIL;
				NIL->left = NIL;
				NIL->right = NIL;
				NIL->nil_node = true;
				_alloc.destroy(NIL->_data);
				_alloc.deallocate(NIL->_data, 1);
				NIL->_data = NULL;
				NIL_node._tree = this;
			}

			RBTree(RBTree const& src) : _alloc(), NIL_node(K(), V()), NIL(&NIL_node), root(NIL)
			{*this = src;}

			~RBTree() { tree_delete(root); }

			RBTree& operator=(RBTree const& rhs)
			{
				if (this != &rhs)
				{
					tree_delete(root);
					// глубокая коппия
					root = treecpy(rhs.root, rhs.NIL);
				}
				return *this;
			}

			V& operator[](K const& key) const
			{
				Node* node = find_key(key);
				if (node == NIL)
					throw std::out_of_range("RBTree::operator[]. Invalid key.");
				return node->_data.second;
			}

			Node* min_node(Node* root) const // минимальный узел
			{
				if (!root)
					return NIL;
				Node* ptr = root;
				while (ptr->left != NIL)
					ptr = ptr->left;
				return ptr;
			}

			Node* max_node(Node* root) const // максимальный узел
			{
				if (!root)
					return NIL;
				Node* ptr = root;
				while (ptr->right != NIL)
					ptr = ptr->right;
				return ptr;
			}

			void print_tree() const { print_tree_recursive_call(root); }

		private:
			void print_tree_recursive_call(Node* root, int space = 0) const
			{
				if (root == NIL)
					return;
				space += 10;
				// печатаем рекурсивно, начиная с максимального узла
				print_tree_recursive_call(root->right, space);
				std::cout << std::endl;
				for (int i = 10; i < space; i++)
					std::cout << " ";
				// печатаем корень
				std::cout << root->_data->first << (root->color == Node::RED ? "(R)" : "(B)") << std::endl;
				// печатаем рекурсивно, начиная с корня до минимального узла
				print_tree_recursive_call(root->left, space);
			}

			Node* treecpy(Node* src_root, Node* src_NIL) // копия дерева
			{
				if (src_root == src_NIL)
					return NIL;
				Node* copy = nodecpy(src_root, src_NIL);
				copy->parent = NIL;
				copy->left = treecpy(src_root->left, src_NIL);
				copy->left->parent = copy;
				copy->right = treecpy(src_root->right, src_NIL);
				copy->right->parent = copy;
				return copy;
			}

			Node* nodecpy(Node const* src_node, Node const* src_NIL) // копия узла
			{
				if (src_node == src_NIL)
					return NIL;
				Node* new_node = new Node(*src_node);
				return new_node;
			}

			void tree_delete(Node* node) // удаляем дерево
			{
				if (node == NIL)
					return;
				tree_delete(node->left);
				tree_delete(node->right);
				node_delete(node);
			}

			void node_delete(Node* node) // удаляем узел
			{
				if (node->_data)
				{
					_alloc.destroy(node->_data);
					_alloc.deallocate(node->_data, 1);
					node->_data = NULL;
				}
				delete node;
			}

		public:

			Node* find_key(K const& key) const // Возвращает указатель узла на ключ
			{
				Node* ptr = root;
				while (ptr != NIL && ptr->_data->first != key)
				{
					if (key < ptr->_data->first)
					{
						ptr = ptr->left;
					}
					else
					{
						ptr = ptr->right;
					}
				}
				return ptr;
			}

			ft::pair< Node*, bool > insert_key(K const& key, V const& val) // добавляем key
			{
				Node* parent = NIL;
				Node* ptr = root;
				// начинаем с корня, повторяем до тех пор, пока ptr не станет равным NIL, в конце цикла родителем является узел перед указателем
				while (ptr != NIL)
				{
					parent = ptr;
					// текущая позиция key, заменить его value
					if (key == ptr->_data->first)
					{
						ptr->_data->second = val;
						return ft::make_pair(ptr, false);
					}
					// key < key позиции, перейти к левому дочернему элементу
					else if (key < ptr->_data->first)
					{
						ptr = ptr->left;
					}
					else
					{
						ptr = ptr->right;
					}
				}
				// Мы нашли новую позицию узла в точке ptr (NIL)
				Node* new_node = new Node(this, key, val);
				new_node->nil_node = false;
				new_node->parent = parent; // родитель нового узла - текущая позиция (ptr)
				if (parent == NIL)
				{
					root = new_node; // Если дерево было пустым, это первый узел (корень)
				}
				// new_node становится дочерним элементом текущей позиции (слева или справа)
				else if (new_node->_data->first < parent->_data->first)
				{
					parent->left = new_node;
				}
				else
				{
					parent->right = new_node;
				}
				// new_node красный при вставке
				new_node->color = Node::RED;
				new_node->left = NIL;
				new_node->right = NIL;
				rebalance_after_insert(new_node);
				return ft::make_pair(new_node, true);
			}

			bool erase_key(K key) // удаление key
			{
				// z: узел для удаления из дерева
				Node* z = find_key(key);
				if (z == NIL)
					return 0;
				Node* x;
				Node* y = z;
				typename Node::Color y_original_color = y->color;

				if (z->left == NIL)
				{
					// узел для стирания не имеет левого дочернего элемента
					x = z->right;
					erase_node_from_tree(z, z->right);
				}
				else if (z->right == NIL)
				{
					// узел для стирания не имеет правильного дочернего элемента
					x = z->left;
					erase_node_from_tree(z, z->left);
				}
				else
				{
					// узел для стирания имеет 2 дочерних элемента
					y = min_node(z->right);
					y_original_color = y->color;
					x = y->right;
					if (y->parent == z)
					{
						x->parent = y;
					}
					else
					{
						erase_node_from_tree(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					erase_node_from_tree(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				node_delete(z);
				if (y_original_color == Node::BLACK)
					rebalance_after_erase(x);
				return 1;
			}

		private:
			// u: узел для стирания v: узел для присоединения при удалении u
			void erase_node_from_tree(Node* u, Node* v)
			{
				// Узел, который нужно стереть, является корнем
				if (u->parent == NIL)
				{
					root = v;
				}
				else if (u == u->parent->left)
				{
					u->parent->left = v;
				}
				else
				{
					u->parent->right = v;
				}
				v->parent = u->parent;
			}

			void rebalance_after_insert(Node* ptr) // балансировка при добавлении 
			{
				// Проверить красное нарушение, требование 3: красный узел не имеет красного дочернего элемента
				while (ptr->parent->color == Node::RED)
				{
					// если родитель узла является левым дочерним элементом дедушки ptr тогда дядя ptr является правым потомком дедушки ptr
					if (ptr->parent == ptr->parent->parent->left)
					{
						Node* uncle = ptr->parent->parent->right;
						// дядя ptr красный
						if (uncle->color == Node::RED)
						{
							ptr->parent->color = Node::BLACK;       // родитель становится черным
							uncle->color = Node::BLACK;             // дядя становится черным
							ptr->parent->parent->color = Node::RED; // дедушка становится красным
							ptr = ptr->parent->parent; // перемещается на 2 уровня дерева выше (дедушка)
						}
						// или дядя ptr черный
						else 
						{
							// node правый ребенок его родителей, дядя черный
							if (ptr == ptr->parent->right)
							{
								ptr = ptr->parent; // меняем родительский на дочерний
								rotate_left(ptr);  // ptr становится правым потомком своего родителя
							}
							ptr->parent->color = Node::BLACK;
							ptr->parent->parent->color = Node::RED;
							rotate_right(ptr->parent->parent);
						}
					}
					// если родитель узла является правым дочерним элементом дедушки ptr тогда дядя ptr является левым потомком дедушки ptr
					else
					{
						Node* uncle = ptr->parent->parent->left;
						if (uncle->color == Node::RED)
						{
							ptr->parent->color = Node::BLACK;
							uncle->color = Node::BLACK;
							ptr->parent->parent->color = Node::RED;
							ptr = ptr->parent->parent;
						}
						// или дядя ptr черный 
						else
						{
							if (ptr == ptr->parent->left)
							{
								ptr = ptr->parent;
								rotate_right(ptr);
							}
							ptr->parent->color = Node::BLACK;
							ptr->parent->parent->color = Node::RED;
							rotate_left(ptr->parent->parent);
						}
					}
				}
				root->color = Node::BLACK;
			}

			void rebalance_after_erase(Node* ptr) // балансировка при удалении
			{
				while (ptr != root && ptr->color == Node::BLACK)
				{
					// ptr — левый ребенок
					if (ptr == ptr->parent->left)
					{
						Node* brother = ptr->parent->right;
						if (brother->color == Node::RED)
						{
							brother->color = Node::BLACK;
							ptr->parent->color = Node::RED;
							rotate_left(ptr->parent);
							brother = ptr->parent->right;
						}
						if (brother->left->color == Node::BLACK && brother->right->color == Node::BLACK)
						{
							brother->color = Node::RED;
							ptr = ptr->parent;
						}
						else
						{
							if (brother->right->color == Node::BLACK)
							{
								brother->left->color = Node::BLACK;
								brother->color = Node::RED;
								rotate_right(brother);
								brother = ptr->parent->right;
							}
							brother->color = ptr->parent->color;
							ptr->parent->color = Node::BLACK;
							brother->right->color = Node::BLACK;
							rotate_left(ptr->parent);
							ptr = root;
						}
					}
					// ptr — правый ребенок
					else
					{
						Node* brother = ptr->parent->left;
						if (brother->color == Node::RED)
						{
							brother->color = Node::BLACK;
							ptr->parent->color = Node::RED;
							rotate_right(ptr->parent);
							brother = ptr->parent->left;
						}
						if (brother->right->color == Node::BLACK && brother->left->color == Node::BLACK)
						{
							brother->color = Node::RED;
							ptr = ptr->parent;
						}
						else
						{
							if (brother->left->color == Node::BLACK)
							{
								brother->right->color = Node::BLACK;
								brother->color = Node::RED;
								rotate_left(brother);
								brother = ptr->parent->left;
							}
							brother->color = ptr->parent->color;
							ptr->parent->color = Node::BLACK;
							brother->left->color = Node::BLACK;
							rotate_right(ptr->parent);
							ptr = root;
						}
					}
				}
				ptr->color = Node::BLACK;
			}


	/* https://ressources.unisciel.fr/algoprog/s46bst/emodules/rn00macours1/res/rn00cours-texte-xxx.pdf

      |          rotate_right(x)                   |
      x        ----------------------->            y
     / \                                          / \
    y   C                                        A   x
   / \                                              / \
  A   B                                            B   C
*/
			void rotate_right(Node* x) //правый поворот
			{
				Node* y = x->left;  // (y) - левый ребенок (x)
				x->left = y->right; // (y) правый ребенок (B) становится левым ребенком (x)
				if (y->right != NIL)
					y->right->parent = x; // сделать (x) родителем (B)
				y->parent = x->parent; // родитель (y) становится родителем (x)
				// если (x) является корнем, вместо этого сделайте (y) корнем
				if (x->parent == NIL)
				{
					root = y;
				}
				// сделать (y) новым дочерним элементом родителя (x)
				else if (x == x->parent->right)
				{
					x->parent->right = y;
				}
				else
				{
					x->parent->left = y;
				}
				// (x) становится правым потомком (y)
				y->right = x;
				x->parent = y;
			}

/*

      |          rotate_left(x)                   |
      x        ----------------------->           y
     / \                                         / \
    A   y                                       x   C
       / \                                     / \
      B   C                                   A  B
  */
			void rotate_left(Node* x) //левый поворот
			{
				Node* y = x->right; // (y) правый ребенок (x)
				x->right = y->left; // (y) левый ребенок (B) становится правым ребенком (x)
				if (y->left != NIL)
				{
					y->left->parent = x; // сделать (x) родителем (B)
				}
				y->parent = x->parent; // родитель (y) становится родителем (x)
				// если (x) является корнем, вместо этого сделайте (y) корнем
				if (x->parent == NIL)
				{
					root = y;
				}
				// сделать (y) новым дочерним элементом родителя (x)
				else if (x == x->parent->left)
				{
					x->parent->left = y;
				}
				else
				{
					x->parent->right = y;
				}
				// (x) становится левым потомком (y)
				y->left = x;
				x->parent = y;
			}
	};
}
