#include "Erreur_manager.h"



Erreur_manager::Erreur_manager(TimeDivision* td){TD=td;}

void Erreur_manager::Traiter_Erreur(Info_Erreur e)
{
  TD->TimeLine_at(e.tl_index)->pp_score();
  cout <<"tl index: "<<e.tl_index<<"    score: "<< TD->TimeLine_at(e.tl_index)->get_score()<<endl;
  switch(e.info_piece->type)
  {
  case pions:
    Pion(e);
    break;
  default:
    if(e.piece_index != -1 && e.info_piece->action == eat)
    {
      Oublie_conscient_cas_B(e,e.tl_index);
    }
    else if(e.piece_index == -1)
    {
      Oublie_conscient_cas_A(e,e.tl_index,2);
    }
    else
    {
      TD->TimeLine_at(e.tl_index)->score_kill();
    }
    break;
  }
}
void Erreur_manager::Pion(Info_Erreur e)
{
  Piece* p = NULL;
  TimeLine* tl;
  int* proxs;

  //j'ai exist mais la piece que je veut manger no
  if(e.piece_index != -1 && e.info_piece->action == eat)
  {
    proxs = TD->diviser(2,e.tl_index);  
    //je suppose 2 posibiliter:
    //      1) manger en passant.
    //      2) erreur de notation "piece oublier"  ('_').
    //1)
    p = Manger_en_passant(e);
    tl = TD->TimeLine_at(proxs[0]);
    if(p == NULL)
    {
      //piece por manger en passant n'est pas trouver donc je suppose (pour l'instant)
      //que ça doit etre le 2em cas, donc detruir timeline
      tl->score_kill();
    }
    else
    {
      tl->add_instant_on_top(p,e.info_piece->coord,e.info_piece->action, e.info_piece->info);
    }
    //2)
    Oublie_conscient_cas_B(e,proxs[1]);
    //END
  }

  //je n'exist pas
  Oublie_conscient_cas_A(e,e.tl_index,2);
}
Piece* Erreur_manager::Manger_en_passant(Info_Erreur e)
{
  Coord c;
  int index;
  Piece* p = NULL;  
  TimeLine* tl = TD->TimeLine_at(e.tl_index);
  if(e.info_piece->color)
  {
    p = tl->chessplate->piece_at_coord(e.info_piece->coord.x(), e.info_piece->coord.y()-1);
    
    if(p == NULL)
    {
      //cout << "Erreur: impossible de manger en passant, car il n'exist aucune piece"<<endl;
      //p = Traitement_erreur();
    }
    else
    {
      c = p->get_pos_at(p->get_TM_size()-2);
      index = p->get_movements_at(p->get_TM_size()-1);
      if(index != e.tl_instance_index-1 || c.x() != p->get_last_pos().x() ||
	 c.y() != p->get_last_pos().y() + 2)
      {
	return NULL;
      }
    }
  }
  else
  {
    p = tl->chessplate->piece_at_coord(e.info_piece->coord.x(), e.info_piece->coord.y()+1);
    
    if(p == NULL)
    {
      //cout << "Erreur: impossible de manger en passant, car il n'exist aucune piece"<<endl;
      
      //p = Traitement_erreur();
    }
    else
    {
      c = p->get_pos_at(p->get_TM_size()-2);
      index = p->get_movements_at(p->get_TM_size()-1);
      
      if(index != e.tl_instance_index-1 || c.x() != p->get_last_pos().x() ||
	 c.y() != p->get_last_pos().y()-2)
      {
	return NULL;
      }
    }
  }

  return p;
}
void Erreur_manager::Oublie_conscient_cas_A(Info_Erreur e, int index_tl, int prof)
{
  TimeLine* tl = TD->TimeLine_at(index_tl);
  int nb = 0;
  
  int* null_pieces = tl->get_all_piece_NULL(nb);
  int* proxs = TD->diviser(nb,index_tl);
    
  std::vector<Arbre*> arbres;
  std::vector<Anode> chemin;
  int nb_chemin;
  Piece* piece;
  Piece* piece_to_kill;
  TimeLine* tl_prox;
  int* proxs_arbres;
  int* proxs_chemins;
  
  for(int i = 0; i < nb; i++)
  {
    tl_prox = TD->TimeLine_at(proxs[i]);

    arbres = Gen_Arbre(tl_prox, e.info_piece->coord,prof);
    if(arbres.size() == 0)
    {
      tl_prox->score_kill();
      continue;
    }
    proxs_arbres = TD->diviser(arbres.size(), proxs[i]);
    for(int j = 0; j < arbres.size(); j++)
    {
      tl_prox = TD->TimeLine_at(proxs_arbres[j]);

      nb_chemin = arbres[j]->nb_chemin();

      if(tl_prox->chessplate->at(arbres[j]->index)->get_Type() != e.info_piece->type)
      {
	tl_prox->score_kill();
	continue;
      }
      proxs_chemins = TD->diviser(nb_chemin, proxs_arbres[j]);
      for(int z = 0; z < nb_chemin; z++)
      {
	tl_prox = TD->TimeLine_at(proxs_chemins[z]);
	chemin = arbres[j]->chemin_at(z);
	if(chemin.size() == 0)
	  continue;
	piece = tl_prox->chessplate->at(arbres[j]->index);
	
	//-------------
	piece_to_kill = tl_prox->chessplate->piece_at_coord(chemin[0].c.x(), chemin[0].c.y());
	if(piece_to_kill != NULL)
	{
	  piece_to_kill->set_Alive(false);
	  tl_prox->update_at(piece, Action::eat, Info(), null_pieces[i]);
	}
	else
	  tl_prox->update_at(piece, Action::move, Info(), null_pieces[i]);
	
	piece->add_movements(null_pieces[i], chemin[0].c);
	//-------------------
	//-------------------
	if(e.info_piece->action == eat)
	{
	  piece_to_kill = tl_prox->chessplate->piece_at_coord(chemin[1].c.x(), chemin[1].c.y());
	  if(piece_to_kill != NULL)
	    piece_to_kill->set_Alive(false);
	  else
	    cout <<"ERREUR - Erreur manager - piece_to_kill not found"<<endl;
	}
	
	tl_prox->add_instant_on_top(tl_prox->chessplate->at(arbres[j]->index),
				    e.info_piece->coord, e.info_piece->action,
				    e.info_piece->info);
	//-----------------------
      }      
    }
  }
}
void Erreur_manager::Oublie_conscient_cas_B(Info_Erreur e, int index_tl)
{    
  //cout << "Erreur coord x: "<<e.coord.x()<<"  y: "<<e.coord.y()<<endl;    
  TimeLine* tl = TD->TimeLine_at(index_tl);
  int nb = 0;
  
  int* null_pieces = tl->get_all_piece_NULL(nb);
  int* proxs = TD->diviser(nb,index_tl);

  //ChessPlate* chessplate;
  std::vector<Arbre*> arbres;
  Piece* piece;
  Piece* piece_to_kill;
  TimeLine* tl_prox;
  int* proxs_arbres;
    
  for(int i = 0; i < nb; i++)
  {
    tl_prox = TD->TimeLine_at(proxs[i]);
    
    arbres = Gen_Arbre(tl_prox, e.info_piece->coord,1);
    
    if(arbres.size() == 0)
    {
      tl_prox->score_kill();
      continue;
    }
    proxs_arbres = TD->diviser(arbres.size(), proxs[i]);
    for(int j = 0; j < arbres.size(); j++)
    {
      tl_prox = TD->TimeLine_at(proxs_arbres[j]);

      //chessplate = gen_old_chessplate(tl_prox, null_pieces[i]);
      piece = tl_prox->chessplate->at(arbres[j]->index);
      //-----
      
      piece_to_kill = tl_prox->chessplate->piece_at_coord(arbres[j]->arbre_struct[1].c.x(), arbres[j]->arbre_struct[1].c.y());
      if(piece_to_kill != NULL)
      {
	piece_to_kill->set_Alive(false);
	tl_prox->update_at(piece, Action::eat, Info(), null_pieces[i]);
      }
      else
	tl_prox->update_at(piece, Action::move, Info(), null_pieces[i]);
      
      piece->add_movements(null_pieces[i],
			   arbres[j]->arbre_struct[1].c);
      
      
      //-----
      piece->set_Alive(false);

      tl_prox->add_instant_on_top(tl_prox->chessplate->at(e.piece_index),
				  e.info_piece->coord, e.info_piece->action,
				  e.info_piece->info);
    }
  }
}
std::vector<Arbre*> Erreur_manager::Gen_Arbre(TimeLine* tl, Coord c, int prof)
{
  //GEN ARBRE
  std::vector<Arbre*> arbres;
  for(int h = 0; h < tl->chessplate->size(); h++)
  {
    if(!tl->chessplate->at(h)->get_Alive())
      continue;
    
    ArbreMovement AM(tl->chessplate);
    Arbre* a = AM.Generait_arbre(tl->chessplate->at(h),h,c,prof);
    if(a->arbre_struct.size() > 0)
      arbres.push_back(a);
  }
  return arbres;
}
//vérifie le coup doit engendrer un eat
bool Erreur_manager::Verif_eat(Info_Erreur e)
{    
  Piece* p = NULL;
  int pPosX; 
  int pPosY;
  //position de la pièce jouée
  

  TimeLine* tl = TD->TimeLine_at(e.tl_index);

  //pour chaque coup joué avant ce tour
  for(int i=0;i<=e.tl_instance_index;i++)
  { 
    p = tl->get_instant_at(e.tl_index)->p;
    //on récupère le dernier moment ou la pièce a été jouée
    int lastTime = p->time_to_previous_pos_time(i);

    //si c'est le dernier coup ou la pièce a été jouée 
    if(lastTime==i)
    {
      //si la pièce est encore en vie et que c'est une pièce adverse
      if(p->get_Alive()||p->get_Color()!=e.info_piece->color)
      {
        pPosX = p->get_pos_at(lastTime).x();
        pPosY = p->get_pos_at(lastTime).y();
        //Si le coordonnée du coup sont égales a celle de pièce
        if(e.info_piece->coord.x()==pPosX||e.info_piece->coord.y()==pPosY)
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


