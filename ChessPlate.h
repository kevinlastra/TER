#ifndef CHESSPLATE
#define CHESSPLATE

#include "Piece.h"
#include "Coord.h"

class ChessPlate
{
 private:
  Piece** pieces;
  int p_size = 32;
 public:
  ChessPlate();
  ChessPlate(ChessPlate*);
  ~ChessPlate();

  Piece* at(int);
  int size();
  void promotion();
  //renvoi a y b un roi et une tour, dependant de la couleur et du cote de la tour
  //queen: cote gauche
  //roi: cote droit
  void return_Castling(bool,Type,int&,int&);//Type reference if is queen side or king side

  //cherche une piece avec les parametre suivant
  //Type, couleur et qui peuve aller a une coordoner x et y
  Piece* find_piece(Type,bool,int,int);
  //find_ps mais avec plus de parametre de check
  //int: une position x dans un temps t-1, bool: si pion ou no
  Piece* find_piece_ambiguos(Type,bool,int,int,int,bool);

  //return une piece a une coord especifique, null si rien
  Piece* piece_at_coord(int,int);

    //check si entre 2 coordoner il n'existe pas de piece
  bool check_Bishop_path(Coord,Coord);
  bool check_Rok_path(Coord,Coord);
};

#endif
