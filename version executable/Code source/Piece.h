#ifndef PIECE
#define PIECE
#include "Coord.h"
#include <string>

using namespace std;

enum Type {roi, dame, fous, cavaliers,
	   tours, pions,NONE};


class Piece
{
 private:  
  Type type;
  bool color;//Blanc:true    Noir:false
  bool alive;//vivant ou mort

  //liste de positions dans le temps
  Coord* pos;

  //liste d'index de temps ou la pièce à bougé.
  int* Temps_movements;

  //taille actuelle et maximale
  int TM_size=0;
  int TM_max_size;

  int score = 0;
  
  void resize();
 public:

  //construteur et destructeur
  Piece();
  Piece(Type,bool,int,int);//type,couleur,x,y
  Piece(Piece*);
  ~Piece();

  //get et set
  void set_Type(char);
  void set_Type(Type);
  void set_Coord_at(Coord, int);
  void set_Color(bool);
  void set_Alive(bool);
  void pp_score();
  
  Type get_Type();
  Coord* get_Coord();
  bool get_Color();
  bool get_Alive();
  int get_score();
  //dame, fous, tours
  bool piece_rampant();
  int get_TM_size();
  int get_TM_max_size();

  //renvoi la liste de temps et des coordonnées
  int* get_TM();
  Coord* get_Coords();

  //renvoie la postion i dans la liste de positions
  Coord get_pos_at(int);
  //renvoi la position en haut de la liste
  Coord get_last_pos();
  //
  int get_index_pos_inf(int);
  //
  void pp_TM_sup(int);
  //
  int get_last_time();
  //renvoi le temps ou la il a
  //bouger dans la position i de la liste
  int get_movements_at(int);

  /* Transforme i le temps dans le TimeLine et
  renvoi j l'index de la coordonnée ou il a bougé
  au temps i */
  int time_to_pos_index(int);

  //Retourne l'index dans la timeline de la prochaine position de la piece
  int time_to_next_pos_time(int);
  int time_to_previous_pos_time(int);
  //Ajoute un temps et une coordonnée
  void add_movements(int, Coord);

  //Elimine le temps et la coordonnée à l'index i
  void remove_movements_at(int);

  //Teste si la piece peut bouger à une coordonnée donnée
  bool Test_movements(Coord*,bool,int);
  bool Test_mov_Tour(Coord*, int);
  bool Test_mov_Fous(Coord*, int);
  bool Test_mov_Cavaliers(Coord*, int);

  //to string de la pièce a un temps donné
  string toString_At(int);

  //tostring simple, true pour afficher sur le terminal
  string toString(bool=false);

};

//Methodes pour transformer un caractère en type , en string ou transformer un type en string
Type char_to_type(char);
string char_to_type_string(char);
string type_to_type_string(Type);

#endif
