#include "Func.hpp"
#include <climits>
#include <list>
#include <time.h>
#include <typeinfo>

using std::cout;
using std::endl;
int main()
{
	cout << "Hello ft_containers !" << endl;
	/**************************** Test 1 ****************************************/
	FT::vector< int > vec1(5, 253);
	cout << BOLDWHITE + "\n=== Test 01 - vector ===" + CLR << endl;
	cout << ">> vector< int > vec1(5, 253); = ";
	cout << GREEN + "[" << vec1[0] << ", " << vec1[1] << ", " << vec1[2] << "]" + CLR << "\n";
	// size()
	cout << ">> vec1.size() = ";
	cout << GREEN << vec1.size() << CLR << endl;
	// max_size()
	cout << ">> vec1.max_size() = ";
	cout << GREEN << vec1.max_size() << CLR << endl;
	// copy constructor
	cout << ">> vector< int > vec_copy(vec1);" << endl;
	FT::vector< int > vec_copy(vec1);
	cout << ">> vec_copy = ";
	print_vector(vec_copy);
	cout << ">> vec_copy.size() = ";
	cout << GREEN << vec_copy.size() << CLR << endl;
	cout << ">> vec_copy.max_size() = ";
	cout << GREEN << vec_copy.max_size() << CLR << endl;
	cout << ">> vec_copy[1] = 1111" << endl;
	vec_copy[1] = 1111;
	cout << ">> vec_copy = ";
	print_vector(vec_copy);
	cout << ">> vec1 = ";
	print_vector(vec1);

	/**************************** Test 2 ****************************************/
	cout << BOLDWHITE + "\n=== Test 02 - iterator, vector::begin(), operator*(), "
		"etc... ===" + CLR << endl;
	cout << ">> *vec1.begin() = ";
	cout << GREEN << *vec1.begin() << CLR << endl;
	cout << ">> it = vec1.begin();" << endl;
	FT::vector< int >::iterator it;
	it = vec1.begin();
	cout << ">> *it = 67;" << endl;
	*it = 67;
	cout << ">> *it = ";
	cout << GREEN << *it << CLR << endl;
	cout << ">> &(*vec1.end()) = ";
	cout << &(*vec1.end()) << CLR << endl;
	cout << ">> vec1.front() = ";
	cout << GREEN << vec1.front() << CLR << endl;
	cout << ">> vec1.back() = ";
	cout << GREEN << vec1.back() << CLR << endl;
	cout << ">> vec1.at(7) = ";
	try
	{
		cout << GREEN << vec1.at(7) << CLR << endl;
	}
	catch (std::out_of_range& e)
	{
		cout << YELLOW << "catch (std::out_of_range& e) " + CLR << "{ " << e.what() << " }" << endl;
	}
	cout << ">> vec1.at(3) = ";
	try
	{
		cout << GREEN << vec1.at(3) << CLR << endl;
	}
	catch (std::out_of_range& e)
	{
		cout << YELLOW << "catch (std::out_of_range& e) " + CLR << "{ " << e.what() << " }" << endl;
	}
	cout << ">> vec1.at(0) = ";
	cout << GREEN << vec1.at(0) << CLR << endl;

	/**************************** Test 3 ****************************************/
	cout << BOLDWHITE + "\n=== Test 03 - vector::reserve, capacity ===" + CLR << endl;
	cout << ">> vec1.reserve(ULONG_MAX); = ";
	try
	{
		vec1.reserve(ULONG_MAX);
	}
	catch (std::length_error& e)
	{
		cout << YELLOW << "catch (std::length_error& e) " + CLR << "{ " << e.what() << " }" << endl;
	}
	cout << ">> vec1.capacity = ";
	cout << GREEN << vec1.capacity() << CLR << endl;
	cout << ">> vec1.reserve(24)" << endl;
	vec1.reserve(24);
	cout << ">> vec1.capacity = ";
	cout << GREEN << vec1.capacity() << CLR << endl;
	cout << ">> vec1.reserve(10)" << endl;
	vec1.reserve(10);
	cout << ">> vec1.capacity = ";
	cout << GREEN << vec1.capacity() << CLR << endl;

	/**************************** Test 4 ****************************************/
	cout << BOLDWHITE + "\n=== Test 04 - vector::resize ===" + CLR << endl;
	cout << ">> vec1.resize(8, 43) = ";
	vec1.resize(8, 43);
	print_vector(vec1);
	cout << ">> vec1.capacity = ";
	cout << GREEN << vec1.capacity() << CLR << endl;
	cout << ">> vec1.resize(5, 43) = ";
	vec1.resize(5, 43);
	print_vector(vec1);
	cout << ">> vec1.capacity = ";
	cout << GREEN << vec1.capacity() << CLR << endl;

	/**************************** Test 5 ****************************************/
	cout << BOLDWHITE + "\n=== Test 05 - vector::push_back ===" + CLR << endl;
	cout << ">> vec1.push_back(55)" << endl;
	vec1.push_back(55);
	cout << ">> vec1.push_back(14)" << endl;
	vec1.push_back(14);
	cout << ">> vec1.push_back(405)" << endl;
	vec1.push_back(405);
	print_vector(vec1);
	cout << ">> vec1.size() = ";
	cout << GREEN << vec1.size() << CLR << endl;

	/**************************** Test 6 ****************************************/
	cout << BOLDWHITE + "\n=== Test 06 - vector::pop_back ===" + CLR << endl;
	cout << ">> vec1.pop_back() * 2" << endl;
	vec1.pop_back();
	vec1.pop_back();
	print_vector(vec1);
	cout << ">> vec1.size() = ";
	cout << GREEN << vec1.size() << CLR << endl;

	/**************************** Test 7 ****************************************/
	cout << BOLDWHITE + "\n=== Test 07 - vector::clear ===" + CLR << endl;
	cout << ">> vec1.clear()" << endl;
	vec1.clear();
	print_vector(vec1);
	cout << ">> vec1.size() = ";
	cout << GREEN << vec1.size() << CLR << endl;
	cout << ">> vec1.capacity() = ";
	cout << GREEN << vec1.capacity() << CLR << endl;

	/**************************** Test 8 ****************************************/
	cout << BOLDWHITE + "\n=== Test 08 - vector of vectors ===" + CLR << endl;
	cout << ">> vec1.resize(15, 344);" << endl;
	vec1.resize(10, 344);
	cout << ">> vec1[4] = 665" << endl;
	vec1[4] = 665;
	cout << ">> vec1 = ";
	print_vector(vec1);
	cout << ">> vector< vector< int > > vec2(4, vec1);" << endl;
	FT::vector< FT::vector< int > > vec2(4, vec1);
	cout << ">> vec2[1][1] = 3333;" << endl;
	cout << ">> vec2[2][1] = 5555;" << endl;
	cout << ">> vec2[3][1] = 888;" << endl;
	vec2[1][1] = 3333;
	vec2[2][1] = 5555;
	vec2[3][1] = 888;
	for (size_t i = 0; i < vec2.size(); i++)
	{
		cout << ">> vec2[" << i << "] = ";
		print_vector(vec2[i]);
	}

	/**************************** Test 9 ***************************************/
	cout << BOLDWHITE + "\n=== Test 09 - vector::assign ===" + CLR << endl;
	cout << ">> vec1 = ";
	print_vector(vec1);
	cout << ">> vec1.assign(5, 0000);" << endl;
	vec1.assign(5, 0000);
	cout << ">> vec1 = ";
	print_vector(vec1);
	cout << ">> vec1.size() = ";
	cout << GREEN << vec1.size() << CLR << endl;
	cout << ">> vec1.capacity() = ";
	cout << GREEN << vec1.capacity() << CLR << endl;
	cout << ">> vec2[0] = ";
	print_vector(vec2[0]);
	cout << ">> vec1.assign(vec2[0].begin(), vec2[0].end())" << endl;
	vec1.assign(vec2[0].begin(), vec2[0].end());
	cout << ">> vec1 = ";
	print_vector(vec1);
	cout << ">> vec1.size() = ";
	cout << GREEN << vec1.size() << CLR << endl;

	/**************************** Test 10 ***************************************/
	cout << BOLDWHITE + "\n=== Test 10 - vector::insert ===" + CLR << endl;
	cout << " vector< std::string > vec3{ \"one\", \"two\", \"five\" };" << endl;
	FT::vector< std::string > vec3;
	vec3.push_back("one");
	vec3.push_back("two");
	vec3.push_back("five");
	cout << ">> vec3 = ";
	print_vector(vec3);
	cout << " vec3.insert(vec3.begin(), \"22542\");" << endl;
	vec3.insert(vec3.begin(), "22542");
	cout << ">> vec3 = ";
	print_vector(vec3);
	cout << " vector< std::string > vec4{ \"AAA\", \"EEE\", \"GGG\" };" << endl;
	FT::vector< std::string > vec4;
	vec4.push_back("AAA");
	vec4.push_back("EEE");
	vec4.push_back("GGG");
	cout << ">> vec4 = ";
	print_vector(vec4);
	cout << " vec3.insert(vec3.begin(), vec4.begin(), vec4.end());" << endl;
	vec3.insert(vec3.begin(), vec4.begin(), vec4.end());
	cout << ">> vec3 = ";
	print_vector(vec3);

	/**************************** Test 11 ***************************************/
	cout << BOLDWHITE + "\n=== Test 11 - vector::erase ===" + CLR << endl;
	cout << ">> vector< std::string >::iterator ptr = vec3.begin();" << endl;
	FT::vector< std::string >::iterator ptr = vec3.begin();
	cout << ">> vector< std::string >::iterator ret;" << endl;
	FT::vector< std::string >::iterator ret;

	cout << ">> while (*ptr != \"one\") { ptr++; }" << endl;
	while (*ptr != "one")
	{
		ptr++;
	}
	cout << ">> ret = vec3.erase(ptr);" << endl;
	ret = vec3.erase(ptr);
	cout << ">> *ret = ";
	cout << GREEN << *ret << CLR << endl;
	cout << ">> vec3 = ";
	print_vector(vec3);
	cout << ">> vec3.size() = ";
	cout << GREEN << vec3.size() << CLR << endl;
	cout << ">> vec3.erase(vec3.begin(), vec3.begin() + 2);" << endl;
	vec3.erase(vec3.begin(), vec3.begin() + 2);
	cout << ">> vec3 = ";
	print_vector(vec3);
	cout << ">> vec3.size() = ";
	cout << GREEN << vec3.size() << CLR << endl;

	/**************************** Test 12 ***************************************/
	cout << BOLDWHITE + "\n=== Test 12 - vector::swap and ft::swap() ===" + CLR << endl;

	cout << ">> vec3 = ";
	print_vector(vec3);
	cout << ">> vec4 = ";
	print_vector(vec4);
	cout << ">> vec3.swap(vec4);" << endl;
	vec3.swap(vec4);
	cout << ">> vec3 = ";
	print_vector(vec3);
	cout << ">> vec3.size() = ";
	cout << GREEN << vec3.size() << CLR << endl;
	cout << ">> vec4 = ";
	print_vector(vec4);
	cout << ">> vec4.size() = ";
	cout << GREEN << vec4.size() << CLR << endl;
	cout << ">> swap(vec3, vec4);" << endl;
	FT::swap(vec3, vec4);
	cout << ">> vec3 = ";
	print_vector(vec3);
	cout << ">> vec4 = ";
	print_vector(vec4);

	/**************************** Test 13 ***************************************/
	cout << BOLDWHITE + "\n=== Test 13 - vector's relational operators ===" + CLR << endl;
	cout << ">> vector< int > foo(5, 133);" << endl;
	FT::vector< int > foo(5, 133); // 5 целых числа со значением 133
	cout << ">> foo = ";
	print_vector(foo);
	cout << ">> vector< int > foo2(3, 435);" << endl;
	FT::vector< int > foo2(3, 435); // 3 целых числа со значением 435
	cout << ">> foo2 = ";
	print_vector(foo2);
	if (foo == foo2)
		cout << "foo == foo2" << CLR << endl;
	if (foo != foo2)
		cout << GREEN << "foo != foo2" << CLR << endl;
	if (foo < foo2)
		cout << GREEN << "foo < foo2" << CLR << endl;
	if (foo > foo2)
		cout << "foo > foo2" << CLR << endl;
	if (foo <= foo2)
		cout << GREEN << "foo <= foo2" << CLR << endl;
	if (foo >= foo2)
		cout << "foo >= foo2" << CLR << endl;

	/**************************** Test 14 ***************************************/
	cout << BOLDWHITE + "\n=== Test 14 - vector, reverse iterator, const iterator ===" + CLR << endl;
	FT::vector< std::string > vec5;
	vec5.push_back("TOR");
	vec5.push_back("10");
	vec5.push_back("Lokki");
	vec5.push_back("84");

	cout << ">> FT::vector< std::string > vec5{ \"TOR\", 10,  \"Lokki\", 84 };" << endl;
	print_vector(vec5);
	cout << ">> FT::vector< std::string >::reverse_iterator rev_it = vec5.rbegin();" << endl;
	FT::vector< std::string >::reverse_iterator rev_it = vec5.rbegin();
	cout << ">> FT::vector< std::string >::const_iterator const_it = vec5.end();" << endl;
	FT::vector< std::string >::const_iterator const_it = vec5.end();
	cout << ">> *rev_it = ";
	cout << GREEN << *rev_it << CLR << endl;
	cout << ">> rev_it++;" << endl;
	rev_it++;
	cout << ">> *rev_it = ";
	cout << GREEN << *rev_it << CLR << endl;
	cout << ">> const_it--;" << endl;
	const_it--;
	cout << ">> *const_it = ";
	cout << GREEN << *const_it << CLR << endl;

	/**************************** Test 15 ***************************************/
	cout << BOLDWHITE + "\n=== Test 15 - stack ===" + CLR << "\n";
	cout << ">> FT::stack<int, FT::vector<int>> numbers;" << endl;
	FT::stack< int, FT::vector< int > > numbers;
	cout << ">> numbers.push(0);" << endl;
	cout << ">> numbers.push(1);" << endl;
	cout << ">> numbers.push(2);" << endl;
	cout << ">> numbers.push(3);" << endl;
	cout << ">> numbers.push(4);" << endl;
	numbers.push(0);
	numbers.push(1);
	numbers.push(2);
	numbers.push(3);
	numbers.push(4);
	cout << ">> numbers = ";
	print_stack(numbers);
	cout << ">> numbers.pop();" << endl;
	numbers.pop();
	cout << ">> numbers = ";
	print_stack(numbers);
	cout << ">> numbers.top() = ";
	cout << GREEN << numbers.top() << CLR << endl;
	cout << ">> numbers.size() = ";
	cout << GREEN << numbers.size() << CLR << endl;
	cout << ">> numbers.empty() = ";
	cout << GREEN << numbers.empty() << CLR << endl;
	cout << ">> numbers.pop();" << endl;
	cout << ">> numbers.pop();" << endl;
	cout << ">> numbers.pop();" << endl;
	cout << ">> numbers.pop();" << endl;
	numbers.pop();
	numbers.pop();
	numbers.pop();
	numbers.pop();
	cout << ">> numbers.empty() = ";
	cout << GREEN << numbers.empty() << CLR << endl;
	cout << ">> numbers.size() = ";
	cout << GREEN << numbers.size() << CLR << endl;
	cout << ">> FT::stack<int, FT::vector< int >> numbers2;" << endl;
	FT::stack< int, FT::vector< int > > numbers2;
	cout << ">> numbers2.push(100);" << endl;
	numbers2.push(100);
	cout << ">> numbers.push(100);" << endl;
	numbers.push(100);
	cout << ">> (numbers == numbers2) = ";
	cout << GREEN << (numbers == numbers2) << CLR << endl;
	cout << ">> (numbers != numbers2) = ";
	cout << GREEN << (numbers != numbers2) << CLR << endl;
	cout << ">> (numbers < numbers2) = ";
	cout << GREEN << (numbers < numbers2) << CLR << endl;
	cout << ">> (numbers <= numbers2) = ";
	cout << GREEN << (numbers <= numbers2) << CLR << endl;
	cout << ">> (numbers > numbers2) = ";
	cout << GREEN << (numbers > numbers2) << CLR << endl;
	cout << ">> (numbers >= numbers2) = ";
	cout << GREEN << (numbers >= numbers2) << CLR << endl;

	cout << ">> FT::stack<int, std::list<int>> numbers3;" << endl;
	FT::stack< int, std::list< int > > numbers3;
	cout << ">> numbers3.push(222);" << endl;
	cout << ">> numbers3.push(333);" << endl;
	cout << ">> numbers3.push(444);" << endl;
	cout << ">> numbers3.push(555);" << endl;
	cout << ">> numbers3.push(666);" << endl;
	numbers3.push(222);
	numbers3.push(333);
	numbers3.push(444);
	numbers3.push(555);
	numbers3.push(666);
	cout << ">> numbers3 = ";
	print_stack(numbers3);

	/****************** Test 16 - iterator traits *******************************/
	cout << BOLDWHITE + "\n=== Test 16 ===" + CLR << endl;
	typedef FT::iterator_traits< FT::vector< std::string >::iterator > traits;
	if (typeid(traits::iterator_category) == typeid(std::random_access_iterator_tag))
	cout << "standard_iterator is a random-access iterator" << endl;
	if (typeid(traits::iterator_category) == typeid(std::bidirectional_iterator_tag))
	cout << "standard_iterator is a bidirectional iterator" << endl;

	typedef FT::iterator_traits< std::map< std::string, std::string >::iterator > traits2;
	if (typeid(traits2::iterator_category) == typeid(std::random_access_iterator_tag))
	cout << "map_iterator is a random-access iterator" << endl;
	if (typeid(traits2::iterator_category) == typeid(std::bidirectional_iterator_tag))
	cout << "map_iterator is a bidirectional iterator" << endl;

	/****************** Test 17 - RBTree tests **********************************/
	cout << BOLDWHITE + "\n=== Test 17 - RBTree tests ===" + CLR << endl;
	ft::RBTree< std::string, int, std::allocator< ft::pair< std::string, int > >,
				ft::pair< std::string, int > > tree;
	tree.insert_key("AAAS", 0);
	tree.insert_key("GGGT", 1);
	tree.insert_key("RRRR", 2);
	tree.insert_key("ff", 3);
	tree.insert_key("sd", 4);
	tree.insert_key("EED", 5);
	tree.insert_key("hHH", 6);
	tree.insert_key("ZZE", 7);
	tree.insert_key("ZZC", 8);
	tree.print_tree();

	cout << ">> tree.erase_key(\"EED\");" << endl;
	tree.erase_key("EED");
	tree.print_tree();
	cout << ">> tree.erase_key(\"ZZE\");" << endl;
	tree.erase_key("ZZE");
	tree.print_tree();
	cout << ">> tree.erase_key(\"ff\");" << endl;
	tree.erase_key("ff");
	tree.print_tree();
	cout << ">> tree.insert_key(\"20\");" << endl;
	tree.insert_key("20", 20);
	tree.print_tree();
	cout << ">> tree.insert_key(\"18\");" << endl;
	tree.insert_key("18", 18);
	tree.print_tree();

	/****************** Test 18 - map tests I ***********************************/
	cout << BOLDWHITE + "\n=== Test 18 - map tests I ===" + CLR << endl;
	cout << ">> map< std::string, std::string > mapping;" << endl;
	FT::map< std::string, std::string > mapping;
	cout << ">> mapping[\"test1\"] = ok test 1;" << endl;
	mapping["test1"] = "ok test 1";
	cout << ">> mapping[\"test1\"] = ";
	cout << GREEN << mapping["test1"] << CLR << endl;
	cout << ">> mapping[\"test1\"] = ok 42;" << endl;
	mapping["test1"] = "ok 42";
	cout << ">> mapping[\"test1\"] = ";
	cout << GREEN << mapping["test1"] << CLR << endl;
	cout << ">> mapping[\"test2\"] = ok test 2;" << endl;
	mapping["test2"] = "ok test 2";
	cout << ">> mapping[\"test2\"] = ";
	cout << GREEN << mapping["test2"] << CLR << endl;
	// mapping["test3"] = "TEST 3";
	cout << ">> msping.size = " << mapping.size() << endl;
	cout << ">> map< std::string, std::string >::iterator map_it = " "mapping.begin();" << endl;
	FT::map< std::string, std::string >::iterator map_it = mapping.begin();
	cout << ">> map_it->first = ";
	cout << GREEN << map_it->first << CLR << endl;
	cout << ">> map_it->second = ";
	cout << GREEN << map_it->second << CLR << endl;
	cout << ">> (*map_it).first = ";
	cout << GREEN << (*map_it).first << CLR << endl;

	/****************** Test 19 - map tests II **********************************/
	cout << BOLDWHITE + "\n=== Test 19 - map tests II ===" + CLR << endl;
	cout << ">> map< std::string, std::string >::iterator it_copy = map_it++;" << endl;
	FT::map< std::string, std::string >::iterator it_copy = map_it++;
	cout << ">> map_it = ";
	cout << GREEN << "(" << map_it->first << ", " << map_it->second << ")" << CLR << endl;
	cout << ">> it_copy = ";
	cout << GREEN << "(" << it_copy->first << ", " << it_copy->second << ")" << CLR << endl;

	FT::map< std::string, int > mapping2;
	FT::map< std::string, int >::iterator map_it2;
	mapping2["Piter"] = 0;
	mapping2["Halk"] = 1;
	mapping2["Stark"] = 2;
	mapping2["Vision"] = 3;
	mapping2["LOkki"] = 4;
	mapping2["Batman"] = 5;
	mapping2["Superman"] = 6;
	mapping2["Flash"] = 7;
	mapping2["Aquaman"] = 8;

	ft::RBTree< std::string, int, std::allocator< ft::pair< std::string, int > >,
				ft::pair< std::string, int > > tree2;
	tree2.insert_key("Piter", 0);
	tree2.insert_key("Halk", 1);
	tree2.insert_key("Stark", 2);
	tree2.insert_key("Vision", 3);
	tree2.insert_key("LOkki", 4);
	tree2.insert_key("Batman", 5);
	tree2.insert_key("Superman", 6);
	tree2.insert_key("Flash", 7);
	tree2.insert_key("Aquaman", 8);
	tree2.print_tree();

	cout << ">> map_it2 = mapping2.begin()++;" << endl;
	map_it2 = mapping2.begin()++;
	cout << ">> map_it2->first = ";
	cout << map_it2->first << endl;
	cout << ">> for (map_it2 = mapping2.begin(); map_it2 != mapping2.end(); map_it2++)" << endl;
	cout << GREEN << "{";
	for (map_it2 = mapping2.begin(); map_it2 != mapping2.end(); map_it2++)
	{
		cout << "(" << map_it2->first << ", " << map_it2->second << ")" << " ";
	}
	cout << "}" << CLR << endl;
	cout << ">> for (map_it2 = mapping2.begin(); map_it2 != mapping2.end(); ++map_it2)" << endl;
	cout << GREEN << "{";
	for (map_it2 = mapping2.begin(); map_it2 != mapping2.end(); ++map_it2)
	{
		cout << "(" << map_it2->first << ", " << map_it2->second << ")" << " ";
	}
	cout << "}" << CLR << endl;

	/****************** Test 20 - map tests III *********************************/
	cout << BOLDWHITE + "\n=== Test 20 - map tests III ===" + CLR << endl;
	cout << ">> while (map_it2 != mapping2.begin()) { map_it2--; map_it2; } " << endl;

	cout << GREEN << "{";
	while (map_it2 != mapping2.begin())
	{
		map_it2--;
		cout << "(" << map_it2->first << ", " << map_it2->second << ")" << " ";
	}
	cout << "}" << CLR << endl;
	cout << ">> map_it2 = mapping2.begin();" << endl;
	map_it2 = mapping2.end();
	cout << ">> while (map_it2 != mapping2.begin()) { --map_it2; map_it2; } " << endl;
	cout << GREEN << "{";
	while (map_it2 != mapping2.begin())
	{
		--map_it2;
		cout << "(" << map_it2->first << ", " << map_it2->second << ")" << " ";
	}
	cout << "}" << CLR << endl;

	/****************** Test 21 - map tests IV **********************************/
	cout << BOLDWHITE + "\n=== Test 21 - map tests IV ===" + CLR << endl;
	FT::map< std::string, int >::reverse_iterator r;
	r = mapping2.rend();
	cout << ">> r--" << endl;
	r--;
	cout << ">> r->first = ";
	cout << GREEN << r->first << CLR << endl;
	cout << ">> r++" << endl;
	cout << ">> r++" << endl;
	r++;
	r++;
	cout << ">> r->first = ";
	cout << GREEN << r->first << CLR << endl;
	cout << ">> r++" << endl;
	cout << GREEN << "{";
	for (; r != mapping2.rend(); r++)
	{
		cout << "(" << r->first << ", " << r->second << ")" << " ";
	}
	cout << "}" << CLR << endl;
	cout << ">> r--" << endl;
	r--;
	cout << ">> r->first = ";
	cout << GREEN << r->first << CLR << endl;
	cout << ">> mapping2.rbegin()->first = ";
	cout << GREEN << mapping2.rbegin()->first << CLR << endl;
	FT::map< std::string, int >::reverse_iterator r2;
	r2 = r++;
	cout << ">> r2->first = ";
	cout << GREEN << r2->first << CLR << endl;
	cout << ">> --r" << endl;
	r2 = --r;
	cout << ">> --r" << endl;
	r2 = --r;
	cout << ">> r2->first = ";
	cout << GREEN << r2->first << CLR << endl;
	cout << ">> ++r" << endl;
	r2 = ++r;
	cout << ">> r2->first = ";
	cout << GREEN << r2->first << CLR << endl;
	cout << ">> ++r" << endl;
	r2 = ++r;
	r2 = r++;
	cout << ">> r->first = ";
	cout << GREEN << r->first << CLR << endl;
	r2 = r--;
	cout << ">> [TEST] r2->first = ";
	cout << GREEN << r2->first << CLR << endl;
	cout << ">> r2->first = ";
	cout << GREEN << r2->first << CLR << endl;
	cout << ">> r = mapping2.rbegin();" << endl;
	r = mapping2.rbegin();
	cout << ">> r->first = ";
	cout << GREEN << r->first << CLR << endl;
	cout << ">> for (; r != mapping2.rend(); r++)" << endl;
	cout << GREEN << "{";
	for (; r != mapping2.rend(); r++)
	{
		cout << "(" << r->first << ", " << r->second << ")" << " ";
	}
	cout << "}" << CLR << endl;

	/****************** Test 22 - map functions I *******************************/
	cout << BOLDWHITE + "\n=== Test 22 - map functions I ===" + CLR << endl;
	cout << ">> mapping2.empty() = ";
	cout << GREEN << mapping2.empty() << CLR << endl;
	cout << ">> mapping2.size() = ";
	cout << GREEN << mapping2.size() << CLR << endl;
	cout << ">> mapping2.max_size() = ";
	cout << mapping2.max_size() << CLR << endl;
	cout << ">> mapping2[\"Halk\"] = ";
	cout << GREEN << mapping2["Halk"] << CLR << endl;
	cout << ">> mapping2.size() = ";
	cout << GREEN << mapping2.size() << CLR << endl;
	cout << ">> mapping2.begin()->first = ";
	cout << GREEN << mapping2.begin()->first << CLR << endl;
	cout << ">> mapping2.begin()->second = ";
	cout << GREEN << mapping2.begin()->second << CLR << endl;
	cout << ">> mapping2.insert(mapping2.begin(), FT::make_pair(\"Ron\", 42));" << endl;
	mapping2.insert(mapping2.begin(), FT::make_pair("Ron", 42));
	cout << ">> mapping2.size() = ";
	cout << GREEN << mapping2.size() << CLR << endl;
	cout << ">> mapping2[\"Ron\"] = ";
	cout << GREEN << mapping2["Ron"] << CLR << endl;
	cout << ">> mapping2.insert(mapping2.begin(), FT::make_pair(\"Ron\", 4224));" << endl;
	mapping2.insert(mapping2.begin(), FT::make_pair("Ron", 4224));
	cout << ">> mapping2.size() = ";
	cout << GREEN << mapping2.size() << CLR << endl;
	cout << ">> mapping2[\"Ron\"] = ";
	cout << GREEN << mapping2["Ron"] << CLR << endl;
	tree2.insert_key("Ron", 42);
	tree2.print_tree();

	/****************** Test 23 - map functions II ******************************/
	cout << BOLDWHITE + "\n=== Test 23 - map functions II ===" + CLR << endl;
	cout << ">> map< std::string, int > mapping3;" << endl;
	FT::map< std::string, int > mapping3;
	cout << ">> mapping3 = mapping2;" << endl;
	mapping3 = mapping2;
	cout << ">> mapping2.begin()._M_node = ";
	cout << mapping2.begin()._M_node << CLR << endl;
	cout << ">> mapping3.begin()._M_node = ";
	cout << mapping3.begin()._M_node << CLR << endl;

	cout << ">> mapping2.begin()->first = ";
	cout << GREEN << mapping2.begin()->first << CLR << endl;
	cout << ">> mapping3.begin()->first = ";
	cout << GREEN << mapping3.begin()->first << CLR << endl;

	cout << ">> mapping2.size() = ";
	cout << GREEN << mapping2.size() << CLR << endl;
	cout << ">> mapping3.size() = ";
	cout << GREEN << mapping3.size() << CLR << endl;
	cout << ">> (mapping3 == mapping2) = ";
	cout << GREEN << (mapping3 == mapping2) << CLR << endl;
	cout << ">> mapping2.erase(\"Halk\");" << endl;
	cout << "return_value = " << GREEN << mapping2.erase("Halk") << CLR << endl;
	cout << ">> mapping2.size() = ";
	cout << GREEN << mapping2.size() << CLR << endl;
	cout << ">> mapping3.size() = ";
	cout << GREEN << mapping3.size() << CLR << endl;
	cout << ">> (mapping3 == mapping2) = ";
	cout << GREEN << (mapping3 == mapping2) << CLR << endl;

	cout << ">> mapping2.erase(++mapping2.begin(), mapping2.end());" << endl;
	mapping2.erase(++mapping2.begin(), mapping2.end());
	cout << ">> mapping2.size() = ";
	cout << GREEN << mapping2.size() << CLR << endl;
	cout << ">> mapping2.begin()->first = ";
	cout << GREEN << mapping2.begin()->first << CLR << endl;

	cout << ">> mapping2.erase(mapping2.begin());" << endl;
	mapping2.erase(mapping2.begin());
	cout << ">> mapping2.size() = ";
	cout << GREEN << mapping2.size() << CLR << endl;

	/**************** Test 24 - map functions III *******************************/
	cout << BOLDWHITE + "\n=== Test 24 - map functions III ===" + CLR << endl;
	mapping2.insert(FT::make_pair("AA", 0));
	mapping2.insert(FT::make_pair("NN", 1));
	mapping2.insert(FT::make_pair("DD", 3));
	mapping2.insert(FT::make_pair("LL", 4));
	mapping2.insert(FT::make_pair("FF", 5));
	mapping2.insert(FT::make_pair("SS", 6));

	cout << ">> mapping2.begin()->first = ";
	cout << GREEN << mapping2.begin()->first << CLR << endl;
	cout << ">> mapping2.size() = ";
	cout << GREEN << mapping2.size() << CLR << endl;
	cout << ">> mapping3.begin()->first = ";
	cout << GREEN << mapping3.begin()->first << CLR << endl;
	cout << ">> mapping3.size() = ";
	cout << GREEN << mapping3.size() << CLR << endl;

	mapping2.swap(mapping3);
	cout << ">> mapping2.swap(mapping3);" << endl;
	cout << ">> mapping2.begin()->first = ";
	cout << GREEN << mapping2.begin()->first << CLR << endl;
	cout << ">> mapping2.size() = ";
	cout << GREEN << mapping2.size() << CLR << endl;
	cout << ">> mapping3.begin()->first = ";
	cout << GREEN << mapping3.begin()->first << CLR << endl;
	cout << ">> mapping3.size() = ";
	cout << GREEN << mapping3.size() << CLR << endl;

	/**************** Test 25 - map functions IV ********************************/
	cout << BOLDWHITE + "\n=== Test 25 - map functions IV ===" + CLR << endl;
	cout << ">> mapping2.clear();" << endl;
	mapping2.clear();
	cout << ">> mapping2.size() = ";
	cout << GREEN << mapping2.size() << CLR << endl;
	cout << ">> mapping3.count(\"AA\") = ";
	cout << GREEN << mapping3.count("AA") << CLR << endl;
	cout << ">> mapping3.count(\"LL\") = ";
	cout << GREEN << mapping3.count("LL") << CLR << endl;

	cout << ">> map_it2 =  mapping3.lower_bound(\"NN\");" << endl;
	map_it2 = mapping3.lower_bound("NN");
	cout << ">> map_it2->first = ";
	cout << GREEN << map_it2->first << CLR << endl;

	cout << ">> map_it2 =  mapping3.upper_bound(\"DD\");" << endl;
	map_it2 = mapping3.upper_bound("DD");
	cout << ">> map_it2->first = ";
	cout << GREEN << map_it2->first << CLR << endl;

	FT::pair< FT::map< std::string, int >::iterator, FT::map< std::string, int >::iterator > res;
	cout << ">> res = mapping3.equal_range(\"DD\");" << endl;
	res = mapping3.equal_range("DD");
	cout << ">> res.first->first = ";
	cout << GREEN << res.first->first << CLR << endl;
	cout << ">> res.second->first = ";
	cout << GREEN << res.second->first << CLR << endl;

	/**************** Performance tests *****************************************/
	cout << BOLDWHITE + "\n=== Performance tests - vector ===" + CLR << endl;

	void (*func_ptr)() = perf_vector_push_back;
	cout << ">> Test 01: vector::push_back for 10000 items <<" << endl;
	chrono(func_ptr, "vector::push_back");
	cout << endl;

	cout << ">> Test 02: vector::insert for 10000 items <<" << endl;
	func_ptr = perf_vector_insert;
	chrono(func_ptr, "vector::insert");
	cout << endl;

	cout << ">> Test 02: vector::clear for 10000 items <<" << endl;
	func_ptr = perf_vector_clear;
	chrono(func_ptr, "vector::clear");
	cout << endl;

	cout << ">> Test 03: map::insert for 10000 items <<" << endl;
	func_ptr = perf_map_insert;
	chrono(func_ptr, "map::insert");
	cout << endl;

	cout << ">> Test 04: map::clear for 10000 items <<" << endl;
	func_ptr = perf_map_clear;
	chrono(func_ptr, "map::clear");
	cout << endl;
}

	// cout << "###################################################################################" << endl;
	// cout << "[s1] Default constructor:" << endl;
	// ft::set<std::string>	s1;
	// cout << "s1.size(): " << s1.size() << endl;
	// cout << "s1.empty(): " << std::boolalpha << s1.empty() << endl;
	// cout << "s1.begin() == s1.end(): " << (s1.begin() == s1.end()) << endl;
	// cout << "s1.insert(\"a\")"<< endl;
	// cout << "s1.insert(\"b\")"<< endl;
	// cout << "s1.insert(\"c\")"<< endl;
	// cout << "s1.insert(\"e\")"<< endl;
	// cout << "s1.insert(\"f\")"<< endl;
	// cout << "s1.insert(\"g\")"<< endl;
	// s1.insert("a");
	// s1.insert("b");
	// s1.insert("c");
	// s1.insert("e");
	// s1.insert("f");
	// s1.insert("g");
	// cout << "s1.size(): " << s1.size() << endl;
	// cout << "s1.empty(): " << std::boolalpha << s1.empty() << endl;
	// cout << "s1.begin() == s1.end(): " << (s1.begin() == s1.end()) << endl;
	// print_set(s1, "s1");
	// cout << "s1.erase(--s1.end())" << endl;
	// s1.erase(--s1.end());
	// cout << "s1.erase(s1.find(\"e\"))" << endl;
	// s1.erase(s1.find("e"));
	// print_set(s1, "s1");
	// cout << "s1.size(): " << s1.size() << endl;
	// cout << "s1.count(\"a\"): " << s1.count("a") << endl;
	// cout << "s1.count(\"e\"): " << s1.count("e") << endl;

	// cout << "***********************************************************************************" << endl;

	// cout << "[s2] Copy constructor:" << endl;
	// ft::set<std::string>	s2(s1);
	// cout << "s2.size(): " << s2.size() << endl;
	// cout << "s2.empty(): " << s2.empty() << endl;
	// cout << "s2.begin() == s2.end(): " << (s2.begin() == s2.end()) << endl;
	// print_set(s2, "s2");
	// cout << "s2.insert(\"new\") "<< endl;
	// s2.insert("new");
	// cout << "s2.size(): " << s2.size() << endl;
	// print_set(s2, "s2");
	// cout << "s2.lower_bound(1): " << *s2.lower_bound("1") << endl;
	// cout << "s2.upper_bound(1): " << *s2.upper_bound("1") << endl;
	// cout << "s2.equal_range(1): " << *s2.equal_range("1").first << endl;
	// cout << "s2.lower_bound(a): " << *s2.lower_bound("a") << endl;
	// cout << "s2.lower_bound(d): " << *s2.lower_bound("d") << endl;
	// cout << "s2.lower_bound(f): " << *s2.lower_bound("f") << endl;
	// cout << "s2.upper_bound(a): " << *s2.upper_bound("a") << endl;
	// cout << "s2.upper_bound(d): " << *s2.upper_bound("d") << endl;
	// cout << "s2.upper_bound(f): " << *s2.upper_bound("f") << endl;
	// cout << "s2.equal_range(a): " << *s2.equal_range("a").first << endl;
	// cout << "s2.equal_range(d): " << *s2.equal_range("d").first << endl;
	// cout << "s2.equal_range(f): " << *s2.equal_range("f").first << endl;
	// cout << "*s2.find(new): " << *s2.find("new") << endl;
	// cout << "*s2.find(old): " << *s2.find("old") << endl;

	// print_set(s1, "s1");
	// print_set(s2, "s2");
	// cout << "s1.swap(s2)" << endl;
	// s1.swap(s2);
	// print_set(s1, "s1");
	// print_set(s2, "s2");
	// cout << "*s1.begin(): " << *s1.begin() << endl;
	// cout << "*(++s1.begin()): " << *(++s1.begin()) << endl;
	// cout << "*(--s1.end()): " << *(--s1.end()) << endl;
	// cout << "s1.erase(++s1.begin(), s1.end())" << endl;
	// s1.erase(++s1.begin(), s1.end());
	// print_set(s1, "s1");

	// cout << "*s2.begin(): " << *s2.begin() << endl;
	// cout << "*(++s2.begin()): " << *(++s2.begin()) << endl;
	// cout << "*(--s2.end()): " << *(--s2.end()) << endl;
	// cout << "s2.erase(++s2.begin(), --s2.end())" << endl;
	// s2.erase(++s2.begin(), --s2.end());
	// print_set(s2, "s2");
	// ft::set<std::string>::iterator	last = s2.begin();
	// (void)last;
	// cout << "###################################################################################" << endl;