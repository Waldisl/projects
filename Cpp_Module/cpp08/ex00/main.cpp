#include "easyfind.hpp"
#include <deque>

using std::endl;
using std::cout;
using std::vector;
using std::deque;

int	main()
{
	{
		vector<int> array(10);
		srand(time(NULL));
		for (int i = 0; i < 10; i++)
		{
			array[i] = rand() % 10;
		}

		int	search1 = 7;
		int	search2 = 4;
		vector<int>::iterator r1 = easyfind(array, search1);
		vector<int>::iterator r2 = easyfind(array, search2);

		if (r1 != array.end())
			cout << "\tFound: " << *r1 << endl;
		else
			cout << "\tError: Notfound " << search1 << endl;

		if (r2 != array.end())
			cout << "\tFound: " << *r2 << endl;
		else
			cout << "\tError: Notfound " << search2 << endl;
	}

	cout << endl;
	{
		deque<double> arr(10);
		srand(time(NULL));
		for (int i = 0; i < 10; i++)
		{
			arr[i] = rand() % 10;
		}

		double	search3 = 2;
		double	search4 = 9;
		deque<double>::iterator r3 = easyfind(arr, search3);
		deque<double>::iterator r4 = easyfind(arr, search4);

		if (r3 != arr.end())
			cout << "\tFound: " << *r3 << endl;
		else
			cout << "\tError: Notfound " << search3 << endl;

		if (r4 != arr.end())
			cout << "\tFound: " << *r4 << endl;
		else
			cout << "\tError: Notfound " << search4 << endl;
		// try
		// {
		// 	easyfind(arr, search3);
		// 	cout << "\tFound: " << search3 << endl;
		// }
		// catch (std::string  e)
		// {
		// 	e.push_back('2');
		// 	cout << e << endl;
		// }

		// try
		// {
		// 	easyfind(arr, search4);
		// 	cout << "\tFound: " << search4 << endl;
		// }
		// catch (std::string  e)
		// {
		// 	e.push_back('9');
		// 	cout << e << endl;
		// }
	}
}
