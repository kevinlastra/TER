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
  void Factorize(Piece**,Coord*,bool,Type,string*);//factorize switch(exeption de pion)

  void return_Castling(bool,Type,int&,int&);//Type reference if is queen side or king side
  Piece* find_ps(Type,bool,int,int);//type,color,x,y

  //type,color,x,y,(le dernier parametre permet
  //d'envoiyer la dernier x position,
  //dans le cas ou la piece mange,
  //ex.dxc5 d est la dernier x position)
  Piece* find_ps_bis(Type,bool,int,int,int);
  
  TimeLine* get_tl();
  Piece** get_p();
  
  void INIT_P();  
};

#endif
