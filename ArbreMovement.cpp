#include "ArbreMovement.h"
#include <iostream>

ArbreMovement::ArbreMovement(ChessPlate* c):chessplate(c){}
ArbreMovement::~ArbreMovement(){}
std::vector<Anode> ArbreMovement::Generait_arbre(Piece* p, Coord c, int prof)
{
  Anode node(p->get_last_pos(),-1);
  arbre.push_back(node);
  for(int i = 0; i < prof; i++)
  {
    AddProfondeur(p->get_Type(),p->get_Color());
  }
  clean_nodes(c);
  
  return arbre;
}
void ArbreMovement::clean_nodes(Coord c)
{
  bool find;
  do
  {
    find = false;
    for(int i = arbre.size()-1; i >=  0; i--)
    {
      if(arbre[i].nb_succ == 0 && (arbre[i].c.x() != c.x() || arbre[i].c.y() != c.y()))
      {
	find = true;

	if(arbre[i].prev != -1)
	  arbre[arbre[i].prev].nb_succ--;
	
	arbre.erase(arbre.begin()+i);
	break;
      }
    }
  }
  while(find);
}
void ArbreMovement::AddProfondeur(Type type,bool color)
{
  int size = arbre.size();
  for(int i = 0; i < size; i++)
  {
    if(arbre[i].nb_succ == 0)
    {
      switch(type)
      {
      case roi:
	King(i);
	break;
      case dame:
	Queen(i);
	break;
      case pions:
	Pawn(i,color);
	break;
      case tours:
	Rok(i);
	break;
      case fous:
	Bishop(i);
	break;
      case cavaliers:
	Knigth(i);
	break;
      }
    }
  }
}
void ArbreMovement::Pawn(int i, bool color)
{
  int u = color?1:-1;
  if(arbre[i].c.y()+1*u < 9 && arbre[i].c.y()+1*u > 0)
  {
    Coord c(arbre[i].c.x(), arbre[i].c.y()+1*u);
    Anode node(c,i);
    arbre[i].nb_succ++;
    arbre.push_back(node);

    if(arbre[i].c.x()+1 < 9)
    {
      Coord c1(arbre[i].c.x()+1, arbre[i].c.y()+1*u);
      Anode node1(c1,i);
      arbre[i].nb_succ++;
      arbre.push_back(node1);
    }
    if(arbre[i].c.x()-1 > 0)
    {
      Coord c2(arbre[i].c.x()-1, arbre[i].c.y()+1*u);
      Anode node2(c2,i);
      arbre[i].nb_succ++;
      arbre.push_back(node2);
    }
  }
}
void ArbreMovement::Rok(int i)
{
  for(int j = 1; j <= 8; j++)
  {
    if(arbre[i].c.x() != j)
    {
      Coord c(j, arbre[i].c.y());
      Anode node(c, i);
      arbre[i].nb_succ++;
      arbre.push_back(node);
    }

    if(arbre[i].c.y() != j)
    {
      Coord c(arbre[i].c.x(), j);
      Anode node(c, i);
      arbre[i].nb_succ++;
      arbre.push_back(node);
    }
  }
}
void ArbreMovement::Knigth(int i)
{
  if(arbre[i].c.x()-1 > 0 && arbre[i].c.y()+2 <= 8)
  {
    Coord c(arbre[i].c.x()-1, arbre[i].c.y()+2);
    Anode node(c, i);
    arbre[i].nb_succ++;
    arbre.push_back(node);
  }
  if(arbre[i].c.x()+1 <= 8 && arbre[i].c.y()+2 <= 8)
  {
    Coord c1(arbre[i].c.x()+1, arbre[i].c.y()+2);
    Anode node1(c1, i);
    arbre[i].nb_succ++;
    arbre.push_back(node1);
  }
  if(arbre[i].c.x()-1 > 0 && arbre[i].c.y()-2 > 0)
  {
    Coord c2(arbre[i].c.x()-1, arbre[i].c.y()-2);
    Anode node2(c2, i);
    arbre[i].nb_succ++;
    arbre.push_back(node2);
  }
  if(arbre[i].c.x()+1 <= 8 && arbre[i].c.y()-2 > 0)
  {
    Coord c3(arbre[i].c.x()+1, arbre[i].c.y()-2);
    Anode node3(c3, i);
    arbre[i].nb_succ++;
    arbre.push_back(node3);
  }
  if(arbre[i].c.x()+2 <= 8 && arbre[i].c.y()+1 <= 8)
  {
    Coord c4(arbre[i].c.x()+2, arbre[i].c.y()+1);
    Anode node4(c4, i);
    arbre[i].nb_succ++;
    arbre.push_back(node4);
  }
  if(arbre[i].c.x()+2 <= 8 && arbre[i].c.y()-1 > 0)
  {
    Coord c5(arbre[i].c.x()+2, arbre[i].c.y()-1);
    Anode node5(c5, i);
    arbre[i].nb_succ++;
    arbre.push_back(node5);
  }
  if(arbre[i].c.x()-2 > 0 && arbre[i].c.y()+1 <= 8)
  {
    Coord c6(arbre[i].c.x()-2, arbre[i].c.y()+1);
    Anode node6(c6, i);
    arbre[i].nb_succ++;
    arbre.push_back(node6);
  }
  if(arbre[i].c.x()-2 > 0 && arbre[i].c.y()-1 > 0)
  {
    Coord c7(arbre[i].c.x()-2, arbre[i].c.y()-1);
    Anode node7(c7, i);
    arbre[i].nb_succ++;
    arbre.push_back(node7);
  }
}
void ArbreMovement::Bishop(int i)
{
  Coord c(arbre[i].c.x(), arbre[i].c.y());
  for(int j = 1; j <= 8; j++)
  {
    if(arbre[i].c.x()+j <= 8 && arbre[i].c.y()+j <= 8)
    {
      Coord c(arbre[i].c.x()+j, arbre[i].c.y()+j);
      Anode node(c, i);
      arbre[i].nb_succ++;
      arbre.push_back(node);
    }

    if(arbre[i].c.x()-j > 0 && arbre[i].c.y()+j <= 8)
    {
      Coord c(arbre[i].c.x()-j, arbre[i].c.y()+j);
      Anode node(c, i);
      arbre[i].nb_succ++;
      arbre.push_back(node);
    }

    if(arbre[i].c.x()-j > 0 && arbre[i].c.y()-j > 0)
    {
      Coord c(arbre[i].c.x()-j, arbre[i].c.y()-j);
      Anode node(c, i);
      arbre[i].nb_succ++;
      arbre.push_back(node);
    }

    if(arbre[i].c.x()+j <= 8 && arbre[i].c.y()-j > 0)
    {
      Coord c(arbre[i].c.x()+j, arbre[i].c.y()-j);
      Anode node(c, i);
      arbre[i].nb_succ++;
      arbre.push_back(node);
    }
  }
}
void ArbreMovement::King(int i)
{
  if(arbre[i].c.x()+1 <= 8)
  {
    Coord c(arbre[i].c.x()+1, arbre[i].c.y());
    Anode node(c, i);
    arbre[i].nb_succ++;
    arbre.push_back(node);
  }
  if(arbre[i].c.x()-1 > 0)
  {
    Coord c1(arbre[i].c.x()-1, arbre[i].c.y());
    Anode node1(c1, i);
    arbre[i].nb_succ++;
    arbre.push_back(node1);
  }
  
  Pawn(i,true);
  Pawn(i,false);
}
void ArbreMovement::Queen(int i)
{
  Rok(i);
  Bishop(i);
}

Anode::Anode(Coord c_, int prev_)
{
  c = c_;
  prev = prev_;
  nb_succ=0;
}
