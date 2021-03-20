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
struct Arbre
{
  std::vector<Anode> arbre_struct;
  Piece* piece;
};
class ArbreMovement
{
 private:
  Arbre* arbre;
  ChessPlate* chessplate;
  
  
 public:
  ArbreMovement(ChessPlate*);
  ~ArbreMovement();

  Arbre* Generait_arbre(Piece*, Coord, int);
  void AddProfondeur(Type,bool);//tipe de la piece a bouger
  Piece* get_piece();
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
