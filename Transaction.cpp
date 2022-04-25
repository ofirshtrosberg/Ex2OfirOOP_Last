// Ofir Shtrosberg 207828641
#include "Transaction.h"
#define _CRT_SECURE_NO_WARNINGS
// constructor
Transaction::Transaction(Account *s, Account *d, double amount, const char *date){
    m_date = nullptr;
    SetSource(s);
    SetDes(d);
    SetAmount(amount);
    SetDate(date);
}
// copy constructor
Transaction::Transaction(const Transaction &other){
    m_date = nullptr;
    SetDate(other.m_date);
    SetAmount(other.m_amount);
    SetSource(other.m_source);
    SetDes(other.m_destination);
}
// change the source 
void Transaction::SetSource(Account *src){
    m_source = src;
}
// change the destination
void Transaction::SetDes(Account *dst){
    m_destination = dst;
}
// change the amount
void Transaction::SetAmount(double amount){
    m_amount = amount;
}
// change the date
void Transaction::SetDate(const char *date){
    if (m_date != nullptr) {
        delete[] m_date;
    }
    m_date = new char[strlen( date ) + 1];
    strcpy( m_date, date );
}
// return the current source
Account * Transaction::GetSource() const{
    return m_source;
}
// return the current destination
Account * Transaction::GetDes() const{
    return m_destination;
}
// return the current amount
double Transaction::GetAmount() const{
    return m_amount;
}
// return the current date
char * Transaction::GetDate() const{
    return m_date;
}
