#pragma once
#include <iostream>
using namespace std;
#include <string>

class Person
{
public:
  Person(string name = "", int age = 0) noexcept;
  virtual ~Person();
  // Person& operator = ( const Person& )

  void setName( string newName );
  void setAge( int newAge );
  void setPerson( string newName, int newAge);

  string getName() const;
  int getAge() const;

private:
  string m_Name;
  int m_Age;
};

