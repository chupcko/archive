#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAXDM 128
#define AGLA_LEN_VALUE 32
#define AGLA_MAX_CLASS 11
#define BS 13
#define BT 16

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

enum
{
  NISTA=-1,
  Lplus,
  Lminus,
  Lputa,
  Lpodeljeno,
  Lna,
  Lx,
  Lbroj,
  Lfunkcija,
  Llz,
  Ldz,
  AGLA_EOF
} AGLA_class;
char AGLA_value[AGLA_LEN_VALUE+1];
int AGLA_len;
int FJA_pos;
int AGLA_new_pos=1;
char *AGLA_string;
char *FJA_error;

int AGLA_scanner(void)
{
  static int len[AGLA_MAX_CLASS-1];
  static int pos[AGLA_MAX_CLASS-1];
  static unsigned char ss[UCHAR_MAX+1]=
  {
    BS,BS,BS,BS,BS,BS,BS,BS,BS,0,0,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,
    0,BS,BS,BS,BS,BS,BS,BS,11,12,3,1,BS,2,8,4,7,7,7,7,7,7,7,7,7,7,BS,BS,BS,BS,BS,BS,
    BS,10,10,10,10,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,6,10,10,BS,BS,BS,5,BS,
    BS,10,10,10,10,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,6,10,10,BS,BS,BS,BS,BS,
    BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,
    BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,
    BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,
    BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS,BS
  };
  static int pr[BT][BS]=
  {
    {0,1,2,3,4,5,6,7,BT,8,8,9,10},
    {BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,BT,BT,8,8,BT,8,8,BT,BT},
    {BT,BT,BT,BT,BT,BT,BT,7,11,13,BT,BT,BT},
    {BT,BT,BT,BT,BT,BT,8,8,BT,8,8,BT,BT},
    {BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,BT,BT,BT,12,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,BT,BT,BT,12,BT,13,BT,BT,BT},
    {BT,15,15,BT,BT,BT,BT,14,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,BT,BT,BT,14,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,BT,BT,BT,14,BT,BT,BT,BT,BT}
  };
  int c;
  int n;
  int st;
  st=0;
  do
  {
    switch(st)
    {
      case 0:
        FJA_pos=AGLA_new_pos;
        n=0;
        AGLA_class=NISTA;
        break;
      case 1:
        AGLA_class=Lplus;
        len[Lplus]=n;
        pos[Lplus]=AGLA_new_pos;
        break;
      case 2:
        AGLA_class=Lminus;
        len[Lminus]=n;
        pos[Lminus]=AGLA_new_pos;
        break;
      case 3:
        AGLA_class=Lputa;
        len[Lputa]=n;
        pos[Lputa]=AGLA_new_pos;
        break;
      case 4:
        AGLA_class=Lpodeljeno;
        len[Lpodeljeno]=n;
        pos[Lpodeljeno]=AGLA_new_pos;
        break;
      case 5:
        AGLA_class=Lna;
        len[Lna]=n;
        pos[Lna]=AGLA_new_pos;
        break;
      case 6:
        AGLA_class=Lx;
        len[Lx]=n;
        pos[Lx]=AGLA_new_pos;
        len[Lfunkcija]=n;
        pos[Lfunkcija]=AGLA_new_pos;
        break;
      case 7:
      case 12:
      case 14:
        AGLA_class=Lbroj;
        len[Lbroj]=n;
        pos[Lbroj]=AGLA_new_pos;
        break;
      case 8:
        AGLA_class=Lfunkcija;
        len[Lfunkcija]=n;
        pos[Lfunkcija]=AGLA_new_pos;
        break;
      case 9:
        AGLA_class=Llz;
        len[Llz]=n;
        pos[Llz]=AGLA_new_pos;
        break;
      case 10:
        AGLA_class=Ldz;
        len[Ldz]=n;
        pos[Ldz]=AGLA_new_pos;
    }
    if(!(c=*AGLA_string))
      switch(st)
      {
        case 0:
          AGLA_class=AGLA_EOF;
        default:
          st=BT;
      }
    else
    {
      AGLA_string++;
      AGLA_new_pos++;
      if(n==AGLA_LEN_VALUE)
      {
        FJA_error="Predugacak broj ili ime_funkcije";
        return 1;
      }
      AGLA_value[n]=c;
      n++;
      st=ss[(int)c]==BS?BT:pr[st][ss[(int)c]];
    }
  }
  while(st!=BT);
  if(AGLA_class==NISTA)
  {
    FJA_error="Nepoznata leksema";
    return 1;
  }
  else
  {
    if(AGLA_class==AGLA_EOF)
      AGLA_len=0;
    else
    {
      AGLA_len=len[AGLA_class];
      AGLA_string+=AGLA_len-n;
      AGLA_new_pos=pos[AGLA_class];
    }
    AGLA_value[AGLA_len]='\0';
  }
  return 0;
}

