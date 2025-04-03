#include "Pupil.h"

int Pupil::m_baseID = 10000;

Pupil::Pupil( string name , int age, string className ): Person(name, age)
{
  setClassName( className );
  m_ID = to_string( m_baseID++ );
}

void Pupil::clearNotes()
{
  for( int i = 0; i < MAXSUBJECTS; i++) //MAXNOTES
  {
    m_Notes[i] = 0;
  }
}
void Pupil::setNote( Subjects subject, double note )
{
  if (subject >= POLSKI && subject <= NIEMIECKI && note >= 2 && note <= 5)
    m_Notes[subject] = note;
}

double Pupil::calcAve()
{
  double suma = 0;// suma ocen
  int noteNo = 0;//ile ocen

  for (int i = 0; i < MAXSUBJECTS; i++)
  {
    if (m_Notes[i] >= 0)
    {
      suma += m_Notes[i];
      noteNo++;
    }
    else continue;
  }
  if (noteNo == 0) return 0;
  //double average = suma / noteNo;
  //return average;
  return m_Ave = (noteNo)? suma / noteNo : 0;
}
 
void Pupil::printPupil()
{
  cout << getID() << ' ' << getName() << " (" << getClassName() << "), " << getAge() << " lat ";
  //cout << " average " << calcAve() << endl;
  printf(" average %.2lf\n", calcAve());
  cout << "\t"; printOutfit();
}

