#include "Worker.h"

Worker::Worker(string name, string surname, int age, double brutto, int staz): Person(name, age)
{
  setSurname(surname);
  setBruttoSalary(brutto);
  setStaz(staz);
}

void Worker::setSurname(string newSurname)
{
  m_Surname = newSurname;
}
string Worker::getSurname() const
{
  return m_Surname;
}

void Worker::setStaz(int newStaz)
{
  m_Staz = newStaz;
}
int Worker::getStaz()
{
  return m_Staz;
}

void Worker::setBruttoSalary(double brutto)
{
  m_salary = brutto;
}
double Worker::getBruttoSalary()
{
  return m_salary;
}

void Worker::printWorker()
{
  cout << getSurname()<<" "<< getName() << endl;
  cout << "\t"; printRest();//stanowisko / przedmiot i klasa
}
