#pragma once
#include "Person.h"

class Worker: public Person
{
public:
  Worker( string name="", string surname="", int age=0, double brutto=0, int staz=0);

  void setSurname(string newSurname);
  string getSurname() const;

  void setStaz(int newStaz);//lata doswiadczenia
  int getStaz();

  void setBruttoSalary(double brutto);
  double getBruttoSalary();
  virtual double NettoSalary() = 0; //?? abstrakcyjna

  void setSubject(string subject);
  string getSubject();//przedmiot
  void setClassName(string className);
  string getClassName();// wychowawca klasy

  void setStanowisko(string stanowisko);
  string getStanowisko();

  void printWorker();
  virtual void printRest() {}; //abstrakcyjna dla nauczyciela przdemiot i klasa/pusty
                                //dla admin stanowisko
private:
  double m_salary;
  string m_Surname;
  int m_Staz;
  string m_Subject;
  string m_ClassName;
  string m_Stanowisko;

};
////////// inline ///////////

inline void Worker::setSubject(string subject)
{
  m_Subject = subject;
}
inline string Worker::getSubject()
{
  return m_Subject;
}

inline void Worker::setClassName(string className)
{
  m_ClassName = className;
}
inline string Worker::getClassName()
{
  return m_ClassName;
}

inline void Worker::setStanowisko(string stanowisko)
{
  m_Stanowisko = stanowisko;
}
inline string Worker::getStanowisko()
{
  return m_Stanowisko;
}