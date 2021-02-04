#include <iostream>
#include "Lecture.h"
#include <string>

using namespace std;

int main(int argc, char** argv)
{
  if(argc != 2)
  {
    cout << "argc error" << endl;
    return 1;
  }
  string path(argv[1]);
  Lecture lecture;
  lecture.Read(&path);
  string* s = lecture.return_lm();
  int size = lecture.get_size();
  
  for(int i = 0; i < size; i++)
  {
    cout << s[i] << endl;
  }
  
  return 1;
}
