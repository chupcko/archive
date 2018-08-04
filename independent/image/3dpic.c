#include <stdlib.h>
#include <time.h>

#include "image.h"

#define myrandomize srand((unsigned)time(NULL))
#define myrandom(n) (int)((float)(n)*rand()/((float)RAND_MAX+1.0))

#define POMAK 100
#define UVECJANJE -5

#define MAXX 600
#define MAXY 400
#define MAXC 256

int mysqrt(long x)
{
  long int s;
  int y;
  s=0l;
  y=0;
  do
  {
    s+=(long)(y+y+1);
    y++;
  }
  while(s<=x);
  return y-1;
}

int z(int x,int y)
{
  long a;
  a=(long)(x-300)*(long)(x-300)+(long)(y-200)*(long)(y-200);
  return a<=10000?20+mysqrt(10000-a):x>55&&x<155&&y>105&&y<205?60:0;
}

int main(void)
{
  Image img;
  int x;
  int y;
  int flag;
  static int korist[MAXX];
  InitImage(&img,MAXX,MAXY,MAXC);
  myrandomize;
  for(x=0;x<MAXC;x++)
    SetColor(&img,x,myrandom(MAXC),myrandom(MAXC),myrandom(MAXC));
  for(y=0;y<MAXY;y++)
  {
    for(x=0;x<MAXX;x++)
      korist[x]=0;
    do
    {
      flag=1;
      x=0;
      while(x<MAXX&&korist[x])
        x++;
      if(x==MAXX)
        flag=0;
      else
      {
        int cl=myrandom(MAXC);
        while(x<MAXX)
        {
          SetPixel(&img,x,y,cl);
          korist[x]=1;
          x+=POMAK+z(x,y)/UVECJANJE;
        }
      }
    }
    while(flag);
  }
  WriteGIFImage(&img);
  DeleteImage(&img);
  return 0;
}
