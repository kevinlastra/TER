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

  //cas ou type = pion
  int x;//example dxe3  var x = d
};
//struct en construction, tous les info ne sont pas utiliser
struct Info_Erreur
{
  //l'index de la piece dans le tl
  int piece_index;     

  //en cas ou la piece n'est pas trouver,
  //donc en collect tous les infos possible
  Info_piece* info_piece;
  //
  
  int tl_index;        //index du tl
  int tl_instance_index;     //index de l'instance dans le tl
};

#endif
