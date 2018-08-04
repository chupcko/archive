#include <stdlib.h>
#include <string.h>
#include "azot.h"
#include "lexana.h"
#include "regexp.h"
#include "semdom.h"

String *Novi_string(void)
{
  String *s;
  s=(String *)malloc(sizeof(String));
  if(s==NULL)
    LA_error("Nema vise mesta za stringove");
  return s;
}

void Konkatenacija(String d,String s)
{
  int i;
  int j;
  i=0;
  while(d[i]!='\0')
    i++;
  j=0;
  while(i<MAX_DUZINA_STRINGA&&s[j]!='\0')
  {
    d[i]=s[j];
    i++;
    j++;
  }
  d[i]='\0';
}

void Kopiraj_string_od_do(String d,String s,int i,int j)
{
  int l;
  l=0;
  while(i+l<j&&s[i+l]!='\0')
  {
    d[l]=s[i+l];
    l++;
  }
  d[l]='\0';
}

Array *Novi_niz(void)
{
  Array *n;
  n=(Array *)malloc(sizeof(Array));
  if(n==NULL)
    LA_error("Nema vise memorije za niz");
  n->max_broj_indeksa=MAX_BROJ_INDEKSA;
  n->indeksi=(Indeks *)calloc(n->max_broj_indeksa,sizeof(Indeks));
  if(n->indeksi==NULL)
    LA_error("Nema vise memorije za indekse");
  n->broj_indeksa=0;
  return n;
}

void Oslobodi_celiju(Celija *c)
{
  if(c->tip==Tip_string)
    free(c->vrednost.v_string);
}

int Celija_nije_prostog_tipa(Celija *c)
{
  return
    c->tip!=Tip_bool&&
    c->tip!=Tip_integer&&
    c->tip!=Tip_real&&
    c->tip!=Tip_string;
}

#define sign(x) (x)<0?-1:(x)==0?0:1

int Uporedi_celije(Celija *x,Celija *y)
{
  int b;
  switch(x->tip)
  {
    case Tip_bool:
      Konvertuj_celiju_u_bool(y);
      return !!x->vrednost.v_bool-!!y->vrednost.v_bool;
      break;
    case Tip_integer:
      Konvertuj_celiju_u_integer(y);
      return sign(x->vrednost.v_integer-y->vrednost.v_integer);
      break;
    case Tip_real:
      Konvertuj_celiju_u_real(y);
      return sign(x->vrednost.v_real-y->vrednost.v_real);
      break;
    case Tip_string:
      Konvertuj_celiju_u_string(y);
      b=strncmp(*x->vrednost.v_string,*y->vrednost.v_string,sizeof(String));
      Oslobodi_celiju(y);
      return b;
      break;
    default:
      return 0;
  }
}

void Konvertuj_celiju_u_bool(Celija *c)
{
  int b;
  if(c->tip!=Tip_bool)
  {
    switch(c->tip)
    {
      case Tip_integer:
        b=c->vrednost.v_integer!=0;
        break;
      case Tip_real:
        b=c->vrednost.v_real!=0.0;
        break;
      case Tip_string:
        b=strlen(*c->vrednost.v_string);
        Oslobodi_celiju(c);
        break;
      case Tip_celija:
      case Tip_unknown:
        b=0;
        break;
      default:
        LA_error("Ne mogu konvertovati u bool");
    }
    c->tip=Tip_bool;
    c->vrednost.v_bool=b;
  }
}

void Konvertuj_celiju_u_integer(Celija *c)
{
  long l;
  if(c->tip!=Tip_integer)
  {
    switch(c->tip)
    {
      case Tip_bool:
        l=c->vrednost.v_bool?1l:0;
        break;
      case Tip_real:
        l=(long)c->vrednost.v_real;
        break;
      case Tip_string:
        if(sscanf(*c->vrednost.v_string,"%ld",&l)!=1)
          l=0;
        Oslobodi_celiju(c);
        break;
      case Tip_celija:
      case Tip_unknown:
        l=0;
        break;
      default:
        LA_error("Ne mogu konvertovati u integer");
    }
    c->tip=Tip_integer;
    c->vrednost.v_integer=l;
  }
}

