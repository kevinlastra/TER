#ifndef COORD
#define COORD

class Coord
{
 private:
  int x_axis;
  int y_axis;
 public:
  Coord();
  Coord(int, int);

  //renvoi x et y
  int x();
  int y();

  //actualize x et y
  void update(int,int);
};
//destructeur!!

#endif
