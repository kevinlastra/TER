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
    cout <<liste[i]<<endl;
    temps_index = i;
    interpreteur(&liste[i]);
  }
  //while(EM->fill_none_piece());
  //TD->clear_score();
}
Identify::~Identify()
{
  delete EM;
  delete TD;
}

void Identify::interpreteur(string* piece)
{
  //INIT
  int ascii = (int)piece[0][0];
  
  Info_piece* info_piece = new Info_piece();
  info_piece->color = temps_index%2==0;
  Piece* p;

  //START CALC
  TD->clear_score();
  int size = TD->size();
  for(int i = 0; i < size;i++)
  {
    //cout << "TIMELINE: "<<i<<"    size: "<<size<<"     "<<piece[0]<<endl;
    p = NULL;
    
    info_piece->action = int_to_act(3);
    info_piece->coord = Coord();
    info_piece->info = Info(false, false);

    TL_index = i;
    tl = TD->TimeLine_at(i);
    
    if(piece[0][(*piece).size()-1] == '+')
      info_piece->info.echec = true;
    
    info_piece->type = char_to_type(ascii);
    if(ascii >= 65 && ascii <= 90)
    {
      if(ascii == 'K')
      {
	Factorize(&p, info_piece, piece);
      }
      else if(ascii == 'Q' || ascii == 'B' || ascii == 'N' || ascii == 'R')
      {
	if((int)piece[0][2] < 97 || piece[0][1] == 'x')
	{
	  Factorize(&p, info_piece, piece); 
	}
	else
	{
	  info_piece->info.ambiguous = true;
	  p = tl->chessplate->find_piece_ambiguos(info_piece->type,
						  info_piece->color,
						  (int)piece[0][2]-96,
						  (int)piece[0][3]-48,
						  (int)piece[0][1]-96,
						  false);
	  info_piece->coord = Coord((int)piece[0][2]-96,
				   (int)piece[0][3]-48);
	  info_piece->action = int_to_act(0);
	}
      }
      else if(ascii == 'O')
      {
	int a,b;
	
	info_piece->action = int_to_act(3);
	if(piece[0] == "O-O")
	{
	  //cout <<endl<< "Rok-kingside & King change: "<<endl<<endl;
	  tl->chessplate->return_Castling(info_piece->color,roi,a,b);
	  
	  p = tl->chessplate->at(a);
	  info_piece->coord = Coord(p->get_last_pos().x()+2,
				   p->get_last_pos().y());
	  
	  
	  tl->add_instant_on_top(p,info_piece->coord,
				 int_to_act(2),info_piece->info);
	  
	  p = tl->chessplate->at(b);
	  info_piece->coord = Coord(info_piece->coord.x()-1,
				   info_piece->coord.y());
	  
	  tl->add_instant_on_top(p,info_piece->coord,
				 int_to_act(2),info_piece->info);
	  continue;
	}
	else if(piece[0] == "O-O-O")
	{
	  //cout <<endl<< "Rok-queenside & king change: "<<endl<<endl;
	  tl->chessplate->return_Castling(info_piece->color,dame,a,b);
	  
	  p = tl->chessplate->at(a);
	  info_piece->coord = Coord(p->get_last_pos().x()-2,
				   p->get_last_pos().y());
	  
	  tl->add_instant_on_top(p,info_piece->coord,int_to_act(2),
				 info_piece->info);
	  
	  p = tl->chessplate->at(b);
	  info_piece->coord = Coord(info_piece->coord.x()+1,
				   info_piece->coord.y());
	  
	  tl->add_instant_on_top(p,info_piece->coord,int_to_act(2),
				 info_piece->info);
	  continue;
	}
      }
    }
    else if(piece[0] == "_")
    {
      p = new Piece(NONE,info_piece->color,-1,-1);
      info_piece->coord = Coord(-1,-1);
    }
    else
    {
      //cout << "Pion: " << piece[0]<<endl;
      if(piece[0][1] != 'x')
      {      
	//simple movement
	if(piece[0][2] == '\0' || piece[0][2] == '+')
	{
	  p = tl->chessplate->find_piece(pions,info_piece->color,
					 (int)piece[0][0]-96,
					 (int)piece[0][1]-48);
	  
	  info_piece->coord = Coord((int)piece[0][0]-96,
				   (int)piece[0][1]-48);
	  info_piece->action = int_to_act(0);

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
	  p = tl->chessplate->find_piece(pions,info_piece->color,
					 (int)piece[0][0]-96,
					 (int)piece[0][1]-48);
	  p->set_Alive(false);
	  info_piece->coord = Coord((int)piece[0][0]-96,
				   (int)piece[0][1]-48);
	  
	  info_piece->action = int_to_act(3);
	  
	  tl->add_instant_on_top(p,info_piece->coord,info_piece->action,
				 info_piece->info);
	  p = tl->chessplate->at(tl->chessplate->size());
	  p->set_Type(piece[0][2]);
	  p->set_Color(info_piece->color);
	  p->add_movements(0,p->get_last_pos());

	  
	  tl->chessplate->promotion();
	  
	  tl->add_instant_on_top(p,info_piece->coord,info_piece->action,
				 info_piece->info);
	  
	  continue;
	}
      }
      else//pion mange
      {
	info_piece->info.ambiguous = true;
	//cout <<"-----"<<piece[0]<<endl;
	p = tl->chessplate->find_piece_ambiguos(pions,info_piece->color,
						(int)piece[0][2]-96,
						(int)piece[0][3]-48,
						(int)piece[0][0]-96,
						true);
	info_piece->x = (int)piece[0][0]-96;
	info_piece->coord = Coord((int)piece[0][2]-96,
				 (int)piece[0][3]-48);
	info_piece->action = int_to_act(1);
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
      if(info_piece->action == 1)
      {
	if(Tuer(tl->chessplate->index_of(p),
		info_piece) == -1)
	{
	  continue;
	}
      }
      tl->add_instant_on_top(p,info_piece->coord,
			     info_piece->action,
			     info_piece->info);
    }
    else if(p == NULL)
    {
      //cout <<endl<<"Erreur: "<< piece[0] << endl;

      Error.piece_index = -1;
      
      Error.info_piece = info_piece;
      
      Error.tl_index = TL_index;
      Error.tl_instance_index = temps_index;

      Traitement_erreur();
    }
  }
  delete info_piece;
}
void Identify::Factorize(Piece** p, Info_piece* ip, string* s)
{
  if(s[0][1] != 'x')
  {
    ip->coord = Coord((int)s[0][1]-96,(int)s[0][2]-48);
    *p = tl->chessplate->find_piece(ip->type,ip->color,
				    (int)s[0][1]-96,
				    (int)s[0][2]-48);
    
    ip->action = int_to_act(0);
  }
  else
  {
    ip->coord = Coord((int)s[0][2]-96,(int)s[0][3]-48);
    *p = tl->chessplate->find_piece(ip->type,ip->color,
				    (int)s[0][2]-96,
				    (int)s[0][3]-48);
    
    ip->action = int_to_act(1);
  }
}
int Identify::Tuer(int p_index, Info_piece* ip)
{
  //cout << "----------Tuer--------"<<endl;
  Piece* piece_to_kill = tl->chessplate->piece_at_coord(ip->coord.x(), ip->coord.y());
  
  if(piece_to_kill != NULL
     && piece_to_kill->get_Color() != tl->chessplate->at(p_index)->get_Color())
  {
    piece_to_kill->set_Alive(false);
    return 0;
  }
  else  //Preparation pour traitement d'erreur
  {
    Error.piece_index = p_index;
    
    Error.info_piece = ip;
    
    Error.tl_index = TL_index;
    Error.tl_instance_index = temps_index;

    Traitement_erreur();
    return -1;
  }
}



TimeDivision* Identify::get_TimeLines()
{
  return TD;
}

void Identify::Traitement_erreur()
{
  
  /*cout <<"Indentify -TE-   Type: "<<type_to_type_string(Error.info_piece->type)
       <<"    x: "
       <<(char)(96+Error.info_piece->coord.x())<<"    y: "
       <<Error.info_piece->coord.y()<<endl;
  */
  EM->Traiter_Erreur(Error);
}