void Konvertuj_celiju_u_real(Celija *c)
{
  double d;
  if(c->tip!=Tip_real)
  {
    switch(c->tip)
    {
      case Tip_bool:
        d=c->vrednost.v_bool?1.0:0.0;
        break;
      case Tip_integer:
        d=(double)c->vrednost.v_integer;
        break;
      case Tip_real:
        break;
      case Tip_string:
        if(sscanf(*c->vrednost.v_string,"%lg",&d)!=1)
          d=0.0;
        Oslobodi_celiju(c);
        break;
      case Tip_celija:
      case Tip_unknown:
        d=0.0;
        break;
      default:
        LA_error("Ne mogu konvertovati u real");
    }
    c->tip=Tip_real;
    c->vrednost.v_real=d;
  }
}

void Konvertuj_celiju_u_string(Celija *c)
{
  String *s;
  if(c->tip!=Tip_string)
  {
    switch(c->tip)
    {
      case Tip_bool:
        s=Novi_string();
        strcpy(*s,c->vrednost.v_bool?"True":"False");
        break;
      case Tip_integer:
        s=Novi_string();
        sprintf(*s,"%ld",c->vrednost.v_integer);
        break;
      case Tip_real:
        s=Novi_string();
        sprintf(*s,"%g",c->vrednost.v_real);
        break;
      case Tip_string:
        break;
      case Tip_celija:
      case Tip_unknown:
        s=Novi_string();
        *s[0]='\0';
        break;
      default:
        LA_error("Ne mogu konvertovati u string");
    }
    c->tip=Tip_string;
    c->vrednost.v_string=s;
  }
}

void Konvertuj_celiju_u_niz(Celija *c)
{
  if(c->tip!=Tip_array)
  {
    if(c->tip==Tip_celija)
    {
      c->vrednost.v_celija->tip=Tip_array;
      c->vrednost.v_celija->vrednost.v_array=Novi_niz();
      c->tip=Tip_array;
      c->vrednost.v_array=c->vrednost.v_celija->vrednost.v_array;
    }
    else
      LA_error("Ne mogu konvertvati u niz");
  }
}

void Konvertuj_celiju_u_file(Celija *c)
{
  if(c->tip!=Tip_file)
  {
    if(c->tip==Tip_celija)
    {
      if(Broj_datoteka==MAX_BROJ_DATOTEKA)
        LA_error("Mnogo datoteka");
      c->vrednost.v_celija->tip=Tip_file;
      c->vrednost.v_celija->vrednost.v_file=Broj_datoteka;
      c->tip=Tip_file;
      c->vrednost.v_file=Broj_datoteka;
      Broj_datoteka++;
    }
    else
      LA_error("Ne mogu konvertovati u datoteku");
  }
}

void Konvertuj_celiju_u_indeks(Celija *c)
{
  if(Celija_nije_prostog_tipa(c))
    if(c->tip==Tip_celija||c->tip==Tip_unknown)
      Konvertuj_celiju_u_integer(c);
    else
      LA_error("Indeks moze biti samo prost tip");
}

void Kopiraj_celiju(Celija *d,Celija *s,int tvrdo)
{
  d->tip=s->tip;
  switch(s->tip)
  {
    case Tip_bool:
      d->vrednost.v_bool=s->vrednost.v_bool;
      break;
    case Tip_integer:
      d->vrednost.v_integer=s->vrednost.v_integer;
      break;
    case Tip_real:
      d->vrednost.v_real=s->vrednost.v_real;
      break;
    case Tip_string:
      if(tvrdo)
      {
        d->vrednost.v_string=Novi_string();
        strncpy(*d->vrednost.v_string,*s->vrednost.v_string,sizeof(String));
      }
      else
        d->vrednost.v_string=s->vrednost.v_string;
      break;
    case Tip_array:
      d->vrednost.v_array=s->vrednost.v_array;
      break;
    case Tip_file:
      d->vrednost.v_file=s->vrednost.v_file;
      break;
    case Tip_func_proc:
    case Tip_function:
    case Tip_procedure:
      d->vrednost.v_func_proc=s->vrednost.v_func_proc;
      break;
    case Tip_celija:
      d->vrednost.v_celija=s->vrednost.v_celija;
  }
}

