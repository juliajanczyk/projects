#pragma once
#include "Worker.h"

class Teacher: public Worker
{
public:

  Teacher( string name , string surname, int age, double brutto, int staz);

  double calcTax();
  double getTax();//?
  double NettoSalary();
  //void setNettoSalary();//?
  bool isSupervisor();

  void printRest(); // przedmiot ktorego uczy, klasa

private:
  double m_salary;
  double m_tax;
  bool m_supervisor;
};
/// i ///
inline double Teacher::getTax()
{
  return m_tax;
}

inline bool Teacher::isSupervisor()
{
  return m_supervisor;
}
