#ifndef TIME_LINE
#define TIME_LINE

#include "Piece.h"

//enum d'action -- move: d'une coordone a une autre
//              -- eat: une piece mange une autre
//              -- change: dans le cas ou tour et le roi fait du king castling(O-O) ou queen castling(O-O-O)
//              -- none: cas de base
enum Action {move, eat, change, none};

//structure qui permet la lecture correct de TimeLine
//pour a instant j, i est l'index de la coordoner dans p
struct Instance
{
  int i;
  Piece* p;
  Action a;
};

class TimeLine
{
 private:
  //liste d'action
  Action* act;
  //liste de piece dans le temps
  Piece** piece;

  //taille actuel et maximal
  int max_size;
  int size;

  //resize pour act et piece
  void resize_tl();
  
 public:
  //constructeur, destructeur
  TimeLine();
  ~TimeLine();

  //Generation du TimeLine
  void add_instance_on_top(Piece*,Coord,Action);
  void add_instance_at(Piece*,Coord,Action,int);
  
  void update_at(Piece*,Action,int);
  void remove_at(int);

  //return la taille de piece ou act
  int get_size();

  //transforme un entier dans une action 1-> move 2->eat etc....
  Action int_to_act(int);
  
  //debug 
  void toString();
  
  //###   Manipulation du TimeLine  ####

  //pour a instant j, renvoi une instance du TimeLine
  Instance* get_instance_at(int);

  Coord* get_next_coord(int);
};

#endif
