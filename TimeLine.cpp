#include "TimeLine.h"
#include <iostream>

using namespace std;

TimeLine::TimeLine():chessplate(new ChessPlate()){}
TimeLine::TimeLine(ChessPlate* c)
{
  chessplate = new ChessPlate(c);
}

TimeLine::TimeLine(TimeLine* tl)
{
  chessplate = new ChessPlate(tl->chessplate);
  instants = std::vector<Instant>(tl->get_instants());
  score = tl->get_score();
}
TimeLine::~TimeLine(){}
Info::Info(){}
Info::Info(bool e, bool a)
{
  echec = e;
  ambiguous = a;
}
Instant::Instant(int index, Piece* piece, Action act, Info inf)
{
  i = index;
  p = piece;
  a = act;
  info.echec = inf.echec;
  info.ambiguous = inf.ambiguous;
}
void TimeLine::add_instant_on_top(Piece* p, Coord c, Action a, Info inf)
{
  Instant ins(p->time_to_pos_index(instants.size()), p, a, inf);
  
  ins.i = p->time_to_pos_index(instants.size());
  
  p->add_movements(instants.size(), c);  

  instants.push_back(ins);
}
void TimeLine::add_instant_at(Piece* p, Coord c, Action a, Info inf, int j)
{
  Instant ins(p->time_to_pos_index(instants.size()), p, a, inf);
  
  std::vector<Instant>::iterator it=instants.begin();
  instants.insert(it+j, ins);
  
  p->add_movements(j, c);
}
void TimeLine::update_at(Piece* p, Action a, Info info, int i)
{
  cout << p->toString(true)<<endl;
  instants.at(i).p->set_Type(p->get_Type());
  instants.at(i).p->set_Coord_at(p->get_pos_at(i),i);
  //instants.at(i).p->add_movements(instants.size(), c); 
  instants.at(i).p->set_Color(p->get_Color());
  
  instants.at(i).i = p->time_to_pos_index(i);
  instants.at(i).a = a;
  instants.at(i).info = info;
  cout << p->toString(true)<<endl;
}
void TimeLine::remove_at(int j)
{
  instants.erase(instants.begin()+j);
}

int TimeLine::get_size()
{
  return instants.size();
}
void TimeLine::score_kill()
{
  score = 1000;
}
void TimeLine::pp_score()
{
  score++;
}
int TimeLine::get_score()
{
  return score;
}
void TimeLine::toString()
{
  int j;
  for(int i = 0; i < instants.size(); i++)
  {
    if(i < 10)
      cout <<i<<".  ";
    else
      cout <<i<<". ";

    j = instants[i].p->time_to_pos_index(i);
    cout<< instants[i].p->toString_At(j)
	<<"    Action: "<<instants[i].a
	<<"    Echec? "<<instants[i].info.echec
	<<"    Ambiguous? "<<instants[i].info.ambiguous
	<<endl<<endl;
    
  }
}
Instant* TimeLine::get_instant_at(int i)
{
  return &instants[i];
}
std::vector<Instant> TimeLine::get_instants(){return instants;}
Coord* TimeLine::get_next_coord(int i)
{
  int nextTime = instants.at(i).p->time_to_next_pos_time(i);
  
  Coord* nextCoord = instants.at(nextTime).p->get_Coords();
}
int* TimeLine::get_all_piece_NULL(int& nb)
{
  for(int i = 0; i < instants.size(); i++)
  {
    if(instants[i].p->get_Type() == NONE)
    {
      nb++;
    }
  }
  int* indexs = new int[nb];
  int j = 0;
  for(int i = 0; i < instants.size(); i++)
  {
    if(instants[i].p->get_Type() == NONE)
    {
      indexs[j] = i;
      j++;
    }
  }
  return indexs;
}
Action int_to_act(int i)
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
