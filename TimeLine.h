#ifndef TIME_LINE
#define TIME_LINE

#include "Piece.h"
#include "ChessPlate.h"
#include "ArbreMovement.h"
#include <vector>


//énumération d'actions
//              -- move: d'une coordone a une autre
//              -- eat: une piece mange une autre
//              -- change: dans le cas ou tour et le roi fait du king castling(O-O) ou
//                         queen castling(O-O-O)
//              -- none: cas de base
enum Action {move, eat, change, promotion, none};

struct Info
{
  bool echec;//la pièce à l'instant i est en echec avec le roi
  bool ambiguous;//la pièce à l'instant i peut être ambiguous

  Info();
  Info(bool, bool);
};
//Structure qui permet la lecture correcte de la TimeLine
//pour un instant j, i est l'index de la coordonnée dans p
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
  //nombre total de pièces de type none("_") lues dans le pgn
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

  //retourne la taille de la liste
  int get_size();
  
  //score
  void score_kill(); //score = 1000, cette operation sert à tuer le timeline dans le prochain balayage
  void pp_score();   //score++
  int get_local_score();
  int get_global_score();
  //
  void pp_none_p();
  int get_nb_none_p();
  //debug 
  void toString();
  
  //###   Manipulation du TimeLine  ####

  //Pour a instant j, renvoi une instance de la TimeLine
  Instant* get_instant_at(int);
  std::vector<Instant> get_instants();
  Coord* get_next_coord(int);

  //
  void Check_timeline();
  //
  bool get_color(int);
  //retourne toutes les pièce de type NULL
  int* get_all_piece_NULL(int&);

  Coord* Verif_echec(int);
};

//transforme un entier dans une action 1-> move 2->eat etc....
Action int_to_act(int);
#endif
