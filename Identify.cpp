#include "Identify.h"
#include "Piece.h"
#include "Coord.h"
#include <string>
#include <iostream>

using namespace std;

Identify::Identify()
{
  tl = new TimeLine;
  INIT_P();
}
Identify::Identify(string* l, int size)
{
  liste = l;
  tl = new TimeLine;
  INIT_P();

  for(int i = 0; i < size; i++)
  {
    identify_ps(&liste[i], i);
  }
}
Identify::~Identify()
{
  for(int i = 0; i < 32; i++)
    delete pieces[i];
  delete pieces;
}
void Identify::identify_ps(string* piece, int i)
{
  int ascii = (int)piece[0][0];
  bool color = i%2==0;
  Piece* p = NULL;
  Coord newcoord;
  if(ascii >= 65 && ascii <= 90)
  {
    switch(ascii)
    {
    case 'K':
      //cout << "King: "<<piece[0]<<endl;
      Factorize(&p, &newcoord, color, roi, piece);
      break;
    case 'Q':
      //cout << "Queen: "<<piece[0]<<endl;
      Factorize(&p, &newcoord, color, dame, piece);
      break;
    case 'B':
      //cout << "Bishop: "<<piece[0]<<endl;
      Factorize(&p, &newcoord, color, fous, piece);
      break;
    case 'N':
      //cout << "Knigth: "<<piece[0]<<endl;
      Factorize(&p, &newcoord, color, cavaliers, piece);
      break;
    case 'R':
      //cout << "Rok: "<<piece[0]<<endl;
      Factorize(&p, &newcoord, color, tours, piece);
      break;
    case 'O':
      if(piece[0] == "O-O")
      {
	cout <<endl<< "Rok change: "<<piece[0]<<endl<<endl;
      }
      else if(piece[0] == "O-O-O")
      {
	cout <<endl<< "Rok change: "<<piece[0]<<endl<<endl;
      }
      break;
    default://'_'
      cout << "---------undef: "<<piece[0]<<endl;
      break;
    }
  }
  else
  {
    //cout << "Pion: " << piece[0]<<endl;
    if(piece[0][1] != 'x')
    {
      p = find_ps(pions,color,(int)piece[0][0]-96,(int)piece[0][1]-48);
      newcoord = Coord((int)piece[0][0]-96,(int)piece[0][1]-48);
    }
    else
    {
      p = find_ps_bis(pions,color,(int)piece[0][2]-96,
		      (int)piece[0][3]-48,(int)piece[0][0]-96);
      newcoord = Coord((int)piece[0][2]-96,(int)piece[0][3]-48);
    }
  }
  if(p != NULL)
  {
    p->set_Coord(newcoord);
    tl->add_instance_on_top(p,tl->int_to_act(0));
  }
}
void Identify::Factorize(Piece** p, Coord* c, bool color, Type t, string* s)
{
   if(s[0][1] != 'x')
   {
     p[0] = find_ps(t,color,(int)s[0][1]-96,(int)s[0][2]-48);
     c[0] = Coord((int)s[0][1]-96,(int)s[0][2]-48);
   }
   else
   {
     p[0] = find_ps(t,color, (int)s[0][2]-96, (int)s[0][3]-48);
     c[0] = Coord((int)s[0][2]-96,(int)s[0][3]-48);
   }
}
Piece* Identify::find_ps(Type t, bool color, int x, int y)
{
  Coord c(x,y);
  for(int i = 0; i < 32; i++)
  {
    if(pieces[i]->get_Type() == t &&
       pieces[i]->get_Color() == color &&
       pieces[i]->Test_movements(&c))
    {
      return pieces[i];
      break;
    }
  }
}
Piece* Identify::find_ps_bis(Type t, bool color, int x, int y, int xfrom)
{
  Coord c(x,y);
  for(int i = 0; i < 32; i++)
  {
    if(pieces[i]->get_Type() == t &&
       pieces[i]->get_Color() == color &&
       pieces[i]->get_Coord().x() == xfrom &&
       pieces[i]->Test_movements(&c))
    {
      return pieces[i];
      break;
    }
  }
}
TimeLine* Identify::get_tl()
{
  return tl;
}
Piece** Identify::get_p()
{
  return pieces;
}
void Identify::INIT_P()
{
  pieces = new Piece*[32];

  pieces[0] = new Piece(pions,true,1,2);
  pieces[1] = new Piece(pions,true,2,2);
  pieces[2] = new Piece(pions,true,3,2);
  pieces[3] = new Piece(pions,true,4,2);
  pieces[4] = new Piece(pions,true,5,2);
  pieces[5] = new Piece(pions,true,6,2);
  pieces[6] = new Piece(pions,true,7,2);
  pieces[7] = new Piece(pions,true,8,2);

  pieces[8] = new Piece(pions,false,1,7);
  pieces[9] = new Piece(pions,false,2,7);
  pieces[10] = new Piece(pions,false,3,7);
  pieces[11] = new Piece(pions,false,4,7);
  pieces[12] = new Piece(pions,false,5,7);
  pieces[13] = new Piece(pions,false,6,7);
  pieces[14] = new Piece(pions,false,7,7);
  pieces[15] = new Piece(pions,false,8,7);

  pieces[16] = new Piece(tours,true,1,1);
  pieces[17] = new Piece(tours,true,8,1);

  pieces[18] = new Piece(tours,false,1,8);
  pieces[19] = new Piece(tours,false,8,8);

  pieces[20] = new Piece(cavaliers,true,2,1);
  pieces[21] = new Piece(cavaliers,true,7,1);

  pieces[22] = new Piece(cavaliers,false,2,8);
  pieces[23] = new Piece(cavaliers,false,7,8);

  pieces[24] = new Piece(fous,true,3,1);
  pieces[25] = new Piece(fous,true,6,1);

  pieces[26] = new Piece(fous,false,3,8);
  pieces[27] = new Piece(fous,false,6,8);

  pieces[28] = new Piece(roi,true,4,1);
  pieces[29] = new Piece(roi,false,4,8);

  pieces[30] = new Piece(dame,true,5,1);
  pieces[31] = new Piece(dame,false,5,8);
}
