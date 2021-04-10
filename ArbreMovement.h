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
  int prof;
  int prev;           //node parent

  Anode(Coord, int, int);  //constructeur
  Anode();
};
struct Arbre
{
  std::vector<Anode> arbre_struct;   //arbre de coordoner
  int index;                         //reference de la piece dans chessplate

  Arbre(Anode,int);                  //constructeur

  int nb_chemin(int);
  std::vector<Anode> chemin_at(int,int);
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

  Arbre* Generait_arbre(Piece*, int, Coord, int);
  Arbre* Generait_arbre(int, int);
  //ajout un niveau de profondeur
  void AddProfondeur(Type, int);//tipe de la piece a bouger

  //nettoi les branches pour les quelle la feuille n'arrive pas a la coordoner
  void clean_nodes(Coord,int);
  
  //ajout un movement selon le type de piece
  void Pawn(int,int);
  void Rok(int,int);
  void Knigth(int,int);
  void Bishop(int,int);
  void King(int,int);
  void Queen(int,int);
};

#endif
