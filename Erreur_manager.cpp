#include "Erreur_manager.h"



Erreur_manager::Erreur_manager(TimeDivision* td){TD=td;}
Erreur_manager::~Erreur_manager(){}
void Erreur_manager::Traiter_Erreur(Info_Erreur e)
{
  /*cout <<"ERREUR - TE -   T: "
       <<"      tl: "<<e.tl_index
       <<"      i: "<<e.tl_instance_index
       <<endl;*/
  TimeLine* tl = TD->TimeLine_at(e.tl_index);
  tl->pp_score();
  int* proxs_castling = TD->diviser(2, e.tl_index);
  Oublie_conscient_cas_castling(e,true,proxs_castling[0]);
  e.tl_index = proxs_castling[1];
  
  switch(e.info_piece->type)
  {
  case pions:
    Pion(e);
    break;
  case fous:
  case dame:
  case tours:
    Piece_rampant(e);
    break;
  default:    
    if(e.piece_index != -1 && e.info_piece->action == eat)
    {
      Oublie_conscient_cas_B(e,e.tl_index);
    }
    else if(e.piece_index == -1)
    {
      Oublie_conscient_cas_A(e,e.tl_index);
    }
    else
    {
      cout << "ERREUR AUCUN CAS DETECTER - Erreur manager"<<endl;
      TD->TimeLine_at(e.tl_index)->score_kill();
    }
    break;
  }
  delete[] proxs_castling;
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
      tl->score_kill();
    }
    else
    {
      tl->add_instant_on_top(p,e.info_piece->coord,e.info_piece->action, e.info_piece->info);
    }
    //2)
    Oublie_conscient_cas_B(e,proxs[1]);
    //END
    delete proxs;
  }

  if(e.piece_index == -1)
  {
    //je n'exist pas
    Oublie_conscient_cas_A(e,e.tl_index);
  }
}
void Erreur_manager::Piece_rampant(Info_Erreur e)
{
  if(e.piece_index == -1)
  {
    //je suppose 2 cas possible:
    //1) soit j'exist mais il existe une piece dans mon chemin
    //   donc cette piece a un erreur d'oublie, CAS C
    //2) soit je n'exist pas, CAS A
    int* proxs = TD->diviser(2, e.tl_index);

    //1)
    Oublie_conscient_cas_C(e,proxs[0]);
    //2)
    Oublie_conscient_cas_A(e,proxs[1]);
    delete[] proxs;
  }
  else 
  {
    if(e.info_piece->action == eat)
    {
      Oublie_conscient_cas_B(e, e.tl_index);
    }
    else
    {
      Oublie_conscient_cas_C(e, e.tl_index);
    }
  }
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
      tl->score_kill();
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
void Erreur_manager::Oublie_conscient_cas_A(Info_Erreur e, int index_tl)
{
  cout << "CAS A"<<endl;
  TimeLine* tl = TD->TimeLine_at(index_tl);
  int nb = 0;
  
  int* null_pieces = tl->get_all_piece_NULL(nb);
  int* proxs = TD->diviser(nb,index_tl);

  Info info;
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
    arbres = Gen_Arbre(tl_prox, e.info_piece->coord,2,e.info_piece->color);
    if(arbres.size() == 0)
    {
      tl_prox->score_kill();
      continue;
    }
    proxs_arbres = TD->diviser(arbres.size(), proxs[i]);
    for(int j = 0; j < arbres.size(); j++)
    {
      tl_prox = TD->TimeLine_at(proxs_arbres[j]);

      nb_chemin = arbres[j]->nb_chemin(2);
      if(tl_prox->chessplate->at(arbres[j]->index)->get_Type() != e.info_piece->type)
      {
	tl_prox->score_kill();
	continue;
      }
      proxs_chemins = TD->diviser(nb_chemin, proxs_arbres[j]);
      
      for(int z = 0; z < nb_chemin; z++)
      {
	tl_prox = TD->TimeLine_at(proxs_chemins[z]);
	chemin = arbres[j]->chemin_at(z,2);
	if(chemin.size() == 0)
	{
	  tl_prox->score_kill();
	  continue;
	}
	
	piece = tl_prox->chessplate->at(arbres[j]->index);
	
	if(piece->get_Color() != tl_prox->get_color(null_pieces[i]))
	{
	  tl->score_kill();
	  continue;
	}
	if(piece->get_Type() == roi && tl_prox->chessplate->check_king_movement(chemin[0].c))
	{
	  tl_prox->score_kill();
	  continue;
	}
	if(piece->piece_rampant()
	   && (!check_piece_rampant_movement(tl_prox,piece->get_Type(),
					    piece->get_last_pos(),
					    chemin[0].c)
	   || !check_piece_rampant_movement(tl_prox,piece->get_Type(),
					    chemin[0].c, chemin[1].c)))
	{
	  tl_prox->score_kill();
	  continue;
	}
	//-------------
	info.ambiguous = check_ambiguiter(tl_prox, chemin[0].c,
					  piece->get_Type(),
					  piece->get_Color(),
					  null_pieces[i]);
	
	piece_to_kill = tl_prox->chessplate->piece_at_coord(chemin[0].c.x(), chemin[0].c.y());
	if(piece_to_kill != NULL)
	{
	  if(piece_to_kill->get_Color() == piece->get_Color())
	  {
	    tl_prox->score_kill();
	    continue;
	  }
	  
	  if(piece->get_Type() != pions
	   || (piece->get_Type() == pions
	       && piece->get_last_pos().x() != chemin[0].c.x()))
	  {
	    piece_to_kill->set_Alive(false);
	    
	    if(piece->get_Type() == pions)
	      info.ambiguous = true;
	    
	    tl_prox->update_at(piece, Action::eat, info, null_pieces[i]);
	  }
	  else
	  {
	    tl_prox->score_kill();
	    continue;
	  }
	}
	else
	  tl_prox->update_at(piece, Action::move, info, null_pieces[i]);
	
	piece->add_movements(null_pieces[i], chemin[0].c);
	//-------------------
	//-------------------
	
	piece_to_kill = tl_prox->chessplate->piece_at_coord(chemin[1].c.x(),
							    chemin[1].c.y());
	if(piece_to_kill != NULL)
	{
	  if(piece_to_kill->get_Color() == piece->get_Color())
	  {
	    tl_prox->score_kill();
	    continue;
	  }
	  if((e.info_piece->action == eat && piece->get_Type() != pions)
	     || (piece->get_Type() == pions
		 && piece->get_last_pos().x() != chemin[1].c.x()))
	    piece_to_kill->set_Alive(false);
	  else
	    tl->score_kill();
	}
	else
	{
	  if(e.info_piece->action == eat)
	  {
	    tl->score_kill();
	    continue;
	  }
	}
	e.info_piece->info.ambiguous = check_ambiguiter(tl_prox, chemin[1].c,
							piece->get_Type(),
							piece->get_Color(),
							null_pieces[i]);
	
	tl_prox->add_instant_on_top(tl_prox->chessplate->at(arbres[j]->index),
				    e.info_piece->coord, e.info_piece->action,
				    e.info_piece->info);
	//-----------------------
      }
      delete[] proxs_chemins;
      delete arbres[j];
    }
    delete[] proxs_arbres;
  }
  delete[] proxs;
  delete[] null_pieces;
}
void Erreur_manager::Oublie_conscient_cas_B(Info_Erreur e, int index_tl)
{
  cout << "CAS B"<<endl;
  TimeLine* tl = TD->TimeLine_at(index_tl);
  int nb = 0;
  
  int* null_pieces = tl->get_all_piece_NULL(nb);
  int* proxs = TD->diviser(nb,index_tl);

  Info info;
  std::vector<Arbre*> arbres;
  Piece* piece;
  Piece* piece_to_kill;
  TimeLine* tl_prox;
  int* proxs_arbres;
    
  for(int i = 0; i < nb; i++)
  {
    tl_prox = TD->TimeLine_at(proxs[i]);

    arbres = Gen_Arbre(tl_prox, e.info_piece->coord,1,e.info_piece->color);
    
    if(arbres.size() == 0)
    {
      tl_prox->score_kill();
      continue;
    }
    proxs_arbres = TD->diviser(arbres.size(), proxs[i]);
    for(int j = 0; j < arbres.size(); j++)
    {
      tl_prox = TD->TimeLine_at(proxs_arbres[j]);

      piece = tl_prox->chessplate->at(arbres[j]->index);
      if(piece->get_Color() != tl->get_color(null_pieces[i]))
      {
	tl->score_kill();
	continue;
      }
      if(piece->get_Type() == roi && tl_prox->chessplate->check_king_movement(arbres[j]->arbre_struct[1].c))
      {
	tl_prox->score_kill();
	continue;
      }
      if(piece->piece_rampant()
	 && !check_piece_rampant_movement(tl_prox,piece->get_Type(),
					  piece->get_last_pos(),
					  arbres[j]->arbre_struct[1].c))
      {
	tl_prox->score_kill();
	continue;
      }
      
      info.ambiguous = check_ambiguiter(tl_prox, arbres[j]->arbre_struct[1].c,
					piece->get_Type(), piece->get_Color(), null_pieces[i]);
      //-----
      
      piece_to_kill = tl_prox->chessplate->piece_at_coord(arbres[j]->arbre_struct[1].c.x(), arbres[j]->arbre_struct[1].c.y());
      if(piece_to_kill != NULL)
      {
	if(piece_to_kill->get_Color() == piece->get_Color())
	{
	  tl_prox->score_kill();
	  continue;
	}
	if(piece->get_Type() != pions
	   || (piece->get_Type() == pions
	       && piece->get_last_pos().x() != arbres[j]->arbre_struct[1].c.x()))
	{
	  piece_to_kill->set_Alive(false);
	
	  if(piece->get_Type() == pions)
	    info.ambiguous = true;
	
	  tl_prox->update_at(piece, Action::eat, info, null_pieces[i]);
	}
	else
	{
	  tl_prox->score_kill();
	  continue;
	}
      }
      else
	tl_prox->update_at(piece, Action::move, info, null_pieces[i]);
      
      piece->add_movements(null_pieces[i],
			   arbres[j]->arbre_struct[1].c);
      
      
      //-----
      piece->set_Alive(false);

      tl_prox->add_instant_on_top(tl_prox->chessplate->at(e.piece_index),
				  e.info_piece->coord, e.info_piece->action,
				  e.info_piece->info);
      //tl_prox->toString();
      delete arbres[j];
    }
    delete[] proxs_arbres;
  }
  delete[] null_pieces;
}
void Erreur_manager::Oublie_conscient_cas_C(Info_Erreur e, int index_tl)
{
  cout << "CAS C"<<endl;
  int nb = 0;
  TimeLine* tl = TD->TimeLine_at(index_tl);
  int* null_pieces = tl->get_all_piece_NULL(nb);
  
  if(nb == 0)
  {
    tl->score_kill();
    return;
  }
  
  Piece* piece;
  Piece* piece_to_kill;
  std::vector<int> piece_indexs;
  Coord coord = e.info_piece->coord;
  
  for(int i = 0; i < tl->chessplate->size(); i++)
  {
    piece = tl->chessplate->at(i);
    if(piece->get_Alive()
       && piece->get_Type() == e.info_piece->type
       && piece->Test_movements(&coord,false,piece->get_TM_size()-1))
    {
      piece_indexs.push_back(i);
    }
  }
  if(piece_indexs.size() == 0)
  {
    tl->score_kill();
    delete[] null_pieces;
    return;
  }
  Info info;
  int* proxs = TD->diviser(piece_indexs.size(), index_tl);
  int* null_proxs;
  int* arbre_proxs;
  int* proxs_arbres;
  std::vector<int> piece_in_path;
  std::vector<Arbre*> arbres;
  for(int i = 0; i < piece_indexs.size(); i++)
  {
    tl = TD->TimeLine_at(proxs[i]);
    piece_in_path = get_piece_in_path(tl->chessplate,
				      tl->chessplate->at(piece_indexs[i])->get_last_pos(),
				      e.info_piece->coord,
				      e.info_piece->type);
    
    arbres = Gen_Arbre(tl, piece_in_path, 1);
    
    if(arbres.size() == 0)
    {
      tl->score_kill();
      continue;
    }
    
    proxs_arbres = TD->diviser(arbres.size(), proxs[i]);
    for(int j = 0; j < arbres.size(); j++)
    {
      tl = TD->TimeLine_at(proxs_arbres[j]);
      null_proxs = TD->diviser(nb,proxs_arbres[j]);
      for(int k = 0; k < nb; k++)
      {
	arbre_proxs = TD->diviser(arbres[j]->arbre_struct.size(), null_proxs[k]);
	for(int h = 0; h < arbres[j]->arbre_struct.size(); h++)
	{
	  tl = TD->TimeLine_at(arbre_proxs[h]);
	  
	  piece = tl->chessplate->at(arbres[j]->index);
	  if(piece->get_Color() != tl->get_color(null_pieces[i]))
	  {
	    tl->score_kill();
	    continue;
	  }
	  
	  if(piece->get_Type() == roi
	     && tl->chessplate->check_king_movement(arbres[j]->arbre_struct[h].c))
	  {
	    tl->score_kill();
	    continue;
	  }
	  
	  if(piece->piece_rampant()&&!check_piece_rampant_movement(tl,piece->get_Type(),
								   piece->get_last_pos(),
								   arbres[j]->arbre_struct[h].c))
	  {
	    tl->score_kill();
	    continue;
	  }
	  info.ambiguous = check_ambiguiter(tl, arbres[j]->arbre_struct[h].c,
					    piece->get_Type(), piece->get_Color(), null_pieces[k]);
	  //------------
	  piece_to_kill = tl->chessplate->piece_at_coord(arbres[j]->arbre_struct[h].c.x(),
							 arbres[j]->arbre_struct[h].c.y());
	  if(piece_to_kill != NULL)
	  {
	    if(piece_to_kill->get_Color() == piece->get_Color())
	    {
	      tl->score_kill();
	      continue;
	    }
	    if(piece->get_Type() != pions
	       || (piece->get_Type() == pions
		   && piece->get_last_pos().x() != arbres[j]->arbre_struct[h].c.x()))
	    {
	      piece_to_kill->set_Alive(false);
	    
	      if(piece->get_Type() == pions)
		info.ambiguous = true;
	      tl->update_at(piece, Action::eat, info, null_pieces[k]);
	    }
	    else
	    {
	      tl->score_kill();
	      continue;
	    }
	  }
	  else
	    tl->update_at(piece, Action::move, info, null_pieces[k]);

	  piece->add_movements(null_pieces[k],
			       arbres[j]->arbre_struct[h].c);
	  
	  tl->add_instant_on_top(tl->chessplate->at(piece_indexs[i]),
				 e.info_piece->coord, e.info_piece->action,
				 e.info_piece->info);
	}
	delete[] arbre_proxs;
      }
      delete[] null_proxs;
      delete arbres[j];
    }
    delete[] proxs_arbres;
  }
  delete[] proxs;
  delete[] null_pieces;
}
void Erreur_manager::Oublie_conscient_cas_castling(Info_Erreur e, bool repair, int tl_index)
{
  bool color = true;
  int nb = 0;
  TimeLine* tl = TD->TimeLine_at(tl_index);
  int* null_indexs = tl->get_all_piece_NULL(nb);
  
  int* indexs = TD->diviser(nb,tl_index);
  int* K_indexs;
  Piece* a;
  Piece* b;

  for(int i = 0; i < nb; i++)
  {
    if(null_indexs[i]-1 > 0)
      color = !tl->get_color(null_indexs[i]);
    if(color)
    {
      //WHITE
      //tour 16(1,1) 17(8,1)
      //roi 28(5,1)
      
      K_indexs = TD->diviser(2,indexs[i]);
      
      tl = TD->TimeLine_at(K_indexs[0]);
      a = tl->chessplate->at(17);
      b = tl->chessplate->at(28);
      
      if(tl->chessplate->piece_at_coord(7,1) == NULL
	 && tl->chessplate->piece_at_coord(6,1) == NULL
	 && a->get_TM_size() == 1
	 && b->get_TM_size() == 1)
      {
	tl->update_at(b, Action::change, Info(), null_indexs[i]);
	tl->add_instant_at(a, Action::change, Info(), null_indexs[i]+1);
	b->add_movements(null_indexs[i], Coord(7,1));
	a->add_movements(null_indexs[i]+1, Coord(6,1));

	if(repair)
	{
	  castling_extension(tl,e,Coord(6,1));
	}
      }
      else
      {
	tl->score_kill();
	delete[] K_indexs;
	continue;
      }
      
      tl = TD->TimeLine_at(K_indexs[1]);
      a = tl->chessplate->at(16);
      b = tl->chessplate->at(28);
      
      if(tl->chessplate->piece_at_coord(2,1) == NULL
	 && tl->chessplate->piece_at_coord(3,1) == NULL
	 && tl->chessplate->piece_at_coord(4,1) == NULL
	 && a->get_TM_size() == 1
	 && b->get_TM_size() == 1)
      {
	tl->update_at(b, Action::change, Info(), null_indexs[i]);
	tl->add_instant_at(a, Action::change, Info(), null_indexs[i]+1);
	b->add_movements(null_indexs[i], Coord(3,1));
	a->add_movements(null_indexs[i]+1, Coord(4,1));

	
	if(repair)
	  castling_extension(tl,e,Coord(4,1));
      }
      else
      {
	tl->score_kill();
	delete[] K_indexs;
	continue;
      }
    }
    else
    {
      //BLACK
      //tour 18(1,8) 19(8,8)
      //roi 29(5,8)
      K_indexs = TD->diviser(2,indexs[i]);
      tl = TD->TimeLine_at(K_indexs[0]);
      a = tl->chessplate->at(19);
      b = tl->chessplate->at(29);
      
      if(tl->chessplate->piece_at_coord(7,8) == NULL
	 && tl->chessplate->piece_at_coord(6,8) == NULL
	 && a->get_TM_size() == 1
	 && b->get_TM_size() == 1)
      {
	tl->update_at(b, Action::change, Info(), null_indexs[i]);
	tl->add_instant_at(a, Action::change, Info(), null_indexs[i]+1);
	b->add_movements(null_indexs[i], Coord(7,8));
	a->add_movements(null_indexs[i]+1, Coord(6,8));

	if(repair)
	{
	  castling_extension(tl,e,Coord(6,8));
	}
      }
      else
      {
	tl->score_kill();
	delete[] K_indexs;
	continue;
      }

      tl = TD->TimeLine_at(K_indexs[1]);
      a = tl->chessplate->at(18);
      b = tl->chessplate->at(29);
      if(tl->chessplate->piece_at_coord(2,8) == NULL
	 && tl->chessplate->piece_at_coord(3,8) == NULL
	 && tl->chessplate->piece_at_coord(4,8) == NULL
	 && a->get_TM_size() == 1
	 && b->get_TM_size() == 1)
      {
	tl->update_at(b, Action::change, Info(), null_indexs[i]);
	tl->add_instant_at(a, Action::change, Info(), null_indexs[i]);
	b->add_movements(null_indexs[i], Coord(3,8));
	a->add_movements(null_indexs[i]+1, Coord(4,8));

	if(repair)
	  castling_extension(tl,e,Coord(4,8));
      }
      else
      {
	tl->score_kill();
	delete[] K_indexs;
	continue;
      }
    }
  }
  delete[] indexs;
  delete[] null_indexs;
}
void Erreur_manager::castling_extension(TimeLine* tl, Info_Erreur e,Coord c)
{
  Piece* piece;
  if(e.piece_index == -1)
  {
    piece = tl->chessplate->piece_at_coord(c.x(), c.y());
    if(piece == NULL || (e.info_piece->type == tours
       && !tl->chessplate->check_Rok_path(c, e.info_piece->coord)))
    {
      tl->score_kill();
      return;
    }
    tl->add_instant_on_top(piece,
			   e.info_piece->coord,
			   e.info_piece->action,
			   e.info_piece->info);
  }
  else
  {
    if(e.info_piece->type == tours
       && !tl->chessplate->check_Rok_path(c,
					  e.info_piece->coord))
    {
      tl->score_kill();
      return;
    }
    piece = tl->chessplate->at(e.piece_index);
    piece->add_movements(e.tl_instance_index, e.info_piece->coord);
    tl->add_instant_on_top(piece,
			   e.info_piece->coord,
			   e.info_piece->action,
			   e.info_piece->info); 
  }
  if(e.info_piece->action == eat)
  {
    piece = tl->chessplate->piece_at_coord(e.info_piece->coord.x(),
				       e.info_piece->coord.y());
    if(piece == NULL)
    {
      tl->score_kill();
      return;
    }
    else
    {
      piece->set_Alive(false);
    }
  }
}
bool Erreur_manager::check_piece_rampant_movement(TimeLine* tl, Type t, Coord c1, Coord c2)
{
  switch(t)
  {
  case fous:
    if(tl->chessplate->check_Bishop_path(c1, c2))
      return true;
    break;
  case tours:
    if(tl->chessplate->check_Rok_path(c1, c2))
      return true;
    break;
  case dame:
  if(tl->chessplate->check_Bishop_path(c1, c2)
     || tl->chessplate->check_Rok_path(c1, c2))
    return true;
  break;
  }
  return false;
}
std::vector<Arbre*> Erreur_manager::Gen_Arbre(TimeLine* tl, Coord c, int prof, bool color)
{
  //GEN ARBRE
  std::vector<Arbre*> arbres;
  Piece* piece;
  for(int h = 0; h < tl->chessplate->size(); h++)
  {
    piece = tl->chessplate->at(h);
    if(!piece->get_Alive() && piece->get_Color() != color)
      continue;
    
    ArbreMovement AM(tl->chessplate);
    Arbre* a = AM.Generait_arbre(tl->chessplate->at(h),h,c,prof);
    if(a->arbre_struct.size() > 0)
    {
      arbres.push_back(a);
    }
  }
  return arbres;
}
std::vector<Arbre*> Erreur_manager::Gen_Arbre(TimeLine* tl, std::vector<int> ps, int prof)
{
  //GEN ARBRE
  std::vector<Arbre*> arbres;
  for(int h = 0; h < ps.size(); h++)
  { 
    ArbreMovement AM(tl->chessplate);
    Arbre* a = AM.Generait_arbre(ps[h],prof);
    if(a->arbre_struct.size() > 0)
      arbres.push_back(a);
  }
  return arbres;
}
std::vector<int> Erreur_manager::get_piece_in_path(ChessPlate* chess, Coord c1, Coord c2, Type t)
{
  std::vector<int> piece_indexs;
  int dst;
  int x = (c1.x() > c2.x())?-1:1;
  int y = (c1.y() > c2.y())?-1:1;
  Piece* p;
  if(t == dame || t == fous)
  {
    dst = abs(c1.x() - c2.x());
    for(int i = 1; i <= dst; i++)
    {
      p = chess->piece_at_coord(c1.x()+i*x, c1.y()+i*y);
      if(p != NULL)
	piece_indexs.push_back(chess->index_of(p));
    }
  }
  if(t == dame || t == tours)
  {
    dst = abs(c1.x() - c2.x())+abs(c1.y() - c2.y());//1 des 2 est egal a 0
    if(c1.x() == c2.x())
    {
      for(int i = 1; i <= dst; i++)
      {
	p = chess->piece_at_coord(c1.x(), c1.y()+i*y);
	if(p != NULL)
	  piece_indexs.push_back(chess->index_of(p));
      }
    }
    else if(c1.y() == c2.y())
    {
      for(int i = 1; i <= dst; i++)
      {
	p = chess->piece_at_coord(c1.x()+i*x, c1.y());
	if(p != NULL)
	  piece_indexs.push_back(chess->index_of(p));
      }
    }
  }
  return piece_indexs;
}
bool Erreur_manager::check_ambiguiter(TimeLine* tl, Coord coord, Type type, bool couleur, int index)
{
  int size = tl->chessplate->size();
  Piece* piece;
  int cpt = 0;
  for(int i = 0; i < size; i++)
  {
    piece = tl->chessplate->at(i);
    if(piece->get_Type() == type
       && piece->get_Color() == couleur
       && piece->Test_movements(&coord, false, piece->get_index_pos_inf(index)))
    {
      cpt++;
    }
  }
  return cpt == 2;
}
bool Erreur_manager::fill_none_piece()
{
  bool null_check = false;
  int size = TD->size();
  for(int h = 0; h < size; h++)
  {
    TimeLine* tl = TD->TimeLine_at(h);
    if(tl->get_score() > MAX_SCORE)
      continue;
    
    int nb_null_piece = 0;
    int* null_indexs = tl->get_all_piece_NULL(nb_null_piece);
    if(nb_null_piece == 0)
      continue;
    null_check = true;
    int chess_size = tl->chessplate->size();
    std::vector<int> alive_pieces;
    for(int i = 0; i < chess_size; i++)
    {
      if(tl->chessplate->at(i)->get_Alive())
      {
	alive_pieces.push_back(i);
      }
    }
    std::vector<Arbre*> arbres = Gen_Arbre(tl, alive_pieces, 1);
    
    Info info;
    int* null_tl_indexs = TD->diviser(nb_null_piece, h);
    int* alive_tl_indexs;
    int* arbre_struct_indexs;
    Piece* piece_to_kill;
    Piece* piece;
    for(int i = 0; i < nb_null_piece; i++)
    {
      alive_tl_indexs = TD->diviser(arbres.size()+1, null_tl_indexs[i]);
      Oublie_conscient_cas_castling(Info_Erreur(),false, alive_tl_indexs[arbres.size()]);
      for(int j = 0; j < arbres.size(); j++)
      {
	  arbre_struct_indexs = TD->diviser(arbres[j]->arbre_struct.size(),
					    alive_tl_indexs[j]);
	  for(int k = 0; k < arbres[j]->arbre_struct.size(); k++)
	  {
	    tl = TD->TimeLine_at(arbre_struct_indexs[k]);
	    tl->pp_score();
	    piece = tl->chessplate->at(arbres[j]->index);
	    if(piece->get_Color() != tl->get_color(null_indexs[i]))
	    {
	      tl->score_kill();
	      continue;
	    }
	    if(piece->get_Type() == roi
	       && tl->chessplate->check_king_movement(arbres[j]->arbre_struct[k].c))
	    {
	      tl->score_kill();
	      continue;
	    }
	    if(piece->piece_rampant()&&!check_piece_rampant_movement(tl,piece->get_Type(),
								     piece->get_last_pos(),
								     arbres[j]->arbre_struct[k].c))
	    {
	      tl->score_kill();
	      continue;
	    }
	    info.ambiguous = check_ambiguiter(tl,
					      arbres[j]->arbre_struct[k].c,
					      piece->get_Type(),
					      piece->get_Color(),
					      null_indexs[i]);
	    
	    piece_to_kill = tl->chessplate->piece_at_coord(arbres[j]->arbre_struct[k].c.x(),
							   arbres[j]->arbre_struct[k].c.y());
	    
	    if(piece_to_kill != NULL)
	    {
	      if(piece_to_kill->get_Color() == piece->get_Color())
	      {
		tl->score_kill();
		continue;
	      }
	      if(piece->get_Type() != pions
		 || (piece->get_Type() == pions
		     && piece->get_last_pos().x() != arbres[j]->arbre_struct[k].c.x()))
	      {
		piece_to_kill->set_Alive(false);
		
		if(piece->get_Type() == pions)
		  info.ambiguous = true;
		tl->update_at(piece, Action::eat, info, null_indexs[i]);
	      }
	      else
	      {
		tl->score_kill();
		continue;
	      }
	    }
	    else
	    {
	      tl->update_at(piece, Action::move, info, null_indexs[i]);
	    }
	    piece->add_movements(null_indexs[i],
				 arbres[j]->arbre_struct[k].c);
	  }
	  delete arbre_struct_indexs;
	}
	delete alive_tl_indexs;
      }
    for(int i = 0; i < arbres.size(); i++)
    {
      delete arbres[i];
    }
    delete null_tl_indexs;
    delete null_indexs;
  }
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


