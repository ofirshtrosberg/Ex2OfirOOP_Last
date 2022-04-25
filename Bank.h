// Ofir Shtrosberg 207828641
#ifndef BANK_H
#define BANK_H

#define _CRT_SECURE_NO_WARNINGS
#include "Account.h"

class Bank
{
public:
	Bank();
	Bank(const char* name, int code);
	~Bank();

public:
	void SetBankName(const char* name);
	void SetAccount(Account** account, int numbeOfAccounts);
	void SetTotal(double total);
	void SetCode(int code);
	const char* GetBankName() const;
	Account** GetAccounts() const;
	int	GetNumberOfAccounts() const;
	double GetTotal() const;
	int	GetCode() const;

public:
	void AddAccount(const Account& account);
	void AddAccount(const Person& per, double amount);
	void AddPerson(const Person& newPerson, const Account& account, double amount);
	void DeleteAccount(const Account& account);
	void DeletePerson(const Person& p);

private:
	char* m_name;
	Account** m_account; //all the accounts in this bank
	int			m_bankCode;
	int			m_numbeOfAccounts; // number of accounts in this bank
	double		m_totalBalance;
};
#endif // BANK_H

