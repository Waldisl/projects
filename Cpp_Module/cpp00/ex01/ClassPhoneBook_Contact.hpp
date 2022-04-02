#ifndef CLASSPHONEBOOK_CONTACT_HPP
#define CLASSPHONEBOOK_CONTACT_HPP

#include <iostream>
#include <string>
#include <iomanip>

class Contact
{
private:
	bool		flag;
	std::string	First;
	std::string	Last;
	std::string	Nick;
	std::string	Number;
	std::string	Secret;

public:
	Contact(void)
	{
		this->flag = false;
	}
	~Contact(void)
	{
	}

	bool		GetFull(void)
	{
		return this->flag;
	}

	std::string	GetFirst(void)
	{
		return this->First;
	}

	std::string	GetLast(void)
	{
		return this->Last;
	}

	std::string	GetNick(void)
	{
		return this->Nick;
	}

	std::string	GetNumber(void)
	{
		return this->Number;
	}

	std::string	GetSecret(void)
	{
		return this->Secret;
	}

	void		SetFull(bool flag)
	{
		this->flag = flag;
	}

	void		SetFirst(std::string str)
	{
		this->First = str;
	}

	void		SetLast(std::string str)
	{
		this->Last = str;
	}

	void		SetNick(std::string str)
	{
		this->Nick = str;
	}

	void		SetNumber(std::string str)
	{
		this->Number = str;
	}

	void		SetSecret(std::string str)
	{
		this->Secret = str;
	}
};

class PhoneBook
{
private:
	Contact Contacts[8];
	int		next;

public:

	PhoneBook(void)
	{
		next = 0;
	}

	~PhoneBook(void)
	{
	}

	int			Getnext()
	{
		return next;
	}

	std::string	GetContactStep(int i, int step)
	{
		if (step == 1)
			return this->Contacts[i].GetFirst();
		else if (step == 2)
			return this->Contacts[i].GetLast();
		else if (step == 3)
			return this->Contacts[i].GetNick();
		else if (step == 4)
			return this->Contacts[i].GetNumber();
		else
			return this->Contacts[i].GetSecret();
	}

	bool		GetContactFull(int i)
	{
		return this->Contacts[i].GetFull();
	}

	void		Setnext(int next)
	{
		this->next = next;
	}

	void		SetContactStep(int i, int step, std::string str)
	{
		if (step == 1)
			this->Contacts[i].SetFirst(str);
		else if (step == 2)
			this->Contacts[i].SetLast(str);
		else if (step == 3)
			this->Contacts[i].SetNick(str);
		else if (step == 4)
			this->Contacts[i].SetNumber(str);
		else if (step == 5)
			this->Contacts[i].SetSecret(str);
	}

	void		SetContactFull(int i)
	{
		this->Contacts[i].SetFull(true);
	}
};

int		ft_add(PhoneBook *PhoneBook);
int		ft_search(PhoneBook *PhoneBook);
void	print_contacts(PhoneBook *PhoneBook);
void	print_short(PhoneBook *PhoneBook, int i);
void	print_long(PhoneBook *PhoneBook, int i, int step);
bool	num_index(std::string index);
void	print_contact(PhoneBook *PhoneBook, int i);

#endif
