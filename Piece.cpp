#include "Piece.h"
#include <string>

Piece::Piece():type(NONE),Temps_movements(new int[10]),TM_size(0),TM_max_size(10),color(true)
{
  type = NONE;
  pos = Coord();
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
void Piece::set_Coord(Coord* c)
{
  pos.update(c->x() ,c->y());
}
void Piece::set_Color(bool b)
{
  color = b;
}
Piece::Type Piece::get_Type()
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
bool Piece::Test_movements(Coord* c)
{
  switch(type)
  {
  case roi:
    int d = (c->x()-pos.x())*(c->x()-pos.x())+
      (c->y()-pos.y())*(c->y()-pos.y());
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
      if(pos.y() == c->y()+1)
      {
	if(pos.x() == c->x()+1 || pos.x() == c->x()-1)
	{
	  return true;
	}
      }
    }
    else
    {
      if(pos.y() == c->y()-1)
      {
	if(pos.x() == c->x()+1 || pos.x() == c->x()-1)
	{
	  return true;
	}
      }
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
  if(pos.y() == c->y()-2 &&
     (pos.x()==c->x()+1 || pos.x()==c->x()-1))
  {
    return true;
  }
  if(pos.y() == c->y()+2 &&
     (pos.x()==c->x()+1 || pos.x()==c->x()-1))
  {
    return true;
  }
  if(pos.x() == c->x()-2 &&
     (pos.y()==c->y()+1 || pos.y()==c->y()-1))
  {
    return true;
  }
  if(pos.x() == c->x()+2 &&
     (pos.y()==c->y()+1 || pos.y()==c->y()-1))
  {
    return true;
  }
  return false;
}
