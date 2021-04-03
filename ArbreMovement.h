#ifndef ARBRE_MOVEMENT
#define ARBRE_MOVEMENT

#include "Coord.h"
#include "Piece.h"
#include "ChessPlate.h"
#include <vector>

//## ERREUR POSSIBLE ##
//cette classe n'a pas ete tester pour des profondeur > 1
//#####################

//Node pour construir l'arbre de movement
struct Anode
{
  Coord c;            //coordoner du node
  int prev;           //node parent
  std::vector<int> child_indexs;

  Anode(Coord, int);  //constructeur
};
struct Arbre
{
  std::vector<Anode> arbre_struct;   //arbre de coordoner
  int index;                         //reference de la piece dans le tl

  Arbre(Anode,int);                  //constructeur

  int nb_chemin();
  std::vector<Anode> chemin_at(int);
};


class ArbreMovement
{
 private:
  Arbre* arbre;            //pointeur de struct Arbre
  ChessPlate* chessplate;  //pointeur sur chessplate
  Piece* piece;            //pointeur sur une piece pour construir l'arbre
  
 public:
  ArbreMovement(ChessPlate*);
  ~ArbreMovement();

  Arbre* Generait_arbre(Piece*,int, Coord, int);

  //ajout un niveau de profondeur
  void AddProfondeur(Type);//tipe de la piece a bouger

  //nettoi les branches pour les quelle la feuille n'arrive pas a la coordoner
  void clean_nodes(Coord);
  
  //ajout un movement selon le type de piece
  void Pawn(int);
  void Rok(int);
  void Knigth(int);
  void Bishop(int);
  void King(int);
  void Queen(int);
};

#endif
