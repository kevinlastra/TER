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
  ChessPlate(const ChessPlate*);
  ~ChessPlate();

  Piece* at(int);
  int size();
  void promotion();
  //Renvoie a et b, un roi et une tour, dépendant de la couleur et du côté de la tour
  //Dame: cote gauche
  //Roi: cote droit
  void return_Castling(bool,Type,int&,int&);

  //Cherche une pièce avec les paramètres suivants:
  //Type, couleur, coordonnées x et y atteignables par la pièce
  Piece* find_piece(Type,bool,int,int);
  //Version adaptée à un coup ambigü.
  //int: une position x dans un temps t-1, bool: si la pièce est un pion ou non
  Piece* find_piece_ambiguos(Type,bool,int,int,int,bool);

  //Retourne une pièce avec une coordonnée spécifique ou null si il n'en existe pas.
  Piece* piece_at_coord(int,int);

  
  Piece* piece_at_init(int,int);
  //Retourne l'index d'une pièce donnée
  int index_of(Piece*);
  //Vérifie si il n'existe pas de pièce sur les chemins que peuvent prendre certaines pièces.
  bool check_king_movement(Coord);
  bool check_piece_rampant_movement(Type,Coord, Coord);
  bool check_Bishop_path(Coord,Coord);
  bool check_Rok_path(Coord,Coord);

  //Affiche les pièces du plateau.
  void Print();
};

#endif
