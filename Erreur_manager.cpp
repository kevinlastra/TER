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

    
    cout << "Erreur coord x: "<<e.coord.x()<<"  y: "<<e.coord.y()<<endl;
    
    tl = TD->TimeLine_at(proxs[1]);
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
      //----
      /*cout << "###########"<<endl;
      TD->TimeLine_at(proxs_arbres[0])->toString();
      cout << "###########"<<endl;
      TD->TimeLine_at(proxs_arbres[1])->toString();
      //---
      exit(1);*/
      //UTILISER ARBRE
      for(int j = 0; j < arbres.size(); j++)
      {
	tl_proxs = TD->TimeLine_at(proxs_arbres[j]);
	
	piece = tl_proxs->chessplate->at(arbres[j]->index);

	if(j == 0)
	{
	  cout << " index: "<<arbres[j]->index<<"    "<<piece<<"    "<<tl_proxs<<"    "<<piece<<endl;
	}
	for(int z = 1; z < arbres[j]->arbre_struct.size(); z++)
	{
	  piece->add_movements(null_pieces[i],
			       arbres[j]->arbre_struct[z].c);
	  
	  tl_proxs->update_at(piece, Action::move, Info(), null_pieces[i]);
	}
	piece->set_Alive(false);
	cout <<"tl size: "<< tl_proxs->get_size()<<endl;
	cout << tl_proxs->get_instant_at(tl_proxs->get_size()-1)->p->toString()<<endl;
	tl_proxs->add_instant_on_top(tl_proxs->chessplate->at(e.piece_index),
				     e.coord, e.action, e.info);
	//cout <<"tl size: "<< tl_proxs->get_size()<<endl;
	//tl_proxs->toString();
	//exit(1);
      }
    }
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
