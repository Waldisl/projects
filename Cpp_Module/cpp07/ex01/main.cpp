#include <iostream>
#include "iter.hpp"

int main(void)
{
	cout << endl << "String Array" << endl;
	string arr1[] = {"HI", ",", "Iter", "."};
	iter(arr1, 4, &print);

	cout << endl << "Int Array" << endl;
	int arr2[] = {33, 59, 2, 130};
	iter(arr2, 4, &print);

	cout << endl << "Float Array" << endl;
	float arr3[] = {12.4, 463.45, 328.6, 4.0};
	iter(arr3, 4, &print);

	cout << endl << "Double Array" << endl;
	double arr4[] = {423.545, 2.54, 56.78, 55.42222};
	iter(arr4, 4, &print);

	return 0;
}