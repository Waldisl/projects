#pragma  once

/*Этот заголовок определяет серию классов для получения информации о типе во время компиляции.
Заголовок содержит:
Вспомогательные классы: стандартные классы для помощи в создании констант времени компиляции.
Признаки типов: классы для получения характеристик типов в виде постоянных значений времени компиляции.
Преобразования типов: классы для получения новых типов путем применения определенных преобразований к существующим типам.*/
namespace ft 
{
/* remove_cv получает тип T без какой-либо константы или изменчивой квалификации верхнего уровня .
Преобразованный тип получает псевдоним как тип члена remove_cv::type .
Если T имеет cv-квалификацию ( const и/или volatile ), это тот же тип, что и T , но без его cv-квалификации . В противном случае это Т без изменений.
Обратите внимание, что этот класс просто получает тип, используя другой тип в качестве модели, но не преобразует значения или объекты между этими типами. 
Чтобы явно удалить квалификатор cv объекта, const_castможет быть использован.*/
	template < class T > struct remove_cv { typedef T type; };
	template < class T > struct remove_cv< const T > { typedef T type; };
	template < class T > struct remove_cv< volatile T > { typedef T type; };
	template < class T > struct remove_cv< const volatile T > { typedef T type; };
	template < class T > struct remove_const { typedef T type; };
	template < class T > struct remove_const< const T > { typedef T type; };
	template < class T > struct remove_volatile { typedef T type; };
	template < class T > struct remove_volatile< volatile T > { typedef T type; };

	template < typename T, T Val > 
	struct integral_constant
	{
		typedef integral_constant type;
		typedef T                 value_type;
		enum { value = Val };
	};
/*Интегральная постоянная
Этот шаблон предназначен для предоставления констант времени компиляции в качестве типов.
Он используется несколькими частями стандартной библиотеки в качестве базового класса для трейт-типов, особенно в их логическом варианте: см. true_type и false_type .*/
	typedef integral_constant< bool, true >  true_type;
	typedef integral_constant< bool, false > false_type;

/* is_integral Класс признаков, определяющий, является ли T целочисленным типом.
Он наследуется от integer_constant как true_type или false_type , в зависимости от того, является ли T целочисленным типом*/
	template < typename T > struct is_integral_base : public false_type {};

	template <> struct is_integral_base< bool > : public true_type {typedef bool value;};

	template <> struct is_integral_base< char > : public true_type {typedef char value;};

	template <> struct is_integral_base< wchar_t > : public true_type {typedef wchar_t value;};

	template <> struct is_integral_base< short > : public true_type {typedef short value;};

	template <> struct is_integral_base< unsigned short > : public true_type {typedef short value;};

	template <> struct is_integral_base< int > : public true_type {typedef int value;};

	template <> struct is_integral_base< unsigned int > : public true_type {typedef int value;};
	
	template <> struct is_integral_base< long > : public true_type {typedef long value;};
	
	template <> struct is_integral_base< unsigned long > : public true_type {typedef long value;};

	template <> struct is_integral_base< long long > : public true_type {typedef long long value;};

	template <> struct is_integral_base< unsigned long long > : public true_type {typedef long long value;};

	template < typename T > struct is_integral : public is_integral_base< typename remove_cv< T >::type >::type {};

/* enable_if Включить тип, если условие выполнено
Тип T включается как тип члена enable_if::type , если bool имеет значение true.
В противном случае enable_if::type не определен.
Это полезно, чтобы скрыть подписи во время компиляции, когда определенное условие не выполняется, 
поскольку в этом случае член enable_if::type не будет определен, и попытка компиляции с его использованием завершится ошибкой.*/
	template < bool, typename T = void > struct enable_if {};

	template < typename T > struct enable_if< true, T > { typedef T type; };

/* disable_if Выключить тип, если условие не выполнено*/
	template < bool, typename T = void > struct disable_if {};

	template < typename T > struct disable_if< false, T > { typedef T type; };

/* is_same Класс признака, который определяет, является ли T тем же типом, что и U , включая ту же квалификацию const и/или volatile , если таковая имеется.
Два разных имени типа считаются представляющими один и тот же тип, если и только если одно является определением типа другого: два имени, 
представляющие типы с точно такими же характеристиками, но ни одно из которых не является определением типа другого, не считаются одним и тем же типом.*/
	template < typename T, typename U > struct is_same : public false_type {};
	template < typename T > struct is_same< T, T > : public true_type {};
}
