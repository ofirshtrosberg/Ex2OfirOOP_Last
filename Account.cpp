// Ofir Shtrosberg 207828641
#include "Account.h"
#include "iostream"
using namespace std;

// for the account number
int accountsCounter = 0;
//constructor
Account::Account() {
	++accountsCounter;
	m_totalPersons = 0;
	m_persons = nullptr;
	m_numberOfTransaction = 0;
	m_transactionList = nullptr;
	SetAccountNumber(accountsCounter);
	SetBalance(0);
}
//constructor
Account::Account(Person** persons, int count, double balance) {
	++accountsCounter;
	SetAccountNumber(accountsCounter);
	SetBalance(balance);
	m_totalPersons = 0;
	m_persons = nullptr;
	m_transactionList = nullptr;
	m_numberOfTransaction = 0;
	SetPersons(persons, count);
}
//constructor
Account::Account(const Person& person, double balance) {
	++accountsCounter;
	SetAccountNumber(accountsCounter);
	SetBalance(balance);
	m_persons = new Person * [1];
	m_persons[0] = new Person(person);
	m_totalPersons = 1;
	m_transactionList= nullptr;
    m_numberOfTransaction=0;
}
//copy constructor
Account::Account(const Account& other) {
	m_totalPersons = 0;
	m_persons = nullptr;
	m_numberOfTransaction = 0;
	m_transactionList = nullptr;
	SetAccountNumber(other.m_accountNumber);
	SetBalance(other.m_balance);
	SetTransactions(other.m_transactionList, other.m_numberOfTransaction);
	SetPersons(other.m_persons, other.m_totalPersons);
}
//destructor
Account::~Account()
{
	clearPersons();
	clearTransactions();
}
//change the person array
void Account::SetPersons(Person** persons, int count) {
	clearPersons();
	if (persons == nullptr || count == 0) {
		m_persons = nullptr;
		m_totalPersons = 0;
		SetBalance(0);
		return;
	}
	m_totalPersons = count;
	m_persons = new Person*[m_totalPersons];
	for( int i = 0; i < m_totalPersons; i++ )
	    m_persons[i] = new Person( *( persons[i] ) );
}
//change the account number 
void Account::SetAccountNumber(int number) {
	m_accountNumber = number;
}
//change the balance
void Account::SetBalance(double balance) {
	m_balance = balance;
}
//change the transactions list
void Account::SetTransactions(Transaction** newTransaction, int count)
{
	clearTransactions();
	if (newTransaction == nullptr || count == 0) {
		m_transactionList = nullptr;
		m_numberOfTransaction = 0;
		return;
	}
	m_numberOfTransaction = count;
	m_transactionList = new Transaction * [m_numberOfTransaction];
	for (int i = 0; i < m_numberOfTransaction; i++)
	{
		m_transactionList[i] = new Transaction(*(newTransaction[i]));
	}
}
// return the current transactions list
Transaction** Account::GetTransactions() {
	return m_transactionList;
}
// return the current amount of transactions
int Account::GetNumOfTransactions() {
	return m_numberOfTransaction;
}
// return the current person arr
Person** Account::GetPersons() const {
	return m_persons;
}
// return the current len of person arr
int Account::GetTotalPersons() const {
	return m_totalPersons;
}
// return the current account number
int Account::GetAccountNumber() const {
	return m_accountNumber;
}
// return the current balance
double Account::GetBalance() const {
	return m_balance;
}
// withdraw transaction
void Account::Withdraw(double amount, const char* date) {
	auto transaction = new Transaction(this, this, ((-1)*amount), date);
	AddTransaction(*transaction);
}
// deposit transaction
void Account::Deposit(double amount, const char* date) {
	auto transaction = new Transaction(this, this, amount, date);
	AddTransaction(*transaction);
}
// add person to m_persons
void Account::AddPerson(const Person& newPerson, double amount) {
	//check if the person is already exist in current account
	bool personIsFound = false;
	for (int i = 0; i < m_totalPersons; ++i) {
		if (newPerson.GetId() == m_persons[i]->GetId())
			personIsFound = true;
	}
	if (!personIsFound) {
		//update the balance
		SetBalance((m_balance + amount));
		//create a new arr with the new person
		int tempPersonArrLen = m_totalPersons + 1;
		auto tempPersonArr = new Person * [tempPersonArrLen];
		for (int i = 0; i < m_totalPersons; ++i) {
			tempPersonArr[i] = new Person(*m_persons[i]);
		}
		tempPersonArr[m_totalPersons] = new Person(newPerson);
		//delete the old m_persons and update it to be the new arr
		clearPersons();
		m_persons = tempPersonArr;
		m_totalPersons = tempPersonArrLen;
	}
}
// delete person from m_persons
void Account::DeletePerson(const Person& oldPerson)
{
	// check if the person exist in the current account
	int oldPersonIndex = 0;
	bool personIsFound = false;
	for (int i = 0; i < m_totalPersons; ++i)
	{
		if (m_persons[i]->GetId() == oldPerson.GetId())
		{
			oldPersonIndex = i;
			personIsFound = true;
			break;
		}
	}
	//if the person exist, delete him
	if (personIsFound) {
		//if its the last person cleaning the arr (m_persons)
		if (m_totalPersons == 1) {
			clearPersons();
			m_persons = nullptr;
			m_totalPersons = 0;
			return;

		}
		//if its not the last person update the arr to be without him
		int tempPersonArrLen = m_totalPersons - 1;
		auto tempPersonArr = new Person * [tempPersonArrLen];
		int tempPersonArrIndex = 0;
		for (int i = 0; i < m_totalPersons; ++i)
		{
			if (i != oldPersonIndex)
			{
				tempPersonArr[tempPersonArrIndex] = new Person(*m_persons[i]);
				tempPersonArrIndex++;
			}
		}
		clearPersons();
		m_persons = tempPersonArr;
		m_totalPersons = tempPersonArrLen;
	}
}

