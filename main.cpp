#include <iostream>
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

  TimeLine* tl = iden.get_TimeLine();
  tl->toString();

  Instance* ins = tl->get_instance_at(tl->get_size()-1);



  /*int j = 0;
  cout << "i: "<<ins->i<<"   Action: "<<ins->a
       <<"  Piece("<<ins->p->get_pos_at(ins->i).x()
       <<","<<ins->p->get_pos_at(ins->i).y()<<"):"
       <<ins->p->get_Type()<<endl;;

  string write_path= "output/result.pgn";
  Ecriture ecriture;
  ecriture.Write(tl,&write_path);
  Comparer comparer;
  comparer.Compare(argv[1],"output/result.pgn");
  */
  return 1;
}
