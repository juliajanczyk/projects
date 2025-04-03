#pragma once
#include "Person.h"
#define MAXNOTES 7
#define MAXSUBJECTS  NIEMIECKI+1

//typedef enum{ POLSKI, MATEMATYKA, FIZYKA, CHEMIA, INFORMATYKA, ANGIELSKI, NIEMIECKI} Subjects //c
enum Subjects { POLSKI, MATEMATYKA, FIZYKA, CHEMIA, INFORMATYKA, ANGIELSKI, NIEMIECKI}; //c++

class Pupil: public Person
{
public:
  Pupil( string name="", int age=0, string className="" );
  string getID() const;

  void clearNotes();
  void setNote( Subjects subject, double note );
  
  double getAve() const;
  double calcAve();
 
  void setClassName(string newClassName);
  string getClassName();

  void printPupil();
  virtual void printOutfit() = 0;//abstrakcyjna

protected:
  string m_ID; //identyfikator danego ucznia, czesciowo tworzony w konstruktorze ucznia

private:
  static int m_baseID;
  double m_Notes[MAXSUBJECTS];
  double m_Ave;
  string m_ClassName;
};


inline double Pupil::getAve() const
{
  return m_Ave;
}

inline string Pupil::getID() const
{
  return m_ID;
}

inline void Pupil::setClassName(string newClassName)
{
  m_ClassName = newClassName;
}

inline string Pupil::getClassName()
{
  return m_ClassName;
}