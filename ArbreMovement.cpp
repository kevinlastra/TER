#include "ArbreMovement.h"
#include <iostream>

ArbreMovement::ArbreMovement(ChessPlate* c):chessplate(c){}
ArbreMovement::~ArbreMovement(){}
Arbre* ArbreMovement::Generait_arbre(Piece* p,int i, Coord c, int prof)
{
  piece = p;
  Anode node(p->get_last_pos(),-1, 0);
  arbre = new Arbre(node, i);
  for(int j = 0; j < prof; j++)
  {
    AddProfondeur(p->get_Type(), j+1);
  }
  if(arbre->arbre_struct.size() > 0)
  {
    clean_nodes(c,prof);
  }
  return arbre;
}
Arbre* ArbreMovement::Generait_arbre(int i, int prof)
{
  piece = chessplate->at(i);
  Anode node(piece->get_last_pos(),-1, 0);
  arbre = new Arbre(node, i);
  for(int j = 0; j < prof; j++)
  {
    AddProfondeur(piece->get_Type(), j+1);
  }
  return arbre;
}
void ArbreMovement::clean_nodes(Coord c, int prof)
{
  bool find;
  Anode as;
  Anode asp;
  int cpt = 0;
  do
  {
    find = false;
    for(int i = arbre->arbre_struct.size()-1; i >=  0; i--)
    {
      as = arbre->arbre_struct[i];
      if(as.prof == prof)
      {
	if(as.c.x() != c.x() || as.c.y() != c.y())
	{
	  find = true;
	  if(as.prev != -1)
	  {	  
	    arbre->arbre_struct.erase(arbre->arbre_struct.begin()+i);
	    //effacer fils
	    for(int j = i; j < arbre->arbre_struct.size(); j++)
	      if(arbre->arbre_struct[j].prev >= i)
		arbre->arbre_struct[j].prev--;
	  }
	  else
	  {
	    find = false;
	    arbre->arbre_struct.clear();
	    break;
	  }
	}
      }
      else
      {
	cpt = 0;
	for(int j = i+1; j < arbre->arbre_struct.size(); j++)
	{
	  if(i == arbre->arbre_struct[j].prev)
	  {
	    cpt++;
	  }
	}
	if(cpt > 0)
	  break;
	arbre->arbre_struct.erase(arbre->arbre_struct.begin()+i);
	//effacer fils
	for(int j = i; j < arbre->arbre_struct.size(); j++)
	  if(arbre->arbre_struct[j].prev >= i)
	    arbre->arbre_struct[j].prev--;
	
	find = true;
      }
    }
  }
  while(find);
}
void ArbreMovement::AddProfondeur(Type t,int prof)
{
  int size = arbre->arbre_struct.size();
  for(int i = 0; i < size; i++)
  {
    if(arbre->arbre_struct[i].prof == prof-1)
    {
      switch(t)
      {
      case roi:
	King(i,prof);
	break;
      case dame:
	Queen(i,prof);
	break;
      case pions:
	Pawn(i,prof);
	break;
      case tours:
	Rok(i,prof);
	break;
      case fous:
	Bishop(i,prof);
	break;
      case cavaliers:
	Knigth(i,prof);
	break;
      }
    }
  }
}
void ArbreMovement::Pawn(int i, int prof)
{
  int u = piece->get_Color()?1:-1;
  
  if(arbre->arbre_struct[i].c.y()+1*u < 9
     && arbre->arbre_struct[i].c.y()+1*u > 0)
  {
    Coord c(arbre->arbre_struct[i].c.x(),
	    arbre->arbre_struct[i].c.y()+1*u);
    
    Anode node(c,i,prof);
    
    arbre->arbre_struct.push_back(node);

    if(arbre->arbre_struct[i].c.x()+1 < 9)
    {
      Coord c1(arbre->arbre_struct[i].c.x()+1,
	       arbre->arbre_struct[i].c.y()+1*u);
      Anode node1(c1,i,prof);
      arbre->arbre_struct.push_back(node1);
    }
    if(arbre->arbre_struct[i].c.x()-1 > 0)
    {
      Coord c2(arbre->arbre_struct[i].c.x()-1,
	       arbre->arbre_struct[i].c.y()+1*u);
      Anode node2(c2,i,prof);
      arbre->arbre_struct.push_back(node2);
    }
  }
  if(arbre->arbre_struct[i].c.y()+2*u < 9
     && arbre->arbre_struct[i].c.y()+2*u > 0
     && piece->get_TM_size() == 1)
  {
    Coord c3(arbre->arbre_struct[i].c.x(),
	     arbre->arbre_struct[i].c.y()+2*u);
    Anode node3(c3,i,prof);
    arbre->arbre_struct.push_back(node3);
  }
}
void ArbreMovement::Rok(int i, int prof)
{
  for(int j = 1; j <= 8; j++)
  {
    if(arbre->arbre_struct[i].c.x() != j)
    {
      Coord c(j, arbre->arbre_struct[i].c.y());
      Anode node(c, i,prof);
      arbre->arbre_struct.push_back(node);
    }

    if(arbre->arbre_struct[i].c.y() != j)
    {
      Coord c(arbre->arbre_struct[i].c.x(), j);
      Anode node(c, i,prof);
      arbre->arbre_struct.push_back(node);
    }
  }
}
void ArbreMovement::Knigth(int i, int prof)
{
  if(arbre->arbre_struct[i].c.x()-1 > 0 && arbre->arbre_struct[i].c.y()+2 <= 8)
  {
    Coord c(arbre->arbre_struct[i].c.x()-1, arbre->arbre_struct[i].c.y()+2);
    Anode node(c, i,prof);
    arbre->arbre_struct.push_back(node);
  }
  if(arbre->arbre_struct[i].c.x()+1 <= 8 && arbre->arbre_struct[i].c.y()+2 <= 8)
  {
    Coord c1(arbre->arbre_struct[i].c.x()+1, arbre->arbre_struct[i].c.y()+2);
    Anode node1(c1, i,prof);
    arbre->arbre_struct.push_back(node1);
  }
  if(arbre->arbre_struct[i].c.x()-1 > 0 && arbre->arbre_struct[i].c.y()-2 > 0)
  {
    Coord c2(arbre->arbre_struct[i].c.x()-1, arbre->arbre_struct[i].c.y()-2);
    Anode node2(c2, i,prof);
    arbre->arbre_struct.push_back(node2);
  }
  if(arbre->arbre_struct[i].c.x()+1 <= 8 && arbre->arbre_struct[i].c.y()-2 > 0)
  {
    Coord c3(arbre->arbre_struct[i].c.x()+1, arbre->arbre_struct[i].c.y()-2);
    Anode node3(c3, i,prof);
    arbre->arbre_struct.push_back(node3);
  }
  if(arbre->arbre_struct[i].c.x()+2 <= 8 && arbre->arbre_struct[i].c.y()+1 <= 8)
  {
    Coord c4(arbre->arbre_struct[i].c.x()+2, arbre->arbre_struct[i].c.y()+1);
    Anode node4(c4, i,prof);
    arbre->arbre_struct.push_back(node4);
  }
  if(arbre->arbre_struct[i].c.x()+2 <= 8 && arbre->arbre_struct[i].c.y()-1 > 0)
  {
    Coord c5(arbre->arbre_struct[i].c.x()+2, arbre->arbre_struct[i].c.y()-1);
    Anode node5(c5, i,prof);
    arbre->arbre_struct.push_back(node5);
  }
  if(arbre->arbre_struct[i].c.x()-2 > 0 && arbre->arbre_struct[i].c.y()+1 <= 8)
  {
    Coord c6(arbre->arbre_struct[i].c.x()-2, arbre->arbre_struct[i].c.y()+1);
    Anode node6(c6, i,prof);
    arbre->arbre_struct.push_back(node6);
  }
  if(arbre->arbre_struct[i].c.x()-2 > 0 && arbre->arbre_struct[i].c.y()-1 > 0)
  {
    Coord c7(arbre->arbre_struct[i].c.x()-2, arbre->arbre_struct[i].c.y()-1);
    Anode node7(c7, i,prof);
    arbre->arbre_struct.push_back(node7);
  }
}
void ArbreMovement::Bishop(int i, int prof)
{
  Coord c(arbre->arbre_struct[i].c.x(), arbre->arbre_struct[i].c.y());
  for(int j = 1; j <= 8; j++)
  {
    if(arbre->arbre_struct[i].c.x()+j <= 8 && arbre->arbre_struct[i].c.y()+j <= 8)
    {
      Coord c(arbre->arbre_struct[i].c.x()+j, arbre->arbre_struct[i].c.y()+j);
      Anode node(c, i,prof);
      arbre->arbre_struct.push_back(node);
    }

    if(arbre->arbre_struct[i].c.x()-j > 0 && arbre->arbre_struct[i].c.y()+j <= 8)
    {
      Coord c(arbre->arbre_struct[i].c.x()-j, arbre->arbre_struct[i].c.y()+j);
      Anode node(c, i,prof);
      arbre->arbre_struct.push_back(node);
    }

    if(arbre->arbre_struct[i].c.x()-j > 0 && arbre->arbre_struct[i].c.y()-j > 0)
    {
      Coord c(arbre->arbre_struct[i].c.x()-j, arbre->arbre_struct[i].c.y()-j);
      Anode node(c, i,prof);
      arbre->arbre_struct.push_back(node);
    }

    if(arbre->arbre_struct[i].c.x()+j <= 8 && arbre->arbre_struct[i].c.y()-j > 0)
    {
      Coord c(arbre->arbre_struct[i].c.x()+j, arbre->arbre_struct[i].c.y()-j);
      Anode node(c, i,prof);
      arbre->arbre_struct.push_back(node);
    }
  }
}
void ArbreMovement::King(int i, int prof)
{
  if(arbre->arbre_struct[i].c.x()+1 <= 8)
  {
    Coord c(arbre->arbre_struct[i].c.x()+1,
	    arbre->arbre_struct[i].c.y());
    Anode node(c, i,prof);
    arbre->arbre_struct.push_back(node);
  }
  if(arbre->arbre_struct[i].c.x()-1 > 0)
  {
    Coord c1(arbre->arbre_struct[i].c.x()-1,
	     arbre->arbre_struct[i].c.y());
    Anode node1(c1, i,prof);
    arbre->arbre_struct.push_back(node1);
  }
  
  if(arbre->arbre_struct[i].c.y()+1 < 9)
  {
    Coord c2(arbre->arbre_struct[i].c.x(),
	    arbre->arbre_struct[i].c.y()+1);
    
    Anode node2(c2,i,prof);
    arbre->arbre_struct.push_back(node2);

    if(arbre->arbre_struct[i].c.x()+1 < 9)
    {
      Coord c3(arbre->arbre_struct[i].c.x()+1,
	       arbre->arbre_struct[i].c.y()+1);
      Anode node3(c3,i,prof);
      arbre->arbre_struct.push_back(node3);
    }
    if(arbre->arbre_struct[i].c.x()-1 > 0)
    {
      Coord c4(arbre->arbre_struct[i].c.x()-1,
	       arbre->arbre_struct[i].c.y()+1);
      Anode node4(c4,i,prof);
      arbre->arbre_struct.push_back(node4);
    }
  }
  if(arbre->arbre_struct[i].c.y()-1 > 0)
  {
    Coord c5(arbre->arbre_struct[i].c.x(),
	     arbre->arbre_struct[i].c.y()-1);
    
    Anode node5(c5,i,prof);
    arbre->arbre_struct.push_back(node5);

    if(arbre->arbre_struct[i].c.x()+1 < 9)
    {
      Coord c6(arbre->arbre_struct[i].c.x()+1,
	       arbre->arbre_struct[i].c.y()-1);
      Anode node6(c6,i,prof);
      arbre->arbre_struct.push_back(node6);
    }
    if(arbre->arbre_struct[i].c.x()-1 > 0)
    {
      Coord c7(arbre->arbre_struct[i].c.x()-1,
	       arbre->arbre_struct[i].c.y()-1);
      Anode node7(c7,i,prof);
      arbre->arbre_struct.push_back(node7);
    }
  }
}
void ArbreMovement::Queen(int i, int prof)
{
  Rok(i,prof);
  Bishop(i,prof);
}

Anode::Anode(Coord c_, int prev_, int prof_)
{
  c = c_;
  prev = prev_;
  prof = prof_;
}
Anode::Anode(){}
Arbre::Arbre(Anode a, int i)
{
  arbre_struct.push_back(a);
  index = i;
}

int Arbre::nb_chemin(int prof)
{
  int cpt = 0;
  for(int i = 0; i < arbre_struct.size(); i++)
  {
    if(arbre_struct[i].prof == prof)
    {
      cpt++;
    }
  }
  
  return cpt;
}
std::vector<Anode> Arbre::chemin_at(int i, int prof)
{
  int index;
  int cpt = 0;
  for(int j = 0; j < arbre_struct.size(); j++)
  {
    if(arbre_struct[j].prof == prof)
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
