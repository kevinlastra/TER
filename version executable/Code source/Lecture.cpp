#include <fstream>
#include <iostream>
#include <string>
#include "Lecture.h"

using namespace std;

Lecture::Lecture():lm_size(0),max_lmsize(4)
{
  l_movements = new string[4];
}
Lecture::~Lecture()
{
  delete[] l_movements;
}


void Lecture::Read(string* path)
{
  ifstream file(*path);

  if(!file.is_open())
  {
    cout <<"Lecture.cpp - Read() - file input not open" << endl;
    return;
  }

  string line;
  while(getline(file, line))
  {
    if(line.compare("1-0")==0 || line.compare("0-1")==0 ||
       line.compare("1/2-1/2")==0 || line.compare("*")==0)
      break;
    
    string s = line.substr(line.find_first_of(" ",0)+1);
    string a = s.substr(0, s.find_first_of(" "));
    add_string(&a);

    if(s.find_first_of(" ") != string::npos)
    {
      string b = s.substr(s.find_first_of(" ")+1);
      add_string(&b);
    }
  }
  file.close();
}
string* Lecture::return_lm()
{
  return l_movements;
}
int Lecture::get_size()
{
  return lm_size;
}
void Lecture::add_string(string* s)
{
  if(lm_size == max_lmsize)
  {
    resize_lm();
  }
  l_movements[lm_size] = (*s);
  lm_size++;
}
void Lecture::resize_lm()
{
  max_lmsize *= 2;
  string* lm = new string[max_lmsize];
  for(int i = 0; i < lm_size;i++)
  {
    lm[i] = l_movements[i];
  }
  delete[] l_movements;
  l_movements = lm;
}
