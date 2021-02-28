#include "Identify.h"
#include "Piece.h"
#include "Coord.h"
#include <string>
#include <iostream>

using namespace std;

Identify::Identify()
{
  TD = new TimeDivision;
}
Identify::Identify(string* l, int size)
{
  liste = l;
  TD = new TimeDivision;
  
  for(int i = 0; i < size; i++)
  {
    identify_ps(&liste[i], i);
  }
}
Identify::~Identify(){}

void Identify::identify_ps(string* piece, int index)
{
  int ascii = (int)piece[0][0];
  bool color = index%2==0;

  int act;
  Piece* p;
  
  Coord newcoord;
  Info info;

  int nb_timeline = TD->nb_timeline_end();
  int* tls = TD->timelines_end();
  MultiTimeLine* mtl;
  for(int i = 0; i < nb_timeline; i++)
  {
    act = 3;
    p = NULL;
    newcoord = Coord();
    info = Info(false, false);

    mtl = TD->get_TimeLine_at(tls[i]);
    
    if(piece[0][(*piece).size()-1] == '+')
      info.echec = true;
    if(ascii >= 65 && ascii <= 90)
    {
      if(ascii == 'K')
      {
	Factorize(mtl->tl, &p, &newcoord, color, roi, piece, act);
      }
      else if(ascii == 'Q' || ascii == 'B' || ascii == 'N' || ascii == 'R')
      {
	if((int)piece[0][2] < 97 || piece[0][1] == 'x')
	{
	  Factorize(mtl->tl, &p, &newcoord, color, char_to_type(ascii), piece, act); 
	}
	else
	{
	  info.ambiguous = true;
	  p = mtl->tl->chessplate->find_piece_ambiguos(char_to_type(ascii),color,(int)piece[0][2]-96,
						      (int)piece[0][3]-48,
						      (int)piece[0][1]-96,false);
	  newcoord = Coord((int)piece[0][2]-96,(int)piece[0][3]-48);
	  act = 0;
	}
      }
      else if(ascii == 'O')
      {
	int a,b;
	
	act = 3;
	if(piece[0] == "O-O")
	{
	  //cout <<endl<< "Rok-kingside & King change: "<<endl<<endl;
	  mtl->tl->chessplate->return_Castling(color,roi,a,b);
	  
	  p = mtl->tl->chessplate->at(a);
	  newcoord = Coord(p->get_last_pos().x()+2,
			   p->get_last_pos().y());
	  
	  
	  mtl->tl->add_instant_on_top(p,newcoord,int_to_act(2),info);
	  
	  p = mtl->tl->chessplate->at(b);
	  newcoord = Coord(newcoord.x()-1, newcoord.y());
	  
	  mtl->tl->add_instant_on_top(p,newcoord,int_to_act(2),info);
	  continue;
	}
	else if(piece[0] == "O-O-O")
	{
	  //cout <<endl<< "Rok-queenside & king change: "<<endl<<endl;
	  mtl->tl->chessplate->return_Castling(color,dame,a,b);
	  
	  p = mtl->tl->chessplate->at(a);
	  newcoord = Coord(p->get_last_pos().x()-2,
			   p->get_last_pos().y());
	  
	  mtl->tl->add_instant_on_top(p,newcoord,int_to_act(2),info);
	  
	  p = mtl->tl->chessplate->at(b);
	  newcoord = Coord(newcoord.x()+1, newcoord.y());
	  
	  mtl->tl->add_instant_on_top(p,newcoord,int_to_act(2),info);
	  continue;
	}
      }
    }
    else if(piece[0] == "_")
    {
      int time_pos = mtl->deb+mtl->tl->get_size();
      
      int* tls_ = TD->diviser(tls[i],2,time_pos);
      
      MultiTimeLine* mtl_;
      for(int j = 0; j < 2;j++)
      {
	mtl_ = TD->get_TimeLine_at(tls_[j]);
	p = new Piece();
	newcoord = Coord(0,0);
	
	mtl_->tl->add_instant_on_top(p,newcoord,int_to_act(act), info);
      }
      continue;
    }
    else
    {
      //cout << "Pion: " << piece[0]<<endl;
      if(piece[0][1] != 'x')
      {      
	//simple movement
	if(piece[0][2] == '\0' || piece[0][2] == '+')
	{
	  p = mtl->tl->chessplate->find_piece(pions,color,(int)piece[0][0]-96,(int)piece[0][1]-48);
	  
	  newcoord = Coord((int)piece[0][0]-96,(int)piece[0][1]-48);
	  act = 0;
	  
	}//promotion
	else if(piece[0][2] >= 65 && piece[0][2] <= 90)
	{
	  p = mtl->tl->chessplate->find_piece(pions,color,(int)piece[0][0]-96,(int)piece[0][1]-48);
	  p->set_Alive(false);
	  newcoord = Coord((int)piece[0][0]-96,(int)piece[0][1]-48);
	  
	  act = 3;
	  
	  mtl->tl->add_instant_on_top(p,newcoord,int_to_act(act), info);
	  
	  p = mtl->tl->chessplate->at(chessplate->size());
	  p->set_Type(piece[0][2]);
	  p->set_Color(color);
	  p->add_movements(0,p->get_last_pos());

	  
	  mtl->tl->chessplate->promotion();
	  
	  mtl->tl->add_instant_on_top(p,newcoord,int_to_act(act), info);
	  
	  continue;
	}
      }
      else//pion mange
      {
	info.ambiguous = true;
	
	p = mtl->tl->chessplate->find_piece_ambiguos(pions,color,(int)piece[0][2]-96,
						(int)piece[0][3]-48,(int)piece[0][0]-96,true);
	newcoord = Coord((int)piece[0][2]-96,(int)piece[0][3]-48);
	act = 1;
      }
    }

    
    if(p != NULL)
    {
	if(act == 1)
	{
	  Piece* piece_to_kill = mtl->tl->chessplate->piece_at_coord(newcoord.x(), newcoord.y());
	  //test pour "prise en passant"
	  if(p->get_Type() == pions && piece_to_kill == NULL && (ascii >= 97 && ascii <= 104))
	  {
	    Coord c;
	    int index;
	    if(color)
	    {
	      piece_to_kill = mtl->tl->chessplate->piece_at_coord(newcoord.x(), newcoord.y()-1);
	      c = piece_to_kill->get_pos_at(piece_to_kill->get_TM_size()-2);
	      index = piece_to_kill->get_movements_at(piece_to_kill->get_TM_size()-1);
	      
	      if(index != i-1 || c.x() != piece_to_kill->get_last_pos().x() ||
		 c.y() != piece_to_kill->get_last_pos().y() + 2)
		piece_to_kill = NULL;
	    }
	    else
	    {
	      piece_to_kill = mtl->tl->chessplate->piece_at_coord(newcoord.x(), newcoord.y()+1);
	      c = piece_to_kill->get_pos_at(piece_to_kill->get_TM_size()-2);
	      index = piece_to_kill->get_movements_at(piece_to_kill->get_TM_size()-1);
	      
	      if(index != i-1 || c.x() != piece_to_kill->get_last_pos().x() ||
		 c.y() != piece_to_kill->get_last_pos().y()-2)
		piece_to_kill = NULL;
	    }
	  }
	  if(piece_to_kill == NULL)
	  {
	    cout << "erreur piece en passant, piece == null"<<endl;
	    continue;
	  }
	  
	  piece_to_kill->set_Alive(false);
	}
	mtl->tl->add_instant_on_top(p,newcoord,int_to_act(act), info);
    }
    else if(p == NULL)
    {    
      cout <<endl<<"Error: "<< piece[0] << endl<<endl;;
    }
  }
}
void Identify::Factorize(TimeLine* tl, Piece** p, Coord* c, bool color, Type t, string* s, int& act)
{
  if(s[0][1] != 'x')
  {
    p[0] = tl->chessplate->find_piece(t,color,(int)s[0][1]-96,(int)s[0][2]-48);
    c[0] = Coord((int)s[0][1]-96,(int)s[0][2]-48);
    act = 0;
  }
  else
  {
    p[0] = tl->chessplate->find_piece(t,color, (int)s[0][2]-96, (int)s[0][3]-48);
    c[0] = Coord((int)s[0][2]-96,(int)s[0][3]-48);

    act = 1;
  }
}


TimeDivision* Identify::get_TimeLines()
{
  return TD;
}
Type Identify::char_to_type(char type)
{
  switch(type)
  {
  case 'K':
    return roi;
    break;
  case 'Q':
    return dame;
    break;
  case 'B':
    return fous;
    break;
  case 'N':
    return cavaliers;
    break;
  case 'R':
    return tours;
    break;
  default:
    return pions;
    break;
  }
}
