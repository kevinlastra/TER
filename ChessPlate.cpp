#include "ChessPlate.h"
#include <iostream>

ChessPlate::ChessPlate()
{
  pieces = new Piece*[48];
  

  //pions blanc
  pieces[0] = new Piece(pions,true,1,2);
  pieces[1] = new Piece(pions,true,2,2);
  pieces[2] = new Piece(pions,true,3,2);
  pieces[3] = new Piece(pions,true,4,2);
  pieces[4] = new Piece(pions,true,5,2);
  pieces[5] = new Piece(pions,true,6,2);
  pieces[6] = new Piece(pions,true,7,2);
  pieces[7] = new Piece(pions,true,8,2);

  //pions noir
  pieces[8] = new Piece(pions,false,1,7);
  pieces[9] = new Piece(pions,false,2,7);
  pieces[10] = new Piece(pions,false,3,7);
  pieces[11] = new Piece(pions,false,4,7);
  pieces[12] = new Piece(pions,false,5,7);
  pieces[13] = new Piece(pions,false,6,7);
  pieces[14] = new Piece(pions,false,7,7);
  pieces[15] = new Piece(pions,false,8,7);

  //tours blanc
  pieces[16] = new Piece(tours,true,1,1);
  pieces[17] = new Piece(tours,true,8,1);

  //tours noir
  pieces[18] = new Piece(tours,false,1,8);
  pieces[19] = new Piece(tours,false,8,8);

  //cavaliers blanc
  pieces[20] = new Piece(cavaliers,true,2,1);
  pieces[21] = new Piece(cavaliers,true,7,1);

  //cavaliers noir
  pieces[22] = new Piece(cavaliers,false,2,8);
  pieces[23] = new Piece(cavaliers,false,7,8);

  //fous blanc
  pieces[24] = new Piece(fous,true,3,1);
  pieces[25] = new Piece(fous,true,6,1);

  //fous noir
  pieces[26] = new Piece(fous,false,3,8);
  pieces[27] = new Piece(fous,false,6,8);

  //roi blanc et noir
  pieces[28] = new Piece(roi,true,5,1);
  pieces[29] = new Piece(roi,false,5,8);

  //dame blanc et noir
  pieces[30] = new Piece(dame,true,4,1);
  pieces[31] = new Piece(dame,false,4,8);

  //promotion blanc
  pieces[32] = new Piece();
  pieces[33] = new Piece();
  pieces[34] = new Piece();
  pieces[35] = new Piece();
  pieces[36] = new Piece();
  pieces[37] = new Piece();
  pieces[38] = new Piece();
  pieces[39] = new Piece();

  //promotion noir
  pieces[40] = new Piece();
  pieces[41] = new Piece();
  pieces[42] = new Piece();
  pieces[43] = new Piece();
  pieces[44] = new Piece();
  pieces[45] = new Piece();
  pieces[46] = new Piece();
  pieces[47] = new Piece();
}
ChessPlate::ChessPlate(ChessPlate* CP)
{
  pieces = new Piece*[48];
  
  p_size = CP->p_size;
  for(int i = 0; i < p_size; i++)
  {
    pieces[i] = new Piece(CP->pieces[i]);
  }
  for(int i = p_size; i < 48; i++)
  {
    pieces[i] = new Piece();
  }
}
ChessPlate::~ChessPlate()
{
  for(int i = 0; i < p_size; i++)
    delete pieces[i];
  delete pieces; 
}
Piece* ChessPlate::at(int i)
{
  return pieces[i];
}
int ChessPlate::size(){return p_size;}
void ChessPlate::promotion(){p_size++;}
void ChessPlate::return_Castling(bool color,Type t, int &a, int &b)
{
  if(color)
    a = 28;
  else
    a = 29;
  
  if(t == roi)
  {
    if(color)
      b = 17;
    else
      b = 19;
  }
  else if(t == dame)
  {
    if(color)
      b = 16;
    else
      b = 18; 
  }
}

