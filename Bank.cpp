// Ofir Shtrosberg 207828641
#include "Bank.h"
#include "iostream"
//#define _CRT_SECURE_NO_WARNINGS
using namespace std;
//constructor
Bank::Bank() {
    SetTotal(0);
    SetCode(0);
    m_name = nullptr;
    m_account= nullptr;
    m_numbeOfAccounts=0;
}
//constructor
Bank::Bank(const char *name, int code) {
    SetTotal(0);
    SetCode(code);
    m_name = nullptr;
    SetBankName(name);
    m_account= nullptr;
    m_numbeOfAccounts=0;
}

// destructor delete the name and accounts
Bank::~Bank() {
    if (m_numbeOfAccounts > 0) {
        for (int i = 0; i < m_numbeOfAccounts; ++i) {
            DeleteAccount(*m_account[i]);
        }
        delete[] m_account;
    }
    delete[] m_name;
}

// change the name
void Bank::SetBankName(const char *name) {
    if (m_name != nullptr) {
        delete[] m_name;
    }

    m_name = new char[strlen(name) + 1];
    strcpy(m_name, name);
}
// change the accounts arr
void Bank::SetAccount(Account **account, int numbeOfAccounts) {
    // clear m_account
    if (m_numbeOfAccounts > 0) {
        for (int i = 0; i < m_numbeOfAccounts; ++i) {
            for (int j = 0; j < m_account[i]->GetTotalPersons(); ++j) {
                m_account[i]->DeletePerson(*(m_account[i]->GetPersons()[j]));
            }
            delete m_account[i];
        }
        delete[] m_account;
    }
    m_account = nullptr;

    if (account == nullptr || numbeOfAccounts == 0) {
        m_account = nullptr;
        m_numbeOfAccounts = 0;
        SetTotal(0);
        return;
    }

    m_numbeOfAccounts = numbeOfAccounts;
    m_account = new Account*[m_numbeOfAccounts];
    for( int i = 0; i <m_numbeOfAccounts; i++ )
        m_account[i] = new Account( *( account[i] ) );

    // update the total balance
    double currTotalBalance = 0;
    for (int i = 0; i < m_numbeOfAccounts; ++i) {
        currTotalBalance += m_account[i]->GetBalance();
    }
    SetTotal(currTotalBalance);
}
// change the total balance
void Bank::SetTotal(double total) {
    m_totalBalance = total;
}
// change the code
void Bank::SetCode(int code) {
    m_bankCode = code;
}
// return the current name
const char *Bank::GetBankName() const {
    return m_name;
}
// return the current accounts arr
Account **Bank::GetAccounts() const {
    return m_account;
}
// return the current number of accounts
int Bank::GetNumberOfAccounts() const {
    return m_numbeOfAccounts;
}
// return the current total balance
double Bank::GetTotal() const {
    return m_totalBalance;
}
// return the current code
int Bank::GetCode() const {
    return m_bankCode;
}
// add the account to the bank's accounts arr
void Bank::AddAccount(const Account &account) {
    //check if the account is already exist
    bool accountIsFound = false;
    for (int i = 0; i < m_numbeOfAccounts; ++i) {
        if (m_account[i]->GetAccountNumber() == account.GetAccountNumber())
            accountIsFound = true;
    }
    // if the account is not exist, adding it
    if (!accountIsFound) {
        int tempAccountArrLen = m_numbeOfAccounts + 1;
        auto tempAccountArr = new Account * [tempAccountArrLen];
        for (int i = 0; i < m_numbeOfAccounts; ++i) {
            tempAccountArr[i] = new Account(*m_account[i]);
        }
        tempAccountArr[m_numbeOfAccounts] = new Account(account);

        // delete m_account
        if (m_numbeOfAccounts > 0) {
            for (int i = 0; i < m_numbeOfAccounts; i++)
            {
                delete m_account[i];
            }
            delete[] m_account;
        }
        m_account = nullptr;
        m_account = tempAccountArr;
        m_numbeOfAccounts = tempAccountArrLen;
        //update the total balance
        double totalBalance = 0;
        for (int j = 0; j < m_numbeOfAccounts; j++)
        {
            totalBalance += m_account[j]->GetBalance();
        }
        SetTotal(totalBalance);
    }
}
// add the account to the bank's accounts arr
void Bank::AddAccount(const Person &per, double amount) {
    Account account(per, amount);
    AddAccount(account);
}
// add person to the givem account
// if the account not exist creating account for this person
void Bank::AddPerson(const Person &newPerson, const Account &account, double amount) {
    //check if the account is already exist
    for (int i = 0; i < m_numbeOfAccounts; ++i) {
        if (m_account[i]->GetAccountNumber() == account.GetAccountNumber()) {
            m_account[i]->AddPerson(newPerson, amount);
            //update the balance
            double totalBalance = 0;
            for (int j = 0; j < m_numbeOfAccounts; j++)
            {
                totalBalance += m_account[j]->GetBalance();
            }
            SetTotal(totalBalance);
            return;
        }
    }
    //if the account not exist creating new account
    AddAccount(newPerson, amount);
}
// delete the account from the bank's account arr
void Bank::DeleteAccount(const Account &account) {
    // check if the account exist
    int oldAccountIndex = 0;
    bool accountIsFound = false;
    for (int i = 0; i < m_numbeOfAccounts; ++i)
    {
        if (m_account[i]->GetAccountNumber() == account.GetAccountNumber())
        {
            oldAccountIndex = i;
            accountIsFound = true;
            break;
        }
    }
    // if the account exist delete it
    if (accountIsFound) {
        // if its the last account clear m_account
        if (m_numbeOfAccounts == 1) {
            delete m_account[0];
            delete[] m_account;
            m_account = nullptr;
            m_numbeOfAccounts = 0;
            return;

        }
        // if its not the last account update the accounts arr and remove the given account
        int tempAccountArrLen = m_numbeOfAccounts - 1;
        auto tempAccountArr = new Account * [tempAccountArrLen];
        int tempAccountArrIndex = 0;
        for (int i = 0; i < m_numbeOfAccounts; ++i)
        {
            if (i != oldAccountIndex)
            {
                tempAccountArr[tempAccountArrIndex] = new Account(*m_account[i]);
                tempAccountArrIndex++;
            }
        }
        // delete m_account
        if (m_numbeOfAccounts > 0) {
            for (int i = 0; i < m_numbeOfAccounts; i++)
            {
                delete m_account[i];
            }
            delete[] m_account;
        }
        m_account = nullptr;

        m_account = tempAccountArr;
        m_numbeOfAccounts = tempAccountArrLen;

        // update the total balance
        double totalBalance = 0;
        for (int j = 0; j < m_numbeOfAccounts; j++)
        {
            totalBalance += m_account[j]->GetBalance();
        }
        SetTotal(totalBalance);
    }
}
// delete the given person from all the accounts
void Bank::DeletePerson(const Person &p) {
   /* int numOfAccountTemp = m_numbeOfAccounts;*/
    for (int i = 0; i < m_numbeOfAccounts; ++i) {
        m_account[i]->DeletePerson(p);
        // if it was the las person in the account, delete the account
        if (m_account[i]->GetTotalPersons() == 0) {
            DeleteAccount(*m_account[i]);
           // m_numbeOfAccounts -= 1;
        }
    }
}

