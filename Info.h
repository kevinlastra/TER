#ifndef INFO
#define INFO

#include "Coord.h"
#include "Piece.h"
#include "TimeLine.h"

struct Info_piece
{
  Type type;
  Coord coord;
  Action action;
  bool color;
  Info info;
  int coordAmbiguous;  //coordonnées a préciser en cas de coup ambigü

  //cas ou type = pion
  int x;//example dxe3  var x = d
};

struct Info_Erreur
{
  //l'index de la pièce dans la timeline
  int piece_index;     

  //cas ou la pièce n'est pas trouvée
  //donc on collecte toutes les infos possibles
  Info_piece* info_piece;
  //
  bool errorEat;
  int tl_index;        //index de la timeline
  int tl_instance_index;     //index de l'instance dans la timeline
};

#endif
