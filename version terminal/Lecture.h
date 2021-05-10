#include <string>

using namespace std;

class Lecture
{
 private:
  //liste de mots
  string* l_movements;

  //taile actuel et maximal de la liste
  int max_lmsize;
  int lm_size;

  //resize de la liste
  void resize_lm();
 public:
  //constructeur et destructeur
  Lecture();
  ~Lecture();

  //lecture d'un fichier avec le path
  void Read(string*);

  //renvoi la liste de mots
  string* return_lm();

  //renvoi la taille
  int get_size();

  //ajout a la fin un mots
  void add_string(string*);

};
