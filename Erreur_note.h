#ifndef ERREUR_NOTE
#define ERREUR_NOTE

#include "Info.h"
#include "TimeDivision.h"
#include "Piece.h"
#include "ArbreMovement.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

class Erreur_note
{
 private:
  TimeDivision* TD;
    
 public:
  Erreur_note(TimeDivision*);
  ~Erreur_note();


  void Traiter_Erreur(Info_Erreur);

  //traitement pour les piece du type Pion
  //Actuellement sont traiter 2 cas:
  //1 - manger en passant
  //detection d'un erreur de notation apres un oublie volontaire ("_")
  void Pion(Info_Erreur,int,int*);

  void Piece_rampant(Info_Erreur,int,int*);
  //traitement de "l'erreur" manger en passant
  Piece* Manger_en_passant(Info_Erreur);

  //3 cas possible:
  //A) Je n'exist pas.
  //B) La piece que je veut tuer n'existe pas.
  //C) Il existe une piece dans mon chemin qui ne devrait pas exister
  //Info Erreur, index timeline, nb_none_piece, none_piece_indexs
  void Oublie_conscient_cas_A(Info_Erreur,int,int,int*);
  void Oublie_conscient_cas_B(Info_Erreur,int,int,int*);
  void Oublie_conscient_cas_C(Info_Erreur,int,int,int*);
  //time line index, color
  void Oublie_conscient_cas_castling(Info_Erreur,bool,int,int,int*);
  void Error_extension(TimeLine*,Info_Erreur);
  //
  void Oublie_conscient_cas_promotion(Info_Erreur,int,int,int*);
  //
  
  //tl,coord, prof, color
  std::vector<Arbre*> Gen_Arbre(TimeLine*,Coord,int,bool);
  std::vector<Arbre*> Gen_Arbre(TimeLine*,std::vector<int>,int);

  std::vector<int> get_piece_in_path(ChessPlate*,Coord,Coord,Type);
  //coordoner, type, couleur, temps dans tl
  bool check_ambiguiter(TimeLine*, Coord, Type, bool,int);
};

#endif
