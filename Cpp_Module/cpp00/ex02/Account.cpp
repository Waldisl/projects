#include <iostream>
#include "Account.hpp"
#include <iomanip>
#include <ctime>

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

int		Account::getNbAccounts(void)
{
	return Account::_nbAccounts;
}

int		Account::getTotalAmount(void)
{
	return Account::_totalAmount;
}

int		Account::getNbDeposits(void)
{
	return Account::_totalNbDeposits;
}

int		Account::getNbWithdrawals(void)
{
	return Account::_totalNbWithdrawals;
}

void	Account::displayAccountsInfos(void)
{
	Account::_displayTimestamp();

	std::cout << "accounts:" << Account::_nbAccounts << ";"
		<< "total:" << Account::_totalAmount << ";"
		<< "deposits:" << Account::_totalNbDeposits << ";"
		<< "withdrawals:" << Account::_totalNbWithdrawals << std::endl;
	Account::_totalAmount = 0;
}

Account::Account(int initial_deposit)
{
	this->_accountIndex = this->_nbAccounts;
	this->_amount = initial_deposit;
	this->_nbDeposits = 0;
	this->_nbWithdrawals = 0;
	this->_nbAccounts++;

	this->_totalAmount += this->_amount;

	this->_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";"
		<< "amount:" << this->_amount << ";" << "created" << std::endl;
}

Account::~Account(void)
{
	this->_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";"
		<< "amount:" << this->_amount << ";" << "closed" << std::endl;
}

void	Account::makeDeposit(int deposit)
{
	int		temp = this->_amount;

	this->_amount += deposit;
	this->_nbDeposits++;
	this->_totalNbDeposits += _nbDeposits;
	this->_totalAmount += this->_amount;
	this->_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";" << "p_amount:" << temp << ";"
		<< "deposit:" << deposit << ";" << "amount:" << this->_amount << ";" 
		<< "nb_deposits:" << this->_nbDeposits << std::endl;
}

bool	Account::makeWithdrawal(int withdrawal)
{
	int		temp = this->_amount;

	this->_displayTimestamp();
	if (withdrawal < this->_amount)
	{
		this->_amount -= withdrawal;
		this->_nbWithdrawals++;
		this->_totalNbWithdrawals += _nbWithdrawals;
		this->_totalAmount += this->_amount;
		std::cout << "index:" << this->_accountIndex << ";"
		<< "p_amount:" << temp << ";" << "withdrawal:" << withdrawal << ";"
		<< "amount:" << this->_amount << ";" 
		<< "nb_withdrawals:" << this->_nbDeposits << std::endl;
		return true;
	}
	else
	{
		this->_totalAmount += this->_amount;
		std::cout << "index:" << this->_accountIndex << ";"
		<< "p_amount:" << temp << ";" << "withdrawal:" << "refused"
		<< std::endl;
	}
	return false;
}

int		Account::checkAmount(void) const
{
	if (this->_amount < 0)
		return (0);
	return (1);
}

void	Account::_displayTimestamp()
{
	std::time_t	timsec = std::time(0);
	std::tm		*times = std::localtime(&timsec);

	
	std::cout << std::setfill('0') << "[" << (1900 + times->tm_year) 
		<< std::setw(2) << times->tm_mon + 1 << std::setw(2) << times->tm_mday << "_"
		<< std::setw(2) << times->tm_hour << std::setw(2) << times->tm_min
		<< std::setw(2) << times->tm_sec << "]" << " ";
}

void	Account::displayStatus(void) const
{
	this->_displayTimestamp();

	std::cout << "index:" << this->_accountIndex << ";"
		<< "amount:" << this->_amount << ";"
		<< "deposits:" << this->_nbDeposits << ";"
		<< "withdrawals:" << this->_nbWithdrawals << std::endl;
}