int Jeste_indeks(Array *niz,int i,Celija *c)
{
  if(c->tip!=niz->indeksi[i].indeks.tip)
    return 0;
  switch(c->tip)
  {
     case Tip_bool:
       return !!niz->indeksi[i].indeks.vrednost.v_bool==!!c->vrednost.v_bool;
     case Tip_integer:
       return niz->indeksi[i].indeks.vrednost.v_integer==c->vrednost.v_integer;
     case Tip_real:
       return niz->indeksi[i].indeks.vrednost.v_real==c->vrednost.v_real;
     case Tip_string:
       return !strncmp(*niz->indeksi[i].indeks.vrednost.v_string,*c->vrednost.v_string,sizeof(String));
  }
}

int Pronadji_indeks(Array *niz,Celija *c)
{
  int i;
  Konvertuj_celiju_u_indeks(c);
  i=0;
  while(i<niz->broj_indeksa&&!Jeste_indeks(niz,i,c))
    i++;
  return i;
}

Celija *Ubaci_indeks(Array *niz,Celija *indeks)
{
  int i;
  i=Pronadji_indeks(niz,indeks);
  if(i==niz->broj_indeksa)
  {
    if(niz->broj_indeksa==niz->max_broj_indeksa)
    {
      niz->max_broj_indeksa+=MAX_BROJ_INDEKSA;
      niz->indeksi=(Indeks *)realloc(niz->indeksi,sizeof(Indeks)*(long)niz->max_broj_indeksa);
      if(niz->indeksi==NULL)
        LA_error("Mnogo indeksa");
    }
    Kopiraj_celiju(&niz->indeksi[i].indeks,indeks,0);
    niz->indeksi[i].celija.tip=Tip_unknown;
    niz->broj_indeksa++;
  }
  else
    Oslobodi_celiju(indeks);
  return &niz->indeksi[i].celija;
}

void Obrisi_niz(Array *niz)
{
  int i;
  for(i=0;i<niz->broj_indeksa;i++)
  {
    Oslobodi_celiju(&niz->indeksi[i].indeks);
    Oslobodi_celiju(&niz->indeksi[i].celija);
  }
  niz->broj_indeksa=0;
}

void Obrisi_indeks(Array *niz,Celija *c)
{
  int i;
  int j;
  i=Pronadji_indeks(niz,c);
  if(i!=niz->broj_indeksa)
  {
    for(j=i+1;j<niz->broj_indeksa;j++)
    {
      Oslobodi_celiju(&niz->indeksi[j-1].indeks);
      Oslobodi_celiju(&niz->indeksi[j-1].celija);
      Kopiraj_celiju(&niz->indeksi[j-1].indeks,&niz->indeksi[j].indeks,0);
      Kopiraj_celiju(&niz->indeksi[j-1].celija,&niz->indeksi[j].celija,0);
    }
    niz->broj_indeksa--;
  }
}

int Uporedi_indekse_indeks(Indeks *x,Indeks *y)
{
  Celija c;
  Kopiraj_celiju(&c,&y->indeks,1);
  return Uporedi_celije(&x->indeks,&c);
}

int Uporedi_indekse_celija(Indeks *x,Indeks *y)
{
  Celija c;
  Kopiraj_celiju(&c,&y->celija,1);
  return Uporedi_celije(&x->celija,&c);
}

void Proveri_broj_argumenata(int i)
{
  if(Dubina_steka-Pozivi_func_proc[Broj_poziva_func_proc-1].stek!=i)
    LA_error("Pogresan broj argumenata");
}

void Proveri_najmanji_broj_argumenata(int i)
{
  if(Dubina_steka-Pozivi_func_proc[Broj_poziva_func_proc-1].stek<i)
    LA_error("Pogresan broj argumenata");
}

void Proveri_od_do_broj_argumenata(int i,int j)
{
  if
  (
    Dubina_steka-Pozivi_func_proc[Broj_poziva_func_proc-1].stek<i||
    Dubina_steka-Pozivi_func_proc[Broj_poziva_func_proc-1].stek>j
  )
    LA_error("Pogresan broj argumenata");
}

void SD_init(void)
{
  Radi=R_normal;
  Broj_func_proc=0;
  Datoteke[0]=stdin;
  Datoteke[1]=stdout;
  Broj_datoteka=2;
  Broj_varijabli=0;
  Broj_poziva_func_proc=0;
  Pravi_poziv_func_proc=-1;
  Dubina_steka=0;
  RE_cache_init();
}
