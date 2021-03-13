#ifndef ARBRE_MOVEMENT
#define ARBRE_MOVEMENT

#include "Coord.h"
#include "Piece.h"
#include "ChessPlate.h"
#include <vector>


struct Anode
{
  Coord c;
  int prev;
  int nb_succ;

  Anode(Coord, int);
};
class ArbreMovement
{
 private:
  std::vector<Anode> arbre;
  ChessPlate* chessplate;
  
 public:
  ArbreMovement(ChessPlate*);
  ~ArbreMovement();

  std::vector<Anode> Generait_arbre(Piece*, Coord, int);
  void AddProfondeur(Type,bool);//tipe de la piece a bouger

  void clean_nodes(Coord);
  //coord final
  void Pawn(int, bool);
  void Rok(int);
  void Knigth(int);
  void Bishop(int);
  void King(int);
  void Queen(int);
};

#endif
