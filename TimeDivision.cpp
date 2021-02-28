#include "TimeDivision.h"
#include "TimeLine.h"
#include <iostream>

using namespace std;


TimeDivision::TimeDivision()
{
  MTL.push_back(new MultiTimeLine);
  
  MTL[0]->tl = new TimeLine();
  MTL[0]->deb = 0;
  MTL[0]->prev = -1;
}
TimeDivision::~TimeDivision(){}
int* TimeDivision::diviser(int index, int nb, int deb)
{
  
  MTL[index]->prox = new int[nb];

  MTL[index]->prox_size += 2;
  
  int j = 0;
  for(int i = 0; i < nb; i++)
  {
    MTL.push_back(new MultiTimeLine());
    j = MTL.size()-1;
    cout << "new branch index: "<<j<<"  deb: "<<deb<<endl;
    MTL[j]->deb = deb;
    MTL[j]->tl = new TimeLine(MTL[index]->tl->chessplate);
    MTL[j]->prev = index;
    
    MTL[index]->prox[i] = j;
  }
  return MTL[index]->prox;
}
int TimeDivision::nb_timeline_end()
{
  int cnt = 0;
  for(int i = 0; i < MTL.size(); i++)
  {
    if(MTL[i]->prox_size == 0)
    {
      cnt++;
    }
  }
  return cnt;
}
int* TimeDivision::timelines_end()
{
  int* indexs = new int[nb_timeline_end()];
  int j = 0;
  for(int i = 0; i < MTL.size(); i++)
  {
    if(MTL[i]->prox_size == 0)
    {
      indexs[j] = i;
      j++;
    }
  }

  return indexs;
}
MultiTimeLine* TimeDivision::get_TimeLine_at(int i)
{
  return MTL[i];
}
