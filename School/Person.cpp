#include "Person.h"

Person::Person( string name, int age ) noexcept
{
  setName( name );
  setAge( age );
}

Person::~Person() {};

void Person::setName( string newName )
{
  m_Name = newName;
}
void Person::setAge( int newAge )
{
  m_Age = newAge;
}
void Person::setPerson( string newName, int newAge) //???
{
  setName(newName);//m_Name = newName;
  setAge(newAge);//m_Age = newAge;
}

string Person::getName() const
{
  return m_Name;
}
int Person::getAge() const
{
  return m_Age;
}