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
  //pointeur de la TimeLine
  TimeDivision* TD;
  
  Erreur_manager* EM;
  Info_Erreur Error;
  
  //liste de mots lus par le lecteur ref-> Lecteur.h
  string* liste;


  
  TimeLine* tl;

  //index de la timeline traitée
  int TL_index;
  //temps de lecture pour construire le tl
  int temps_index;
 public:
  //constructeur et destructeur
  Identify();
  Identify(string*,int);
  ~Identify();

  TimeDivision* get_TimeLines();
  void Traitement_erreur();
 private:
  //pour un mot et une couleur, ajoute une piece dans la TimeLine
  void interpreteur(string*);

  //factorise des operations
  void Factorize(Piece**,Info_piece*,string*);
  
  //index de la piece qui mange, coordonnées de la piece à tuer
  bool Tuer(int,Piece*);

};

#endif
