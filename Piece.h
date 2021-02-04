#ifndef PIECE
#define PIECE

#include "Coord.h"
#include <string>

using namespace std;

enum Type {roi, dame, fous, cavaliers,
	   tours, pions,NONE};


class Piece
{
 private:  
  Type type;
  bool color;//B:true N:false
  
  Coord pos;
  
  int* Temps_movements;//TM
  int TM_size;
  int TM_max_size;
 public:
  Piece();
  Piece(Type,bool,int,int);
  Piece(Piece*);
  ~Piece();
  
  void set_Type(char);
  void set_Coord(Coord);
  void set_Color(bool);
  
  Type get_Type();
  Coord get_Coord();
  bool get_Color();
  
  int get_TM_size();
  int get_TM_max_size();
  int* get_TM();
  int get_movements_at(int);
  void add_movements(int);
  void remove_movements_at(int);

  void resize();

  bool Test_movements(Coord*);
  bool Test_mov_Tour(Coord*);
  bool Test_mov_Fous(Coord*);
  bool Test_mov_Cavaliers(Coord*);

  string toString();
};

#endif
