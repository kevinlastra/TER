#include <string>

using namespace std;

class Lecture
{
 private:
  string* l_movements;
  int max_lmsize;
  int lm_size;
 public:
  Lecture();
  ~Lecture();

  void Read(string*);
  string* return_lm();
  int get_size();
  void add_string(string*);

  void resize_lm();
};
