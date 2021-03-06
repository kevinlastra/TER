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
  std::vector<Instant> ins = tl->get_instants();
  Coord c;
  Piece* p;
  for(int i = 0; i < tl->get_size(); i++)
  {
    c = ins[i].p->get_pos_at(0);
    p = chessplate->piece_at_init(c.x,c.y);
    if(p != NULL)
    {
      Instant a(ins[i].i, p,
		ins[i].a,ins[i].info);
    
      instants.push_back(a);
    }
    else
    {
      Instant a(ins[i].i, new Piece(ins[i].p),
		    ins[i].a,ins[i].info);
    
      instants.push_back(a);
    }
  }
  score = tl->get_local_score();
  nb_none_piece = tl->get_nb_none_p();
}
TimeLine::~TimeLine()
{
  delete chessplate;
}
Info::Info(){echec=false;ambiguous=false;}
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
void TimeLine::add_instant_at(Piece* p, Action a, Info inf, int j)
{
  Instant ins(p->time_to_pos_index(instants.size()), p, a, inf);
  
  std::vector<Instant>::iterator it=instants.begin();
  instants.insert(it+j, ins);

  for(int i = j+1; i < instants.size(); i++)
  {
    instants[i].p->pp_TM_sup(i-1);
  }
}
void TimeLine::update_at(Piece* p, Action a, Info info, int i)
{
  delete instants.at(i).p;
  instants.at(i).p = p;
  
  instants.at(i).i = p->time_to_pos_index(i);
  instants.at(i).a = a;
  instants.at(i).info = info;
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
int TimeLine::get_local_score()
{
  return score;
}
int TimeLine::get_global_score()
{
  int max_sc = 0;
  int sc = 0;
  for(int i = 0; i < chessplate->size(); i++)
  {
    sc = chessplate->at(i)->get_score();
    if(sc > max_sc)
      max_sc = sc;
  }
  return max_sc;
}
void TimeLine::pp_none_p(){nb_none_piece++;}
int TimeLine::get_nb_none_p(){return nb_none_piece;};
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
    //cout<< instants[i].p->toString_At(j)
    cout << instants[i].p->toString(true)
	 <<"   "<<instants[i].p<<endl
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
void TimeLine::Check_timeline()
{
  ChessPlate* chess = new ChessPlate();
  Piece* piece;
  Piece* k_piece;
  Coord c1, c2;
  int index = 0;
  int* tm;
  bool ERROR = false;

  int size = instants.size();
  for(int i = 0; i < size; i++)
  {
    //FROM
    //cout <<type_to_type_string(instants[i].p->get_Type())<<endl;
    if(instants[i].p->get_Type() == NONE)
    {
      cout<<"???"<<endl;
      continue;
    }
    
    tm = instants[i].p->get_TM();
    
    for(int j = 0; j < instants[i].p->get_TM_size(); j++)
    {
      if(tm[j] == i)
      {
	index = j;
	break;
      }
    }
    c1 = Coord(instants[i].p->get_pos_at(index-1).x,
	      instants[i].p->get_pos_at(index-1).y);
    piece = chess->piece_at_coord(c1.x,c1.y);
    //TO
    index = instants[i].p->time_to_pos_index(i);
    c2 = Coord(instants[i].p->get_pos_at(index).x,
	      instants[i].p->get_pos_at(index).y);
    if(piece != NULL)
    {
      if(piece->Test_movements(&c2, instants[i].a == eat, piece->get_TM_size()-1))
      {
	switch(piece->get_Type())
	{
	case tours:
	  if(instants[i].a != change)
	    ERROR = !chess->check_Rok_path(c1,c2);
	  break;
	case fous:
	  ERROR = !chess->check_Bishop_path(c1,c2);
	  break;
	case dame:
	  ERROR = !chess->check_Rok_path(c1,c2)
	    && !chess->check_Bishop_path(c1,c2);
	  break;
	}
      }
      else
      {
	if(instants[i].a != change)
	{
	  ERROR = true;
	}
      }
    }
    else
    {
      ERROR = true;
    }
    if(ERROR)
    {
      score_kill();
      break;
    }
    else
    {
      Coord* posRoi = Verif_echec(i);
      if(instants[i].p->Test_movements(posRoi,true,instants[i].i))
      {
        if(!instants[i].p->piece_rampant() 
	   ||(instants[i].p->piece_rampant()
	      && !chessplate->check_piece_rampant_movement(instants[i].p->get_Type(),
							   c1,
							   *posRoi)))
	{
	  instants[i].info.echec = true;
	}
      }
      else
      {
        instants[i].info.echec = false;
      }
      if(instants[i].a == eat)
      {
        k_piece = chess->piece_at_coord(c2.x,c2.y);
        if(k_piece == NULL && piece->get_Type() == pions)
        {
          if(piece->get_Color())
            k_piece = chess->piece_at_coord(c2.x,c2.y-1);
          else
            k_piece = chess->piece_at_coord(c2.x,c2.y+1);
        }
        
        if(k_piece == NULL)
        {
          score_kill();
          break;
        }
        
        k_piece->set_Alive(false);
      }
      piece->add_movements(i,c2);
      if(instants[i].a == promotion)
      {
	piece->set_Alive(false);

	//promotion
	i++;
	piece = chess->at(chess->size());
	piece->set_Type(instants[i].p->get_Type());
	piece->set_Type(instants[i].p->get_Color());
	piece->add_movements(0,c2);

	chess->promotion();
      }
    }
  }
  delete chess;
}
bool TimeLine::get_color(int i)
{
  bool color = true;
  //impossible de faire un castling a l'index 0
  for(int j = 1; j < instants.size() && j <= i; j++)
  {
    color = !color;
    if(instants[j].a == change)
      j++;
  }
  return color;
}
int* TimeLine::get_all_piece_NULL(int& nb)
{
  nb = 0;
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

Coord* TimeLine::Verif_echec(int i)
{
  Piece* p_Test;
  bool couleur = instants[i].p->get_Color();
  //cout<<"recup var"<<endl;
  int size = chessplate->size();
  
  //cout<<"instant recupéré"<<endl;
  //1: on recupère le roi adverse si il n'a pas été joué on utilise les coord de debut
  
    
    
      for(int i = 0; i < size; i++)
      {
        p_Test = chessplate->at(i);
          
        //cout<<"tl size: "<<tl->get_size()<<endl;
        //p_Test->toString();
        if(p_Test->get_Type() == roi
          && p_Test->get_Color() != couleur)
        {
          return p_Test->get_Coord();
        }
        
      }
  return NULL;
}

