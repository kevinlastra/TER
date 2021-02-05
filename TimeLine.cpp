#include "TimeLine.h"
#include <iostream>

using namespace std;

TimeLine::TimeLine():max_size(4),size(0)
{
  act = new Action[4];
  piece = new Piece*[4];  
}
TimeLine::~TimeLine()
{
  delete[] act;
  delete[] piece;
}

void TimeLine::add_instance_on_top(Piece* p, Action a)
{
  if(size==max_size)
    resize_tl();

  act[size] = a;
  piece[size] = p;

  
  size++;
  p->add_movements(size);
}
void TimeLine::add_instance_at(Piece* p, Action a, int j)
{
  if(size+1==max_size)
    resize_tl();
  
  for(int i = size-1; i >= j; i--)
  {
    piece[i+1] = piece[i];
    act[i+1] = act[i];
  }
  piece[j] = p;
  act[j] = a;
  
  p->add_movements(j);
  size++;
}
void TimeLine::update_at(Piece* p, Action a, int i)
{  
  piece[i]->set_Type(p->get_Type());
  piece[i]->set_Coord(p->get_Coord());
  piece[i]->set_Color(p->get_Color());

  act[i] = a;
}
void TimeLine::remove_at(int j)
{
  for(int i = j+1; i < size; i++)
  {
    piece[i-1] = piece[i];
  }
  size--;
}
TimeLine::Instance* TimeLine::get_instance_at(int i)
{
  TimeLine::Instance* ins;
  ins->a = act[i];
  ins->p = piece[i];
  return ins;
}
int TimeLine::get_size()
{
  return size;
}
TimeLine::Action TimeLine::int_to_act(int i)
{
  switch(i)
  {
  case 0:
    return move;
    break;
  case 1:
    return eat;
    break;
  case 2:
    return change;
    break;
  default:
    return NONE;
    break;
  }
}
void TimeLine::resize_tl()
{
  max_size *= 2;
  Action* a_ = new Action[max_size];
  Piece** piece_ = new Piece*[max_size];

  for(int i = 0; i < size; i++)
  {
    a_[i] = act[i];
    piece_[i] = piece[i];
  }

  delete[] act;
  delete[] piece;

  act = a_;
  piece = piece_;
}
void TimeLine::toString()
{
  for(int i = 0; i < size; i++)
  {
    if(i < 10)
      cout <<i<<".  ";
    else
      cout <<i<<". ";
    cout<< piece[i]->toString() <<"    act: "<<act[i]<< endl;
  }
}