// add transaction to the current transaction list
void Account::AddTransaction(const Transaction& newTransaction)
{
	//update the transaction list of the dest account
	Account* desAccountPointer = newTransaction.GetDes();
	int desTransListLen = desAccountPointer->GetNumOfTransactions();
	int tempDesTransListLen = desTransListLen + 1;
	auto tempDestTransList = new Transaction * [tempDesTransListLen];
	for (int i = 0; i < desTransListLen; ++i)
	{
		tempDestTransList[i] = new Transaction(*desAccountPointer->GetTransactions()[i]);
	}
	tempDestTransList[desAccountPointer->GetNumOfTransactions()] = new Transaction(newTransaction);
	desAccountPointer->SetTransactions(tempDestTransList, tempDesTransListLen);
	//delete tempDestTransList
	for (int i = 0; i < tempDesTransListLen; ++i) {
		if(tempDestTransList[i]!=nullptr)
			delete tempDestTransList[i];
	}
	delete[] tempDestTransList;
	//update the balance
	newTransaction.GetDes()->SetBalance(desAccountPointer->GetBalance() + newTransaction.GetAmount());

	// if not deposit or withdraw need to update both accounts
	// update the transaction list of the src account
	if (newTransaction.GetDes() != newTransaction.GetSource())
	{
		Account* srcAccountPointer = newTransaction.GetSource();
		int srcTransListLen = srcAccountPointer->GetNumOfTransactions();
		int tempSrcTransListLen = srcTransListLen + 1;
		auto tempSrcTransList = new Transaction * [tempSrcTransListLen];
		for (int i = 0; i < srcTransListLen; ++i)
		{
			tempSrcTransList[i] = new Transaction(*srcAccountPointer->GetTransactions()[i]);
		}
		tempSrcTransList[srcAccountPointer->GetNumOfTransactions()] = new Transaction(newTransaction);
		srcAccountPointer->SetTransactions(tempSrcTransList, tempSrcTransListLen);
		//delete tempDestTransList
		for (int i = 0; i < tempSrcTransListLen; ++i) {
			if(tempSrcTransList[i]!=nullptr)
				delete tempSrcTransList[i];
		}
		delete[] tempSrcTransList;
		//update the balance
		newTransaction.GetSource()->SetBalance(srcAccountPointer->GetBalance() - newTransaction.GetAmount());
	}
}

// delete transactions list
void Account::clearTransactions()
{
	if (m_transactionList!= nullptr)
	{
		for (int i = 0; i < m_numberOfTransaction; ++i) {
			if(m_transactionList[i]!=nullptr)
				delete m_transactionList[i];
		}
		delete[] m_transactionList;
		m_transactionList = nullptr;
		m_numberOfTransaction = 0;
	}
}
// delete m_persons list
void Account::clearPersons()
{
	if (m_totalPersons > 0)
	{
		for (int i = 0; i < m_totalPersons; ++i) {
			if(m_persons[i]!=nullptr)
				delete m_persons[i];
		}
		delete[] m_persons;
		m_persons = nullptr;
		m_totalPersons = 0;
	}
}

