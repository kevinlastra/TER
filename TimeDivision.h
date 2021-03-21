#ifndef TIMEDIVISION
#define TIMEDIVISION

#include <vector>
#include "TimeLine.h"
#include "Piece.h"

#define MAX_SCORE 4

class TimeDivision
{
 private:
  std::vector<TimeLine*> TimeLines;
  

 public:
  TimeDivision();
  ~TimeDivision();
  
  //parametres: index dans MTL du TL qu'on veut diviser, nb de division, deb du nouveau timeline
  int* diviser(int,int);

  TimeLine* TimeLine_at(int);
  int size();

  //indexs,number of indexs,index to kill
  void transform_indexs_before_kill(int*,int,int);
  void remove_tl_at(int);

  void clear_score();
  //prints
  void Print_adresse();
};
#endif
