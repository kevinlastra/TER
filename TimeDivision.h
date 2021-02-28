#ifndef TIMEDIVISION
#define TIMEDIVISION

#include <vector>
#include "TimeLine.h"
#include "Piece.h"

struct MultiTimeLine
{
  TimeLine* tl;
  int deb;
  int* prox;//prochains timelines
  int prox_size;
  int prev;//remonter dans l'arbre
};
class TimeDivision
{
 private:
  std::vector<MultiTimeLine*> MTL;
  

 public:
  TimeDivision();
  ~TimeDivision();

  int* diviser(int,int,int);//index of incoming timeline, nb de division, deb du nouveau timeline
  int nb_timeline_end();
  int* timelines_end();
  MultiTimeLine* get_TimeLine_at(int);
};
#endif
