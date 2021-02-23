#ifndef TIME_LINE
#define TIME_LINE

#include "Piece.h"
#include <vector>


//enum d'action -- move: d'une coordone a une autre
//              -- eat: une piece mange une autre
//              -- change: dans le cas ou tour et le roi fait du king castling(O-O) ou
//                         queen castling(O-O-O)
//              -- none: cas de base
enum Action {move, eat, change, promotion, none};

//structure qui permet la lecture correct de TimeLine
//pour un instant j, i est l'index de la coordoner dans p
struct Info
{
  bool echec;//la piece a l'instant i est on echec avec le roi
  bool ambiguous;//la piece a l'instant i peut etre ambiguous
};
struct Instant
{
  int i;
  Piece* p;
  Action a;
  Info info;
};

class TimeLine
{
 private:
  std::vector<Instant> instants;

  //taille de la liste
  int size;
  
 public:
  //constructeur, destructeur
  TimeLine();
  ~TimeLine();

  //Generation du TimeLine
  void add_instant_on_top(Piece*,Coord,Action,Info);
  void add_instant_at(Piece*,Coord,Action,Info,int);
  
  void update_at(Piece*,Action,Info,int);
  void remove_at(int);

  //return la taille de la liste
  int get_size();

  //transforme un entier dans une action 1-> move 2->eat etc....
  Action int_to_act(int);
  
  //debug 
  void toString();
  
  //###   Manipulation du TimeLine  ####

  //pour a instant j, renvoi une instance du TimeLine
  Instant* get_instant_at(int);

  Coord* get_next_coord(int);
};

#endif
