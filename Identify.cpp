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
  TD->clear_score();
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

  //START CALC
  TD->clear_score();
  int size = TD->size();
  for(int i = 0; i < size;i++)
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
      cout << "piece type = '_'   at "<<temps_index<<endl;
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

    //tests
    /*
    Error.type = NONE;
    Error.coord = newcoord;
    Error.action = none;
    Error.color = temps_index%2==0;
    Error.info = info;
        
    Error.MTL_index = MTL_index;
    Error.Temps_actuel = temps_index;
    if(EM->Verif_echec(Error)){
      cout<<"Echec correct"<<endl;
    }else{
      cout<<"erreur d'echec"<<endl;
    }
    */

	  
	}//promotion
	else if(piece[0][2] >= 65 && piece[0][2] <= 90)
	{
	  p = tl->chessplate->find_piece(pions,color,(int)piece[0][0]-96,(int)piece[0][1]-48);
	  p->set_Alive(false);
	  newcoord = Coord((int)piece[0][0]-96,(int)piece[0][1]-48);
	  
	  act = 3;
	  
	  tl->add_instant_on_top(p,newcoord,int_to_act(act), info);
	  p = tl->chessplate->at(tl->chessplate->size());
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
	//cout <<"-----"<<piece[0]<<endl;
	p = tl->chessplate->find_piece_ambiguos(pions,color,(int)piece[0][2]-96,
						(int)piece[0][3]-48,(int)piece[0][0]-96,true);
	newcoord = Coord((int)piece[0][2]-96,(int)piece[0][3]-48);
	act = 1;
  //tests
  /*
  Error.type = NONE;
  Error.coord = newcoord;
  Error.action = none;
  Error.color = temps_index%2==0;
  Error.info = info;
      
  Error.MTL_index = MTL_index;
  Error.Temps_actuel = temps_index;
  if(EM->Erreur_eat(Error)){
    cout<<"eat correct"<<endl;
  }else{
    cout<<"erreur de eat"<<endl;
  }
  */
  }
    }

    
    if(p != NULL)
    {
      if(act == 1)
      {
	if(Tuer(tl->chessplate->index_of(p),newcoord,info,type) == -1)
	{
	  continue;
	}
      }
      tl->add_instant_on_top(p,newcoord,int_to_act(act), info);
    }
    else if(p == NULL)
    {
      cout <<endl<<"Erreur: "<< piece[0] << endl<<endl;

      Error.type = NONE;
      Error.coord = newcoord;
      Error.action = none;
      Error.color = temps_index%2==0;
      Error.info = info;
      
      Error.MTL_index = MTL_index;
      Error.Temps_actuel = temps_index;

      Traitement_erreur();
      //cout << "return to Identify (L189 aprox.)"<<endl;
    }
  }
}
void Identify::Factorize(Piece** p, Coord* c, bool color, Type t, string* s, int& act)
{
  if(s[0][1] != 'x')
  {
    *c = Coord((int)s[0][1]-96,(int)s[0][2]-48);
    *p = tl->chessplate->find_piece(t,color,(int)s[0][1]-96,(int)s[0][2]-48);
    
    act = 0;
  }
  else
  {
    *c = Coord((int)s[0][2]-96,(int)s[0][3]-48);
    *p = tl->chessplate->find_piece(t,color, (int)s[0][2]-96, (int)s[0][3]-48);
    
    act = 1;
  }
}
int Identify::Tuer(int p_index, Coord c, Info info, Type type)
{
  //cout << "----------Tuer--------"<<endl;
  Piece* piece_to_kill = tl->chessplate->piece_at_coord(c.x(), c.y());
  
  //Preparation pour traitement d'erreur
  if(piece_to_kill == NULL)
  {
    cout << "Erreur: piece a tuée introuvable.  index: "<<p_index<<endl;
    Error.piece_index = p_index;
    
    Error.type = type;
    Error.coord = c;
    Error.action = eat;
    Error.color = temps_index%2==0;
    Error.info = info;
    
    Error.MTL_index = MTL_index;
    Error.Temps_actuel = temps_index;

    Traitement_erreur();
    //cout << "return to Identify (L227 aprox.)"<<endl;
    return -1;
  }

  piece_to_kill->set_Alive(false);
  //cout <<"----------Mort-----------"<<endl;
  return 0;
}



TimeDivision* Identify::get_TimeLines()
{
  return TD;
}

void Identify::Traitement_erreur()
{
  cout <<"Type: "<<type_to_type_string(Error.type)<<"    x: "
       <<(char)(96+Error.coord.x())<<"    y: "<<Error.coord.y()<<endl;

  EM->Traiter_Erreur(Error);
}
