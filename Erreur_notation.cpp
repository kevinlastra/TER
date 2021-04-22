#include "Erreur_notation.h"

Erreur_notation::Erreur_notation(TimeDivision* td):TD(td){}
Erreur_notation::~Erreur_notation(){}

bool Erreur_notation::Traiter_Erreur(Info_Erreur e)
{

  //cout<<"traitement erreur"<<endl;
  /*cout<<"debut enot"<<endl;
  cout <<"ERREUR - TE -   T: "
       <<"      tl: "<<e.tl_index
       <<"      i: "<<e.tl_instance_index
       <<endl;
  */

  bool resolu = false;
  TimeLine* tl = TD->TimeLine_at(e.tl_index);
  tl->pp_score();
  int* proxs;
  
  //resolu = Erreur_type(e);
  //Verif_eat(e.info_piece,e.piece_index,e.tl_index);
  if(e.info_piece->type!= NONE){

    proxs = TD->diviser(2,e.tl_index);
    Erreur_coord(e,proxs[0]);
    Erreur_type(e,proxs[1]);
  }
  delete[] proxs;
  return resolu;
}


bool Erreur_notation::Erreur_coord(Info_Erreur error,int index_tl){
  //cout<<"err coord"<<endl;
  Info_piece* infP = error.info_piece; 
  bool couleur_piece = infP->color;
  Coord coord_piece = infP->coord;
  Type type_piece = infP->type;
  TimeLine* tl = TD->TimeLine_at(index_tl);
  TimeLine* next_TL;
  Piece* piece;
  Piece* piece_test;
  Piece* piece_to_kill;
  std::vector<int> index_type;
  std::vector<Anode> chemin;
  ArbreMovement AM(tl->chessplate);
  Arbre* arbre;
  int nb_chemins;
  int* next_try;
  int* next_tm;
  bool pion = true;
  bool found = false;
  index_type = Get_index_from_type(type_piece, couleur_piece, tl->chessplate);
  int size= index_type.size();

  if(type_piece!=Type::pions){
    pion=false;
  }
  if(size==0){
    tl->score_kill();
    return found;
  }
  next_try= TD->diviser(size,index_tl);
  for(int i = 0 ; i<=size-1; i++)
  {
    tl = TD->TimeLine_at(next_try[i]);

    piece = tl->chessplate->at(index_type[i]);
    piece->pp_score();

    arbre = AM.Generait_arbre(index_type[i],1);
    nb_chemins=arbre->nb_chemin(1);
    found = false;
    
    next_tm=TD->diviser(nb_chemins, next_try[i]);
      for(int n=0; n< nb_chemins ; n++)
      {
        
        tl=TD->TimeLine_at(next_tm[n]);
        piece = tl->chessplate->at(index_type[i]);
        chemin = arbre->chemin_at(n,1);
        if(chemin.size() == 0)
        {
          tl->score_kill();
          continue;
        }
        
        
        if(piece->get_Type() == roi && tl->chessplate->check_king_movement(chemin[0].c))
        {
          tl->score_kill();
          continue;
        }
	
	      if(piece->piece_rampant()
	            && !tl->chessplate->check_piece_rampant_movement(piece->get_Type(),
					    piece->get_last_pos(),
					    chemin[0].c))
        {
          tl->score_kill();
          continue;
        }
        
        piece_to_kill = tl->chessplate->piece_at_coord(chemin[0].c.x, chemin[0].c.y);
	      if(piece_to_kill != NULL)
        {
          if(error.info_piece->action!= Action::eat){
            tl->score_kill();
            continue;
          }
          if(piece_to_kill->get_Color() == piece->get_Color())
          {
            tl->score_kill();
            continue;
          }
	  
          if(piece->get_Type() != pions
            || (piece->get_Type() == pions
            && piece->get_last_pos().x != chemin[0].c.x))
          {
            piece_to_kill->set_Alive(false);
            piece_to_kill->pp_score();
            
          }
          else
          {
            tl->score_kill();
            continue;
          }
          }else{
            if(error.info_piece->action== Action::eat)
            {
              tl->score_kill();
              continue;
            }
          }
          tl->add_instant_on_top(tl->chessplate->at(arbre->index),
            chemin[0].c,
            infP->action,
            infP->info);

          piece->add_movements(arbre->index, chemin[0].c);
      }
      delete[] next_tm;
  }
  delete[] next_try;
  return found;
}


