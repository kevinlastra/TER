#include "TimeLine.h"
#include <iostream>

using namespace std;

TimeLine::TimeLine():size(0){}
TimeLine::~TimeLine(){}

void TimeLine::add_instant_on_top(Piece* p, Coord c, Action a, Info* inf)
{
  Instant ins;
  ins.p = p;
  ins.a = a;
  ins.info = inf;
  
  ins.i = p->time_to_pos_index(size);
  
  p->add_movements(size, c);  
  size++;

  instants.push_back(ins);
}
void TimeLine::add_instant_at(Piece* p, Coord c, Action a, Info* inf, int j)
{
  Instant ins;
  ins.p = p;
  ins.a = a;
  ins.info = inf;
  ins.i = p->time_to_pos_index(size);
  
  std::vector<Instant>::iterator it=instants.begin();
  instants.insert(it+j, ins);
  
  p->add_movements(j, c);
  size++;
}
void TimeLine::update_at(Piece* p, Action a, Info* info, int i)
{
  instants.at(i).p->set_Type(p->get_Type());
  instants.at(i).p->set_Coord_at(p->get_pos_at(i),i);
  instants.at(i).p->set_Color(p->get_Color());
  
  instants.at(i).i = p->time_to_pos_index(i);
  instants.at(i).a = a;
  instants.at(i).info = info;
}
void TimeLine::remove_at(int j)
{
  instants.erase(instants.begin()+j);
  size--;
}

int TimeLine::get_size()
{
  return size;
}
Action TimeLine::int_to_act(int i)
{
  switch(i)
  {
  case 0:
    return Action::move;
    break;
  case 1:
    return Action::eat;
    break;
  case 2:
    return Action::change;
    break;
  case 3:
    return Action::promotion;
    break;
  default:
    return Action::none;
    break;
  }
}
void TimeLine::toString()
{
  int j;
  for(int i = 0; i < size; i++)
  {
    if(i < 10)
      cout <<i<<".  ";
    else
      cout <<i<<". ";

    j = instants.at(i).p->time_to_pos_index(i);
    cout<< instants.at(i).p->toString_At(j)
	<<"    Action: "<<instants.at(i).a
	<<"    Echec? "<<instants.at(i).info->echec
	<<"    Ambiguous? "<<instants.at(i).info->ambiguous
	<<endl<<endl;
    
  }
}
Instant* TimeLine::get_instant_at(int i)
{
  return &instants.at(i);
}

Coord* TimeLine::get_next_coord(int i)
{
  int nextTime = instants.at(i).p->time_to_next_pos_time(i);
  
  Coord* nextCoord = instants.at(nextTime).p->get_Coords();
}
