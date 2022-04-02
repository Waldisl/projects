#include "Mutantstack.hpp"
#include <list>
#include <cstdlib>

int main()
{
	MutantStack<int> mstack;

	mstack.push(5);
	mstack.push(17);

	std::cout << mstack.top() << std::endl;

	mstack.pop();

	std::cout << mstack.size() << std::endl;

	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);

	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();

	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);
	// std::stack<int, std::vector<int> > s(mstack);

	cout << "\tLIST" << endl;

	std::list<int> mstack1;
	mstack1.push_back(5);
	mstack1.push_back(17);
	cout << "[ " << mstack1.back() << " ]";
	mstack1.pop_back();
	cout << "[ " << mstack1.size() << " ]";
	mstack1.push_back(3);
	mstack1.push_back(5);
	mstack1.push_back(737);
	//[...]
	mstack1.push_back(0);
	std::list<int>::iterator it1 = mstack1.begin();
	std::list<int>::iterator ite1 = mstack1.end();
	++it1;
	--it1;
	while (it1 != ite1)
	{
		cout << "[ " << *it1 << " ]";
		++it1;
	}
	cout << endl << endl;

	cout << "REVERSE FLOAT" << endl;

	MutantStack<float> fl;
	for (int i = 0; i < 25; i++)
	{
		fl.push(i);
		cout << "[ " << fl.top() << " ]";
	}
	cout << endl;
	MutantStack<float>::criter it2 = fl.rbegin();
	MutantStack<float>::criter ite2 = fl.rend();
	while (it2 != ite2)
	{
		cout << "[ " << *it2 << " ]";
		++it2;
	}
	cout << endl << endl;


	cout << "RANDOM DOUBLE REVERSE" << endl;

	MutantStack<double> doub;
	srand(time(0));
	for (int i = 0; i < 25; ++i)
		doub.push(rand() % 1000);
	MutantStack<double>::riter it3 = doub.rbegin();
	MutantStack<double>::riter ite3 = doub.rend();
	while (it3 != ite3)
	{
		while (it3 != ite3)
		{
			cout << "[ " << *it3 << " ]";
			++it3;
		}
	}
	cout << endl;
	return 0;
}