#ifndef TIME_LINE
#define TIME_LINE

#include "Piece.h"

class TimeLine
{
 public:
  enum Action {move, eat, change, NONE};
  struct Instance
  {
    Action a;
    Piece* p;
  };
  //-------------------
  struct Block_Vrai
  {
    int a;
    int b;
  };
  //--------------------
 private:  
  Action* act;
  Piece** piece;

  int max_size;
  int size;
  
  
  //Block_vrai n'est pas encore util

  Block_Vrai* bv;
  int max_size_bv;
  int size_bv;
  //-------------------
 public:
  TimeLine();
  ~TimeLine();

  void add_instance_on_top(Piece*,Action);
  void add_instance_at(Piece*,Action,int);
  
  void update_at(Piece*,Action,int);
  void remove_at(int);
  
  Instance* get_instance_at(int);
  int get_size();

  Action int_to_act(int);
  
  void resize_tl();

  void toString();
};

#endif
