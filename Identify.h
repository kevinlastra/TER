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

  //index du timeline traiter
  int TL_index;
  //temps de lecture pour construir le tl
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
  void Factorize(Piece**,Info_piece*,string*);
  
  //index de la piece assasin, coord de la piece a tuer
  bool Tuer(int,Piece*);

};

#endif
