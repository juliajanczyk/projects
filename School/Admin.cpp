#include "Admin.h"

Admin::Admin(string name, string surname, int age, double brutto, int staz ): Worker(name, surname, age, brutto, staz)
{
  //setStanowisko(stanowisko);
  //setNettoSalary
}

double Admin::calcTax()
{
  double koszt_uzysku = 111.25;
  double kwota_wolna = 556.02;
  double tax = (getBruttoSalary() - koszt_uzysku);
  tax = (tax * 18 / 100 - kwota_wolna);

  if (tax < 0)
    return 0;
  return tax;
}
double Admin::getTax()
{
  return m_tax;
}

double Admin::NettoSalary()
{
  return ( getBruttoSalary() - calcTax() );
}

void Admin::printRest()
{
  cout <<"Administrator na stanowisku "<< getStanowisko() << endl;
} 
