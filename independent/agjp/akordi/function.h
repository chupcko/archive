#include <stdio.h>

#define DUZINA 24

enum
{
  A,
  Ais,
  B,
  C,
  Cis,
  D,
  Dis,
  E,
  F,
  Fis,
  G,
  Gis
} Tonovi[DUZINA];
int Duzina;
char *Poruka="Mnogo tonova";

void ispisi_ton(int i)
{
  static char *imena[12]=
  {
    "A",
    "A#",
    "B",
    "C",
    "C#",
    "D",
    "D#",
    "E",
    "F",
    "F#",
    "G",
    "G#"
  };
  printf("%s",imena[i]);
}

int f_ispis(void)
{
  int i;
  printf(" =");
  for(i=0;i<Duzina;i++)
  {
    putchar((int)' ');
    ispisi_ton(Tonovi[i]);
  }
  putchar((int)'\n');
  return 0;
}

int f_a(void)
{
  Tonovi[0]=A;
  ispisi_ton(A);
  return 0;
}

int f_ais(void)
{
  Tonovi[0]=Ais;
  ispisi_ton(Ais);
  return 0;
}

int f_b(void)
{
  Tonovi[0]=B;
  ispisi_ton(B);
  return 0;
}

int f_c(void)
{
  Tonovi[0]=C;
  ispisi_ton(C);
  return 0;
}

int f_cis(void)
{
  Tonovi[0]=Cis;
  ispisi_ton(Cis);
  return 0;
}

int f_d(void)
{
  Tonovi[0]=D;
  ispisi_ton(D);
  return 0;
}

int f_dis(void)
{
  Tonovi[0]=Dis;
  ispisi_ton(Dis);
  return 0;
}

int f_e(void)
{
  Tonovi[0]=E;
  ispisi_ton(E);
  return 0;
}

int f_f(void)
{
  Tonovi[0]=F;
  ispisi_ton(F);
  return 0;
}

int f_fis(void)
{
  Tonovi[0]=Fis;
  ispisi_ton(Fis);
  return 0;
}

int f_g(void)
{
  Tonovi[0]=G;
  ispisi_ton(G);
  return 0;
}

int f_gis(void)
{
  Tonovi[0]=Gis;
  ispisi_ton(Gis);
  return 0;
}

int f_mol(void)
{
  Tonovi[1]=(Tonovi[0]+3)%12;
  Tonovi[2]=(Tonovi[0]+7)%12;
  Duzina=3;
  printf(" m");
  return 0;
}

int f_dur(void)
{
  Tonovi[1]=(Tonovi[0]+4)%12;
  Tonovi[2]=(Tonovi[0]+7)%12;
  Duzina=3;
  return 0;
}

int f_sus(void)
{
  Tonovi[1]=(Tonovi[0]+5)%12;
  Tonovi[2]=(Tonovi[0]+7)%12;
  Duzina=3;
  printf(" sus4");
  return 0;
}

int f_dim(void)
{
  Tonovi[1]=(Tonovi[0]+3)%12;
  Tonovi[2]=(Tonovi[0]+6)%12;
  Tonovi[3]=(Tonovi[0]+9)%12;
  Duzina=4;
  printf(" dim");
  return 0;
}

int f_o5m(void)
{
  Tonovi[2]=(Tonovi[0]+6)%12;
  printf("/-5");
  return 0;
}

int f_o5p(void)
{
  Tonovi[2]=(Tonovi[0]+8)%12;
  printf("/5+");
  return 0;
}

int f_o6(void)
{
  if(Duzina==DUZINA)
  {
    AGLA_error=Poruka;
    return 1;
  }
  Tonovi[Duzina]=(Tonovi[0]+9)%12;
  Duzina++;
  printf("/6");
  return 0;
}

int f_o7(void)
{
  if(Duzina==DUZINA)
  {
    AGLA_error=Poruka;
    return 1;
  }
  Tonovi[Duzina]=(Tonovi[0]+10)%12;
  Duzina++;
  printf("/7");
  return 0;
}

int f_omaj7(void)
{
  if(Duzina==DUZINA)
  {
    AGLA_error=Poruka;
    return 1;
  }
  Tonovi[Duzina]=(Tonovi[0]+11)%12;
  Duzina++;
  printf("/maj7");
  return 0;
}

int f_o9m(void)
{
  if(Duzina==DUZINA)
  {
    AGLA_error=Poruka;
    return 1;
  }
  Tonovi[Duzina]=(Tonovi[0]+1)%12;
  Duzina++;
  printf("/-9");
  return 0;
}

int f_o9(void)
{
  if(Duzina==DUZINA)
  {
    AGLA_error=Poruka;
    return 1;
  }
  Tonovi[Duzina]=(Tonovi[0]+2)%12;
  Duzina++;
  printf("/9");
  return 0;
}

int f_o9p(void)
{
  if(Duzina==DUZINA)
  {
    AGLA_error=Poruka;
    return 1;
  }
  Tonovi[Duzina]=(Tonovi[0]+3)%12;
  Duzina++;
  printf("/9+");
  return 0;
}

int f_o11(void)
{
  if(Duzina==DUZINA)
  {
    AGLA_error=Poruka;
    return 1;
  }
  Tonovi[Duzina]=(Tonovi[0]+5)%12;
  Duzina++;
  printf("/11");
  return 0;
}

int f_o11p(void)
{
  if(Duzina==DUZINA)
  {
    AGLA_error=Poruka;
    return 1;
  }
  Tonovi[Duzina]=(Tonovi[0]+6)%12;
  Duzina++;
  printf("/11+");
  return 0;
}

int f_o13(void)
{
  if(Duzina==DUZINA)
  {
    AGLA_error=Poruka;
    return 1;
  }
  Tonovi[Duzina]=(Tonovi[0]+9)%12;
  Duzina++;
  printf("/13");
  return 0;
}