Piece* ChessPlate::find_piece(Type t, bool color, int x, int y)
{
  Coord c(x,y);
  for(int i = 0; i < p_size; i++)
  {
    if(pieces[i]->get_Type() == t &&
     pieces[i]->get_Color() == color &&
     pieces[i]->Test_movements(&c,false, pieces[i]->get_TM_size()-1) &&
     pieces[i]->get_Alive())
    {
      if(t == fous)
      {
	if(check_Bishop_path(pieces[i]->get_last_pos(),c))
	{
	  return pieces[i];
	}
	else
	  continue;
      }
      else if(t == tours)
      {
	if(check_Rok_path(pieces[i]->get_last_pos(),c))
	  return pieces[i];
	else
	  continue;
      }
      else
      {
	return pieces[i];
      }
   }
 }
 return NULL;
}
Piece* ChessPlate::find_piece_ambiguos(Type t, bool color, int x, int y, int xfrom, bool pawn)
{
  Coord c(x,y);
  for(int i = 0; i < p_size; i++)
  {
    if(pieces[i]->get_Type() == t &&
     pieces[i]->get_Color() == color &&
     pieces[i]->get_last_pos().x() == xfrom &&
     pieces[i]->Test_movements(&c,pawn,pieces[i]->get_TM_size()-1) &&
     pieces[i]->get_Alive())
    {
      if(t == fous)
      {
	if(check_Bishop_path(pieces[i]->get_last_pos(),c))
        {
	  return pieces[i];
	}
	else  
         continue;
      }
      else if(t == tours)
      {
	if(check_Rok_path(pieces[i]->get_last_pos(),c))
	  return pieces[i];
	else
	  continue;
      }
      else
      {
	return pieces[i];
      }
    }
  }
  return NULL;
}
Piece* ChessPlate::piece_at_coord(int x, int y)
{
  for(int i = 0; i < p_size; i++)
  {
    if(pieces[i]->get_last_pos().x() == x &&
     pieces[i]->get_last_pos().y() == y &&
     pieces[i]->get_Alive())
    {
      return pieces[i];
    }
  }
  return NULL;
}
bool ChessPlate::check_Bishop_path(Coord start, Coord end)
{
  int x = (start.x() > end.x())?-1:1;
  int y = (start.y() > end.y())?-1:1;

  int cnt = start.x()-end.x();
  cnt = cnt<0?cnt*-1:cnt;
  
  int j = 1;
  while(j <= cnt)
  {
    for(int i = 0; i < p_size; i++)
    {
      if(pieces[i]->get_last_pos().x() == start.x()+x*j &&
        pieces[i]->get_last_pos().y() == start.y()+y*j &&
        pieces[i]->get_Alive())
	{
	  return false;
	}
    }
    cnt--;
  }
  return true;
}
bool ChessPlate::check_Rok_path(Coord start, Coord end)
{
  int mv;
  int i=1;
  if(start.x() == end.x())
  {
    mv = start.y()>end.y()?-1:1;
    while(start.y()+i*mv != end.y())
    {
      for(int j = 0; j < p_size; j++)
      {
       if(pieces[j]->get_last_pos().x() == start.x() &&
        pieces[j]->get_last_pos().y() == start.y()+i*mv &&
        pieces[j]->get_Alive())
       {
         return false;
       }
     }
     i++;
   }
 }
 else if(start.y() == end.y())
 {
  mv = start.x()>end.x()?-1:1;
  while(start.x()+i*mv != end.x())
  {
    for(int j = 0; j < p_size; j++)
    {
     if(pieces[j]->get_last_pos().y() == start.y() &&
      pieces[j]->get_last_pos().x() == start.x()+i*mv &&
      pieces[j]->get_Alive())
     {
       return false;
     }
   }
   i++;
 }
}
return true;
}
