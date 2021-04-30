#ifndef ARBRE_MOVEMENT
#define ARBRE_MOVEMENT

#include "Coord.h"
#include "Piece.h"
#include "ChessPlate.h"
#include <vector>

//## ERREUR POSSIBLE ##
//cette classe n'a pas ete tester pour des profondeur > 1
//#####################

//Noeud pour construire l'arbre de movements
struct Anode
{
  Coord c;            //coordonnées du noeud
  int prof;
  int prev;           //noeud parent

  Anode(Coord, int, int);  //constructeur
  Anode();
};
struct Arbre
{
  std::vector<Anode> arbre_struct;   //arbre de coordonnées
  int index;                         //référence de la pièce dans le plateau

  Arbre(Anode,int);                  //constructeur

  int nb_chemin(int);
  std::vector<Anode> chemin_at(int,int);
};


class ArbreMovement
{
 private:
  Arbre* arbre;            //pointeur de struct Arbre
  ChessPlate* chessplate;  //pointeur sur le plateau
  Piece* piece;            //pointeur sur une pièce pour construire l'arbre
  
 public:
  ArbreMovement(ChessPlate*);
  ~ArbreMovement();

  Arbre* Generait_arbre(Piece*, int, Coord, int);
  Arbre* Generait_arbre(int, int);
  //Ajoute un niveau de profondeur
  void AddProfondeur(Type, int);//type de la pièce à bouger

  //Nettoie les branches pour lesquelles la feuille n'arrive pas à la coordonnée passée en argument
  void clean_nodes(Coord,int);
  
  //Ajoute un movement selon le type de piece
  void Pawn(int,int);
  void Rok(int,int);
  void Knigth(int,int);
  void Bishop(int,int);
  void King(int,int);
  void Queen(int,int);
};

#endif
