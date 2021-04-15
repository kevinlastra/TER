#include "Erreur_note.h"

Erreur_note::Erreur_note(TimeDivision* td):TD(td){}
Erreur_note::~Erreur_note(){}

void Erreur_note::Traiter_Erreur(Info_Erreur e)
{
  /*cout <<"ERREUR - TE -   T: "
       <<"      tl: "<<e.tl_index
       <<"      i: "<<e.tl_instance_index
       <<endl;*/

  TimeLine* tl = TD->TimeLine_at(e.tl_index);
  tl->pp_score();

  int nb = 0;
  int* null_pieces = tl->get_all_piece_NULL(nb);
  if(nb == 0)
  {
    tl->score_kill();
    return;
  }
  
  int* proxs_castling = TD->diviser(2, e.tl_index);
  Oublie_conscient_cas_castling(e,true,proxs_castling[0]);
  e.tl_index = proxs_castling[1];
  
  switch(e.info_piece->type)
  {
  case pions:
    Pion(e,nb,null_pieces);
    break;
  case fous:
  case dame:
  case tours:
    Piece_rampant(e,nb,null_pieces);
    break;
  default:    
    if(e.piece_index != -1 && e.info_piece->action == eat)
    {
      Oublie_conscient_cas_B(e,e.tl_index,nb,null_pieces);
    }
    else if(e.piece_index == -1)
    {
      Oublie_conscient_cas_A(e,e.tl_index,nb,null_pieces);
    }
    else
    {
      cout << "ERREUR AUCUN CAS DETECTER - Erreur manager"<<endl;
      TD->TimeLine_at(e.tl_index)->score_kill();
    }
    break;
  }
  
  delete[] null_pieces;
  delete[] proxs_castling;
}
void Erreur_note::Pion(Info_Erreur e,int nb, int* null_pieces)
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
      p->pp_score();
      tl->add_instant_on_top(p,e.info_piece->coord,e.info_piece->action, e.info_piece->info);
    }
    //2)
    Oublie_conscient_cas_B(e,proxs[1],nb,null_pieces);
    //END
    delete proxs;
  }

  if(e.piece_index == -1)
  {
    //je n'exist pas
    Oublie_conscient_cas_A(e,e.tl_index,nb,null_pieces);
  }
  
}
void Erreur_note::Piece_rampant(Info_Erreur e,int nb, int* null_pieces)
{
  if(e.piece_index == -1)
  {
    //je suppose 2 cas possible:
    //1) soit j'exist mais il existe une piece dans mon chemin
    //   donc cette piece a un erreur d'oublie, CAS C
    //2) soit je n'exist pas, CAS A
    int* proxs = TD->diviser(2, e.tl_index);

    //1)
    Oublie_conscient_cas_C(e,proxs[0],nb,null_pieces);
    //2)
    Oublie_conscient_cas_A(e,proxs[1],nb,null_pieces);
    delete[] proxs;
  }
  else 
  {
    if(e.info_piece->action == eat)
    {
      Oublie_conscient_cas_B(e, e.tl_index,nb,null_pieces);
    }
    else
    {
      Oublie_conscient_cas_C(e, e.tl_index,nb,null_pieces);
    }
  }
}
Piece* Erreur_note::Manger_en_passant(Info_Erreur e)
{
  Coord c;
  int index;
  Piece* p = NULL;  
  TimeLine* tl = TD->TimeLine_at(e.tl_index);
  if(e.info_piece->color)
  {
    p = tl->chessplate->piece_at_coord(e.info_piece->coord.x, e.info_piece->coord.y-1);
    
    if(p == NULL)
    {
      //cout << "Erreur: impossible de manger en passant, car il n'exist aucune piece"<<endl;
      //p = Traitement_erreur();
      tl->score_kill();
    }
    else
    {
      c = p->get_pos_at(p->get_TM_size()-2);
      index = p->get_movements_at(p->get_TM_size()-1);
      
      if(index != e.tl_instance_index-1 || c.x != p->get_last_pos().x ||
	 c.y != p->get_last_pos().y + 2)
      {
	return NULL;
      }
    }
  }
  else
  {
    p = tl->chessplate->piece_at_coord(e.info_piece->coord.x, e.info_piece->coord.y+1);
    
    if(p == NULL)
    {
      tl->score_kill();
    }
    else
    {
      c = p->get_pos_at(p->get_TM_size()-2);
      index = p->get_movements_at(p->get_TM_size()-1);
      
      if(index != e.tl_instance_index-1 || c.x != p->get_last_pos().x ||
	 c.y != p->get_last_pos().y-2)
      {
	return NULL;
      }
    }
  }

  return p;
}
void Erreur_note::Oublie_conscient_cas_A(Info_Erreur e, int index_tl,int nb_null, int* null_pieces)
{
  TimeLine* tl = TD->TimeLine_at(index_tl);
  
  int* proxs;

  Info info;
  std::vector<Arbre*> arbres;
  std::vector<Anode> chemin;
  int nb_chemin;
  Piece* piece;
  Piece* piece_to_kill;
  TimeLine* tl_prox;
  int* proxs_arbres;
  int* proxs_chemins;

  arbres = Gen_Arbre(tl, e.info_piece->coord,2,e.info_piece->color);
  if(arbres.size() == 0)
  {
    tl_prox->score_kill();
    return;
  }
  proxs_arbres = TD->diviser(arbres.size(), index_tl);
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
      proxs = TD->diviser(nb_null, proxs_chemins[z]);
      for(int i = 0; i < nb_null; i++)
      {
	tl_prox = TD->TimeLine_at(proxs[i]);
	piece = tl_prox->chessplate->at(arbres[j]->index);
	/*if(piece->get_Color() != tl_prox->get_color(null_pieces[i]))
	{
	  tl->score_kill();
	  continue;
	  }*/
	
	
	if(piece->get_Type() == roi && tl_prox->chessplate->check_king_movement(chemin[0].c))
	{
	  tl_prox->score_kill();
	  continue;
	}
	
	if(piece->piece_rampant()
	   && (!tl->chessplate->check_piece_rampant_movement(piece->get_Type(),
					     piece->get_last_pos(),
					     chemin[0].c)
	       || !tl->chessplate->check_piece_rampant_movement(piece->get_Type(),
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
      
	piece_to_kill = tl_prox->chessplate->piece_at_coord(chemin[0].c.x, chemin[0].c.y);
	if(piece_to_kill != NULL)
	{
	  if(piece_to_kill->get_Color() == piece->get_Color())
	  {
	    tl_prox->score_kill();
	    continue;
	  }
	  
	  if(piece->get_Type() != pions
	     || (piece->get_Type() == pions
		 && piece->get_last_pos().x != chemin[0].c.x))
	  {
	    piece_to_kill->set_Alive(false);
	    piece_to_kill->pp_score();
	    
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
	piece->pp_score();
	//-------------------
	//-------------------
	
	piece_to_kill = tl_prox->chessplate->piece_at_coord(chemin[1].c.x,
							    chemin[1].c.y);
	if(piece_to_kill != NULL)
	{
	  if(piece_to_kill->get_Color() == piece->get_Color())
	  {
	    tl_prox->score_kill();
	    continue;
	  }
	  if((e.info_piece->action == eat && piece->get_Type() != pions)
	     || (piece->get_Type() == pions
		 && piece->get_last_pos().x != chemin[1].c.x))
	  {
	    piece_to_kill->set_Alive(false);
	    piece_to_kill->pp_score();
	  }
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
      
	tl_prox->add_instant_on_top(piece,
				    e.info_piece->coord, e.info_piece->action,
				    e.info_piece->info);
	piece->pp_score();
	//-----------------------
      }
      delete[] proxs;
    }
    delete[] proxs_chemins;
    delete arbres[j];
  }
  delete[] proxs_arbres;
}
void Erreur_note::Oublie_conscient_cas_B(Info_Erreur e, int index_tl,int nb_null, int* null_pieces)
{
  TimeLine* tl = TD->TimeLine_at(index_tl);
  
  int* proxs;

  Info info;
  std::vector<Arbre*> arbres;
  Piece* piece;
  Piece* piece_to_kill;
  TimeLine* tl_prox;
  int* proxs_arbres;

  arbres = Gen_Arbre(tl, e.info_piece->coord,1,e.info_piece->color);
    
  if(arbres.size() == 0)
  {
    tl->score_kill();
    return;
  }
  proxs_arbres = TD->diviser(arbres.size(), index_tl);
  for(int j = 0; j < arbres.size(); j++)
  {    
    proxs = TD->diviser(nb_null, proxs_arbres[j]);
    for(int i = 0; i < nb_null; i++)
    {
      tl_prox = TD->TimeLine_at(proxs[i]);
      piece = tl_prox->chessplate->at(arbres[j]->index);
      
      /*if(piece->get_Color() != tl->get_color(null_pieces[i]))
      {
	tl->score_kill();
	continue;
	}*/
      
      if(piece->get_Type() == roi && tl_prox->chessplate->check_king_movement(arbres[j]->arbre_struct[1].c))
      {
	tl_prox->score_kill();
	continue;
      }
      
      if(piece->piece_rampant()
	 && !tl->chessplate->check_piece_rampant_movement(piece->get_Type(),
					  piece->get_last_pos(),
					  arbres[j]->arbre_struct[1].c))
      {
	tl_prox->score_kill();
	continue;
      }
      
      info.ambiguous = check_ambiguiter(tl_prox,
					arbres[j]->arbre_struct[1].c,
					piece->get_Type(),
					piece->get_Color(), null_pieces[i]);
      //-----
      
      piece_to_kill = tl_prox->chessplate->piece_at_coord(arbres[j]->arbre_struct[1].c.x,
							  arbres[j]->arbre_struct[1].c.y);
      if(piece_to_kill != NULL)
      {
	if(piece_to_kill->get_Color() == piece->get_Color())
	{
	  tl_prox->score_kill();
	  continue;
	}
	if(piece->get_Type() != pions
	   || (piece->get_Type() == pions
		 && piece->get_last_pos().x != arbres[j]->arbre_struct[1].c.x))
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
      piece->pp_score();
     
      piece->set_Alive(false);
      
      tl_prox->add_instant_on_top(tl_prox->chessplate->at(e.piece_index),
				  e.info_piece->coord, e.info_piece->action,
				  e.info_piece->info);
      tl_prox->chessplate->at(e.piece_index)->pp_score();
    }
    delete[] proxs;
    delete arbres[j];
  }
  delete[] proxs_arbres;
}
void Erreur_note::Oublie_conscient_cas_C(Info_Erreur e, int index_tl, int nb_null, int* null_pieces)
{
  TimeLine* tl = TD->TimeLine_at(index_tl);
  
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
      null_proxs = TD->diviser(nb_null,proxs_arbres[j]);
      for(int k = 0; k < nb_null; k++)
      {
	arbre_proxs = TD->diviser(arbres[j]->arbre_struct.size(), null_proxs[k]);
	for(int h = 0; h < arbres[j]->arbre_struct.size(); h++)
	{
	  tl = TD->TimeLine_at(arbre_proxs[h]);
	  
	  piece = tl->chessplate->at(arbres[j]->index);
	  
	  /*if(piece->get_Color() != tl->get_color(null_pieces[k]))
	  {
	    tl->score_kill();
	    continue;
	    }*/
	  
	  if(piece->get_Type() == roi
	     && tl->chessplate->check_king_movement(arbres[j]->arbre_struct[h].c))
	  {
	    tl->score_kill();
	    continue;
	  }
	  
	  if(piece->piece_rampant()&&!tl->chessplate->check_piece_rampant_movement(piece->get_Type(),
								   piece->get_last_pos(),
								   arbres[j]->arbre_struct[h].c))
	  {
	    tl->score_kill();
	    continue;
	  }
	  info.ambiguous = check_ambiguiter(tl, arbres[j]->arbre_struct[h].c,
					    piece->get_Type(), piece->get_Color(), null_pieces[k]);
	  //------------
	  piece_to_kill = tl->chessplate->piece_at_coord(arbres[j]->arbre_struct[h].c.x,
							 arbres[j]->arbre_struct[h].c.y);
	  if(piece_to_kill != NULL)
	  {
	    if(piece_to_kill->get_Color() == piece->get_Color())
	    {
	      tl->score_kill();
	      continue;
	    }
	    if(piece->get_Type() != pions
	       || (piece->get_Type() == pions
		   && piece->get_last_pos().x != arbres[j]->arbre_struct[h].c.x))
	    {
	      piece_to_kill->set_Alive(false);
	      piece_to_kill->pp_score();
	      
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
	  piece->pp_score();
	  
	  tl->add_instant_on_top(tl->chessplate->at(piece_indexs[i]),
				 e.info_piece->coord, e.info_piece->action,
				 e.info_piece->info);
	  tl->chessplate->at(piece_indexs[i])->pp_score();
	}
	delete[] arbre_proxs;
      }
      delete[] null_proxs;
      delete arbres[j];
    }
    delete[] proxs_arbres;
  }
  delete[] proxs;
}
void Erreur_note::Oublie_conscient_cas_castling(Info_Erreur e, bool repair, int tl_index)
{
  bool color = true;
  int nb = 0;
  TimeLine* tl = TD->TimeLine_at(tl_index);
  int* null_indexs = tl->get_all_piece_NULL(nb);
  if(nb == 0)
  {
    tl->score_kill();
    delete[] null_indexs;
    return;
  }
  int* indexs = TD->diviser(nb,tl_index);
  int* K_indexs;
  Piece* a;
  Piece* b;

  for(int i = 0; i < nb; i++)
  {
    if(null_indexs[i]-1 > 0)
      color = tl->get_color(null_indexs[i]);
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
	b->pp_score();
	a->add_movements(null_indexs[i]+1, Coord(6,1));
	a->pp_score();
	
	if(repair)
	{
	  castling_extension(tl,e,Coord(6,1));
	}
      }
      else
	tl->score_kill();
      
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
	b->pp_score();
	a->add_movements(null_indexs[i]+1, Coord(4,1));
	a->pp_score();
	
	if(repair)
	  castling_extension(tl,e,Coord(4,1));
      }
      else
	tl->score_kill();
      
      delete[] K_indexs;
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
	b->pp_score();
	a->add_movements(null_indexs[i]+1, Coord(6,8));
	a->pp_score();
	
	if(repair)
	{
	  castling_extension(tl,e,Coord(6,8));
	}
      }
      else
	tl->score_kill();

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
	b->pp_score();
	a->add_movements(null_indexs[i]+1, Coord(4,8));
	a->pp_score();
	
	if(repair)
	  castling_extension(tl,e,Coord(4,8));
      }
      else
	tl->score_kill();
      
      delete[] K_indexs;
    }
  }
  delete[] indexs;
  delete[] null_indexs;
}
void Erreur_note::castling_extension(TimeLine* tl, Info_Erreur e,Coord c)
{
  Piece* piece;
  if(e.piece_index == -1)
  {
    piece = tl->chessplate->piece_at_coord(c.x, c.y);
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
    piece->pp_score();
  }
  if(e.info_piece->action == eat)
  {
    piece = tl->chessplate->piece_at_coord(e.info_piece->coord.x,
				       e.info_piece->coord.y);
    if(piece == NULL)
    {
      tl->score_kill();
      return;
    }
    else
    {
      piece->set_Alive(false);
      piece->pp_score();
    }
  }
}

