#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
  LEX_ime,
  LEX_lambda,
  LEX_tacka,
  LEX_lzag,
  LEX_dzag,
  LEX_EOF
} LEX_tip;

int LEX_slovo;
int LEX_koje_ime;
FILE *LEX_dat;

#define MAX_DUZINA_IMENA 32
#define MAX_BROJ_IMENA 1024

struct
{
  enum
  {
    NIJE,
    JESTE
  } dejstvo;
  char ime[MAX_DUZINA_IMENA+1];
} Imena[MAX_BROJ_IMENA];
int BrojImena;

void Error(char *s)
{
  fprintf(stderr,"%s\n",s);
  exit(1);
}

void LEX_scanner(void)
{
  enum
  {
    q0,
    q1,
    q2,
    qE
  } stanje=q0;
  char ime[MAX_DUZINA_IMENA+1];
  int duzina_imena;
  do
  {
    switch(stanje)
    {
      case q0:
        switch(LEX_slovo)
        {
          case (int)' ':
          case (int)'\t':
          case (int)'\n':
            break;
          case (int)'%':
            stanje=q1;
            break;
          case EOF:
            LEX_tip=LEX_EOF;
            stanje=qE;
            break;
          case (int)')':
            LEX_tip=LEX_dzag;
            stanje=qE;
            break;
          case (int)'(':
            LEX_tip=LEX_lzag;
            stanje=qE;
            break;
          case (int)'.':
            LEX_tip=LEX_tacka;
            stanje=qE;
            break;
          case (int)'#':
            LEX_tip=LEX_lambda;
            stanje=qE;
            break;
          default:
            LEX_tip=LEX_ime;
            stanje=q2;
            ime[0]=(char)LEX_slovo;
            duzina_imena=1;
        }
        break;
      case q1:
        switch(LEX_slovo)
        {
          case EOF:
            LEX_tip=LEX_EOF;
            stanje=qE;
            break;
          case (int)'\n':
            stanje=q0;
        }
        break;
      case q2:
        if
        (
          LEX_slovo==(int)' '||
          LEX_slovo==(int)'\t'||
          LEX_slovo==(int)'\n'||
          LEX_slovo==(int)'%'||
          LEX_slovo==EOF||
          LEX_slovo==(int)')'||
          LEX_slovo==(int)'('||
          LEX_slovo==(int)'.'||
          LEX_slovo==(int)'#'
        )
        {
          stanje=qE;
          ime[duzina_imena]='\0';
          LEX_koje_ime=0;
          while
          (
            LEX_koje_ime<BrojImena&&
            strcmp(Imena[LEX_koje_ime].ime,ime)
          )
            LEX_koje_ime++;
          if(LEX_koje_ime==BrojImena)
          {
            if(BrojImena==MAX_BROJ_IMENA)
              Error("Mnogo imena");
            Imena[BrojImena].dejstvo=NIJE;
            strcpy(Imena[BrojImena++].ime,ime);
          }
        }
        else
          if(duzina_imena<MAX_DUZINA_IMENA)
            ime[duzina_imena++]=(char)LEX_slovo;
    }
    if(stanje!=qE)
      LEX_slovo=fgetc(LEX_dat);
  }
  while(stanje!=qE);
  if(LEX_tip!=LEX_EOF&&LEX_tip!=LEX_ime)
    LEX_slovo=fgetc(LEX_dat);
}

struct Cvor
{
  enum
  {
    IME,
    KOMBINATOR,
    VARIJABLA,
    LAMBDA,
    APLIKACIJA
  } tip;
  enum
  {
    SADRZI_LAMBDA,
    SADRZI_IME,
    SADRZI_SLOBODNU
  } oznaka;
  int ime;
  struct Cvor *levo;
  struct Cvor *desno;
};

typedef struct Cvor *Drvo;

#define MAX_ALLOC 8192

struct Cvor AllocCvor[MAX_ALLOC];
int BrojAlloc;

Drvo NoviCvor(void)
{
  if(BrojAlloc==MAX_ALLOC)
    Error("Nema vise mesta");
  return AllocCvor+BrojAlloc++;
}

Drvo PARSER_izraz(void);

Drvo PARSER_faktor(void)
{
  Drvo d1;
  switch(LEX_tip)
  {
    case LEX_ime:
      d1=NoviCvor();
      d1->tip=IME;
      d1->ime=LEX_koje_ime;
      LEX_scanner();
      break;
    case LEX_lambda:
      LEX_scanner();
      {
        Drvo d2=NULL;
        do
        {
          if(LEX_tip!=LEX_ime)
            Error("Ocekivao sam imena pa .");
          if(d2==NULL)
          {
            d1=NoviCvor();
            d1->tip=LAMBDA;
            d1->ime=LEX_koje_ime;
            d2=d1;
          }
          else
          {
            d2->levo=NoviCvor();
            d2=d2->levo;
            d2->tip=LAMBDA;
            d2->ime=LEX_koje_ime;
          }
          LEX_scanner();
        }
        while(LEX_tip!=LEX_tacka);
        LEX_scanner();
        d2->levo=PARSER_izraz();
      }
      break;
    case LEX_lzag:
      LEX_scanner();
      d1=PARSER_izraz();
      if(LEX_tip!=LEX_dzag)
        Error("cekivao sam )");
      LEX_scanner();
      break;
    default:
      Error("Ocekivao sam ime, #, (");
  }
  return d1;
}

Drvo PARSER_izraz(void)
{
  Drvo d1=PARSER_faktor();
  while
  (
    LEX_tip!=LEX_dzag&&
    LEX_tip!=LEX_EOF
  )
  {
    Drvo d2=NoviCvor();
    d2->tip=APLIKACIJA;
    d2->levo=d1;
    d2->desno=PARSER_faktor();
    d1=d2;
  }
  return d1;
}

