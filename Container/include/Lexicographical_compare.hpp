#pragma once

namespace ft
{
/*Возвращает true, если диапазон лексикографически[first1,last1) сравнивается меньше , 
чем диапазон . Лексикографическое сравнение — это вид сравнения, обычно используемый для сортировки слов в словарях по алфавиту; 
Он включает в себя последовательное сравнение элементов, имеющих одинаковое положение в обоих диапазонах, 
до тех пор, пока один элемент не станет эквивалентным другому. Результатом сравнения этих первых несовпадающих элементов является результат лексикографического сравнения. 
Если обе последовательности равны до тех пор, пока одна из них не закончится, то более короткая последовательность лексикографически меньше более длинной. 
Элементы сравниваются с использованием для первой версии, а комп .[first2,last2)*/
	template < class InputIt1, class InputIt2 >
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2) 
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template < class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2) 
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}
}
