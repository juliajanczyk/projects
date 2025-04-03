#include "Teacher.h"

Teacher::Teacher(string name, string surname, int age, double brutto, int staz): Worker(name, surname, age, brutto, staz)
{
  //getSubject();
  //getClassName();

}
double Teacher::calcTax()
{
  double koszt_uzysku = 111.25;
  double kwota_wolna = 556.02;
  double tax = ( getBruttoSalary() * 80 / 100 - koszt_uzysku / 2 );
  tax = ( tax * 18 / 100 - kwota_wolna);

  if (tax < 0)
    return 0;
  return tax;
}

double Teacher::NettoSalary()
{
  double brutto = getBruttoSalary();
  double tax = calcTax();
  int wysluga_lat = 0;

  if (getStaz() < 5)
    wysluga_lat = 0;
  else if (getStaz() > 20)
    wysluga_lat = 20;
  else
    wysluga_lat = getStaz();

  brutto = brutto + brutto * wysluga_lat / 100;

  if (isSupervisor())
    return (brutto - tax + 400);//dodatek dla wychowwawcy

  return (brutto - tax);
}

void Teacher::printRest()
{
  cout << "Nauczyciel przedmiotu " << getSubject(); 
  if(isSupervisor()!=0)
    cout<<",  wychowawca " << getClassName() << endl;
}