#include "Identify.h"
#include <iostream>

using namespace std;

Identify::Identify()
{
  TD = new TimeDivision;
  EM = new Erreur_manager(TD);
}
Identify::Identify(string* l, int size)
{
  liste = l;
  TD = new TimeDivision;
  EM = new Erreur_manager(TD);
  
  for(int i = 0; i < size; i++)
  {
    temps_index = i;
    interpreteur(&liste[i]);
  }
}
Identify::~Identify(){}

void Identify::interpreteur(string* piece)
{
  //INIT
  int ascii = (int)piece[0][0];
  
  bool color = temps_index%2==0;
  
  int act;
  Type type = NONE;
  Coord newcoord;
  
  Piece* p;
  
  Info info;

  int nb_timeline = TD->size();

  //START CALC
  for(int i = 0; i < nb_timeline; i++)
  {
    act = 3;
    p = NULL;
    newcoord = Coord();
    info = Info(false, false);

    MTL_index = i;
    tl = TD->TimeLine_at(i);
    
    if(piece[0][(*piece).size()-1] == '+')
      info.echec = true;
    
    type = char_to_type(ascii);
    if(ascii >= 65 && ascii <= 90)
    {
      if(ascii == 'K')
      {
	Factorize(&p, &newcoord, color, type, piece, act);
      }
      else if(ascii == 'Q' || ascii == 'B' || ascii == 'N' || ascii == 'R')
      {
	if((int)piece[0][2] < 97 || piece[0][1] == 'x')
	{
	  Factorize(&p, &newcoord, color, type, piece, act); 
	}
	else
	{
	  info.ambiguous = true;
	  p = tl->chessplate->find_piece_ambiguos(type,color,(int)piece[0][2]-96,
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
	  tl->chessplate->return_Castling(color,roi,a,b);
	  
	  p = tl->chessplate->at(a);
	  newcoord = Coord(p->get_last_pos().x()+2,
			   p->get_last_pos().y());
	  
	  
	  tl->add_instant_on_top(p,newcoord,int_to_act(2),info);
	  
	  p = tl->chessplate->at(b);
	  newcoord = Coord(newcoord.x()-1, newcoord.y());
	  
	  tl->add_instant_on_top(p,newcoord,int_to_act(2),info);
	  continue;
	}
	else if(piece[0] == "O-O-O")
	{
	  //cout <<endl<< "Rok-queenside & king change: "<<endl<<endl;
	  tl->chessplate->return_Castling(color,dame,a,b);
	  
	  p = tl->chessplate->at(a);
	  newcoord = Coord(p->get_last_pos().x()-2,
			   p->get_last_pos().y());
	  
	  tl->add_instant_on_top(p,newcoord,int_to_act(2),info);
	  
	  p = tl->chessplate->at(b);
	  newcoord = Coord(newcoord.x()+1, newcoord.y());
	  
	  tl->add_instant_on_top(p,newcoord,int_to_act(2),info);
	  continue;
	}
      }
    }
    else if(piece[0] == "_")
    {
      cout << "piece type = '_'"<<endl;
      p = new Piece(NONE,color,-1,-1);
      newcoord = Coord(-1,-1);
    }
    else
    {
      //cout << "Pion: " << piece[0]<<endl;
      if(piece[0][1] != 'x')
      {      
	//simple movement
	if(piece[0][2] == '\0' || piece[0][2] == '+')
	{
	  p = tl->chessplate->find_piece(pions,color,(int)piece[0][0]-96,(int)piece[0][1]-48);
	  
	  newcoord = Coord((int)piece[0][0]-96,(int)piece[0][1]-48);
	  act = 0;
	  
	}//promotion
	else if(piece[0][2] >= 65 && piece[0][2] <= 90)
	{
	  p = tl->chessplate->find_piece(pions,color,(int)piece[0][0]-96,(int)piece[0][1]-48);
	  p->set_Alive(false);
	  newcoord = Coord((int)piece[0][0]-96,(int)piece[0][1]-48);
	  
	  act = 3;
	  
	  tl->add_instant_on_top(p,newcoord,int_to_act(act), info);
	  
	  p = tl->chessplate->at(chessplate->size());
	  p->set_Type(piece[0][2]);
	  p->set_Color(color);
	  p->add_movements(0,p->get_last_pos());

	  
	  tl->chessplate->promotion();
	  
	  tl->add_instant_on_top(p,newcoord,int_to_act(act), info);
	  
	  continue;
	}
      }
      else//pion mange
      {
	info.ambiguous = true;
	cout <<"-----"<<piece[0]<<endl;
	p = tl->chessplate->find_piece_ambiguos(pions,color,(int)piece[0][2]-96,
						(int)piece[0][3]-48,(int)piece[0][0]-96,true);
	newcoord = Coord((int)piece[0][2]-96,(int)piece[0][3]-48);
	act = 1;
      }
    }

    
    if(p != NULL)
    {
      if(act == 1)
      {
	Tuer(newcoord,info,type);
      }
      tl->add_instant_on_top(p,newcoord,int_to_act(act), info);
    }
    else if(p == NULL)
    {
      cout <<endl<<"Erreur: "<< piece[0] << endl<<endl;
      
      Traitement_erreur();
    }
  }
}
void Identify::Factorize(Piece** p, Coord* c, bool color, Type t, string* s, int& act)
{
  if(s[0][1] != 'x')
  {
    *p = tl->chessplate->find_piece(t,color,(int)s[0][1]-96,(int)s[0][2]-48);
    *c = Coord((int)s[0][1]-96,(int)s[0][2]-48);
    act = 0;
  }
  else
  {
    *p = tl->chessplate->find_piece(t,color, (int)s[0][2]-96, (int)s[0][3]-48);
    *c = Coord((int)s[0][2]-96,(int)s[0][3]-48);

    act = 1;
  }
}
void Identify::Tuer(Coord c, Info info, Type type)
{
  cout << "----------Tuer--------"<<endl;
  Piece* piece_to_kill = tl->chessplate->piece_at_coord(c.x(), c.y());
  //test pour "prise en passant"
  if(piece_to_kill == NULL)
  {
    cout << "Erreur: piece a tuée introuvable"<<endl;
    Error.type = type;
    Error.coord = c;
    Error.action = eat;
    Error.color = temps_index%2==0;
    Error.info = info;
    
    Error.MTL_index = MTL_index;
    Error.Temps_actuel = temps_index;
    
    Traitement_erreur();
  }

  piece_to_kill->set_Alive(false);
  cout <<"----------Mort-----------"<<endl;
}



TimeDivision* Identify::get_TimeLines()
{
  return TD;
}

void Identify::Traitement_erreur()
{
  cout <<"Type: "<<type_to_type_string(Error.type)<<"    x: "
       <<(char)(96+Error.coord.x())<<"    y: "<<Error.coord.y()+1<<endl;

  EM->Traiter_Erreur(Error);
}
