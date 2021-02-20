#include <string>
#include "Piece.h"
#include "TimeLine.h"

using namespace std;

class Ecriture
{
 private:

  
  //liste de mots
  string coupBlanc;
  string coupNoir;

  //Pieces jouées lors du tour
  Instance* pBlanche;
  Instance* pNoire;

  //leurs noms
  string nomBlanc;
  string nomNoir;

  //prend un entier (de 1 a 8) et lui fait correspondre une lettre ( de a jusqu'a h)
  char intToStr(int);
  string get_str_castling(int);

 public:

  Ecriture();
  ~Ecriture();
  

  //ecriture dans un fichier a partir d'une timeline vers un path
  void Write(TimeLine*,string*);
};
