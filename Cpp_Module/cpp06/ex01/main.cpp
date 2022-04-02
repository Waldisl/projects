#include <iostream>
#include <string>
#include <stdint.h>

using std::exception;
using std::cout;
using std::endl;
using std::string;

struct Data
{
	string	name;
	string	position;
	int		age;
	double	grade;
};

uintptr_t serialize(Data *ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data *deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}

int main(void)
{
	Data *Student1 = new Data();
	Data *Student2;
	Data *Student3;

	Student1->name = "James";
	Student1->position = "Graduate";
	Student1->age = 26;
	Student1->grade = 4.3;

	cout << endl << "\tStudent1" << endl;
	cout << "Name:\t\t" << Student1->name << endl;
	cout << "Position:\t" << Student1->position << endl;
	cout << "Age:\t\t" << Student1->age << endl;
	cout << "Grade:\t\t" << Student1->grade << endl;
	cout << "Pointer adress:\t" << Student1 << endl << endl;
	
	uintptr_t Ser = serialize(Student1);
	
	cout << "Serialization:\t" << Ser << endl;
	
	Student2 = deserialize(Ser);

	cout << endl << "\tStudent2" << endl;
	cout << "Name:\t\t" << Student2->name << endl;
	cout << "Position:\t" << Student2->position << endl;
	cout << "Age:\t\t" << Student2->age << endl;
	cout << "Grade:\t\t" << Student2->grade << endl;
	cout << "Pointer adress:\t" << Student2 << endl << endl;

	uintptr_t Ser1 = serialize(Student2);
	
	cout << "Serialization: " << Ser1 << endl;
	
	Student3 = deserialize(Ser1);

	cout << endl << "\tStudent3" << endl;
	cout << "Name:\t\t" << Student3->name << endl;
	cout << "Position:\t" << Student3->position << endl;
	cout << "Age:\t\t" << Student3->age << endl;
	cout << "Grade:\t\t" << Student3->grade << endl;
	cout << "Pointer adress:\t" << Student3 << endl;

	delete Student1;

	return (0);
}