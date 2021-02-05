#ifndef IDENTIFY
#define IDENTIFY

#include <string>
#include "Piece.h"
#include "TimeLine.h"

using namespace std;

class Identify
{
 private:
  TimeLine* tl;

  string* liste;
  
  Piece** pieces;
  int p_size = 32;
  
 public:
  Identify();
  Identify(string*,int);
  ~Identify();

  void identify_ps(string*,int);
  void Factorize(Piece**,Coord*,bool,Type,string*,int&);//factorize switch(exeption de pion)

  void return_Castling(bool,Type,int&,int&);//Type reference if is queen side or king side
  Piece* find_ps(Type,bool,int,int);//type,color,x,y

  Piece* find_ps_bis(Type,bool,int,int,int,bool);
  
  void kill_at_coord(int,int);
  
  bool check_Bishop_path(Coord,Coord);
  bool check_Rok_path(Coord,Coord);
  
  TimeLine* get_tl();
  Piece** get_p();
  
  void INIT_P();  
};

#endif
