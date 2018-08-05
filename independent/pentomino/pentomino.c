#include <stdio.h>

#define MAXDIM 5
#define OFFSET (MAXDIM-1)
#define MAXPARTS 12

typedef int Part[MAXDIM][MAXDIM];

Part Parts[63]=
{
  {{0,0,0,0,0},{0,0,1,0,0},{0,1,1,1,0},{0,0,1,0,0},{0,0,0,0,0}},
  {{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0}},
  {{0,0,0,0,0},{0,0,0,0,0},{1,1,1,1,1},{0,0,0,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,1,1,0,0},{0,0,1,0,0},{0,1,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,1,0},{0,0,1,0,0},{0,0,1,1,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,1,0,1,0},{0,1,1,1,0},{0,0,0,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,0,0,0},{0,1,1,1,0},{0,1,0,1,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,0,1,0},{0,1,1,1,0},{0,1,0,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,1,0,0,0},{0,1,1,1,0},{0,0,0,1,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,1,0},{0,0,1,0,0},{0,1,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,1,1,0,0},{0,0,1,0,0},{0,0,1,1,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,0,1,0},{0,1,1,1,0},{0,0,0,1,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,1,0,0,0},{0,1,1,1,0},{0,1,0,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,1,1,1,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,1,1,1,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,1,0,0,0},{0,1,1,0,0},{0,0,1,1,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,0,1,0},{0,0,1,1,0},{0,1,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,1,0},{0,1,1,0,0},{0,1,0,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,1,1,0,0},{0,0,1,1,0},{0,0,0,1,0},{0,0,0,0,0}},
  {{0,0,1,0,0},{0,0,1,0,0},{0,0,1,1,1},{0,0,0,0,0},{0,0,0,0,0}},
  {{0,0,1,0,0},{0,0,1,0,0},{1,1,1,0,0},{0,0,0,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,0,0,0},{0,0,1,1,1},{0,0,1,0,0},{0,0,1,0,0}},
  {{0,0,0,0,0},{0,0,0,0,0},{1,1,1,0,0},{0,0,1,0,0},{0,0,1,0,0}},
  {{0,0,0,0,0},{0,0,0,1,0},{1,1,1,1,0},{0,0,0,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,1,0,0,0},{0,1,1,1,1},{0,0,0,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,0,0,0},{1,1,1,1,0},{0,0,0,1,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,0,0,0},{0,1,1,1,1},{0,1,0,0,0},{0,0,0,0,0}},
  {{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,1,1,0,0},{0,0,0,0,0}},
  {{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,1,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,1,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0}},
  {{0,0,0,0,0},{0,0,1,1,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0}},
  {{0,0,0,0,0},{0,1,1,0,0},{0,1,1,1,0},{0,0,0,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,1,0},{0,1,1,1,0},{0,0,0,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,0,0,0},{0,1,1,1,0},{0,1,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,0,0,0},{0,1,1,1,0},{0,0,1,1,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,1,1,0,0},{0,1,1,0,0},{0,0,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,1,0},{0,0,1,1,0},{0,0,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,0,0},{0,1,1,0,0},{0,1,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,0,0},{0,0,1,1,0},{0,0,1,1,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,1,1,0,0},{0,0,1,1,0},{0,0,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,1,0},{0,1,1,0,0},{0,0,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,0,0},{0,0,1,1,0},{0,1,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,0,0},{0,1,1,0,0},{0,0,1,1,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,1,0,0,0},{0,1,1,1,0},{0,0,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,0,1,0},{0,1,1,1,0},{0,0,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,0,0},{0,1,1,1,0},{0,1,0,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,0,0},{0,1,1,1,0},{0,0,0,1,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{1,1,1,0,0},{0,0,1,1,0},{0,0,0,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,1,1},{0,1,1,0,0},{0,0,0,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,0,0,0},{0,0,1,1,0},{1,1,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,0,0,0},{0,1,1,0,0},{0,0,1,1,1},{0,0,0,0,0}},
  {{0,1,0,0,0},{0,1,0,0,0},{0,1,1,0,0},{0,0,1,0,0},{0,0,0,0,0}},
  {{0,0,0,1,0},{0,0,0,1,0},{0,0,1,1,0},{0,0,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,0,0},{0,1,1,0,0},{0,1,0,0,0},{0,1,0,0,0}},
  {{0,0,0,0,0},{0,0,1,0,0},{0,0,1,1,0},{0,0,0,1,0},{0,0,0,1,0}},
  {{0,0,0,0,0},{0,0,1,0,0},{1,1,1,1,0},{0,0,0,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,0,0},{0,1,1,1,1},{0,0,0,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,0,0,0},{1,1,1,1,0},{0,0,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,0,0,0},{0,1,1,1,1},{0,0,1,0,0},{0,0,0,0,0}},
  {{0,0,1,0,0},{0,0,1,0,0},{0,1,1,0,0},{0,0,1,0,0},{0,0,0,0,0}},
  {{0,0,1,0,0},{0,0,1,0,0},{0,0,1,1,0},{0,0,1,0,0},{0,0,0,0,0}},
  {{0,0,0,0,0},{0,0,1,0,0},{0,1,1,0,0},{0,0,1,0,0},{0,0,1,0,0}},
  {{0,0,0,0,0},{0,0,1,0,0},{0,0,1,1,0},{0,0,1,0,0},{0,0,1,0,0}}
};

int BEParts[MAXPARTS+1]={0,1,3,7,11,15,19,23,31,39,47,55,63};

int Fill[OFFSET+MAXDIM*MAXPARTS+OFFSET][OFFSET+MAXDIM*MAXPARTS+OFFSET];
int Mask[OFFSET+MAXDIM*MAXPARTS+OFFSET][OFFSET+MAXDIM*MAXPARTS+OFFSET]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
  {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
  {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int Max_mask_x=3;
int Max_mask_y=20;

struct
{
  int x;
  int y;
  int t;
} Position[MAXPARTS];

int next_position(int p)
{
  Position[p].x++;
  if(Position[p].x>=OFFSET+Max_mask_x)
  {
    Position[p].x=0;
    Position[p].y++;
    if(Position[p].y>=OFFSET+Max_mask_y)
    {
      Position[p].y=0;
      Position[p].t++;
      if(Position[p].t>=BEParts[p+1])
        return 0;
    }
  }
  return 1;
}

int add_part(int p)
{
  int x;
  int y;
  int m;
  m=1;
  for(x=0;x<MAXDIM;x++)
    for(y=0;y<MAXDIM;y++)
    {
      Mask[Position[p].x+x][Position[p].y+y]+=Parts[Position[p].t][x][y];
      if(m)
        m=Mask[Position[p].x+x][Position[p].y+y]<=1;
    }
  return m;
}

void sub_part(int p)
{
  int x;
  int y;
  for(x=0;x<MAXDIM;x++)
    for(y=0;y<MAXDIM;y++)
      Mask[Position[p].x+x][Position[p].y+y]-=Parts[Position[p].t][x][y];
}

int fill(int x,int y,int t)
{
  if(Mask[x][y]==0&&Fill[x][y]==0)
  {
    Fill[x][y]=t;
    return fill(x-1,y,t)+fill(x+1,y,t)+fill(x,y-1,t)+fill(x,y+1,t)+1;
  }
  else
    return 0;
}

int proverijelimadela(int xs,int ys,int ps,int u)/***/
{
  int p;
  int t;
  int xt;
  int yt;
  for(p=0;p<=ps;p++)
    for(t=BEParts[p];t<BEParts[p+1];t++)
      for(xt=xs-OFFSET;xt<xs+OFFSET;xt++)
        for(yt=ys-OFFSET;yt<ys+OFFSET;yt++)
        {
          int x;
          int y;
          int n;
          n=1;
          for(x=0;n&&x<MAXDIM;x++)
            for(y=0;n&&y<MAXDIM;y++)
              if(n)
                n=(Fill[xt+x][yt+y]==u&&Parts[t][x][y])||(Fill[xt+x][yt+y]!=t&&(!Parts[t][x][y]));
          if(n)
            return p;
        }
  return ps+1;
}

int right(int p)
{
  int x;
  int y;
  int t;
  for(x=0;x<OFFSET+Max_mask_x+OFFSET;x++)
    for(y=0;y<OFFSET+Max_mask_y+OFFSET;y++)
      Fill[x][y]=0;
  t=1;
  for(x=OFFSET;x<OFFSET+Max_mask_x;x++)
    for(y=OFFSET;y<OFFSET+Max_mask_y;y++)
    {
      int count;
      count=fill(x,y,t);
      if(count>0&&count%MAXDIM!=0)
        return 0;
      if(count==MAXDIM&&proverijelimadela(x,y,p,t)<=p)
        return 0;
/*
      if(count==MAXDIM)
      {
        int pr=proverijelimadela(x,y,t);
        int x1;
        int y1;
        printf("# %d %d (%d %d)\n",p,pr,x,y);
        for(x1=0;x1<OFFSET+Max_mask_x+OFFSET;x1++)
        {
          for(y1=0;y1<OFFSET+Max_mask_y+OFFSET;y1++)
            printf("%02d ",Fill[x1][y1]);
          printf("\n");
        }
        printf("\n");
        if(pr<=p)
        {
          return 0;
        }
      }
*/
      t++;
    }
  return 1;
}

void write(FILE *f,int p)
{
  int x;
  int y;
  int i;
  char s[MAXDIM*MAXPARTS][MAXDIM*MAXPARTS];
  for(x=0;x<Max_mask_x;x++)
    for(y=0;y<Max_mask_y;y++)
      s[x][y]='.';
  for(i=0;i<p;i++)
    for(x=0;x<MAXDIM;x++)
      for(y=0;y<MAXDIM;y++)
        if(Parts[Position[i].t][x][y])
          s[Position[i].x-OFFSET+x][Position[i].y-OFFSET+y]='A'+i;
  fprintf(f,"%d:\n",p);
  for(x=0;x<Max_mask_x;x++)
  {
    for(y=0;y<Max_mask_y;y++)
      fprintf(f,"%c",s[x][y]);
    fprintf(f,"\n");
  }
  fprintf(f,"\n");
  fflush(f);
/*
  for(x=0;x<OFFSET+Max_mask_x+OFFSET;x++)
  {
    for(y=0;y<OFFSET+Max_mask_y+OFFSET;y++)
      printf("%d",Mask[x][y]);
    printf("\n");
  }
  printf("\n");
*/
}

void check(int p)
{
  write(stderr,p);
  if(p==MAXPARTS)
    write(stdout,MAXPARTS);
  else
  {
    Position[p].x=0;
    Position[p].y=0;
    Position[p].t=BEParts[p];
    do
    {
      if(add_part(p)&&right(p))
        check(p+1);
      sub_part(p);
    }
    while(next_position(p));
  }
}

int main(void)
{
  /* Podesi Mask */
  check(0);
  return 0;
}