
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ALLOC 8192
#define MAX_BROJ_PROMENLJIVIH 256
#define MAX_DUZINA_IMENA 32

typedef enum
{
  NULA,
  JEDAN,
  NEKORISTISE
} Konstante;

struct
{
  char ime[MAX_DUZINA_IMENA+1];
  Konstante valuacija;
} Promenljive[MAX_BROJ_PROMENLJIVIH];

int BrojPromenljivih;

struct Cvor
{
  enum
  {
    ITE,
    KONSTANTA,
    PROMENLJIVA
  } tip;
  union
  {
    struct
    {
      struct Cvor *grana1;
      struct Cvor *grana2;
      struct Cvor *grana3;
    } ite;
    Konstante konstanta;
    int promenljiva;
  } u;
};

typedef struct Cvor *Drvo;

struct Cvor AllocCvor[MAX_ALLOC];
int BrojAlloc;

FILE *Fout;
int Korak;

enum
{
  SNISTA=-1,
  Site,
  Slzagrada,
  Szarez,
  Sdzagrada,
  Sime,
  Snula,
  Sjedan,
  SEOF
} SClass;
int SPromenljiva;
int SOldNl;
int SNewNl;
int SOldPos;
int SNewPos;
FILE *Fin;
int SChar;

void Error(char *s)
{
  fprintf(stderr,"Red %d, slovo %d: %s\n",SOldNl,SOldPos,s);
  exit(1);
}

void ScannerChar(void)
{
  SChar=fgetc(Fin);
  if(SChar==(int)'\n')
  {
    SNewNl++;
    SNewPos=0;
  }
  else
    SNewPos++;
}

void Scanner(void)
{
  enum
  {
    S0,
    S1,
    S2,
    SE
  } st=S0;
  char ime[MAX_DUZINA_IMENA+1];
  int duzina_imena;
  SClass=SNISTA;
  do
  {
    switch(st)
    {
      case S0:
        SOldNl=SNewNl;
        SOldPos=SNewPos;
        switch(SChar)
        {
          case EOF:
            SClass=SEOF;
            st=SE;
            break;
          case (int)' ':
          case (int)'\t':
          case (int)'\n':
            break;
          case (int)'{':
            st=S1;
            break;
          case (int)',':
            SClass=Szarez;
            st=SE;
            break;
          case (int)'(':
            SClass=Slzagrada;
            st=SE;
            break;
          case (int)')':
            SClass=Sdzagrada;
            st=SE;
            break;
          case (int)'0':
            SClass=Snula;
            st=SE;
            break;
          case (int)'1':
            SClass=Sjedan;
            st=SE;
            break;
          default:
            if(isalpha(SChar))
            {
              SClass=Sime;
              ime[0]=(char)SChar;
              duzina_imena=1;
              st=S2;
            }
            else
              st=SE;
        }
        break;
      case S1:
        switch(SChar)
        {
          case EOF:
            Error("Kraj datoteke u komentaru");
          case (int)'}':
            st=S0;
        }
        break;
      case S2:
        if(!isalnum(SChar))
          st=SE;
        else
          if(duzina_imena<MAX_DUZINA_IMENA)
            ime[duzina_imena++]=(char)SChar;
    }
    if(st!=SE)
      ScannerChar();
  }
  while(st!=SE);
  switch(SClass)
  {
    case SNISTA:
      Error("Nepoznata leksema");
    case Sime:
      ime[duzina_imena]='\0';
      if(!strcmp(ime,"ite"))
        SClass=Site;
      else
      {
        SPromenljiva=0;
        while
        (
          SPromenljiva<BrojPromenljivih&&
          strcmp(Promenljive[SPromenljiva].ime,ime)
        )
          SPromenljiva++;
        if(SPromenljiva==BrojPromenljivih)
        {
          if(BrojPromenljivih==MAX_BROJ_PROMENLJIVIH)
            Error("Mnogo promenljivih");
          strcpy(Promenljive[BrojPromenljivih].ime,ime);
          Promenljive[BrojPromenljivih++].valuacija=NEKORISTISE;
        }
      }
      break;
    case SEOF:
      break;
    default:
      ScannerChar();
  }
}

Drvo NoviCvor(void)
{
  if(BrojAlloc==MAX_ALLOC)
    Error("Nema vise mesta");
  return AllocCvor+BrojAlloc++;
}

