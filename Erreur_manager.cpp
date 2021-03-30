#include "Erreur_manager.h"



Erreur_manager::Erreur_manager(TimeDivision* td){TD=td;}

void Erreur_manager::Traiter_Erreur(Info_Erreur e)
{
  TD->TimeLine_at(e.MTL_index)->pp_score();
  cout << "score["<<e.MTL_index<<"]: "<<TD->TimeLine_at(e.MTL_index)->get_score()<<endl;
  switch(e.type)
  {
  case pions:
    Pion(e);
    break;
  default:
    TD->TimeLine_at(e.MTL_index)->score_kill();
    break;
  }
}
void Erreur_manager::Pion(Info_Erreur e)
{
  Piece* p = NULL;
  TimeLine* tl;
  int* proxs;
  
  if(e.action == eat)
  {
    proxs = TD->diviser(2,e.MTL_index);
    
    //je suppose 2 posibiliter:
    //      1) manger en passant.
    //      2) erreur de notation "piece oublier"  ('_').
    
    //1)
    
    p = Manger_en_passant(e);
    tl = TD->TimeLine_at(proxs[0]);
    if(p == NULL)
    {
      cout << "Erreur: impossible de manger en passant, la piece a tuer ne remplit pas tout les condition"<<endl;
      tl->score_kill();
    }
    else
    {
      tl->add_instant_on_top(p,e.coord,e.action, e.info);
    }
    //2)
    Oublie_conscient(e,proxs);
    //END
  }
}
Piece* Erreur_manager::Manger_en_passant(Info_Erreur e)
{
  Coord c;
  int index;
  Piece* p = NULL;  
  TimeLine* tl = TD->TimeLine_at(e.MTL_index);
  if(e.color)
  {
    p = tl->chessplate->piece_at_coord(e.coord.x(), e.coord.y()-1);
    
    if(p == NULL)
    {
      cout << "Erreur: impossible de manger en passant, car il n'exist aucune piece"<<endl;
      //p = Traitement_erreur();
    }
    else
    {
      c = p->get_pos_at(p->get_TM_size()-2);
      index = p->get_movements_at(p->get_TM_size()-1);
      if(index != e.Temps_actuel-1 || c.x() != p->get_last_pos().x() ||
	 c.y() != p->get_last_pos().y() + 2)
      {
	return NULL;
      }
    }
  }
  else
  {
    p = tl->chessplate->piece_at_coord(e.coord.x(), e.coord.y()+1);
    
    if(p == NULL)
    {
      cout << "Erreur: impossible de manger en passant, car il n'exist aucune piece"<<endl;
      
      //p = Traitement_erreur();
    }
    else
    {
      c = p->get_pos_at(p->get_TM_size()-2);
      index = p->get_movements_at(p->get_TM_size()-1);
      
      if(index != e.Temps_actuel-1 || c.x() != p->get_last_pos().x() ||
	 c.y() != p->get_last_pos().y()-2)
      {
	return NULL;
      }
    }
  }

  return p;
}
void Erreur_manager::Oublie_conscient(Info_Erreur e, int* proxs)
{    
  cout << "Erreur coord x: "<<e.coord.x()<<"  y: "<<e.coord.y()<<endl;
    
  TimeLine* tl = TD->TimeLine_at(proxs[1]);
  int nb = 0;
  int* null_pieces = tl->get_all_piece_NULL(nb);

  proxs = TD->diviser(nb,proxs[1]);
    
  std::vector<Arbre*> arbres;
  Piece* piece;
  Piece* piece_to_kill;
  TimeLine* tl_proxs;
  int* proxs_arbres;
    
  for(int i = 0; i < nb; i++)
  {
    tl_proxs = TD->TimeLine_at(proxs[i]);
    
    //GEN ARBRE
    for(int h = 0; h < tl->chessplate->size(); h++)
    {
      if(!tl_proxs->chessplate->at(h)->get_Alive())
	continue;
      
      ArbreMovement AM(tl_proxs->chessplate);
      Arbre* a = AM.Generait_arbre(tl_proxs->chessplate->at(h),h,e.coord,1);
      if(a->arbre_struct.size() > 0)
	arbres.push_back(a);
    }
    if(arbres.size() == 0)
    {
      tl_proxs->score_kill();
      continue;
    }
    proxs_arbres = TD->diviser(arbres.size(), proxs[i]);
    for(int j = 0; j < arbres.size(); j++)
    {
      tl_proxs = TD->TimeLine_at(proxs_arbres[j]);
      
      piece = tl_proxs->chessplate->at(arbres[j]->index);
      
      for(int z = 1; z < arbres[j]->arbre_struct.size(); z++)
      {
	piece->add_movements(null_pieces[i],
			     arbres[j]->arbre_struct[z].c);
	
	tl_proxs->update_at(piece, Action::move, Info(), null_pieces[i]);
      }
      piece->set_Alive(false);

      cout << "index: "<<e.piece_index<<endl;
      tl_proxs->add_instant_on_top(tl_proxs->chessplate->at(e.piece_index),
				   e.coord, e.action, e.info);
    }
  }
}

//vérifie le coup doit engendrer un eat
bool Erreur_manager::Verif_eat(Info_Erreur e)
{    
  Piece* p = NULL;
  int pPosX; 
  int pPosY;
  //position de la pièce jouée
  

  TimeLine* tl = TD->TimeLine_at(e.MTL_index);

  //pour chaque coup joué avant ce tour
  for(int i=0;i<=e.Temps_actuel;i++)
  { 
    p = tl->get_instant_at(e.MTL_index)->p;
    //on récupère le dernier moment ou la pièce a été jouée
    int lastTime = p->time_to_previous_pos_time(i);

    //si c'est le dernier coup ou la pièce a été jouée 
    if(lastTime==i);
    {
      //si la pièce est encore en vie et que c'est une pièce adverse
      if(p->get_Alive()||p->get_Color()!=e.color)
      {
        pPosX = p->get_pos_at(lastTime).x();
        pPosY = p->get_pos_at(lastTime).y();
        //Si le coordonnée du coup sont égales a celle de pièce
        if(e.coord.x()==pPosX||e.coord.y()==pPosY)
        {
          return true; //la pièce doit être mangée
        }
      }
    }
  }
  //aucune pièce n'a pu être mangée par ce coup
  return false;
}

/*
bool Erreur_manager::Verif_echec(Info_Erreur e)
{    
  int roiX;
  int roiY;
  bool roiRecu = false;
  int ex;
  int ey;
  TimeLine* tl = TD->TimeLine_at(e.MTL_index);
  //1: on recupère le roi adverse si il n'a pas été joué on utilise les coord de debut
  for(int i=0;i<=e.Temps_actuel;i++)
  { 
    while(!roiRecu)
    {
      p = tl->get_instant_at(e.MTL_index)->p;
      int lastTime = p->time_to_previous_pos_time(i);
      if(lastTime==i)
      {
        if(p->get_Type()==Type::roi||p->get_Color()!=e.color)
        {
          roiX = p->get_pos_at(lastTime).x();
          roiY = p->get_pos_at(lastTime).y();
          
          roiRecu=true;
        }
      }
    }
  }
  //2: on teste pour chaque prochain coup de la pièce si il peut toucher les coordonnées du roi
  
  return false;
}
*/


