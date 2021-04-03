#include "TimeDivision.h"
#include "TimeLine.h"
#include <iostream>

using namespace std;


TimeDivision::TimeDivision()
{
  TimeLines.push_back(new TimeLine);
}
TimeDivision::~TimeDivision(){}
int* TimeDivision::diviser(int nb, int index)
{
  
  int* indexs = new int[nb];
  indexs[0] = index;
  if(nb >= 2)
  {
    for(int i = 1; i < nb; i++)
    {
      cout << "CREATING "<<TimeLines.size()<<endl;
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
  cout << "DELETING "<<i<<endl;
  TimeLines.erase(TimeLines.begin()+i);
}
void TimeDivision::clear_score()
{
  int i = 0;
  while(i < TimeLines.size())
  {
    if(TimeLines[i]->get_score() > MAX_SCORE)
      remove_tl_at(i);
    else
      i++;
  }
}

//PRINTS
void TimeDivision::Print_adresse()
{
  for(int i = 0; i < TimeLines.size(); i++)
  {
    cout << "#   "<<TimeLines[i]<<endl;
  }
}
