#ifndef IDENTIFY
#define IDENTIFY

#include <string>
#include "Piece.h"
#include "TimeLine.h"

using namespace std;

class Identify
{
 private:
  //pointeur du TimeLine
  TimeLine* tl;

  //liste de mots, lue par le lecteur ref-> Lecteur.h
  string* liste;

  //liste de 32 pieces
  Piece** pieces;
  int p_size = 32;
  
 public:
  //constructeur et destructeur
  Identify();
  Identify(string*,int);
  ~Identify();

  //get pieces et TimeLine
  TimeLine* get_tl();
  Piece** get_p();
  
 private:
  //pour un mot et une couleur, ajoute une piece a TimeLine
  void identify_ps(string*,int);

  //factorize des operation
  void Factorize(Piece**,Coord*,bool,Type,string*,int&);

  //renvoi a y b un roi et une tour, dependant de la couleur et du cote de la tour
  //queen: cote gauche
  //roi: cote droit
  void return_Castling(bool,Type,int&,int&);//Type reference if is queen side or king side

  //cherche une piece avec les parametre suivant
  //Type, couleur et qui peuve aller a une coordoner x et y
  Piece* find_ps(Type,bool,int,int);
  //find_ps mais avec plus de parametre de check
  //int: une position x dans un temps t-1, bool: si pion ou no
  Piece* find_ps_bis(Type,bool,int,int,int,bool);

  //return une piece a une coord especifique, null si rien
  Piece* piece_at_coord(int,int);

  //check si entre 2 coordoner il n'existe pas de piece
  bool check_Bishop_path(Coord,Coord);
  bool check_Rok_path(Coord,Coord);

  //INIT des 32 pieces
  void INIT_P();  
};

#endif
