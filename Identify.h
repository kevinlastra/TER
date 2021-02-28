#ifndef IDENTIFY
#define IDENTIFY

#include <string>
#include "TimeDivision.h"
#include "Piece.h"
#include "TimeLine.h"

using namespace std;

class Identify
{
 private:
  //pointeur du TimeLine
  TimeDivision* TD;
  
  //liste de mots, lue par le lecteur ref-> Lecteur.h
  string* liste;

  //liste de 32 pieces
  ChessPlate* chessplate;
  
 public:
  //constructeur et destructeur
  Identify();
  Identify(string*,int);
  ~Identify();

  TimeDivision* get_TimeLines();
  
 private:
  //pour un mot et une couleur, ajoute une piece a TimeLine
  void identify_ps(string*,int);

  //factorize des operation
  void Factorize(TimeLine*,Piece**,Coord*,bool,Type,string*,int&);

  Type char_to_type(char);

};

#endif
