#ifndef TIMEDIVISION
#define TIMEDIVISION

#include <vector>
#include "TimeLine.h"
#include "Piece.h"


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
};
#endif
