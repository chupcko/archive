#include <stdio.h>

typedef Part[5][5];

Part P[12]=
{
  {{0,0,0,0,0},{0,0,1,0,0},{0,1,1,1,0},{0,0,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,0,0,0},{1,1,1,1,1},{0,0,0,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,0,0,0},{0,1,1,1,0},{0,1,0,1,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,1,0},{0,0,1,0,0},{0,1,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,1,1,1,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,1,0,0,0},{0,1,1,0,0},{0,0,1,1,0},{0,0,0,0,0}},
  {{0,0,1,0,0},{0,0,1,0,0},{0,0,1,1,1},{0,0,0,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,1,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0}},
  {{0,0,0,0,0},{0,0,1,0,0},{0,0,1,1,0},{0,0,1,1,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,0,0},{0,1,1,1,0},{0,0,0,1,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,0,0},{0,0,1,1,0},{0,0,0,1,0},{0,0,0,1,0}},
  {{0,0,0,0,0},{0,0,1,0,0},{0,0,1,1,0},{0,0,1,0,0},{0,0,1,0,0}}
};

void Put_part(Part p,int x,int y,int v)
{
  p[x+2][y+2]=v;
}

int Get_part(Part p,int x,int y)
{
  return p[x+2][y+2];
}

int Cmp_part(Part s,Part d)
{
  int x;
  int y;
  for(x=0;x<5;x++)
    for(y=0;y<5;y++)
      if(s[x][y]!=d[x][y])
        return 1;
  return 0;
}

int trx(int t,int x,int y)
{
  return (t&2?1:-1)*(t&4?x:y);
}

int try(int t,int x,int y)
{
  return (t&1?1:-1)*(t&4?y:x);
}

int main(void)
{
  int p;
  int t;
  int x;
  int y;
  Part n[8];
  int pocetakkraj[13];
  int i;
  i=0;
  for(p=0;p<12;p++)
  {
    for(t=0;t<8;t++)
    {
      for(x=-2;x<=2;x++)
        for(y=-2;y<=2;y++)
          Put_part(n[t],trx(t,x,y),try(t,x,y),Get_part(P[p],x,y));
    }
    pocetakkraj[p]=i;
    for(t=0;t<8;t++)
    {
      y=1;
      for(x=0;x<t;x++)
        y=y&&Cmp_part(n[t],n[x]);
      if(y)
      {
        printf("{");
        for(x=0;x<5;x++)
        {
          printf("{");
          for(y=0;y<5;y++)
          {
            printf("%d",n[t][x][y]);
            if(y!=4)
              printf(",");
          }
          printf("}");
          if(x!=4)
            printf(",");
        }
        printf("},\n");
        i++;
      }
    }
    printf("\n");
  }
  pocetakkraj[12]=i;
  for(p=0;p<13;p++)
    printf("%d,",pocetakkraj[p]);
  printf("\n");
  return 0;
}