Drvo KopirajDrvo(Drvo d)
{
  Drvo d1=NoviCvor();
  d1->tip=d->tip;
  switch(d->tip)
  {
    case ITE:
      d1->u.ite.grana1=KopirajDrvo(d->u.ite.grana1);
      d1->u.ite.grana2=KopirajDrvo(d->u.ite.grana2);
      d1->u.ite.grana3=KopirajDrvo(d->u.ite.grana3);
      break;
    case KONSTANTA:
      d1->u.konstanta=d->u.konstanta;
      break;
    case PROMENLJIVA:
      d1->u.promenljiva=d->u.promenljiva;
  }
  return d1;
}

void StampajDrvo(FILE *f,Drvo d)
{
  switch(d->tip)
  {
    case ITE:
      fputs("ite(",f);
      StampajDrvo(f,d->u.ite.grana1);
      fputc((int)',',f);
      StampajDrvo(f,d->u.ite.grana2);
      fputc((int)',',f);
      StampajDrvo(f,d->u.ite.grana3);
      fputc((int)')',f);
      break;
    case KONSTANTA:
      fputc((int)(d->u.konstanta==JEDAN?'1':'0'),f);
      break;
    case PROMENLJIVA:
      if(Promenljive[d->u.promenljiva].valuacija==NEKORISTISE)
        fputs(Promenljive[d->u.promenljiva].ime,f);
      else
        fputc((int)(Promenljive[d->u.promenljiva].valuacija==JEDAN?'1':'0'),f);
  }
}

Drvo Parser(void)
{
  Drvo d=NoviCvor();
  switch(SClass)
  {
    case Site:
      Scanner();
      if(SClass!=Slzagrada)
        Error("Ocekivao sam: (");
      Scanner();
      d->tip=ITE;
      d->u.ite.grana1=Parser();
      if(SClass!=Szarez)
        Error("Ocekivao sam: ,");
      Scanner();
      d->u.ite.grana2=Parser();
      if(SClass!=Szarez)
        Error("Ocekivao sam: ,");
      Scanner();
      d->u.ite.grana3=Parser();
      if(SClass!=Sdzagrada)
        Error("Ocekivao sam: )");
      Scanner();
      break;
    case Sime:
      d->tip=PROMENLJIVA;
      d->u.promenljiva=SPromenljiva;
      Scanner();
      break;
    case Snula:
      d->tip=KONSTANTA;
      d->u.konstanta=NULA;
      Scanner();
      break;
    case Sjedan:
      d->tip=KONSTANTA;
      d->u.konstanta=JEDAN;
      Scanner();
      break;
    default:
      Error("Ocekivao sam: ite, ime, 0, 1");
  }
  return d;
}

Drvo UcitajDrvo(FILE *f)
{
  Drvo d;
  Fin=f;
  SNewNl=1;
  SNewPos=0;
  BrojPromenljivih=0;
  ScannerChar();
  Scanner();
  d=Parser();
  if(SClass!=SEOF)
    Error("Jos znakova na ulazu");
  return d;
}

