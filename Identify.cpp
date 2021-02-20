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
    //cout <<"Liste at("<< i << ")         "<<liste[i]<<endl;
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
  int act = 3;
  Piece* p = NULL;
  Coord newcoord;
  if(ascii >= 65 && ascii <= 90)
  {
    switch(ascii)
    {
      case 'K':
      //cout << "King: "<<piece[0]<<endl;
      Factorize(&p, &newcoord, color, roi, piece, act);
      break;
      case 'Q':
      //cout << "Queen: "<<piece[0]<<"  "<<color<<endl;
      Factorize(&p, &newcoord, color, dame, piece, act);
      break;
      case 'B':
      //cout << "Bishop: "<<piece[0]<<endl;
      Factorize(&p, &newcoord, color, fous, piece, act);
      break;
      case 'N':
	    //cout << "Knigth: "<<piece[0]<<"   "<<act<<endl;
      if((int)piece[0][2] < 96 || piece[0][1] == 'x')
      {
        Factorize(&p, &newcoord, color, cavaliers, piece, act); 
      }
      else
      {
        p = find_ps_bis(cavaliers,color,(int)piece[0][2]-96,
            (int)piece[0][3]-48,(int)piece[0][1]-96,false);
        newcoord = Coord((int)piece[0][2]-96,(int)piece[0][3]-48);
        act = 0;
      }
      break;
     case 'R':
      //cout << "Rok: "<<piece[0]<<endl;
     if((int)piece[0][2] < 96)
     {
       Factorize(&p, &newcoord, color, tours, piece, act);
     }
     else
     {
       p = find_ps_bis(tours,color,(int)piece[0][2]-96,(int)piece[0][3]-48,
		       (int)piece[0][1]-96,false);
       newcoord = Coord((int)piece[0][2]-96,(int)piece[0][3]-48);
       act = 0;
     }
     break;
     case 'O':
     int a,b;
     act = 3;
     if(piece[0] == "O-O")
     {
	//cout <<endl<< "Rok-kingside & King change: "<<endl<<endl;
       return_Castling(color,roi,a,b);

       p = pieces[a];
       newcoord = Coord(pieces[a]->get_last_pos().x()+2,
			pieces[a]->get_last_pos().y());
       
       tl->add_instance_on_top(p,newcoord,tl->int_to_act(2));

       p = pieces[b];
       newcoord = Coord(newcoord.x()-1, newcoord.y());
       
       tl->add_instance_on_top(p,newcoord,tl->int_to_act(2));
       return;
     }
     else if(piece[0] == "O-O-O")
     {
	//cout <<endl<< "Rok-queenside & king change: "<<endl<<endl;
       return_Castling(color,dame,a,b);

       p = pieces[a];
       newcoord = Coord(pieces[a]->get_last_pos().x()-2,
			pieces[a]->get_last_pos().y());
       
       tl->add_instance_on_top(p,newcoord,tl->int_to_act(2));

       p = pieces[b];
       newcoord = Coord(newcoord.x()+1, newcoord.y());
       
       tl->add_instance_on_top(p,newcoord,tl->int_to_act(2));
       return;
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
      if(piece[0][2] == '\0')
      {
	p = find_ps(pions,color,(int)piece[0][0]-96,(int)piece[0][1]-48);
	newcoord = Coord((int)piece[0][0]-96,(int)piece[0][1]-48);
	act = 0;	
      }
      else if(piece[0][2] >= 65 && piece[0][2] <= 90)
      {
	cout << "----promotion-----"<<endl;
	p = find_ps(pions,color,(int)piece[0][0]-96,(int)piece[0][1]-48);
	newcoord = Coord((int)piece[0][0]-96,(int)piece[0][1]-48);
	act = 3;
      }
    }
    else
    {
      p = find_ps_bis(pions,color,(int)piece[0][2]-96,
		      (int)piece[0][3]-48,(int)piece[0][0]-96,true);
      newcoord = Coord((int)piece[0][2]-96,(int)piece[0][3]-48);
      act = 1;
    }
  }
  
  if(p != NULL)
  {
    if(piece[0][1] == 'x')
    {
      Piece* p = piece_at_coord(newcoord.x(), newcoord.y());
      //test pour "manger en passant"
      if(p == NULL && (ascii >= 97 && ascii <= 104))
      {
	Coord c;
	int index;
	if(color)
	{
	  p = piece_at_coord(newcoord.x(), newcoord.y()-1);
	  c = p->get_pos_at(p->get_TM_size()-2);
	  index = p->get_movements_at(p->get_TM_size()-1);

	  if(index != i-1 || c.x() != p->get_last_pos().x() ||
	     c.y() != p->get_last_pos().y()+2)
	    p = NULL;
	}
	else
	{
	  p = piece_at_coord(newcoord.x(), newcoord.y()+1);
	  c = p->get_pos_at(p->get_TM_size()-2);
	  index = p->get_movements_at(p->get_TM_size()-1);

	  if(index != i-1 || c.x() != p->get_last_pos().x() ||
	     c.y() != p->get_last_pos().y()-2)
	    p = NULL;
	}
      }
      if(p == NULL)
      {
	cout << "piece == NULL"<<endl;
	return;
      }
      cout << "killing : "<<p->toString()<<endl;
      p->set_Alive(false);
    }
    tl->add_instance_on_top(p,newcoord,tl->int_to_act(act));
  }
  else if(p == NULL)
  {    
    cout <<endl<<"Error: "<< piece[0] << endl<<endl;;
  }
}
void Identify::Factorize(Piece** p, Coord* c, bool color, Type t, string* s, int& act)
{
  
  if(s[0][1] != 'x')
  {
     //cout << "c:   y:"<<(int)s[0][2]-48<<"    "<<s[0][2]<<endl;
   p[0] = find_ps(t,color,(int)s[0][1]-96,(int)s[0][2]-48);
   c[0] = Coord((int)s[0][1]-96,(int)s[0][2]-48);
   act = 0;
 }
 else
 {
   p[0] = find_ps(t,color, (int)s[0][2]-96, (int)s[0][3]-48);
   c[0] = Coord((int)s[0][2]-96,(int)s[0][3]-48);
   act = 1;
 }
}
void Identify::return_Castling(bool color,Type t, int &a, int &b)
{
  if(color)
    a = 28;
  else
    a = 29;
  
  if(t == roi)
  {
    if(color)
      b = 17;
    else
      b = 19;
  }
  else if(t == dame)
  {
    if(color)
      b = 16;
    else
      b = 18; 
  }
}
Piece* Identify::find_ps(Type t, bool color, int x, int y)
{
  Coord c(x,y);
  for(int i = 0; i < 32; i++)
  {
    if(pieces[i]->get_Type() == t &&
     pieces[i]->get_Color() == color &&
     pieces[i]->Test_movements(&c,false, pieces[i]->get_TM_size()-1) &&
     pieces[i]->get_Alive())
    {
      if(t == fous)
      {
       if(check_Bishop_path(pieces[i]->get_last_pos(),c))
         return pieces[i];
       else
         continue;
     }
     else if(t == tours)
     {
	//cout << "Test Rok Path: "<<check_Rok_path(pieces[i]->get_Coord(),c)<<endl;
       if(check_Rok_path(pieces[i]->get_last_pos(),c))
         return pieces[i];
       else
         continue;
     }
     else
     {
       return pieces[i];
     }
   }
 }
 return NULL;
}
Piece* Identify::find_ps_bis(Type t, bool color, int x, int y, int xfrom, bool pawn)
{
  Coord c(x,y);
  for(int i = 0; i < 32; i++)
  {
    if(pieces[i]->get_Type() == t &&
     pieces[i]->get_Color() == color &&
     pieces[i]->get_last_pos().x() == xfrom &&
     pieces[i]->Test_movements(&c,pawn,pieces[i]->get_TM_size()-1) &&
     pieces[i]->get_Alive())
    {
      if(t == fous)
      {
       if(check_Bishop_path(pieces[i]->get_last_pos(),c))
         return pieces[i];
       else
         continue;
     }
     else if(t == tours)
     {
       if(check_Rok_path(pieces[i]->get_last_pos(),c))
         return pieces[i];
       else
         continue;
     }
     else
     {
       return pieces[i];
     }
   }
 }
}
Piece* Identify::piece_at_coord(int x, int y)
{
  for(int i = 0; i < 32; i++)
  {
    if(pieces[i]->get_last_pos().x() == x &&
     pieces[i]->get_last_pos().y() == y &&
     pieces[i]->get_Alive())
    {
      return pieces[i];
    }
  }
  return NULL;
}
bool Identify::check_Bishop_path(Coord start, Coord end)
{
  int x = (start.x() > end.x())?-1:1;
  int y = (start.y() > end.y())?-1:1;

  int cnt = start.x()-end.x();
  cnt = cnt<0?cnt*-1:cnt;
  
  int j = 1;
  while(j <= cnt)
  {
    for(int i = 0; i < 32; i++)
    {
      if(pieces[i]->get_last_pos().x() == start.x()+x*j &&
        pieces[i]->get_last_pos().y() == start.y()+y*j &&
        pieces[i]->get_Alive())
      {
       return false;
     }
   }
   cnt--;
 }
 return true;
}
bool Identify::check_Rok_path(Coord start, Coord end)
{
  int mv;
  int i=1;
  if(start.x() == end.x())
  {
    mv = start.y()>end.y()?-1:1;
    //cout <<"y: "<< start.y()+i*mv<<"    "<<end.y()<<endl;
    while(start.y()+i*mv != end.y())
    {
      //cout <<"y: "<< start.y()+i*mv<<endl;
      for(int j = 0; j < 32; j++)
      {
       if(pieces[j]->get_last_pos().x() == start.x() &&
        pieces[j]->get_last_pos().y() == start.y()+i*mv &&
        pieces[j]->get_Alive())
       {
         return false;
       }
     }
     i++;
   }
 }
 else if(start.y() == end.y())
 {
  mv = start.x()>end.x()?-1:1;
  while(start.x()+i*mv != end.x())
  {
    for(int j = 0; j < 32; j++)
    {
     if(pieces[j]->get_last_pos().y() == start.y() &&
      pieces[j]->get_last_pos().x() == start.x()+i*mv &&
      pieces[j]->get_Alive())
     {
       return false;
     }
   }
   i++;
 }
}
return true;
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

  pieces[28] = new Piece(roi,true,5,1);
  pieces[29] = new Piece(roi,false,5,8);

  pieces[30] = new Piece(dame,true,4,1);
  pieces[31] = new Piece(dame,false,4,8);
}
