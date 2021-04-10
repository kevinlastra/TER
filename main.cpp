#include <iostream>
#include "TimeDivision.h"
#include "Lecture.h"
#include "Ecriture.h"
#include "Identify.h"
#include "Comparer.h"
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
  
  Identify iden(s,size);
  TimeDivision* tl = iden.get_TimeLines();
  
  cout <<"  NB TIMELINES "<< tl->size()<<endl;
  tl->clear_tl();
  cout <<"  NB TIMELINES "<< tl->size()<<endl;
  
  string write_path= "output/result.pgn";
  Ecriture ecriture;
  ecriture.Write(tl,&write_path);

  //Comparer comparer;
  //comparer.Compare(argv[1],"output/result.pgn");
  return 1;
}
