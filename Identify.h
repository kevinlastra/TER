#ifndef IDENTIFY
#define IDENTIFY

#include <string>
#include "TimeDivision.h"
#include "Piece.h"
#include "Coord.h"
#include "TimeLine.h"
#include "Erreur_manager.h"

using namespace std;


class Identify
{
 private:
  //pointeur du TimeLine
  TimeDivision* TD;
  
  Erreur_manager* EM;
  Info_Erreur Error;
  
  //liste de mots, lue par le lecteur ref-> Lecteur.h
  string* liste;


  
  TimeLine* tl;
  int MTL_index;
  int temps_index;
 public:
  //constructeur et destructeur
  Identify();
  Identify(string*,int);
  ~Identify();

  TimeDivision* get_TimeLines();
  void Traitement_erreur();
 private:
  //pour un mot et une couleur, ajoute une piece a TimeLine
  void interpreteur(string*);

  //factorize des operation
  void Factorize(Piece**,Coord*,bool,Type,string*,int&);
  int Tuer(Coord,Info,Type);

};

#endif
