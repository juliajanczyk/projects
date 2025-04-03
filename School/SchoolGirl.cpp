#include "SchoolGirl.h"

SchoolGirl::SchoolGirl( string name, int age, string ClassName ) noexcept : Pupil(name, age, ClassName)
{
  m_ID = "F_" + m_ID;
}

void SchoolGirl::printOutfit()
{
  cout << "biala bluzka z krawatem, szkolna marynarka, granatowa/czarna spodniczka, plaskie obuwie" << endl;
}
