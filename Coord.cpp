#include "Coord.h"
#include <iostream>

using namespace std;

Coord::Coord():x_axis(0),y_axis(0){}
Coord::Coord(int x_, int y_):x_axis(x_),y_axis(y_){}

int Coord::x(){return x_axis;}
int Coord::y(){return y_axis;}

void Coord::update(int x_, int y_)
{
  x_axis = x_;
  y_axis = y_;
}
