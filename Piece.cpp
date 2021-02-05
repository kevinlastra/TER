#include "Piece.h"
#include <string>
#include <iostream>

using namespace std;

Piece::Piece():type(NONE),Temps_movements(new int[10]),TM_size(0),TM_max_size(10),color(true),alive(true)
{
  pos = Coord();
}
Piece::Piece(Type t, bool c, int x, int y):Temps_movements(new int[10]),TM_size(0),TM_max_size(10)
{
  type = t;
  color = c;
  pos = Coord(x,y);
  alive = true;
}
Piece::Piece(Piece* p):Temps_movements(new int[p->get_TM_max_size()]), color(p->get_Color())
{
  type = p->get_Type();
  pos = Coord(p->get_Coord().x(), p->get_Coord().y());

  TM_size = p->get_TM_size();
  TM_max_size = p->get_TM_max_size();
  
  for(int i = 0; i < TM_size; i++)
  {
    Temps_movements[i] = p->get_movements_at(i);
  }
}
Piece::~Piece()
{
  delete[] Temps_movements;
}
void Piece::set_Type(char c)
{
  switch(c)
  {
  case 'K':
    type = roi;
    break;
  case 'Q':
    type = dame;
    break;
  case 'B':
    type = fous;
    break;
  case 'N':
    type = cavaliers;
    break;
  case 'R':
    type = tours;
    break;
  case '_':
    type = NONE;
    break;
  default:
    type = pions;
    break;
  }
}
void Piece::set_Coord(Coord c)
{
  pos.update(c.x() ,c.y());
}
void Piece::set_Color(bool b)
{
  color = b;
}
void Piece::set_Alive(bool a)
{
  alive = a;
}
Type Piece::get_Type()
{
  return type;
}
Coord Piece::get_Coord()
{
  return pos;
}
bool Piece::get_Color()
{
  return color;
}
bool Piece::get_Alive()
{
  return alive;
}
int Piece::get_TM_size()
{
  return TM_size;
}
int Piece::get_TM_max_size()
{
  return TM_max_size;
}
int* Piece::get_TM()
{
  return Temps_movements;
}
int Piece::get_movements_at(int i)
{
  return Temps_movements[i];
}
void Piece::add_movements(int i)
{  
  Temps_movements[TM_size] = i;
  TM_size++;
  
  if(TM_size == TM_max_size)
  {
    resize();
  }
}
void Piece::remove_movements_at(int j)
{
  if(j >= TM_size)
    return;
  
  for(int i = j+1; i < TM_size; i++)
  {
    Temps_movements[i-1] = Temps_movements[i];
  }
  TM_size--;
}
void Piece::resize()
{
  TM_max_size *= 2;
  int* tm = new int[TM_max_size];
  for(int i = 0; i < TM_size; i++)
  {
    tm[i] = Temps_movements[i];
  }
  delete[] Temps_movements;
  Temps_movements = tm;
}
bool Piece::Test_movements(Coord* c, bool eat)
{
  int d;
  switch(type)
  {
  case roi:
    d = (c->x()-pos.x())*(c->x()-pos.x())+(c->y()-pos.y())*(c->y()-pos.y());
    if(d == 1)
    {
      return true;
    }
    break;
  case dame:
    return Test_mov_Tour(c) || Test_mov_Fous(c);
    break;
  case fous:
    return Test_mov_Fous(c);
    break;
  case cavaliers:
    return Test_mov_Cavaliers(c);
    break;
  case tours:
    return Test_mov_Tour(c);
    break;
  default:
    if(color)
    {
      if(pos.y()+1 == c->y())
      {
	if(pos.x() == c->x())
	  return true;
	if(eat && (pos.x()+1 == c->x() || pos.x()-1 == c->x()))
	{
	  return true;
	}
      }
      else if(pos.y()+2 == c->y() && pos.x() == c->x())
      {
	return true;
      }
    }
    else
    {
      //cout << c->x() << "   " << c->y() << endl;
      //cout << pos.x() << "   "<< pos.y() << endl;
      if(pos.y()-1 == c->y())
      {
	if(pos.x() == c->x())
	  return true;
	if(eat && (pos.x()+1 == c->x() || pos.x()-1 == c->x()))
	{
	  return true;
	}
      }
      else if(pos.y()-2 == c->y() && pos.x() == c->x())
	return true;
    }
    break;
  }
}
bool Piece::Test_mov_Tour(Coord* c)
{
  if(pos.x() == c->x() && pos.y() != c->y())
    return true;
  else if(pos.x() != c->x() && pos.y() == c->y())
    return true;
  return false;
}
bool Piece::Test_mov_Fous(Coord* c)
{
  int x = pos.x()-c->x();
  if(x < 0)
    x*=-1;
  int y = pos.y()-c->y();
  if(y < 0)
    y*=-1;
  if(x == y)
    return true;
  return false;
}
bool Piece::Test_mov_Cavaliers(Coord* c)
{
  if(pos.y()-2 == c->y() &&
     (pos.x()+1==c->x() || pos.x()-1==c->x()))
  {
    return true;
  }
  if(pos.y()+2 == c->y() &&
     (pos.x()+1==c->x() || pos.x()-1==c->x()))
  {
    return true;
  }
  if(pos.x()-2 == c->x() &&
     (pos.y()+1==c->y() || pos.y()-1==c->y()))
  {
    return true;
  }
  if(pos.x()+2 == c->x() &&
     (pos.y()+1==c->y() || pos.y()-1==c->y()))
  {
    return true;
  }
  return false;
}

string Piece::toString()
{
  string s;
  int space;
  switch(type)
  {
  case roi:
    s = "Roi: ";
    space = 5;
    break;
  case dame:
    s = "Dame: ";
    space = 6;
    break;
  case fous:
    s = "Fous: ";
    space = 6;
    break;
  case cavaliers:
    s = "Cavalier: ";
    space = 10;
    break;
  case tours:
    s = "Tour: ";
    space = 6;
    break;
  case NONE:
    s = "NONE: ";
    space = 6;
    break;
  default:
    s = "Pion: ";
    space = 6;
    break;
  }
  for(int i = space; i < 15;i++)
    s+=" ";
  s+="(";
  s+=to_string(pos.x());
  s+=",";
  s+=to_string(pos.y());
  s+=")    ";
  s+=color?"1":"0";
  s+="     Alive:";
  s+=alive?"1":"0";
  return  s;
}
