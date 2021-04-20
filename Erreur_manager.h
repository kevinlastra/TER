#ifndef ERREUR_MANAGER
#define ERREUR_MANAGER

#include "Info.h"
#include "Erreur_note.h"
#include "Erreur_notation.h"
#include "TimeDivision.h"
#include "Piece.h"
#include "ArbreMovement.h"
#include <stdlib.h>
#include <iostream>

using namespace std;


class Erreur_manager
{
 private:

  TimeDivision* TD;
  Erreur_note* EN;
  Erreur_notation* ENOT;
 public:
  //constructeur
  Erreur_manager(TimeDivision*);
  ~Erreur_manager();
  //debut du traitment des erreur
  void Traiter_Erreur(Info_Erreur);
  //
  bool fill_none_piece();
  std::vector<Arbre*> Gen_Arbre(TimeLine*,std::vector<int>,int);
};

#endif
