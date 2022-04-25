// Ofir Shtrosberg 207828641
#include "Person.h"
//#define _CRT_SECURE_NO_WARNINGS
//constructor
Person::Person(){
    m_name = nullptr;
    m_id = 0;
}
//constructor
Person::Person(const char* name, int id){
    m_name = nullptr;
    SetName(name);
    SetId(id);
}
//constructor
Person::Person(const Person& other){
    m_name = nullptr;
    SetName(other.GetName());
    SetId(other.GetId());
}
//destructor
Person::~Person(){
    delete[] m_name;
}
// delete the old name and change to the new name
void Person::SetName(const char* newName){
    delete[] m_name;
    m_name = new char[strlen( newName ) + 1];
    strcpy( m_name, newName );
}
// set the id
void Person::SetId(int newId){
    m_id = newId;
}
// return the name of the person
char* Person::GetName() const{
    return m_name;
}
// return the id of the person
int Person::GetId() const{
    return m_id;
}