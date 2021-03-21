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
  int index;//reference de la piece dans le tl

  Arbre(Anode,int);
};
class ArbreMovement
{
 private:
  Arbre* arbre;
  ChessPlate* chessplate;
  Piece* piece;
  
 public:
  ArbreMovement(ChessPlate*);
  ~ArbreMovement();

  Arbre* Generait_arbre(Piece*,int, Coord, int);
  void AddProfondeur(Type);//tipe de la piece a bouger
  void clean_nodes(Coord);
  //coord final
  void Pawn(int);
  void Rok(int);
  void Knigth(int);
  void Bishop(int);
  void King(int);
  void Queen(int);
};

#endif
