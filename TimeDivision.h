#ifndef TIMEDIVISION
#define TIMEDIVISION

#include <vector>
#include "TimeLine.h"
#include "Piece.h"

#define MAX_SCORE 1

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

  //## ADVERTISEMENT ##
  //detruire un tl peut decaler la lecture des tl
  //pour detruir un tl, on doit attendre que tous les tl soient traites
  //
  //detruit le tl a un index i
  void remove_tl_at(int);
  //nettoi tous les tl dont le score est superieur a MAX_SCORE
  void clear_score();
  void clear_tl();
  //prints
  void Print_adresse();
};
#endif
