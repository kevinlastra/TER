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
    cout << "start copying at index "<<indexs[0]<<endl;
    for(int i = 1; i < nb; i++)
    {
      indexs[i] = TimeLines.size();
      TimeLines.push_back(new TimeLine(TimeLines[index]));
      cout << "new branch generated at "<<indexs[i]<<endl;
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