bool Erreur_notation::Erreur_type(Info_Erreur error,int index_tl){
  //cout<<"erreur type"<<endl;
  Info_piece* infP = error.info_piece; 
  Coord coord_piece = infP->coord;
  bool couleur_piece = infP->color;
  Type type_piece = infP->type;
  TimeLine* tl = TD->TimeLine_at(index_tl);
  TimeLine* next_TL;
  //cout<<"tl obtenue"<<endl;
  std::vector<Piece*> piece_type = Get_piece_from_type(type_piece, couleur_piece, tl->chessplate);
  int size = piece_type.size();
  Piece* piece_test;
  Piece* piece;
  Piece* piece_to_kill;
  int* next_try;
  bool pion = false;
  bool found = false;
  next_try = TD->diviser(5, index_tl);

  for(int i = 0 ; i<5; i++)
  {
    next_TL = TD->TimeLine_at(next_try[i]);
    //cout<<"tl obtenue"<<endl;
    if(!infP->info.ambiguous)
    {
      piece = next_TL->chessplate->find_piece(int_to_type(i),
           couleur_piece,
					 coord_piece.x,
           coord_piece.y);
      //cout<<"piece obtenue"<<endl;

    }else{
      for(int n = 0; n<size; n++){
        if(int_to_type(i)==Type::pions){
          pion = true;
        }

        piece_test = piece_type[n];
        piece = next_TL->chessplate->find_piece_ambiguos(int_to_type(i),
           couleur_piece,
					 coord_piece.x,
           coord_piece.y,
           piece_test->get_Coord()->x,
           pion);
      }
    }
    if(piece == NULL){
      next_TL->score_kill();
      continue;
    }else{
     found = true;
    }
    //cout<<"avant add tl"<<endl;
    /*
    piece_to_kill = tl->chessplate->piece_at_coord(coord_piece.x, coord_piece.y);
	  if(piece_to_kill != NULL)
    {
      if(error.info_piece->action!= Action::eat){
        cout<<"eat score kill"<<endl;
        continue;
      }
      if(piece_to_kill->get_Color() == piece->get_Color())
      {
        cout<<"eat score kill"<<endl;
        continue;
      }
	  
      if(piece->get_Type() != pions
          || (piece->get_Type() == pions
          && piece->get_last_pos().x != coord_piece.x))
      {
      piece_to_kill->set_Alive(false);
      piece_to_kill->pp_score();
            
      }
      else
      {
        cout<<"eat score kill"<<endl;
        tl->score_kill();
        continue;        
      }
    }else{
      if(error.info_piece->action== Action::eat)
      {
        cout<<"eat score kill"<<endl;
        tl->score_kill();
        continue;
      }
        }
        */
        next_TL->add_instant_on_top(piece,
			  coord_piece,
        infP->action,
			  infP->info);
      
  }
  delete[] next_try;
  return found;
}


bool Erreur_notation::Verif_eat(Info_piece* infP,int p_index,int tl_index)
{
  TimeLine* tl = TD->TimeLine_at(tl_index);
  Piece* piece;
  std::vector<Piece*> piece_type = Get_piece_from_type(infP->type,
      infP->color,
      tl->chessplate);
  int size = piece_type.size();
  bool pion = false;
  Piece* piece_to_kill=tl->chessplate->piece_at_coord(infP->coord.x, infP->coord.y);
  Piece piece_test;

  if(piece_to_kill != NULL){

    if(piece_to_kill->get_Color()!=infP->color)
    {
      piece_to_kill->set_Alive(false);
      piece_to_kill->pp_score();
      if(!infP->info.ambiguous)
      {
        piece = tl->chessplate->find_piece(infP->type,
            infP->color,
            infP->coord.x,
            infP->coord.y);
        if(piece == NULL)
        {
          tl->score_kill();
          return false;
        }
      }else{
        for(int n = 0; n<size; n++){
          if(infP->type==Type::pions){
            pion = true;
          }

          piece_test = piece_type[n];
          piece = tl->chessplate->find_piece_ambiguos(infP->type,
            infP->color,
            infP->coord.x,
            infP->coord.y,
            piece_test.get_Coord()->x,
            pion);

          if(piece == NULL)
          {
            tl->score_kill();
            return false;
          }
        }
      }
      return true;
    }
  }
  return false;
}



std::vector<Arbre*> Erreur_notation::Gen_Arbre(TimeLine* tl, Coord c, int prof, bool color)
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

std::vector<Arbre*> Erreur_notation::Gen_Arbre(TimeLine* tl, std::vector<int> ps, int prof)
{
  //GEN ARBRE
  std::vector<Arbre*> arbres;
  for(int h = 0; h < ps.size(); h++)
  { 
    ArbreMovement AM(tl->chessplate);
    cout<<"dans gen arbre"<<endl;
    Arbre* a = AM.Generait_arbre(ps[h],prof);
    if(a->arbre_struct.size() > 0)
      arbres.push_back(a);
  }
  return arbres;
}


bool Erreur_notation::check_ambiguiter(TimeLine* tl, Coord coord, Type type, bool couleur, int index)
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





std::vector<Piece*> Erreur_notation::Get_piece_from_type(Type type, bool color, ChessPlate* chessplate){
  std::vector<Piece*> pieces_list;
  int size = chessplate->size();
  Piece* piece;
  for(int i=0; i<=size;i++){
    piece = chessplate->at(i);
    if(piece->get_Color()==color && piece->get_Alive() == true && piece->get_Type()==type){
      pieces_list.push_back(piece);
    }
  }
  return pieces_list;
}

std::vector<int> Erreur_notation::Get_index_from_type(Type type, bool color, ChessPlate* chessplate){
  std::vector<int> index_list;
  int size = chessplate->size();
  Piece* piece;
  for(int i=0; i<=size;i++){
    piece = chessplate->at(i);
    if(piece->get_Color()==color && piece->get_Alive() == true && piece->get_Type()==type){
      index_list.push_back(i);
    }
  }
  return index_list;
}



Type Erreur_notation::int_to_type(int i)
{
  switch(i)
  {
  case 0:
    return Type::pions;
    break;
  case 1:
    return Type::cavaliers;
    break;
  case 2:
    return Type::fous;
    break;
  case 3:
    return Type::roi;
    break;
  case 4:
    return Type::dame;
    break;
  case 5:
    return Type::tours;
    break;
  default:
    return Type::NONE;
    break;
  }
}
