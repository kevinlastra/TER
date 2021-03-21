#ifndef ERREUR_MANAGER
#define ERREUR_MANAGER

#include "TimeDivision.h"
#include "Piece.h"
#include "ArbreMovement.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

struct Info_Erreur
{
  int piece_index;
  
  Type type;
  Coord coord;
  Action action;
  bool color;
  
  Info info;
  
  int MTL_index;
  int Temps_actuel;
};

class Erreur_manager
{
 private:

  TimeDivision* TD;
 public:
  Erreur_manager(TimeDivision*);

  void Traiter_Erreur(Info_Erreur);

  void Pion(Info_Erreur);

  Piece* Manger_en_passant(Info_Erreur);
};

#endif
