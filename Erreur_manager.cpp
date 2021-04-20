#include "Erreur_manager.h"



Erreur_manager::Erreur_manager(TimeDivision* td)
{
  TD=td;
  EN = new Erreur_note(TD);
  ENOT = new Erreur_notation(TD);
}
Erreur_manager::~Erreur_manager()
{
  delete EN;
  delete ENOT;
}
void Erreur_manager::Traiter_Erreur(Info_Erreur e)
{
  	ENOT->Traiter_Erreur(e);
	EN->Traiter_Erreur(e);
}

bool Erreur_manager::fill_none_piece()
{
  bool null_check = false;
  int size = TD->size();
  for(int h = 0; h < size; h++)
  {
    TimeLine* tl = TD->TimeLine_at(h);
    if(tl->get_local_score() >= MAX_LOCAL_SCORE
       || tl->get_global_score() >= MAX_GLOBAL_SCORE)
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
      EN->Oublie_conscient_cas_castling(Info_Erreur(),false, alive_tl_indexs[arbres.size()]);
      for(int j = 0; j < arbres.size(); j++)
      {
	  arbre_struct_indexs = TD->diviser(arbres[j]->arbre_struct.size(),
					    alive_tl_indexs[j]);
	  for(int k = 0; k < arbres[j]->arbre_struct.size(); k++)
	  {
	    tl = TD->TimeLine_at(arbre_struct_indexs[k]);
	    tl->pp_score();
	    piece = tl->chessplate->at(arbres[j]->index);
	    piece->pp_score();
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
	    if(piece->piece_rampant()&&!tl->chessplate->check_piece_rampant_movement(piece->get_Type(),
								     piece->get_last_pos(),
								     arbres[j]->arbre_struct[k].c))
	    {
	      tl->score_kill();
	      continue;
	    }
	    info.ambiguous = EN->check_ambiguiter(tl,
					      arbres[j]->arbre_struct[k].c,
					      piece->get_Type(),
					      piece->get_Color(),
					      null_indexs[i]);
	    
	    piece_to_kill = tl->chessplate->piece_at_coord(arbres[j]->arbre_struct[k].c.x,
							   arbres[j]->arbre_struct[k].c.y);
	    
	    if(piece_to_kill != NULL)
	    {
	      if(piece_to_kill->get_Color() == piece->get_Color())
	      {
		tl->score_kill();
		continue;
	      }
	      if(piece->get_Type() != pions
		 || (piece->get_Type() == pions
		     && piece->get_last_pos().x != arbres[j]->arbre_struct[k].c.x))
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
  return null_check;
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
