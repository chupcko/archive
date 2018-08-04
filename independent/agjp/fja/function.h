#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAXDM 128

struct
{
  double (*fja)(double);
  char *ime;
} Funkcije[] =
{
  &acos,"acos",
  &asin,"asin",
  &atan,"atan",
  &ceil,"ceil",
  &cos,"cos",
  &cosh,"cosh",
  &exp,"exp",
  &fabs,"fabs",
  &floor,"floor",
  &log,"log",
  &log10,"log10",
  &sin,"sin",
  &sinh,"sinh",
  &sqrt,"sqrt",
  &tan,"tan",
  &tanh,"tanh",
  NULL,""
};

struct
{
  enum
  {
    Oplus,
    Ominus,
    Oputa,
    Opodeljeno,
    Ona,
    Oznak,
    Ofja,
    Obroj,
    Ox
  } sta;
  union
  {
    double broj;
    int fja;
  } u;
} Masina[MAXDM];
int DMasine;

int SFja[MAXDM];
int DSFje;

int Provera(int t)
{
  if(DMasine==MAXDM)
  {
    AGLA_error="Mnogo velika funkcija";
    return 1;
  }
  Masina[DMasine++].sta=t;
  return 0;
}

int Finit(void)
{
  DMasine=0;
  DSFje=0;
  return 0;
}

int Fplus(void)
{
  if(Provera(Oplus))
    return 1;
  return 0;
}

int Fminus(void)
{
  if(Provera(Ominus))
    return 1;
  return 0;
}

int Fputa(void)
{
  if(Provera(Oputa))
    return 1;
  return 0;
}

int Fpodeljeno(void)
{
  if(Provera(Opodeljeno))
    return 1;
  return 0;
}

int Fna(void)
{
  if(Provera(Ona))
    return 1;
  return 0;
}

int Fznak(void)
{
  if(Provera(Oznak))
    return 1;
  return 0;
}

int Ffunkcija(void)
{
  int i=0;
  while(Funkcije[i].fja!=NULL&&strcmp(AGLA_value,Funkcije[i].ime))
    i++;
  if(Funkcije[i].fja==NULL)
  {
    AGLA_error="Nema takve funkcije";
    return 1;
  }
  SFja[DSFje++]=i;
  return 0;
}

int Fpoziv(void)
{
  if(Provera(Ofja))
    return 1;
  Masina[DMasine-1].u.fja=SFja[--DSFje];
  return 0;
}

int Fbroj(void)
{
  if(Provera(Obroj))
    return 1;
  if(sscanf(AGLA_value,"%lf",&Masina[DMasine-1].u.broj)!=1)
  {
    AGLA_error="Neispravan broj";
    return 1;
  }
  return 0;
}

int Fx(void)
{
  if(Provera(Ox))
    return 1;
  return 0;
}

double Izrachunaj(double xx)
{
  static int stek[MAXDM];
  int ds=0;
  int i;
  for(i=0;i<DMasine;i++)
    switch(Masina[i].sta)
    {
      case Oplus:
        ds--;
        stek[ds-1]+=stek[ds];
        break;
      case Ominus:
        ds--;
        stek[ds-1]-=stek[ds];
        break;
      case Oputa:
        ds--;
        stek[ds-1]*=stek[ds];
        break;
      case Opodeljeno:
        ds--;
        stek[ds-1]/=stek[ds];
        break;
      case Ona:
        ds--;
        stek[ds-1]=pow(stek[ds-1],stek[ds]);
        break;
      case Oznak:
        stek[ds-1]=-stek[ds-1];
        break;
      case Ofja:
        stek[ds-1]=(*Funkcije[Masina[i].u.fja].fja)(stek[ds-1]);
        break;
      case Obroj:
        stek[ds++]=Masina[i].u.broj;
        break;
      case Ox:
        stek[ds++]=xx;
    }
  return stek[0];
}
