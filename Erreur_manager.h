#ifndef ERREUR_MANAGER
#define ERREUR_MANAGER

#include "TimeDivision.h"
#include "Piece.h"
#include "ArbreMovement.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

struct Info_piece
{
  Type type;
  Coord coord;
  Action action;
  bool color;
  Info info;

  //cas ou type = pion
  int x;//example dxe3  var x = d
};
//struct en construction, tous les info ne sont pas utiliser
struct Info_Erreur
{
  //l'index de la piece dans le tl
  int piece_index;     

  //en cas ou la piece n'est pas trouver,
  //donc en collect tous les infos possible
  Info_piece* info_piece;
  //
  
  int tl_index;        //index du tl
  int tl_instance_index;     //index de l'instance dans le tl
};

class Erreur_manager
{
 private:

  TimeDivision* TD;
 public:
  //constructeur
  Erreur_manager(TimeDivision*);

  //debut du traitment des erreur
  void Traiter_Erreur(Info_Erreur);

  //traitement pour les piece du type Pion
  //Actuellement sont traiter 2 cas:
  //1 - manger en passant
  //detection d'un erreur de notation apres un oublie volontaire ("_")
  void Pion(Info_Erreur);

  void Piece_rampant(Info_Erreur);
  //traitement de "l'erreur" manger en passant
  Piece* Manger_en_passant(Info_Erreur);

  //3 cas possible:
  //A) Je n'exist pas.
  //B) La piece que je veut tuer n'existe pas.
  //C) Il existe une piece dans mon chemin qui ne devrait pas exister
  //Info Erreur, index timeline, profondeur dans l'arbre
  void Oublie_conscient_cas_A(Info_Erreur,int);
  void Oublie_conscient_cas_B(Info_Erreur,int);
  void Oublie_conscient_cas_C(Info_Erreur,int);
  //time line index, color
  void Oublie_conscient_cas_castling(int);
  //tl,coord, prof, color
  std::vector<Arbre*> Gen_Arbre(TimeLine*,Coord,int);
  std::vector<Arbre*> Gen_Arbre(TimeLine*,std::vector<int>,int);
  std::vector<int> get_piece_in_path(ChessPlate*,Coord,Coord,Type);
  //coordoner, type, couleur, temps dans tl
  bool check_ambiguiter(TimeLine*, Coord, Type, bool,int);
  //
  void fill_none_piece();
  //
  bool Verif_eat(Info_Erreur);
  //bool Verif_echec(Info_Erreur);
};

#endif
