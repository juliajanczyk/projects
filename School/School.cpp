#include <iostream>
using namespace std;
#include "SchoolBoy.h"
#include "SchoolGirl.h"
#include "Teacher.h"
#include "Admin.h"

#define MAXPUPIL 9
#define MAXWORKER 9

void printPupils(Pupil** tab, int PupilNo);
void sortPupils(Pupil** tab, int PupilNo);

void printWorker(Worker** tab, int WorkerNo);

int main()
{
  Pupil* pupils[MAXPUPIL] = { NULL };
  Pupil* v = NULL;
  //double df = 0.01;

  Worker* workers[MAXWORKER] = { NULL };
  Worker* y = NULL;

  pupils[0] = v = new SchoolBoy("Filip Boczek", 16, "4b");
  v->setNote(POLSKI, 3);
  v->setNote(MATEMATYKA, 5);
  v->setNote(FIZYKA, 3.5);
  v->setNote(CHEMIA, 4);
  v->setNote(INFORMATYKA, 4.5);
  v->setNote(ANGIELSKI, 5);
  v->setNote(NIEMIECKI, 4);

  pupils[1] = v = new SchoolGirl("Klaudia Okon", 18, "4a");
 // v->setNote(POLSKI, 5);
  v->setNote(MATEMATYKA, 5);
  v->setNote(FIZYKA, 5);
 // v->setNote(CHEMIA, 4.5);
  v->setNote(INFORMATYKA, 4);
  v->setNote(ANGIELSKI, 5);
 // v->setNote(NIEMIECKI, 4);

  pupils[2] = v = new SchoolGirl("Klaudia Okon", 16, "4a");
  v->setNote(POLSKI, 5);
  v->setNote(MATEMATYKA, 5);
 // v->setNote(FIZYKA, 5);
  v->setNote(CHEMIA, 4.5);
  //v->setNote(INFORMATYKA, 4);
  //v->setNote(ANGIELSKI, 5);
  v->setNote(NIEMIECKI, 4);

  pupils[3] = v = new SchoolBoy("Adam Marchew", 15, "4b");
  v->setNote(POLSKI, 5);
  v->setNote(MATEMATYKA, 5);
  //v->setNote(FIZYKA, 5);
  //v->setNote(CHEMIA, 4.5);
  //v->setNote(INFORMATYKA, 4);
  //v->setNote(ANGIELSKI, 5);
  v->setNote(NIEMIECKI, 4);

  pupils[4] = v = new SchoolGirl("Klaudia Okon", 14, "7a");
  v->setNote(POLSKI, 5);
  v->setNote(MATEMATYKA, 5);
  //v->setNote(FIZYKA, 5);
  //v->setNote(CHEMIA, 4.5);
  //v->setNote(INFORMATYKA, 4);
  //v->setNote(ANGIELSKI, 5);
  v->setNote(NIEMIECKI, 4);

  pupils[5] = v = new SchoolBoy("Adam Okon", 18, "4a");
  v->setNote(POLSKI, 5);
  v->setNote(MATEMATYKA, 5);
  v->setNote(FIZYKA, 5);
  v->setNote(CHEMIA, 4.5);
  v->setNote(INFORMATYKA, 4);
  //v->setNote(ANGIELSKI, 5);
  v->setNote(NIEMIECKI, 4);


  pupils[6] = v = new SchoolBoy("Adam Marchew", 17, "6b");
  v->setNote(POLSKI, 5);
  v->setNote(MATEMATYKA, 2);
  v->setNote(FIZYKA, 2);
  v->setNote(CHEMIA, 4.5);
  v->setNote(INFORMATYKA, 3);
  v->setNote(ANGIELSKI, 5);
  //v->setNote(NIEMIECKI, 4);

  pupils[7] = v = new SchoolGirl("Klaudia Okon", 15, "6b");
  v->setNote(POLSKI, 5);
  //v->setNote(MATEMATYKA, 5);
  v->setNote(FIZYKA, 5);
  v->setNote(CHEMIA, 4.5);
  v->setNote(INFORMATYKA, 4);
  v->setNote(ANGIELSKI, 5);
  //v->setNote(NIEMIECKI, 4);

  pupils[8]= v = new SchoolBoy("Wieslaw Ptak", 17, "5a");

  sortPupils( pupils, MAXPUPIL );
  printPupils( pupils, MAXPUPIL );
  
  workers[0] = y = new Teacher("Mruczek", "Anna", 57, 3400, 15);
  y->setSubject("Angielski");
  y->setClassName("4b");//wychowawca

  workers[1] = y = new Teacher("Marianski", "Witold", 42, 4500, 8);
  y->setSubject("Niemiecki");
 
  workers[2] = y = new Teacher("Zieba", "Maria", 37, 3200, 5);
  y->setSubject("Polski");
  y->setClassName("4a");

  workers[3] = y = new Teacher("Wieszcz", "Marek", 47, 4700, 20);
  y->setSubject("Niemiecki");

  workers[4] = y = new Teacher("Lewandowska", "Julia", 31, 3200, 4);
  y->setSubject("Matematyka");
  y->setClassName("5a");

  workers[5] = y = new Teacher("Mrowik", "Andrzej", 47, 3700, 20);
  y->setSubject("Chemia");

  workers[6] = y = new Admin("Wozniak", "Mariusz", 54, 4700, 27);
  y->setStanowisko("starszy specjalista");
  
  workers[7] = y = new Admin("Mucha", "Angela", 27, 3700, 5);
  y->setStanowisko("mlodszy specjalista");

  workers[8] = y = new Admin("Szpinak", "Ilona", 42, 4000, 15);
  y->setStanowisko("specjalista");

  printWorker(workers, MAXWORKER);
  
}

void printPupils(Pupil** tab, int PupilNo)
{
  for (int i = 0; i < PupilNo; i++)
  {
    tab[i]->printPupil();
    cout << "\n\n";
  }
}
void sortPupils(Pupil** tab, int PupilNo)
{
  for(int i = 1; i < PupilNo; i++)
  {
    int j = i - 1;
    Pupil* v = tab[i];
    while (j <= 0 && v->getName() < tab[j]->getName())
      tab[j + 1] = tab[j--];
    tab[j + 1] = v;
  }
}
void printWorker(Worker** tab, int WorkerNo)
{
  for (int i = 0; i < WorkerNo; i++)
  {
    tab[i]->printWorker();
    cout << "\n\n";
  }
}
