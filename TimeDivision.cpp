#include "TimeDivision.h"
#include "TimeLine.h"
#include <iostream>

using namespace std;


TimeDivision::TimeDivision()
{
  TimeLines.push_back(new TimeLine);
}
TimeDivision::~TimeDivision()
{
  for(int i = 0; i < TimeLines.size(); i++)
    delete TimeLines[i];
  TimeLines.clear();
}
int* TimeDivision::diviser(int nb, int index)
{
  if(nb <= 0)
    return NULL;
  
  int* indexs = new int[nb];
  indexs[0] = index;
  if(nb >= 2)
  {
    for(int i = 1; i < nb; i++)
    {
      indexs[i] = TimeLines.size();
      TimeLines.push_back(new TimeLine(TimeLines[index]));
    }
  }
  return indexs;
}
TimeLine* TimeDivision::TimeLine_at(int i)
{
  return TimeLines[i];
}
int TimeDivision::size()
{
  return TimeLines.size();
}
void TimeDivision::transform_indexs_before_kill(int* indexs, int size, int i)
{
  for(int i = 0; i < size; i++)
  {
    if(indexs[i] > i)
    {
      indexs[i]--;
    }
  }
}
void TimeDivision::remove_tl_at(int i)
{
  delete TimeLines[i];
  TimeLines[i] = nullptr;
}
void TimeDivision::clear_score()
{
  int i = 0;
  int size = TimeLines.size();
  std::vector<TimeLine*> temp;
  cout << "Total to delete: "<<TimeLines.size()<<endl;
  while(i < TimeLines.size())
  {
    if(TimeLines[i]->get_score() >= MAX_SCORE)
    {
      remove_tl_at(i);
    }
    i++;
    //cout << "removing    "<<i<<" of "<<size<<endl;
  }
  for(int i = 0; i < size; i++)
  {
    if(TimeLines[i] != nullptr)
      temp.push_back(TimeLines[i]);
  }
  TimeLines = temp;
}
void TimeDivision::clear_tl()
{
  int i = 0;
  
  int cpt = 0;
  while(i < TimeLines.size())
  {
    TimeLines[i]->Check_timeline();
    if(TimeLines[i]->get_score() > MAX_SCORE)
    {
      remove_tl_at(i);
    }
    i++;
    //cout << "removing    "<<i<<" of "<<size<<endl;
    //cpt++;
  }
  std::vector<TimeLine*> temp;
  
  for(i = 0; i < TimeLines.size(); i++)
  {
    if(TimeLines[i] != nullptr)
    {
      temp.push_back(TimeLines[i]);
    }
  }
  TimeLines = temp;
}
//PRINTS
void TimeDivision::Print_adresse()
{
  for(int i = 0; i < TimeLines.size(); i++)
  {
    cout << "#   "<<TimeLines[i]<<endl;
  }
}