int Dokazi(Drvo d)
{
  Drvo d1;
  Drvo d2;
  int k;
  switch(d->tip)
  {
    case ITE:
      d1=d->u.ite.grana1;
      switch(d1->tip)
      {
        case ITE:
          d2=NoviCvor();
          d2->tip=ITE;
          d2->u.ite.grana1=d1->u.ite.grana3;
          d2->u.ite.grana2=KopirajDrvo(d->u.ite.grana2);
          d2->u.ite.grana3=KopirajDrvo(d->u.ite.grana3);
          d->u.ite.grana1=d1->u.ite.grana2;
          d1->u.ite.grana2=d;
          d1->u.ite.grana3=d2;
          d=d1;
          if(!Dokazi(d))
            return 0;
          d1=d->u.ite.grana2;
          d->u.ite.grana2=d1->u.ite.grana1;
          d->u.ite.grana3=(d->u.ite.grana3)->u.ite.grana1;
          d1->u.ite.grana1=d;
          d=d1;
          fprintf(Fout,"%d\tPrEF(%d)\t",Korak,Korak-1);
          Korak++;
          break;
        case KONSTANTA:
          switch(d1->u.konstanta)
          {
            case JEDAN:
              d2=d->u.ite.grana2;
              if
              (
                (d2->tip==KONSTANTA&&d2->u.konstanta==JEDAN)||
                (d2->tip==PROMENLJIVA&&Promenljive[d2->u.promenljiva].valuacija==JEDAN)
              )
                fprintf(Fout,"%d\tAx1\t",Korak++);
              else
              {
                if(!Dokazi(d2))
                  return 0;
                fprintf(Fout,"%d\tThAx1(%d)\t",Korak,Korak-1);
                Korak++;
              }
              break;
            case NULA:
              d2=d->u.ite.grana3;
              if
              (
                (d2->tip==KONSTANTA&&d2->u.konstanta==JEDAN)||
                (d2->tip==PROMENLJIVA&&Promenljive[d2->u.promenljiva].valuacija==JEDAN)
              )
                fprintf(Fout,"%d\tAx0\t",Korak++);
              else
              {
                if(!Dokazi(d2))
                  return 0;
                fprintf(Fout,"%d\tThAx0(%d)\t",Korak,Korak-1);
                Korak++;
              }
          }
          break;
        case PROMENLJIVA:
          switch(Promenljive[d1->u.promenljiva].valuacija)
          {
            case NEKORISTISE:
              Promenljive[d1->u.promenljiva].valuacija=JEDAN;
              if(!Dokazi(d->u.ite.grana2))
                return 0;
              k=Korak-1;
              Promenljive[d1->u.promenljiva].valuacija=NULA;
              if(!Dokazi(d->u.ite.grana3))
                return 0;
              fprintf(Fout,"%d\tPrAA(%d,%d)\tite(%s,",Korak,k,Korak-1,Promenljive[d1->u.promenljiva].ime);
              Korak++;
              Promenljive[d1->u.promenljiva].valuacija=JEDAN;
              StampajDrvo(Fout,d->u.ite.grana2);
              fputc((int)',',Fout);
              Promenljive[d1->u.promenljiva].valuacija=NULA;
              StampajDrvo(Fout,d->u.ite.grana3);
              fprintf(Fout,")\n%d\tPrC1(%d)\tite(%s,",Korak,Korak-1,Promenljive[d1->u.promenljiva].ime);
              Korak++;
              Promenljive[d1->u.promenljiva].valuacija=NEKORISTISE;
              StampajDrvo(Fout,d->u.ite.grana2);
              fputc((int)',',Fout);
              Promenljive[d1->u.promenljiva].valuacija=NULA;
              StampajDrvo(Fout,d->u.ite.grana3);
              fprintf(Fout,")\n%d\tPrC0(%d)\t",Korak,Korak-1);
              Promenljive[d1->u.promenljiva].valuacija=NEKORISTISE;
              Korak++;
              break;
            case JEDAN:
              d2=d->u.ite.grana2;
              if
              (
                (d2->tip==KONSTANTA&&d2->u.konstanta==JEDAN)||
                (d2->tip==PROMENLJIVA&&Promenljive[d2->u.promenljiva].valuacija==JEDAN)
              )
                fprintf(Fout,"%d\tAx1\t",Korak++);
              else
              {
                if(!Dokazi(d2))
                  return 0;
                fprintf(Fout,"%d\tThAx1(%d)\t",Korak,Korak-1);
                Korak++;
              }
              break;
            case NULA:
              d2=d->u.ite.grana3;
              if
              (
               (d2->tip==KONSTANTA&&d2->u.konstanta==JEDAN)||
               (d2->tip==PROMENLJIVA&&Promenljive[d2->u.promenljiva].valuacija==JEDAN)
              )
                fprintf(Fout,"%d\tAx0\t",Korak++);
              else
              {
                if(!Dokazi(d2))
                  return 0;
                fprintf(Fout,"%d\tThAx0(%d)\t",Korak,Korak-1);
                Korak++;
              }
          }
      }
      break;
    case KONSTANTA:
      switch(d->u.konstanta)
      {
        case JEDAN:
          fprintf(Fout,"%d\tThT\t",Korak++);
          break;
        case NULA:
          return 0;
      }
      break;
    case PROMENLJIVA:
      switch(Promenljive[d->u.promenljiva].valuacija)
      {
        case JEDAN:
          fprintf(Fout,"%d\tThT\t",Korak++);
          break;
        case NULA:
        case NEKORISTISE:
          Promenljive[d->u.promenljiva].valuacija=NULA;
          return 0;
      }
  }
  StampajDrvo(Fout,d);
  fputc((int)'\n',Fout);
  return 1;
}

int main(void)
{
  BrojAlloc=0;
  Korak=1;
  Fout=stdout;
  if(!Dokazi(UcitajDrvo(stdin)))
    if(BrojPromenljivih)
    {
      int i;
      printf("\nNije teorema za:\n");
      for(i=0;i<BrojPromenljivih;i++)
        printf("%s=%d\n",Promenljive[i].ime,Promenljive[i].valuacija==JEDAN);
    }
    else
      printf("Nije teorema\n");
  return 0;
}
