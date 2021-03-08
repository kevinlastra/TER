#ifndef TIMEDIVISION
#define TIMEDIVISION

#include <vector>
#include "TimeLine.h"
#include "Piece.h"

struct MultiTimeLine
{
  TimeLine* tl;

  //deb est le moment dans le temps où identify a trouver un erreur et divise le timeline(prev)
  //en n sub-division, deb sera le premier element des nouveau timeline generer apartir de prev et
  //donc prev-1 et le dernier element de prev
  int deb;
  
  int* prox;//indexs des prochains timelines generer apartir de this
  int prox_size;//nombre de timeline generer apartir de this
  
  int prev;//l'index du timeline d'où previens this
};
class TimeDivision
{
 private:
  std::vector<MultiTimeLine*> MTL;
  

 public:
  TimeDivision();
  ~TimeDivision();
  
  //parametres: index dans MTL du TL qu'on veut diviser, nb de division, deb du nouveau timeline
  int* diviser(int,int,int);

  //nombre de timeline qui n'ont pas de suit ou qui arrive a la fin
  int nb_timeline_end();
  //return les index des timeline qui n'ont pas de suit
  int* timelines_end();

  //return le MTL a l'index n
  MultiTimeLine* get_TimeLine_at(int);
};
#endif
