#ifndef ERREUR_MANAGER
#define ERREUR_MANAGER

#include "TimeDivision.h"
#include "Piece.h"
#include "ArbreMovement.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

//struct en construction, tous les info ne sont pas utiliser
struct Info_Erreur
{
  int piece_index;     //l'index de la piece dans le tl

  //en cas ou la piece n'est pas trouver, donc en collect tous les infos possible
  Type type;
  Coord coord;
  Action action;
  bool color;
  Info info;
  //
  
  int MTL_index;        //index du tl
  int Temps_actuel;     //index de l'instance dans le tl
};

class Erreur_manager
{
 private:

  TimeDivision* TD;
 public:
  //constructeur
  Erreur_manager(TimeDivision*);

  //debut du traitment des erreur
  void Traiter_Erreur(Info_Erreur);

  //traitement pour les piece du type Pion
  //Actuellement sont traiter 2 cas:
  //1 - manger en passant
  //detection d'un erreur de notation apres un oublie volontaire ("_")
  void Pion(Info_Erreur);

  //traitement de "l'erreur" manger en passant
  Piece* Manger_en_passant(Info_Erreur);
  void Oublie_conscient(Info_Erreur,int*);
};

#endif