Drvo Parsiraj(FILE *f)
{
  Drvo d;
  BrojImena=0;
  LEX_dat=f;
  LEX_slovo=fgetc(LEX_dat);
  LEX_scanner();
  BrojAlloc=0;
  d=PARSER_izraz();
  if(LEX_tip!=LEX_EOF)
    Error("Ima jos znakova na ulazu");
  return d;
}

FILE *StampajDat;

void Stampaj(Drvo d)
{
  switch(d->tip)
  {
    case IME:
      fputs(Imena[d->ime].ime,StampajDat);
      break;
    case KOMBINATOR:
      fprintf(StampajDat,"@%d",d->ime);
      break;
    case VARIJABLA:
      fprintf(StampajDat,"$%d",d->ime);
      break;
    case LAMBDA:
      fprintf(StampajDat,"# %s . ",Imena[d->ime].ime);
      Stampaj(d->levo);
      break;
    case APLIKACIJA:
      Stampaj(d->levo);
      fputc((int)' ',StampajDat);
      if(
        d->desno->tip==APLIKACIJA||
        d->desno->tip==LAMBDA
      )
      {
        fputc((int)'(',StampajDat);
        Stampaj(d->desno);
        fputc((int)')',StampajDat);
      }
      else
        Stampaj(d->desno);
  }
}

void StampajDrvo(FILE *f,Drvo d)
{
  StampajDat=f;
  Stampaj(d);
  fputc((int)'\n',f);
}

int SadrziLambda(Drvo d)
{
  if(d->tip==LAMBDA)
    return 1;
  if(d->tip==APLIKACIJA)
    return SadrziLambda(d->levo)||SadrziLambda(d->desno);
  return 0;
}

Drvo KopirajCvor(Drvo d)
{
  Drvo p=NoviCvor();
  p->tip=d->tip;
  p->ime=d->ime;
  p->levo=d->levo;
  p->desno=d->desno;
  return p;
}

#define MAX_BROJ_KOMBINATORA 8192

struct
{
  int varijabli;
  Drvo zamena;
} Kombinatori[MAX_BROJ_KOMBINATORA];
int BrojKombinatora;

int Vezana;

void ZameniVezanu(Drvo d)
{
  switch(d->tip)
  {
    case APLIKACIJA:
      ZameniVezanu(d->levo);
      ZameniVezanu(d->desno);
      break;
    case IME:
      if(d->ime==Vezana)
      {
        d->tip=VARIJABLA;
        d->ime=Kombinatori[BrojKombinatora].varijabli;
      }
  }
}

void OznaciMFES(Drvo d)
{
  switch(d->tip)
  {
    case APLIKACIJA:
      OznaciMFES(d->levo);
      OznaciMFES(d->desno);
      d->oznaka=d->levo->oznaka==SADRZI_LAMBDA?
        SADRZI_LAMBDA:
        d->levo->oznaka==SADRZI_IME?
          d->desno->oznaka:
          d->desno->oznaka==SADRZI_LAMBDA?
            SADRZI_LAMBDA:
            SADRZI_SLOBODNU;
      break;
    case IME:
      d->oznaka=d->ime==Vezana?
        SADRZI_LAMBDA:
        Imena[d->ime].dejstvo==NIJE?
          SADRZI_IME:
          SADRZI_SLOBODNU;
      break;
    default:
      d->oznaka=SADRZI_LAMBDA;
  }
}

Drvo Kicma;

void PronadjiVarijable(Drvo d)
{
  if(d->oznaka==SADRZI_SLOBODNU)
  {
    Drvo d1=KopirajCvor(Kicma);
    Drvo d2=KopirajCvor(d);
    Kicma->tip=APLIKACIJA;
    Kicma->levo=d1;
    Kicma->desno=d2;
    d->tip=VARIJABLA;
    d->ime=Kombinatori[BrojKombinatora].varijabli++;
  }
  else
    if(d->tip==APLIKACIJA)
    {
      PronadjiVarijable(d->levo);
      PronadjiVarijable(d->desno);
    }
}

void SCAF(Drvo d)
{
  switch(d->tip)
  {
    case APLIKACIJA:
      SCAF(d->levo);
      SCAF(d->desno);
      break;
    case LAMBDA:
      Imena[d->ime].dejstvo=JESTE;
      if(SadrziLambda(d->levo))
        SCAF(d->levo);
      Vezana=d->ime;
      OznaciMFES(d->levo);
      if(BrojKombinatora==MAX_BROJ_KOMBINATORA)
        Error("Mnogo kombinatora");
      Kombinatori[BrojKombinatora].zamena=d->levo;
      Kicma=d;
      Kicma->tip=KOMBINATOR;
      Kicma->ime=BrojKombinatora;
      Kombinatori[BrojKombinatora].varijabli=0;
      PronadjiVarijable(Kombinatori[BrojKombinatora].zamena);
      ZameniVezanu(Kombinatori[BrojKombinatora].zamena);
      Kombinatori[BrojKombinatora++].varijabli++;
      Imena[Vezana].dejstvo=NIJE;
  }
}

void StampajSCAF(FILE *in,FILE *out)
{
  int i;
  Drvo d=Parsiraj(in);
  BrojKombinatora=0;
  SCAF(d);
  StampajDrvo(out,d);
  for(i=0;i<BrojKombinatora;i++)
  {
    fprintf(out,"@%d(%d) = ",i,Kombinatori[i].varijabli);
    StampajDrvo(out,Kombinatori[i].zamena);
  }
}

int main(void)
{
  StampajSCAF(stdin,stdout);
  return 0;
}
