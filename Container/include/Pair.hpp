#pragma once

namespace ft
{
	/* Этот класс связывает вместе пару значений, которые могут быть разных типов (Т1 а также Т2). 
	Доступ к отдельным значениям можно получить через его общедоступные члены.первый а также второй.*/
	template < class T1, class T2 >
	struct pair
	{
		public:
			typedef T1 first_type;
			typedef T2 second_type;

			/* Первое значение в pair */
			first_type first;
			/* Первое значение в pair */
			second_type second;

			/* Создает парный объект, элементы которого инициализируются значением. */
			pair() : first(), second(){};

			template < class U, class V >
			pair(const pair< U, V >& pr) : first(pr.first), second(pr.second){};

			pair(const first_type& a, const second_type& b) : first(a), second(b){};

			pair& operator=(const pair& pr)
			{
				first = pr.first;
				second = pr.second;
				return *this;
			};
	};

	template < class T1, class T2 >
	bool operator==(const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs)
	{return lhs.first == rhs.first && lhs.second == rhs.second;}

	template < class T1, class T2 >
	bool operator!=(const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs)
	{return !(lhs == rhs);}

	template < class T1, class T2 >
	bool operator<(const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs)
	{return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);}

	template < class T1, class T2 >
	bool operator<=(const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs)
	{return !(rhs < lhs);}

	template < class T1, class T2 >
	bool operator>(const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs)
	{return rhs < lhs;}

	template < class T1, class T2 >
	bool operator>=(const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs)
	{return !(lhs < rhs);}

	template < class T > void swap(T& a, T& b)
	{
		T c(a);
		a = b;
		b = c;
	}

	template < class T1, class T2 > pair< T1, T2 > make_pair(T1 x, T2 y) {return (pair< T1, T2 >(x, y));}
}
