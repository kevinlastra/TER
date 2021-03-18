#include "Erreur_manager.h"



Erreur_manager::Erreur_manager(TimeDivision* td){TD=td;}

void Erreur_manager::Traiter_Erreur(Info_Erreur e)
{
  Pion(e);
  exit(1);
}
void Erreur_manager::Pion(Info_Erreur e)
{
  Piece* p = NULL;
  TimeLine* tl;
  int* proxs;
  
  if(e.action == eat)
  {
    proxs = TD->diviser(2,e.MTL_index);
    cout <<(proxs==NULL)<<endl;
    //je suppose 2 posibiliter:
    //      1) manger en passant.
    //      2) erreur de notation "piece oublier"  ('_').
    
    //1)
    p = Manger_en_passant(e);
    if(p == NULL)
    {
      cout << "Erreur: impossible de manger en passant, la piece a tuer ne remplit pas tout les condition"<<endl;
    }
    else
    {
      tl = TD->TimeLine_at(proxs[0]);
      tl->add_instant_on_top(p,e.coord,e.action, e.info);
    }
    //2)
    tl = TD->TimeLine_at(proxs[1]);
    int nb = 0;
    int* indexs = tl->get_all_piece_NULL(nb);
    
    proxs = TD->diviser(nb,proxs[1]);
    cout << "Erreur coord x: "<<e.coord.x()<<"  y: "<<e.coord.y()<<endl;
    std::vector<std::vector<Anode>> arbres;
    for(int i = 0; i < nb; i++)
    {
      for(int h = 0; h < tl->chessplate->size(); h++)
      {
	if(!tl->chessplate->at(h)->get_Alive())
	  continue;
	
	ArbreMovement AM(tl->chessplate);
	arbres.push_back(AM.Generait_arbre(tl->chessplate->at(h),e.coord,1));
      }
    
      for(int j = 0; j < arbres.size(); j++)
      {
	for(int z = 0; z < arbres[j].size(); z++)
	{
	  cout << "prev: "<<arbres[j][z].prev
	       <<"   x: "<<arbres[j][z].c.x()
	       <<"   y: "<<arbres[j][z].c.y()<<endl;
	}
	if(arbres[j].size()>0)
	  cout <<endl;
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
