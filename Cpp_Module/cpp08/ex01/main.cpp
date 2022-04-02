#include "Span.hpp"
#include <cstdlib>
#include <climits>

int	main()
{

	Span sp = Span(5);
	sp.addNumber(5);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	cout << sp.shortestSpan() << endl;
	cout << sp.longestSpan() << endl << endl;

	Span sp1 = Span(14);
	sp1.addNumber(499);
	sp1.addNumber(300);
	sp1.addNumber(199);
	try
	{
		cout << sp1.shortestSpan() << endl;
	}
	catch (string g) { cout << g <<endl; }

	try
	{
		cout << sp1.longestSpan() << endl;
	}
	catch (string g) { cout << g <<endl; }

	cout << endl;

	vector<int> temp;
	srand(time(NULL));
	for (int i = 0; i < 10000; ++i)
		temp.push_back(rand() % 100000000);
	Span sp3 = Span(10000);
	sp3.addNumber(temp.begin(), temp.end());
	cout << sp3.shortestSpan() << endl;
	cout << sp3.longestSpan() << endl;

	cout << endl;

	Span sp2 = Span(5);
	sp2.addNumber(INT_MIN);
	sp2.addNumber(INT_MAX);
	cout << sp2.shortestSpan() << endl;
	cout << sp2.longestSpan() << endl;

}