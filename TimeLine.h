#ifndef TIME_LINE
#define TIME_LINE

#include "Piece.h"
#include "ChessPlate.h"
#include <vector>


//enum d'action -- move: d'une coordone a une autre
//              -- eat: une piece mange une autre
//              -- change: dans le cas ou tour et le roi fait du king castling(O-O) ou
//                         queen castling(O-O-O)
//              -- none: cas de base
enum Action {move, eat, change, promotion, none};

struct Info
{
  bool echec;//la piece a l'instant i est on echec avec le roi
  bool ambiguous;//la piece a l'instant i peut etre ambiguous

  Info();
  Info(bool, bool);
};
//structure qui permet la lecture correct de TimeLine
//pour un instant j, i est l'index de la coordoner dans p
struct Instant
{
  int i;
  Piece* p;
  Action a;
  Info info;

  Instant(int,Piece*,Action,Info);
};

class TimeLine
{
 private:
  std::vector<Instant> instants;
  int score = 0;
  //nombre total de piece de type none("_") lit dans le pgn
  int nb_none_piece = 0;
 public:
  ChessPlate* chessplate;
  
  //constructeur, destructeur
  TimeLine();
  TimeLine(ChessPlate*);
  TimeLine(TimeLine*);
  ~TimeLine();

  //Generation du TimeLine
  void add_instant_on_top(Piece*,Coord,Action,Info);
  void add_instant_at(Piece*,Action,Info,int);
  
  void update_at(Piece*,Action,Info,int);
  void remove_at(int);

  //return la taille de la liste
  int get_size();
  
  //score
  void score_kill(); //score = 1000, cette operation ser a tue le tl dans le prochain balayage
  void pp_score();   //score++
  int get_local_score();
  int get_global_score();
  //
  void pp_none_p();
  int get_nb_none_p();
  //debug 
  void toString();
  
  //###   Manipulation du TimeLine  ####

  //pour a instant j, renvoi une instance du TimeLine
  Instant* get_instant_at(int);
  std::vector<Instant> get_instants();
  Coord* get_next_coord(int);

  //
  void Check_timeline();
  //
  bool get_color(int);
  //return tous les piece de type NULL
  int* get_all_piece_NULL(int&);
};

//transforme un entier dans une action 1-> move 2->eat etc....
Action int_to_act(int);
#endif
