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

  //liste de position dans le temps
  Coord* pos;

  //liste de temps ou il a bouger (TM)
  int* Temps_movements;

  //taille actuel et maximal
  int TM_size=0;
  int TM_max_size;

  void resize();
 public:

  //construteur et destructeur
  Piece();
  Piece(Type,bool,int,int);//type,couleur,x,y
  Piece(Piece*);
  ~Piece();

  //get et set
  void set_Type(char);
  void set_Coord_at(Coord, int);
  void set_Color(bool);
  void set_Alive(bool);
  
  Type get_Type();
  Coord* get_Coord();
  bool get_Color();
  bool get_Alive();
  
  int get_TM_size();
  int get_TM_max_size();

  //renvoi la liste de temps et des coordones
  int* get_TM();
  Coord* get_Coords();

  //renvoi la postion i dans la liste de position
  Coord get_pos_at(int);
  //renvoi position en haut de la liste
  Coord get_last_pos();

  int get_last_time();
  //renvoi le temps ou la il a
  //bouger dans la position i de la liste
  int get_movements_at(int);

  //transforme i le temps dans le TimeLine et
  //renvoi j l'index de la coordoner ou il a bouger
  //au temps i
  int time_to_pos_index(int);

  //retourne l'index dans timeline de la prochaine position de la piece
  int time_to_next_pos_time(int);
  int time_to_previous_pos_time(int);
  //ajoute un temps et une coordoner
  void add_movements(int, Coord);

  //elimine le temps et la coordoner a l'index i
  void remove_movements_at(int);

  //test si la piece peut bouger a une telle coordoner
  bool Test_movements(Coord*,bool,int);
  bool Test_mov_Tour(Coord*, int);
  bool Test_mov_Fous(Coord*, int);
  bool Test_mov_Cavaliers(Coord*, int);

  //to string dans le temps
  string toString_At(int);

  //tostring simple, true pour printer
  //tous les coordoner ou il a ete
  string toString(bool=false);
};

//print pour debogage 
Type char_to_type(char);
string char_to_type_string(char);
string type_to_type_string(Type);
#endif