std::vector<Arbre*> Erreur_note::Gen_Arbre(TimeLine* tl, Coord c, int prof, bool color)
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
std::vector<Arbre*> Erreur_note::Gen_Arbre(TimeLine* tl, std::vector<int> ps, int prof)
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

std::vector<int> Erreur_note::get_piece_in_path(ChessPlate* chess, Coord c1, Coord c2, Type t)
{
  std::vector<int> piece_indexs;
  int dst;
  int x = (c1.x > c2.x)?-1:1;
  int y = (c1.y > c2.y)?-1:1;
  Piece* p;
  if(t == dame || t == fous)
  {
    dst = abs(c1.x - c2.x);
    for(int i = 1; i <= dst; i++)
    {
      p = chess->piece_at_coord(c1.x+i*x, c1.y+i*y);
      if(p != NULL)
	piece_indexs.push_back(chess->index_of(p));
    }
  }
  if(t == dame || t == tours)
  {
    dst = abs(c1.x - c2.x)+abs(c1.y - c2.y);//1 des 2 est egal a 0
    if(c1.x == c2.x)
    {
      for(int i = 1; i <= dst; i++)
      {
	p = chess->piece_at_coord(c1.x, c1.y+i*y);
	if(p != NULL)
	  piece_indexs.push_back(chess->index_of(p));
      }
    }
    else if(c1.y == c2.y)
    {
      for(int i = 1; i <= dst; i++)
      {
	p = chess->piece_at_coord(c1.x+i*x, c1.y);
	if(p != NULL)
	  piece_indexs.push_back(chess->index_of(p));
      }
    }
  }
  return piece_indexs;
}
bool Erreur_note::check_ambiguiter(TimeLine* tl, Coord coord, Type type, bool couleur, int index)
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