int UbaciUMasinu(int t)
{
  if(DMasine==MAXDM)
  {
    FJA_error="Mnogo velika funkcija";
    return 1;
  }
  Masina[DMasine++].sta=t;
  return 0;
}

int Ffunkcija(void)
{
  int i=0;
  while(Funkcije[i].fja!=NULL&&strcmp(AGLA_value,Funkcije[i].ime))
    i++;
  if(Funkcije[i].fja==NULL)
  {
    FJA_error="Nema takve funkcije";
    return 1;
  }
  SFja[DSFje++]=i;
  return 0;
}

double FJA_izracunaj(double xx)
{
  static double stek[MAXDM];
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

char *Poruka1="Ocekivao sam: EOS + - * / ^ )";
char *Poruka2="Ocekivao sam: )";

int AGSA_N(void);

int AGSA_L(void)
{
  switch(AGLA_class)
  {
    case Lna:
      if(AGLA_scanner())
        return 1;
      if(AGSA_N())
        return 1;
      if(AGSA_L())
        return 1;
      if(UbaciUMasinu(Ona))
        return 1;
      break;
    case AGLA_EOF:
    case Lplus:
    case Lminus:
    case Lputa:
    case Lpodeljeno:
    case Ldz:
      break;
    default:
      FJA_error=Poruka1;
      return 1;
  }
  return 0;
}

int AGSA_K(void)
{
  switch(AGLA_class)
  {
    case Lputa:
      if(AGLA_scanner())
        return 1;
      if(AGSA_N())
        return 1;
      if(AGSA_L())
        return 1;
      if(UbaciUMasinu(Oputa))
        return 1;
      break;
    case Lpodeljeno:
      if(AGLA_scanner())
        return 1;
      if(AGSA_N())
        return 1;
      if(AGSA_L())
        return 1;
      if(UbaciUMasinu(Opodeljeno))
        return 1;
      break;
    case AGLA_EOF:
    case Lplus:
    case Lminus:
    case Ldz:
      break;
    default:
      FJA_error=Poruka1;
      return 1;
  }
  return 0;
}

int AGSA_S(void)
{
  switch(AGLA_class)
  {
    case Lplus:
      if(AGLA_scanner())
        return 1;
      if(AGSA_N())
        return 1;
      if(AGSA_L())
        return 1;
      if(AGSA_K())
        return 1;
      if(UbaciUMasinu(Oplus))
        return 1;
      break;
    case Lminus:
      if(AGLA_scanner())
        return 1;
      if(AGSA_N())
        return 1;
      if(AGSA_L())
        return 1;
      if(AGSA_K())
        return 1;
      if(UbaciUMasinu(Ominus))
        return 1;
      break;
    case AGLA_EOF:
    case Ldz:
      break;
    default:
      FJA_error="Ocekivao sam: EOS + - )";
      return 1;
  }
  return 0;
}

int AGSA_N(void)
{
  switch(AGLA_class)
  {
    case Lminus:
      if(AGLA_scanner())
        return 1;
      if(AGSA_N())
        return 1;
      if(UbaciUMasinu(Oznak))
        return 1;
      break;
    case Lfunkcija:
      if(Ffunkcija())
        return 1;
      if(AGLA_scanner())
        return 1;
      if(AGLA_class!=Llz)
      {
        FJA_error="Ocekivao sam: (";
        return 1;
      }
      if(AGLA_scanner())
        return 1;
      if(AGSA_N())
        return 1;
      if(AGSA_L())
        return 1;
      if(AGSA_K())
        return 1;
      if(AGSA_S())
        return 1;
      if(AGLA_class!=Ldz)
      {
        FJA_error=Poruka2;
        return 1;
      }
      if(UbaciUMasinu(Ofja))
        return 1;
      Masina[DMasine-1].u.fja=SFja[--DSFje];
      if(AGLA_scanner())
        return 1;
      break;
    case Lbroj:
      if(UbaciUMasinu(Obroj))
        return 1;
      if(sscanf(AGLA_value,"%lf",&Masina[DMasine-1].u.broj)!=1)
      {
        FJA_error="Neispravan broj";
        return 1;
      }
      if(AGLA_scanner())
        return 1;
      break;
    case Lx:
      if(UbaciUMasinu(Ox))
        return 1;
      if(AGLA_scanner())
        return 1;
      break;
    case Llz:
      if(AGLA_scanner())
        return 1;
      if(AGSA_N())
        return 1;
      if(AGSA_L())
        return 1;
      if(AGSA_K())
        return 1;
      if(AGSA_S())
        return 1;
      if(AGLA_class!=Ldz)
      {
        FJA_error=Poruka2;
        return 1;
      }
      if(AGLA_scanner())
        return 1;
      break;
    default:
      FJA_error="Ocekivao sam: - ime_funkcije ( broj x";
      return 1;
  }
  return 0;
}

int FJA_parser(char *s)
{
  AGLA_string=s;
  DMasine=0;
  DSFje=0;
  if(AGLA_scanner())
    return 1;
  if(AGSA_N())
    return 1;
  if(AGSA_L())
    return 1;
  if(AGSA_K())
    return 1;
  if(AGSA_S())
    return 1;
  if(AGLA_class!=AGLA_EOF)
  {
    FJA_error="Prepoznao sam rec ali ima jos na ulazu";
    return 1;
  }
  return 0;
}

/*

  Nachin korishcjenja zaglavlja FJA.H:

  Funkcija FJA_parser prevodi prosledjenu nisku sa opisom funkcije
  (standardno opisana funkcija: + - * / ^ i sve unarne funkcije iz math.h)
  u neku unutrashnju strukturu i vracja 0 ili 1.

  Ako funkcija FJA_parser vrati 1 tada je doshlo do neke greshke (u smislu
  sintakse) i tada cje se u nisci FJA_error nacji opis nastale greshke, a u
  celobrojnoj promenljivoj FJA_pos nacji cje se pozicija unutar niske
  (prosledjene funkciji FJA_parser) gde se desila greshka.

  Ako funkcija FJA_parser vrati 0 tada je sve u redu i mozhe se izrachunati
  vrednost za neko konkretno x uz pomocj funkcije FJA_izracunaj kojoj se
  prosledjuje vrednost argumenta x, a funkcija FJA_izracunaj vracja vrednost
  funkcije.

  Sve greshke u toku izrachunavanja (deljenje 0 i slichno) se obradjuju na
  standardni nachin i nachin obrade greshaka se mozhe promeniti korishcjenjem
  standardnog zaglavlja "SIGNAL.H".

int main(int argc,char *argv[])
{
  if(argc==3)
    if(FJA_parser(argv[1]))
      printf("Greska: %s na poziciji %d\n",FJA_error,FJA_pos);
    else
    {
      double d;
      sscanf(argv[2],"%lf",&d);
      printf("Fja(%lf)=%lf\n",d,FJA_izracunaj(d));
    }
  else
    puts("Prosledi funkciju i vrednost argumenta");
  return 0;
}

*/
