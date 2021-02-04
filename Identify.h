#include <string>
#include "Piece.h"

class Identify
{
 private:
  TimeLine tl;
  int tl_size;
  
  Piece* pieces;
  int p_size;
  
 public:
  Identify();
  Identify(string*);
  ~Identify();

  void identify_ps();
  
  TimeLine* get_tl();
  Piece* get_p();
  
  int get_tlsize();
  int get_psize();
  
  void INIT_P();  
};
