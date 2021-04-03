#include "ArbreMovement.h"
#include <iostream>

ArbreMovement::ArbreMovement(ChessPlate* c):chessplate(c){}
ArbreMovement::~ArbreMovement(){}
Arbre* ArbreMovement::Generait_arbre(Piece* p,int i, Coord c, int prof)
{
  piece = p;
  Anode node(p->get_last_pos(),-1);
  arbre = new Arbre(node, i);
  for(int i = 0; i < prof; i++)
  {
    AddProfondeur(p->get_Type());
  }
  if(arbre->arbre_struct.size() > 0)
  {
    clean_nodes(c);
  }
  return arbre;
}
void ArbreMovement::clean_nodes(Coord c)
{
  bool find;
  int prev;
  do
  {
    find = false;
    for(int i = arbre->arbre_struct.size()-1; i >=  0; i--)
    {
      if(arbre->arbre_struct[i].child_indexs.size() == 0 &&
	 (arbre->arbre_struct[i].c.x() != c.x() || arbre->arbre_struct[i].c.y() != c.y()))
      {
	find = true;
	prev = arbre->arbre_struct[i].prev;
	if(prev != -1)
	  for(int j = 0; j < arbre->arbre_struct[prev].child_indexs.size(); j++)
	  {
	    if(arbre->arbre_struct[prev].child_indexs[j] == i)
	    {
	      arbre->arbre_struct[prev].child_indexs.erase(arbre->arbre_struct[prev].child_indexs.begin()+j);
	    }
	  }
	arbre->arbre_struct.erase(arbre->arbre_struct.begin()+i);
	for(int j = i; j < arbre->arbre_struct.size(); j++)
	{
	  if(arbre->arbre_struct[j].prev >= i)
	  {
	    arbre->arbre_struct[j].prev--;
	  }
	}
	break;
      }
    }
  }
  while(find);
}
void ArbreMovement::AddProfondeur(Type t)
{
  int size = arbre->arbre_struct.size();
  for(int i = 0; i < size; i++)
  {
    if(arbre->arbre_struct[i].child_indexs.size() == 0)
    {
      switch(t)
      {
      case roi:
	King(i);
	break;
      case dame:
	Queen(i);
	break;
      case pions:
	Pawn(i);
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
void ArbreMovement::Pawn(int i)
{
  int u = piece->get_Color()?1:-1;
  if(arbre->arbre_struct[i].c.y()+1*u < 9 && arbre->arbre_struct[i].c.y()+1*u > 0)
  {
    Coord c(arbre->arbre_struct[i].c.x(),
	    arbre->arbre_struct[i].c.y()+1*u);
    
    Anode node(c,i);
    arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
    
    arbre->arbre_struct.push_back(node);

    if(arbre->arbre_struct[i].c.x()+1 < 9)
    {
      Coord c1(arbre->arbre_struct[i].c.x()+1, arbre->arbre_struct[i].c.y()+1*u);
      Anode node1(c1,i);
      arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
      arbre->arbre_struct.push_back(node1);
    }
    if(arbre->arbre_struct[i].c.x()-1 > 0)
    {
      Coord c2(arbre->arbre_struct[i].c.x()-1, arbre->arbre_struct[i].c.y()+1*u);
      Anode node2(c2,i);
      arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
      arbre->arbre_struct.push_back(node2);
    }
  }
  if(arbre->arbre_struct[i].c.y()+2*u < 9 && arbre->arbre_struct[i].c.y()+2*u > 0 && piece->get_TM_size() == 1)
  {
    Coord c3(arbre->arbre_struct[i].c.x(), arbre->arbre_struct[i].c.y()+2*u);
    Anode node3(c3,i);
    arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
    arbre->arbre_struct.push_back(node3);
  }
}
void ArbreMovement::Rok(int i)
{
  for(int j = 1; j <= 8; j++)
  {
    if(arbre->arbre_struct[i].c.x() != j)
    {
      Coord c(j, arbre->arbre_struct[i].c.y());
      Anode node(c, i);
      arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
      arbre->arbre_struct.push_back(node);
    }

    if(arbre->arbre_struct[i].c.y() != j)
    {
      Coord c(arbre->arbre_struct[i].c.x(), j);
      Anode node(c, i);
      arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
      arbre->arbre_struct.push_back(node);
    }
  }
}
void ArbreMovement::Knigth(int i)
{
  if(arbre->arbre_struct[i].c.x()-1 > 0 && arbre->arbre_struct[i].c.y()+2 <= 8)
  {
    Coord c(arbre->arbre_struct[i].c.x()-1, arbre->arbre_struct[i].c.y()+2);
    Anode node(c, i);
    arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
    arbre->arbre_struct.push_back(node);
  }
  if(arbre->arbre_struct[i].c.x()+1 <= 8 && arbre->arbre_struct[i].c.y()+2 <= 8)
  {
    Coord c1(arbre->arbre_struct[i].c.x()+1, arbre->arbre_struct[i].c.y()+2);
    Anode node1(c1, i);
    arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
    arbre->arbre_struct.push_back(node1);
  }
  if(arbre->arbre_struct[i].c.x()-1 > 0 && arbre->arbre_struct[i].c.y()-2 > 0)
  {
    Coord c2(arbre->arbre_struct[i].c.x()-1, arbre->arbre_struct[i].c.y()-2);
    Anode node2(c2, i);
    arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
    arbre->arbre_struct.push_back(node2);
  }
  if(arbre->arbre_struct[i].c.x()+1 <= 8 && arbre->arbre_struct[i].c.y()-2 > 0)
  {
    Coord c3(arbre->arbre_struct[i].c.x()+1, arbre->arbre_struct[i].c.y()-2);
    Anode node3(c3, i);
    arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
    arbre->arbre_struct.push_back(node3);
  }
  if(arbre->arbre_struct[i].c.x()+2 <= 8 && arbre->arbre_struct[i].c.y()+1 <= 8)
  {
    Coord c4(arbre->arbre_struct[i].c.x()+2, arbre->arbre_struct[i].c.y()+1);
    Anode node4(c4, i);
    arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
    arbre->arbre_struct.push_back(node4);
  }
  if(arbre->arbre_struct[i].c.x()+2 <= 8 && arbre->arbre_struct[i].c.y()-1 > 0)
  {
    Coord c5(arbre->arbre_struct[i].c.x()+2, arbre->arbre_struct[i].c.y()-1);
    Anode node5(c5, i);
    arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
    arbre->arbre_struct.push_back(node5);
  }
  if(arbre->arbre_struct[i].c.x()-2 > 0 && arbre->arbre_struct[i].c.y()+1 <= 8)
  {
    Coord c6(arbre->arbre_struct[i].c.x()-2, arbre->arbre_struct[i].c.y()+1);
    Anode node6(c6, i);
    arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
    arbre->arbre_struct.push_back(node6);
  }
  if(arbre->arbre_struct[i].c.x()-2 > 0 && arbre->arbre_struct[i].c.y()-1 > 0)
  {
    Coord c7(arbre->arbre_struct[i].c.x()-2, arbre->arbre_struct[i].c.y()-1);
    Anode node7(c7, i);
    arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
    arbre->arbre_struct.push_back(node7);
  }
}
void ArbreMovement::Bishop(int i)
{
  Coord c(arbre->arbre_struct[i].c.x(), arbre->arbre_struct[i].c.y());
  for(int j = 1; j <= 8; j++)
  {
    if(arbre->arbre_struct[i].c.x()+j <= 8 && arbre->arbre_struct[i].c.y()+j <= 8)
    {
      Coord c(arbre->arbre_struct[i].c.x()+j, arbre->arbre_struct[i].c.y()+j);
      Anode node(c, i);
      arbre->arbre_struct[i].child_indexs
	.push_back(arbre->arbre_struct.size());
      arbre->arbre_struct.push_back(node);
    }

    if(arbre->arbre_struct[i].c.x()-j > 0 && arbre->arbre_struct[i].c.y()+j <= 8)
    {
      Coord c(arbre->arbre_struct[i].c.x()-j, arbre->arbre_struct[i].c.y()+j);
      Anode node(c, i);
      arbre->arbre_struct[i].child_indexs
	.push_back(arbre->arbre_struct.size());
      arbre->arbre_struct.push_back(node);
    }

    if(arbre->arbre_struct[i].c.x()-j > 0 && arbre->arbre_struct[i].c.y()-j > 0)
    {
      Coord c(arbre->arbre_struct[i].c.x()-j, arbre->arbre_struct[i].c.y()-j);
      Anode node(c, i);
      arbre->arbre_struct[i].child_indexs
	.push_back(arbre->arbre_struct.size());
      arbre->arbre_struct.push_back(node);
    }

    if(arbre->arbre_struct[i].c.x()+j <= 8 && arbre->arbre_struct[i].c.y()-j > 0)
    {
      Coord c(arbre->arbre_struct[i].c.x()+j, arbre->arbre_struct[i].c.y()-j);
      Anode node(c, i);
      arbre->arbre_struct[i].child_indexs
	.push_back(arbre->arbre_struct.size());
      arbre->arbre_struct.push_back(node);
    }
  }
}
void ArbreMovement::King(int i)
{
  if(arbre->arbre_struct[i].c.x()+1 <= 8)
  {
    Coord c(arbre->arbre_struct[i].c.x()+1,
	    arbre->arbre_struct[i].c.y());
    Anode node(c, i);
    arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
    arbre->arbre_struct.push_back(node);
  }
  if(arbre->arbre_struct[i].c.x()-1 > 0)
  {
    Coord c1(arbre->arbre_struct[i].c.x()-1,
	     arbre->arbre_struct[i].c.y());
    Anode node1(c1, i);
    arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
    arbre->arbre_struct.push_back(node1);
  }
  
  if(arbre->arbre_struct[i].c.y()+1 < 9)
  {
    Coord c2(arbre->arbre_struct[i].c.x(),
	    arbre->arbre_struct[i].c.y()+1);
    
    Anode node2(c2,i);
    arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
    arbre->arbre_struct.push_back(node2);

    if(arbre->arbre_struct[i].c.x()+1 < 9)
    {
      Coord c3(arbre->arbre_struct[i].c.x()+1,
	       arbre->arbre_struct[i].c.y()+1);
      Anode node3(c3,i);
      arbre->arbre_struct[i].child_indexs
	.push_back(arbre->arbre_struct.size());
      arbre->arbre_struct.push_back(node3);
    }
    if(arbre->arbre_struct[i].c.x()-1 > 0)
    {
      Coord c4(arbre->arbre_struct[i].c.x()-1,
	       arbre->arbre_struct[i].c.y()+1);
      Anode node4(c4,i);
      arbre->arbre_struct[i].child_indexs
	.push_back(arbre->arbre_struct.size());
      arbre->arbre_struct.push_back(node4);
    }
  }
  if(arbre->arbre_struct[i].c.y()-1 > 0)
  {
    Coord c5(arbre->arbre_struct[i].c.x(),
	     arbre->arbre_struct[i].c.y()-1);
    
    Anode node5(c5,i);
    arbre->arbre_struct[i].child_indexs
      .push_back(arbre->arbre_struct.size());
    arbre->arbre_struct.push_back(node5);

    if(arbre->arbre_struct[i].c.x()+1 < 9)
    {
      Coord c6(arbre->arbre_struct[i].c.x()+1,
	       arbre->arbre_struct[i].c.y()-1);
      Anode node6(c6,i);
      arbre->arbre_struct[i].child_indexs
	.push_back(arbre->arbre_struct.size());
      arbre->arbre_struct.push_back(node6);
    }
    if(arbre->arbre_struct[i].c.x()-1 > 0)
    {
      Coord c7(arbre->arbre_struct[i].c.x()-1,
	       arbre->arbre_struct[i].c.y()-1);
      Anode node7(c7,i);
      arbre->arbre_struct[i].child_indexs
	.push_back(arbre->arbre_struct.size());
      arbre->arbre_struct.push_back(node7);
    }
  }
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
}
Arbre::Arbre(Anode a, int i)
{
  arbre_struct.push_back(a);
  index = i;
}

int Arbre::nb_chemin()
{
  int cpt = 0;
  for(int i = 0; i < arbre_struct.size(); i++)
  {
    if(arbre_struct[i].child_indexs.size() == 0)
    {
      cpt++;
    }
  }
  
  return cpt;
}
std::vector<Anode> Arbre::chemin_at(int i)
{
  int index;
  int cpt = 0;
  for(int j = 0; j < arbre_struct.size(); j++)
  {
    if(arbre_struct[j].child_indexs.size() == 0)
    {
      if(cpt == i)
      {
	index = j;
	break;
      }      
      cpt++;
    }
  }

  std::vector<Anode> list;
  Anode node = arbre_struct[index];
  while(node.prev != -1)
  {
    list.insert(list.begin(),node);
    node = arbre_struct[node.prev];
  }
  
  return list;
}
