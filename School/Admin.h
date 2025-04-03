#pragma once
#include "Worker.h"

class Admin: public Worker
{
public:
  Admin(string name=" ", string surname=" ", int age=0, double brutto=0, int staz=0);

  double calcTax();
  double getTax();

  double NettoSalary();
  //double getNettoSalary();//?

  void printRest();// stanowisko

private:
  double m_Nsalary;
  double m_tax;
};
