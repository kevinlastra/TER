#include "Piece.h"
#include <string>
#include <iostream>

using namespace std;

Piece::Piece():type(NONE),Temps_movements(new int[10]),TM_max_size(10),color(true),alive(true),pos(new Coord[10])
{}
Piece::Piece(Type t, bool c, int x, int y):Temps_movements(new int[10]),TM_max_size(10),pos(new Coord[10])
{
  pos[0] = Coord(x,y);
  Temps_movements[0] = -1;
  TM_size++;
  type = t;
  color = c;
  alive = true;
}
Piece::Piece(Piece* p):Temps_movements(new int[p->get_TM_max_size()]), color(p->get_Color()),pos(new Coord[p->get_TM_max_size()]),type(p->get_Type()),alive(p->get_Alive())
{
  TM_size = p->get_TM_size();
  TM_max_size = p->get_TM_max_size();
  
  for(int i = 0; i < TM_size; i++)
  {
    pos[i] = p->get_pos_at(i);
    Temps_movements[i] = p->get_movements_at(i);
  }
}
Piece::~Piece()
{
  delete[] pos;
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
void Piece::set_Coord_at(Coord c, int i)
{
  if(i < TM_size)
    pos[i].update(c.x() ,c.y());
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
Coord* Piece::get_Coord()
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
Coord* Piece::get_Coords()
{
  return pos;
}
Coord Piece::get_pos_at(int i)
{
  return pos[i];
}
Coord Piece::get_last_pos()
{
  return pos[TM_size-1];
}

int Piece::get_last_time()
{
  return Temps_movements[TM_size-1];
}

int Piece::get_movements_at(int i)
{
  return Temps_movements[i];
}
int Piece::time_to_pos_index(int time)
{
  for(int i = 1; i < TM_size; i++)
  {
    //cout <<"------>Time: "<<Temps_movements[i]<<endl;
    //cout <<"------>x: "<< pos[i].x()<<"    y:"<<pos[i].y()<<endl;
    if(Temps_movements[i] == time)
      return i;
  }
}

int Piece::time_to_next_pos_time(int time)
{
  for(int i = 1; i < TM_size; i++)
  {
    if(Temps_movements[i] == time)
    {
      if(Temps_movements[i+1] != NULL)
      {
        return Temps_movements[i+1];
      }
    }
  return 0;
  }
}

int Piece::time_to_previous_pos_time(int time)
{
  for(int i = 1; i < TM_size; i++)
  {
    if(Temps_movements[i] == time)
    {
      return Temps_movements[i-1];
    }
  }
  return -1;
}

void Piece::add_movements(int i, Coord c)
{
  Temps_movements[TM_size] = i;
  pos[TM_size] = c;
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
  Coord* cs = new Coord[TM_max_size];
  
  for(int i = 0; i < TM_size; i++)
  {
    tm[i] = Temps_movements[i];
    cs[i] = pos[i];
  }
  delete[] pos;
  delete[] Temps_movements;

  pos = cs;
  Temps_movements = tm;
}
bool Piece::Test_movements(Coord* c, bool eat, int i)
{
  int d;
  switch(type)
  {
  case roi:
    d = (c->x()-pos[i].x())*(c->x()-pos[i].x())+(c->y()-pos[i].y())*(c->y()-pos[i].y());
    if(d == 1)
    {
      return true;
    }
    break;
  case dame:
    return Test_mov_Tour(c, i) || Test_mov_Fous(c, i);
    break;
  case fous:
    return Test_mov_Fous(c, i);
    break;
  case cavaliers:
    return Test_mov_Cavaliers(c, i);
    break;
  case tours:
    return Test_mov_Tour(c, i);
    break;
  default:
    if(color)
    {
      if(pos[i].y()+1 == c->y())
      {
	if(pos[i].x() == c->x())
	  return true;
	if(eat && (pos[i].x()+1 == c->x() || pos[i].x()-1 == c->x()))
	{
	  return true;
	}
      }
      else if(pos[i].y()+2 == c->y() && pos[i].x() == c->x())
      {
	return true;
      }
    }
    else
    {
      //cout << c->x() << "   " << c->y() << endl;
      //cout << pos.x() << "   "<< pos.y() << endl;
      if(pos[i].y()-1 == c->y())
      {
	if(pos[i].x() == c->x())
	  return true;
	if(eat && (pos[i].x()+1 == c->x() || pos[i].x()-1 == c->x()))
	{
	  return true;
	}
      }
      else if(pos[i].y()-2 == c->y() && pos[i].x() == c->x())
	return true;
    }
    break;
  }
}
bool Piece::Test_mov_Tour(Coord* c, int i)
{
  if(pos[i].x() == c->x() && pos[i].y() != c->y())
    return true;
  else if(pos[i].x() != c->x() && pos[i].y() == c->y())
    return true;
  return false;
}
bool Piece::Test_mov_Fous(Coord* c, int i)
{
  int x = pos[i].x()-c->x();
  if(x < 0)
    x*=-1;
  int y = pos[i].y()-c->y();
  if(y < 0)
    y*=-1;
  if(x == y)
    return true;
  return false;
}
bool Piece::Test_mov_Cavaliers(Coord* c, int i)
{
  if(pos[i].y()-2 == c->y() &&
     (pos[i].x()+1==c->x() || pos[i].x()-1==c->x()))
  {
    return true;
  }
  if(pos[i].y()+2 == c->y() &&
     (pos[i].x()+1==c->x() || pos[i].x()-1==c->x()))
  {
    return true;
  }
  if(pos[i].x()-2 == c->x() &&
     (pos[i].y()+1==c->y() || pos[i].y()-1==c->y()))
  {
    return true;
  }
  if(pos[i].x()+2 == c->x() &&
     (pos[i].y()+1==c->y() || pos[i].y()-1==c->y()))
  {
    return true;
  }
  return false;
}

string Piece::toString_At(int i)
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
  for(int j = space; j < 15;j++)
    s+=" ";
  s+= "Color: ";
  s+=color?"1":"0";
  s+="   x:"+to_string(pos[i].x())+"    y:"+to_string(pos[i].y())+"\n";
  return  s;
}
string Piece::toString(bool cpx)
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
  
  s+="    Color:";
  s+=color?"1":"0";
  s+="     Alive:";
  s+=alive?"1":"0";
  s+="   size:  ";
  s+=to_string(TM_size);
  if(cpx)
  {
    for(int i = 0; i < TM_size; i++)
      {
	s+="\n        (";
	s+=to_string(pos[i].x());
	s+=",";
	s+=to_string(pos[i].y());
	s+=")";
      }
  }
  s+="\n";
  return  s;
}
