#include <string>
#include "Piece.h"
#include "TimeLine.h"
#include "TimeDivision.h"

using namespace std;

class Ecriture
{
 private:

  
  //Liste de mots
  string coupBlanc;
  string coupNoir;

  //Pieces jouées lors du tour
  TimeLine* timeline;
  Instant* pBlanche;
  Instant* pNoire;
  Instant* pLast;

  //Leurs noms
  string nomBlanc;
  string nomNoir;

  //Prend un entier (de 1 a 8) et lui fait correspondre une lettre ( de a jusqu'a h)
  char intToStr(int);
  string get_str_castling(int);

 public:

  Ecriture();
  ~Ecriture();
  

  //Ecriture dans un fichier à partir d'une timeline vers un fichier
  std::vector<string> Write(TimeDivision*,string*);
};
