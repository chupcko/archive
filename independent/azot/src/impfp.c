#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "aprcom.h"
#include "regexp.h"
#include "semdom.h"
#include "setof.h"

char Error_msg[256];

void IF_abs(void)
{
  Proveri_broj_argumenata(1);
  if(Stek[Dubina_steka-1].tip==Tip_integer)
    Stek[Dubina_steka-1].vrednost.v_integer=labs(Stek[Dubina_steka-1].vrednost.v_integer);
  else
  {
    Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
    Stek[Dubina_steka-1].vrednost.v_real=fabs(Stek[Dubina_steka-1].vrednost.v_real);
  }
}

void IF_aprcmp(void)
{
  AC_uzorak u;
  long l;
  Proveri_broj_argumenata(2);
  Dubina_steka--;
  Konvertuj_celiju_u_string(&Stek[Dubina_steka-1]);
  Konvertuj_celiju_u_string(&Stek[Dubina_steka]);
  if(AC_parser(*Stek[Dubina_steka-1].vrednost.v_string,&u))
  {
    sprintf(Error_msg,"Pozicija:%d, %s",AC_pos,AC_error);
    LA_error(Error_msg);
  }
  l=AC_acs(&u,*Stek[Dubina_steka].vrednost.v_string,0);
  Oslobodi_celiju(&Stek[Dubina_steka-1]);
  Oslobodi_celiju(&Stek[Dubina_steka]);
  Stek[Dubina_steka-1].tip=Tip_integer;
  Stek[Dubina_steka-1].vrednost.v_integer=l;
}

void IF_bool(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_bool(&Stek[Dubina_steka-1]);
}

void IF_acos(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_real=acos(Stek[Dubina_steka-1].vrednost.v_real);
}

void IF_asin(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_real=asin(Stek[Dubina_steka-1].vrednost.v_real);
}

void IF_atan(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_real=atan(Stek[Dubina_steka-1].vrednost.v_real);
}

void IF_ceil(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_real=ceil(Stek[Dubina_steka-1].vrednost.v_real);
}

void IF_chop(void)
{
  int i;
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_string(&Stek[Dubina_steka-1]);
  i=0;
  while((*Stek[Dubina_steka-1].vrednost.v_string)[i]!='\0')
    i++;
  if(i>0&&(*Stek[Dubina_steka-1].vrednost.v_string)[i-1]=='\n')
    (*Stek[Dubina_steka-1].vrednost.v_string)[i-1]='\0';
}

void IF_cos(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_real=cos(Stek[Dubina_steka-1].vrednost.v_real);
}

void IF_cosh(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_real=cosh(Stek[Dubina_steka-1].vrednost.v_real);
}

int eof(FILE *f)
{
  int i=fgetc(f);
  if(i!=EOF)
    ungetc(i,f);
  return i==EOF;
}

void IF_eof(void)
{
  Proveri_od_do_broj_argumenata(0,1);
  if(Dubina_steka==Pozivi_func_proc[Broj_poziva_func_proc-1].stek)
  {
    Stek[Dubina_steka].tip=Tip_bool;
    Stek[Dubina_steka].vrednost.v_bool=eof(stdin);
    Dubina_steka++;
  }
  else
  {
    Konvertuj_celiju_u_file(&Stek[Dubina_steka-1]);
    Stek[Dubina_steka-1].tip=Tip_bool;
    Stek[Dubina_steka-1].vrednost.v_bool=eof(Datoteke[Stek[Dubina_steka-1].vrednost.v_file]);
  }
}

void IF_exp(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_real=exp(Stek[Dubina_steka-1].vrednost.v_real);
}

void IF_floor(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_real=floor(Stek[Dubina_steka-1].vrednost.v_real);
}

void IF_fill(void)
{
  int i;
  String *s;
  Proveri_broj_argumenata(2);
  Dubina_steka--;
  Konvertuj_celiju_u_string(&Stek[Dubina_steka-1]);
  Konvertuj_celiju_u_integer(&Stek[Dubina_steka]);
  s=Novi_string();
  (*s)[0]='\0';
  for(i=0;i<Stek[Dubina_steka].vrednost.v_integer;i++)
    Konkatenacija(*s,*Stek[Dubina_steka-1].vrednost.v_string);
  Oslobodi_celiju(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_string=s;
}

void IF_getenv(void)
{
  char *s;
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_string(&Stek[Dubina_steka-1]);
  s=getenv(*Stek[Dubina_steka-1].vrednost.v_string);
  if(s==NULL)
    (*Stek[Dubina_steka-1].vrednost.v_string)[0]='\0';
  else
    strncpy(*Stek[Dubina_steka-1].vrednost.v_string,s,sizeof(String));
}

void IF_input(void)
{
  int i;
  int c;
  String *s;
  Proveri_od_do_broj_argumenata(0,1);
  if(Dubina_steka==Pozivi_func_proc[Broj_poziva_func_proc-1].stek)
  {
    s=Novi_string();
    if(fgets(*s,MAX_DUZINA_STRINGA,stdin)==NULL)
      (*s)[0]='\0';
    Stek[Dubina_steka].tip=Tip_string;
    Stek[Dubina_steka].vrednost.v_string=s;
    Dubina_steka++;
  }
  else
    if(Stek[Dubina_steka-1].tip==Tip_string)
    {
      int d;
      d=(int)(*Stek[Dubina_steka-1].vrednost.v_string)[0];
      i=0;
      do
      {
        c=getchar();
        if(c!=d&&c!=EOF)
        {
          (*Stek[Dubina_steka-1].vrednost.v_string)[i]=(char)c;
          i++;
        }
      }
      while(i<MAX_DUZINA_STRINGA&&c!=d&&c!=EOF);
      (*Stek[Dubina_steka-1].vrednost.v_string)[i]='\0';
    }
    else
    {
      Konvertuj_celiju_u_integer(&Stek[Dubina_steka-1]);
      if(Stek[Dubina_steka-1].vrednost.v_integer>MAX_DUZINA_STRINGA)
        Stek[Dubina_steka-1].vrednost.v_integer=MAX_DUZINA_STRINGA;
      s=Novi_string();
      i=0;
      do
      {
        c=getchar();
        if(c!=EOF)
        {
          (*s)[i]=(char)c;
          i++;
        }
      }
      while(i<Stek[Dubina_steka-1].vrednost.v_integer&&c!=EOF);
      (*s)[i]='\0';
      Stek[Dubina_steka-1].tip=Tip_string;
      Stek[Dubina_steka-1].vrednost.v_string=s;
    }
}

void IF_integer(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_integer(&Stek[Dubina_steka-1]);
}

void IF_lenght(void)
{
  Proveri_broj_argumenata(1);
  if(Stek[Dubina_steka-1].tip==Tip_array)
  {
    Stek[Dubina_steka-1].tip=Tip_integer;
    Stek[Dubina_steka-1].vrednost.v_integer=(long)Stek[Dubina_steka-1].vrednost.v_array->broj_indeksa;
  }
  else
  {
    long l;
    Konvertuj_celiju_u_string(&Stek[Dubina_steka-1]);
    l=strlen(*Stek[Dubina_steka-1].vrednost.v_string);
    Oslobodi_celiju(&Stek[Dubina_steka-1]);
    Stek[Dubina_steka-1].tip=Tip_integer;
    Stek[Dubina_steka-1].vrednost.v_integer=l;
  }
}

void IF_log(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_real=log(Stek[Dubina_steka-1].vrednost.v_real);
}

void IF_log10(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_real=log10(Stek[Dubina_steka-1].vrednost.v_real);
}

void IF_pow(void)
{
  Proveri_broj_argumenata(2);
  Dubina_steka--;
  if
  (
    Stek[Dubina_steka-1].tip==Tip_integer&&
    Stek[Dubina_steka].tip==Tip_integer&&
    Stek[Dubina_steka].vrednost.v_integer>=0
  )
  {
    long l;
    while(Stek[Dubina_steka].vrednost.v_integer>0)
    {
      l*=Stek[Dubina_steka-1].vrednost.v_integer;
      Stek[Dubina_steka].vrednost.v_integer--;
    }
    Stek[Dubina_steka-1].vrednost.v_integer=l;
  }
  else
  {
    Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
    Konvertuj_celiju_u_real(&Stek[Dubina_steka]);
    Stek[Dubina_steka-1].vrednost.v_real=pow(Stek[Dubina_steka-1].vrednost.v_real,Stek[Dubina_steka].vrednost.v_real);
  }
}

void IF_read(void)
{
  int i;
  int c;
  String *s;
  Proveri_od_do_broj_argumenata(1,2);
  Konvertuj_celiju_u_file(&Stek[Pozivi_func_proc[Broj_poziva_func_proc-1].stek]);
  s=Novi_string();
  if(Dubina_steka-Pozivi_func_proc[Broj_poziva_func_proc-1].stek==2)
  {
    Dubina_steka--;
    if(Stek[Dubina_steka].tip==Tip_string)
    {
      i=0;
      do
      {
        c=fgetc(Datoteke[Stek[Dubina_steka-1].vrednost.v_file]);
        if(c!=(int)(*Stek[Dubina_steka].vrednost.v_string)[0]&&c!=EOF)
        {
          (*s)[i]=(char)c;
          i++;
        }
      }
      while
      (
        i<MAX_DUZINA_STRINGA&&
        c!=(int)(*Stek[Dubina_steka].vrednost.v_string)[0]&&
        c!=EOF
      );
      (*s)[i]='\0';
      Oslobodi_celiju(&Stek[Dubina_steka]);
    }
    else
    {
      Konvertuj_celiju_u_integer(&Stek[Dubina_steka]);
      if(Stek[Dubina_steka].vrednost.v_integer>MAX_DUZINA_STRINGA)
        Stek[Dubina_steka].vrednost.v_integer=MAX_DUZINA_STRINGA;
      i=0;
      do
      {
        c=fgetc(Datoteke[Stek[Dubina_steka-1].vrednost.v_file]);
        if(c!=EOF)
        {
          (*s)[i]=(char)c;
          i++;
        }
      }
      while(i<Stek[Dubina_steka].vrednost.v_integer&&c!=EOF);
      (*s)[i]='\0';
    }
  }
  else
    if(fgets(*s,MAX_DUZINA_STRINGA,Datoteke[Stek[Dubina_steka-1].vrednost.v_file])==NULL)
      (*s)[0]='\0';
  Stek[Dubina_steka-1].tip=Tip_string;
  Stek[Dubina_steka-1].vrednost.v_string=s;
}

void IF_real(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
}

void IF_regexp(void)
{
  RE_KA *ka;
  RE_run_results rr;
  Proveri_od_do_broj_argumenata(2,3);
  if(Dubina_steka-Pozivi_func_proc[Broj_poziva_func_proc-1].stek==2)
  {
    Dubina_steka--;
    Konvertuj_celiju_u_string(&Stek[Dubina_steka-1]);
    Konvertuj_celiju_u_string(&Stek[Dubina_steka]);
    ka=RE_cache_find(*Stek[Dubina_steka].vrednost.v_string);
    if
    (
      ka==NULL||
      RE_run_init(ka,&rr)||
      RE_run(ka,*Stek[Dubina_steka-1].vrednost.v_string,&rr,0)
    )
    {
      sprintf(Error_msg,"Pozicija:%d, %s",RE_pos,RE_error);
      LA_error(Error_msg);
    }
  }
  else
  {
    Dubina_steka-=2;
    Konvertuj_celiju_u_string(&Stek[Dubina_steka-1]);
    Konvertuj_celiju_u_string(&Stek[Dubina_steka]);
    Konvertuj_celiju_u_niz(&Stek[Dubina_steka+1]);
    Obrisi_niz(Stek[Dubina_steka+1].vrednost.v_array);
    ka=RE_cache_find(*Stek[Dubina_steka].vrednost.v_string);
    if
    (
      ka==NULL||
      RE_run_init(ka,&rr)||
      RE_run(ka,*Stek[Dubina_steka-1].vrednost.v_string,&rr,0)
    )
    {
      sprintf(Error_msg,"Pozicija:%d, %s",RE_pos,RE_error);
      LA_error(Error_msg);
    }
    if(rr.nasao)
    {
      Celija c;
      Celija *p;
      int i;
      c.tip=Tip_string;
      c.vrednost.v_string=Novi_string();
      strcpy(*c.vrednost.v_string,"a");
      p=Ubaci_indeks(Stek[Dubina_steka+1].vrednost.v_array,&c);
      p->tip=Tip_string;
      p->vrednost.v_string=Novi_string();
      Kopiraj_string_od_do(*p->vrednost.v_string,*Stek[Dubina_steka-1].vrednost.v_string,rr.kraj,MAX_DUZINA_STRINGA);
      c.vrednost.v_string=Novi_string();
      strcpy(*c.vrednost.v_string,"b");
      p=Ubaci_indeks(Stek[Dubina_steka+1].vrednost.v_array,&c);
      p->tip=Tip_string;
      p->vrednost.v_string=Novi_string();
      Kopiraj_string_od_do(*p->vrednost.v_string,*Stek[Dubina_steka-1].vrednost.v_string,0,rr.pocetak);
      c.vrednost.v_string=Novi_string();
      strcpy(*c.vrednost.v_string,"n");
      p=Ubaci_indeks(Stek[Dubina_steka+1].vrednost.v_array,&c);
      p->tip=Tip_integer;
      p->vrednost.v_integer=rr.broj_manje_vece;
      c.vrednost.v_string=Novi_string();
      strcpy(*c.vrednost.v_string,"s");
      p=Ubaci_indeks(Stek[Dubina_steka+1].vrednost.v_array,&c);
      p->tip=Tip_string;
      p->vrednost.v_string=Novi_string();
      (*p->vrednost.v_string)[0]='\0';
      for(i=0;i<rr.broj_akcija;i++)
        Konkatenacija(*p->vrednost.v_string,ka->akcije[rr.akcije[i]].ime);
      c.tip=Tip_integer;
      c.vrednost.v_integer=0;
      p=Ubaci_indeks(Stek[Dubina_steka+1].vrednost.v_array,&c);
      p->tip=Tip_string;
      p->vrednost.v_string=Novi_string();
      Kopiraj_string_od_do(*p->vrednost.v_string,*Stek[Dubina_steka-1].vrednost.v_string,rr.pocetak,rr.kraj);
      for(i=0;i<rr.broj_manje_vece;i++)
        if(rr.manje_vece[i].nasao)
        {
          c.vrednost.v_integer=(long)(i+1);
          p=Ubaci_indeks(Stek[Dubina_steka+1].vrednost.v_array,&c);
          p->tip=Tip_string;
          p->vrednost.v_string=Novi_string();
          Kopiraj_string_od_do(*p->vrednost.v_string,*Stek[Dubina_steka-1].vrednost.v_string,rr.manje_vece[i].pocetak,rr.manje_vece[i].kraj);
        }
    }
  }
  RE_free_run_results(&rr);
  Oslobodi_celiju(&Stek[Dubina_steka-1]);
  Oslobodi_celiju(&Stek[Dubina_steka]);
  Stek[Dubina_steka-1].tip=Tip_bool;
  Stek[Dubina_steka-1].vrednost.v_bool=rr.nasao;
}

void IF_scan(void)
{
  RE_KA *ka;
  RE_frun_results fr;
  Proveri_od_do_broj_argumenata(2,3);
  if(Dubina_steka-Pozivi_func_proc[Broj_poziva_func_proc-1].stek==2)
  {
    Dubina_steka--;
    Konvertuj_celiju_u_file(&Stek[Dubina_steka-1]);
    Konvertuj_celiju_u_string(&Stek[Dubina_steka]);
    ka=RE_cache_find(*Stek[Dubina_steka].vrednost.v_string);
    if
    (
      ka==NULL||
      RE_frun_init(ka,sizeof(String),&fr)||
      RE_frun(ka,Datoteke[Stek[Dubina_steka-1].vrednost.v_file],&fr,0)
    )
    {
      sprintf(Error_msg,"Pozicija:%d, %s",RE_pos,RE_error);
      LA_error(Error_msg);
    }
  }
  else
  {
    Dubina_steka-=2;
    Konvertuj_celiju_u_file(&Stek[Dubina_steka-1]);
    Konvertuj_celiju_u_string(&Stek[Dubina_steka]);
    Konvertuj_celiju_u_niz(&Stek[Dubina_steka+1]);
    Obrisi_niz(Stek[Dubina_steka+1].vrednost.v_array);
    ka=RE_cache_find(*Stek[Dubina_steka].vrednost.v_string);
    if
    (
      ka==NULL||
      RE_frun_init(ka,sizeof(String),&fr)||
      RE_frun(ka,Datoteke[Stek[Dubina_steka-1].vrednost.v_file],&fr,0)
    )
    {
      sprintf(Error_msg,"Pozicija:%d, %s",RE_pos,RE_error);
      LA_error(Error_msg);
    }
    if(fr.nasao)
    {
      Celija c;
      Celija *p;
      int i;
      c.tip=Tip_string;
      c.vrednost.v_string=Novi_string();
      strcpy(*c.vrednost.v_string,"n");
      p=Ubaci_indeks(Stek[Dubina_steka+1].vrednost.v_array,&c);
      p->tip=Tip_integer;
      p->vrednost.v_integer=fr.broj_manje_vece;
      c.vrednost.v_string=Novi_string();
      strcpy(*c.vrednost.v_string,"s");
      p=Ubaci_indeks(Stek[Dubina_steka+1].vrednost.v_array,&c);
      p->tip=Tip_string;
      p->vrednost.v_string=Novi_string();
      (*p->vrednost.v_string)[0]='\0';
      for(i=0;i<fr.broj_akcija;i++)
        Konkatenacija(*p->vrednost.v_string,ka->akcije[fr.akcije[i]].ime);
      c.tip=Tip_integer;
      c.vrednost.v_integer=0;
      p=Ubaci_indeks(Stek[Dubina_steka+1].vrednost.v_array,&c);
      p->tip=Tip_string;
      p->vrednost.v_string=Novi_string();
      strncpy(*p->vrednost.v_string,fr.vrednost,sizeof(String));
      for(i=0;i<fr.broj_manje_vece;i++)
        if(fr.manje_vece[i].nasao)
        {
          c.vrednost.v_integer=(long)(i+1);
          p=Ubaci_indeks(Stek[Dubina_steka+1].vrednost.v_array,&c);
          p->tip=Tip_string;
          p->vrednost.v_string=Novi_string();
          Kopiraj_string_od_do(*p->vrednost.v_string,fr.vrednost,fr.manje_vece[i].pocetak,fr.manje_vece[i].kraj);
        }
    }
  }
  RE_free_frun_results(&fr);
  Oslobodi_celiju(&Stek[Dubina_steka]);
  Stek[Dubina_steka-1].tip=Tip_bool;
  Stek[Dubina_steka-1].vrednost.v_bool=fr.nasao;
}

void IF_sin(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_real=sin(Stek[Dubina_steka-1].vrednost.v_real);
}

void IF_sinh(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_real=sinh(Stek[Dubina_steka-1].vrednost.v_real);
}

void IF_sqrt(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_real=sqrt(Stek[Dubina_steka-1].vrednost.v_real);
}

void IF_string(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_string(&Stek[Dubina_steka-1]);
}

void IF_substitute(void)
{
  RE_KA *ka;
  RE_run_results rr;
  String *s;
  s=Novi_string();
  Proveri_broj_argumenata(3);
  Dubina_steka-=2;
  Konvertuj_celiju_u_string(&Stek[Dubina_steka-1]);
  Konvertuj_celiju_u_string(&Stek[Dubina_steka]);
  Konvertuj_celiju_u_string(&Stek[Dubina_steka+1]);
  strncpy(*s,*Stek[Dubina_steka-1].vrednost.v_string,sizeof(String));
  ka=RE_cache_find(*Stek[Dubina_steka].vrednost.v_string);
  if
  (
    ka==NULL||
    RE_run_init(ka,&rr)
  )
  {
    sprintf(Error_msg,"Regularni izraz u substitute: %d, %s",RE_pos,RE_error);
    LA_error(Error_msg);
  }
  (*Stek[Dubina_steka-1].vrednost.v_string)[0]='\0';
  do
  {
    if(RE_run(ka,*s,&rr,0))
    {
      sprintf(Error_msg,"Regularni izraz u substitute: %d, %s",RE_pos,RE_error);
      LA_error(Error_msg);
    }
    if(rr.nasao)
    {
      long l;
      l=strlen(*Stek[Dubina_steka-1].vrednost.v_string);
      Konkatenacija(*Stek[Dubina_steka-1].vrednost.v_string,*s);
      (*Stek[Dubina_steka-1].vrednost.v_string)[l+rr.pocetak]='\0';
      Konkatenacija(*Stek[Dubina_steka-1].vrednost.v_string,*Stek[Dubina_steka+1].vrednost.v_string);
      Kopiraj_string_od_do(*s,*s,rr.kraj,MAX_DUZINA_STRINGA);
    }
  }
  while(rr.nasao);
  Konkatenacija(*Stek[Dubina_steka-1].vrednost.v_string,*s);
  Oslobodi_celiju(&Stek[Dubina_steka]);
  Oslobodi_celiju(&Stek[Dubina_steka+1]);
  RE_free_run_results(&rr);
}

void IF_substring(void)
{
  String *s;
  s=Novi_string();
  Proveri_od_do_broj_argumenata(2,3);
  if(Dubina_steka-Pozivi_func_proc[Broj_poziva_func_proc-1].stek==2)
  {
    Dubina_steka--;
    Konvertuj_celiju_u_string(&Stek[Dubina_steka-1]);
    Konvertuj_celiju_u_integer(&Stek[Dubina_steka]);
    Kopiraj_string_od_do(*s,*Stek[Dubina_steka-1].vrednost.v_string,(int)Stek[Dubina_steka].vrednost.v_integer,MAX_DUZINA_STRINGA);
  }
  else
  {
    Dubina_steka-=2;
    Konvertuj_celiju_u_string(&Stek[Dubina_steka-1]);
    Konvertuj_celiju_u_integer(&Stek[Dubina_steka]);
    Konvertuj_celiju_u_integer(&Stek[Dubina_steka+1]);
    Kopiraj_string_od_do(*s,*Stek[Dubina_steka-1].vrednost.v_string,(int)Stek[Dubina_steka].vrednost.v_integer,(int)Stek[Dubina_steka+1].vrednost.v_integer);
  }
  Oslobodi_celiju(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_string=s;
}

void IF_system(void)
{
  int i;
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_string(&Stek[Dubina_steka-1]);
  i=system(*Stek[Dubina_steka-1].vrednost.v_string);
  Konvertuj_celiju_u_integer(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_integer=i;
}

void IF_tan(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_real=tan(Stek[Dubina_steka-1].vrednost.v_real);
}

void IF_tanh(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_real=tanh(Stek[Dubina_steka-1].vrednost.v_real);
}

void IF_tell(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_file(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].tip=Tip_integer;
  Stek[Dubina_steka-1].vrednost.v_integer=ftell(Datoteke[Stek[Dubina_steka-1].vrednost.v_file]);
}

void IF_time(void)
{
  time_t t;
  Proveri_broj_argumenata(0);
  Stek[Dubina_steka].tip=Tip_string;
  Stek[Dubina_steka].vrednost.v_string=Novi_string();
  time(&t);
  strftime(*Stek[Dubina_steka].vrednost.v_string,sizeof(String),"%w %d/%m/%Y %H:%M:%S",localtime(&t));
  Dubina_steka++;
}

void IF_tolower(void)
{
  char *s;
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_string(&Stek[Dubina_steka-1]);
  s=*Stek[Dubina_steka-1].vrednost.v_string;
  while(*s!='\0')
  {
    *s=(char)tolower((int)*s);
    s++;
  }
}

void IF_toupper(void)
{
  char *s;
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_string(&Stek[Dubina_steka-1]);
  s=*Stek[Dubina_steka-1].vrednost.v_string;
  while(*s!='\0')
  {
    *s=(char)toupper((int)*s);
    s++;
  }
}

void IF_unknown(void)
{
  int b;
  Proveri_broj_argumenata(1);
  b=Stek[Dubina_steka-1].tip==Tip_celija||Stek[Dubina_steka-1].tip==Tip_unknown;
  Konvertuj_celiju_u_bool(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_bool=b;
}

void IP_close(void)
{
  Proveri_broj_argumenata(1);
  Dubina_steka--;
  Konvertuj_celiju_u_file(&Stek[Dubina_steka]);
  fclose(Datoteke[Stek[Dubina_steka].vrednost.v_file]);
}

void Ispisi_celiju(Celija *c)
{
  int i;
  switch(c->tip)
  {
    case Tip_bool:
      printf("bool:%s",c->vrednost.v_bool?"true":"false");
      break;
    case Tip_integer:
      printf("integer:%ld",c->vrednost.v_integer);
      break;
    case Tip_real:
      printf("real:%g",c->vrednost.v_real);
      break;
    case Tip_string:
      printf("string:%s",*c->vrednost.v_string);
      break;
    case Tip_array:
      printf("array:{");
      for(i=0;i<c->vrednost.v_array->broj_indeksa;i++)
      {
        printf("(");
        Ispisi_celiju(&c->vrednost.v_array->indeksi[i].indeks);
        printf(",");
        Ispisi_celiju(&c->vrednost.v_array->indeksi[i].celija);
        printf(")");
      }
      printf("}");
      break;
    case Tip_file:
      printf("file:");
      break;
    case Tip_func_proc:
    case Tip_function:
    case Tip_procedure:
      printf("funkcija ili procedura");
      break;
    case Tip_celija:
      printf("celija:");
      break;
    case Tip_unknown:
      printf("unknown:\n");
  }
}

void IP_debug(void)
{
  int i;
  Proveri_broj_argumenata(0);
  printf("Debug:\n");
  for(i=0;i<Broj_varijabli;i++)
  {
    printf("%s=",Varijable[i].ime);
    Ispisi_celiju(&Varijable[i].celija);
    printf("\n");
  }
}

void IP_delete(void)
{
  Proveri_od_do_broj_argumenata(1,2);
  Konvertuj_celiju_u_niz(&Stek[Pozivi_func_proc[Broj_poziva_func_proc-1].stek]);
  if(Dubina_steka-Pozivi_func_proc[Broj_poziva_func_proc-1].stek==1)
  {
    Dubina_steka--;
    Obrisi_niz(Stek[Dubina_steka].vrednost.v_array);
  }
  else
  {
    Dubina_steka-=2;
    Obrisi_indeks(Stek[Dubina_steka].vrednost.v_array,&Stek[Dubina_steka+1]);
    Oslobodi_celiju(&Stek[Dubina_steka+1]);
  }
}

void IP_error(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_string(&Stek[Dubina_steka-1]);
  LA_error(*Stek[Dubina_steka-1].vrednost.v_string);
}

void IP_exit(void)
{
  Proveri_broj_argumenata(1);
  Konvertuj_celiju_u_integer(&Stek[Dubina_steka-1]);
  exit((int)Stek[Dubina_steka-1].vrednost.v_integer);
}

void IP_flush(void)
{
  Proveri_od_do_broj_argumenata(0,1);
  if(Dubina_steka==Pozivi_func_proc[Broj_poziva_func_proc-1].stek)
    fflush(stdout);
  else
  {
    Dubina_steka--;
    Konvertuj_celiju_u_file(&Stek[Dubina_steka]);
    fflush(Datoteke[Stek[Dubina_steka].vrednost.v_file]);
  }
}

void IP_opena(void)
{
  Proveri_broj_argumenata(2);
  Dubina_steka-=2;
  Konvertuj_celiju_u_file(&Stek[Dubina_steka]);
  Konvertuj_celiju_u_string(&Stek[Dubina_steka+1]);
  Datoteke[Stek[Dubina_steka].vrednost.v_file]=fopen(*Stek[Dubina_steka+1].vrednost.v_string,"a");
  if(Datoteke[Stek[Dubina_steka].vrednost.v_file]==NULL)
    LA_error("Ne mogu otvoriti datoteku za pisanje");
  Oslobodi_celiju(&Stek[Dubina_steka+1]);
}

void IP_openr(void)
{
  Proveri_broj_argumenata(2);
  Dubina_steka-=2;
  Konvertuj_celiju_u_file(&Stek[Dubina_steka]);
  Konvertuj_celiju_u_string(&Stek[Dubina_steka+1]);
  Datoteke[Stek[Dubina_steka].vrednost.v_file]=fopen(*Stek[Dubina_steka+1].vrednost.v_string,"r");
  if(Datoteke[Stek[Dubina_steka].vrednost.v_file]==NULL)
    LA_error("Ne mogu otvoriti datoteku za citanje");
  Oslobodi_celiju(&Stek[Dubina_steka+1]);
}

void IP_openw(void)
{
  Proveri_broj_argumenata(2);
  Dubina_steka-=2;
  Konvertuj_celiju_u_file(&Stek[Dubina_steka]);
  Konvertuj_celiju_u_string(&Stek[Dubina_steka+1]);
  Datoteke[Stek[Dubina_steka].vrednost.v_file]=fopen(*Stek[Dubina_steka+1].vrednost.v_string,"w");
  if(Datoteke[Stek[Dubina_steka].vrednost.v_file]==NULL)
    LA_error("Ne mogu otvoriti datoteku za pisanje");
  Oslobodi_celiju(&Stek[Dubina_steka+1]);
}

void IP_pipeclose(void)
{
  Proveri_broj_argumenata(1);
  Dubina_steka--;
  Konvertuj_celiju_u_file(&Stek[Dubina_steka]);
  pclose(Datoteke[Stek[Dubina_steka].vrednost.v_file]);
}

void IP_pipeopenr(void)
{
  Proveri_broj_argumenata(2);
  Dubina_steka-=2;
  Konvertuj_celiju_u_file(&Stek[Dubina_steka]);
  Konvertuj_celiju_u_string(&Stek[Dubina_steka+1]);
  Datoteke[Stek[Dubina_steka].vrednost.v_file]=popen(*Stek[Dubina_steka+1].vrednost.v_string,"r");
  if(Datoteke[Stek[Dubina_steka].vrednost.v_file]==NULL)
    LA_error("Ne mogu otvoriti pipe za citanje");
  Oslobodi_celiju(&Stek[Dubina_steka+1]);
}

void IP_pipeopenw(void)
{
  Proveri_broj_argumenata(2);
  Dubina_steka-=2;
  Konvertuj_celiju_u_file(&Stek[Dubina_steka]);
  Konvertuj_celiju_u_string(&Stek[Dubina_steka+1]);
  Datoteke[Stek[Dubina_steka].vrednost.v_file]=popen(*Stek[Dubina_steka+1].vrednost.v_string,"w");
  if(Datoteke[Stek[Dubina_steka].vrednost.v_file]==NULL)
    LA_error("Ne mogu otvoriti pipe za pisanje");
  Oslobodi_celiju(&Stek[Dubina_steka+1]);
}

void IP_print(void)
{
  int i;
  for(i=Pozivi_func_proc[Broj_poziva_func_proc-1].stek;i<Dubina_steka;i++)
    switch(Stek[i].tip)
    {
      case Tip_bool:
        printf("%s",Stek[i].vrednost.v_bool?"true":"false");
        break;
      case Tip_integer:
        printf("%ld",Stek[i].vrednost.v_integer);
        break;
      case Tip_real:
        printf("%g",Stek[i].vrednost.v_real);
        break;
      case Tip_string:
        printf("%s",*Stek[i].vrednost.v_string);
        Oslobodi_celiju(&Stek[i]);
    }
  Dubina_steka=Pozivi_func_proc[Broj_poziva_func_proc-1].stek;
}

void IP_seekb(void)
{
  Proveri_broj_argumenata(2);
  Dubina_steka-=2;
  Konvertuj_celiju_u_file(&Stek[Dubina_steka]);
  Konvertuj_celiju_u_integer(&Stek[Dubina_steka+1]);
  fseek(Datoteke[Stek[Dubina_steka].vrednost.v_file],Stek[Dubina_steka+1].vrednost.v_integer,SEEK_SET);
}

void IP_seekc(void)
{
  Proveri_broj_argumenata(2);
  Dubina_steka-=2;
  Konvertuj_celiju_u_file(&Stek[Dubina_steka]);
  Konvertuj_celiju_u_integer(&Stek[Dubina_steka+1]);
  fseek(Datoteke[Stek[Dubina_steka].vrednost.v_file],Stek[Dubina_steka+1].vrednost.v_integer,SEEK_CUR);
}

void IP_seeke(void)
{
  Proveri_broj_argumenata(2);
  Dubina_steka-=2;
  Konvertuj_celiju_u_file(&Stek[Dubina_steka]);
  Konvertuj_celiju_u_integer(&Stek[Dubina_steka+1]);
  fseek(Datoteke[Stek[Dubina_steka].vrednost.v_file],Stek[Dubina_steka+1].vrednost.v_integer,SEEK_END);
}

void IP_sort(void)
{
  Proveri_broj_argumenata(1);
  Dubina_steka--;
  Konvertuj_celiju_u_niz(&Stek[Dubina_steka]);
  qsort
  (
    Stek[Dubina_steka].vrednost.v_array->indeksi,
    Stek[Dubina_steka].vrednost.v_array->broj_indeksa,
    sizeof(Indeks),
    (int (*)(const void *,const void *))&Uporedi_indekse_celija
  );
}

void IP_sorti(void)
{
  Proveri_broj_argumenata(1);
  Dubina_steka--;
  Konvertuj_celiju_u_niz(&Stek[Dubina_steka]);
  qsort
  (
    Stek[Dubina_steka].vrednost.v_array->indeksi,
    Stek[Dubina_steka].vrednost.v_array->broj_indeksa,
    sizeof(Indeks),
    (int (*)(const void *,const void *))&Uporedi_indekse_indeks
  );
}

void IP_split(void)
{
  RE_KA *ka;
  RE_run_results rr;
  String *s;
  s=Novi_string();
  Proveri_broj_argumenata(3);
  Dubina_steka-=3;
  Konvertuj_celiju_u_string(&Stek[Dubina_steka]);
  Konvertuj_celiju_u_string(&Stek[Dubina_steka+1]);
  Konvertuj_celiju_u_niz(&Stek[Dubina_steka+2]);
  Obrisi_niz(Stek[Dubina_steka+2].vrednost.v_array);
  ka=RE_cache_find(*Stek[Dubina_steka+1].vrednost.v_string);
  if
  (
    ka==NULL||
    RE_run_init(ka,&rr)
  )
  {
    sprintf(Error_msg,"Pozicija:%d, %s",RE_pos,RE_error);
    LA_error(Error_msg);
  }
  strcpy(*s,*Stek[Dubina_steka].vrednost.v_string);
  do
  {
    Celija c;
    Celija *p;
    if(RE_run(ka,*s,&rr,0))
    {
      sprintf(Error_msg,"Pozicija:%d, %s",RE_pos,RE_error);
      LA_error(Error_msg);
    }
    c.tip=Tip_integer;
    c.vrednost.v_integer=(long)(Stek[Dubina_steka+2].vrednost.v_array->broj_indeksa+1);
    p=Ubaci_indeks(Stek[Dubina_steka+2].vrednost.v_array,&c);
    p->tip=Tip_string;
    p->vrednost.v_string=s;
    if(rr.nasao)
    {
      s=Novi_string();
      Kopiraj_string_od_do(*s,*p->vrednost.v_string,rr.kraj,MAX_DUZINA_STRINGA);
      (*p->vrednost.v_string)[rr.pocetak]='\0';
    }
  }
  while(rr.nasao);
  Oslobodi_celiju(&Stek[Dubina_steka]);
  Oslobodi_celiju(&Stek[Dubina_steka+1]);
  RE_free_run_results(&rr);
}

void IP_write(void)
{
  int i;
  Proveri_najmanji_broj_argumenata(1);
  Konvertuj_celiju_u_file(&Stek[Pozivi_func_proc[Broj_poziva_func_proc-1].stek]);
  for(i=Pozivi_func_proc[Broj_poziva_func_proc-1].stek+1;i<Dubina_steka;i++)
    switch(Stek[i].tip)
    {
      case Tip_bool:
        fprintf(Datoteke[Stek[Pozivi_func_proc[Broj_poziva_func_proc-1].stek].vrednost.v_file],"%s",Stek[i].vrednost.v_bool?"true":"false");
        break;
      case Tip_integer:
        fprintf(Datoteke[Stek[Pozivi_func_proc[Broj_poziva_func_proc-1].stek].vrednost.v_file],"%ld",Stek[i].vrednost.v_integer);
        break;
      case Tip_real:
        fprintf(Datoteke[Stek[Pozivi_func_proc[Broj_poziva_func_proc-1].stek].vrednost.v_file],"%g",Stek[i].vrednost.v_real);
        break;
      case Tip_string:
        fprintf(Datoteke[Stek[Pozivi_func_proc[Broj_poziva_func_proc-1].stek].vrednost.v_file],"%s",*Stek[i].vrednost.v_string);
        Oslobodi_celiju(&Stek[i]);
    }
  Dubina_steka=Pozivi_func_proc[Broj_poziva_func_proc-1].stek;
}

I_func_proc I_func[]=
{
  {"abs",&IF_abs},
  {"aprcmp",&IF_aprcmp},
  {"bool",&IF_bool},
  {"acos",&IF_acos},
  {"asin",&IF_asin},
  {"atan",&IF_atan},
  {"ceil",&IF_ceil},
  {"chop",&IF_chop},
  {"cos",&IF_cos},
  {"cosh",&IF_cosh},
  {"eof",&IF_eof},
  {"exp",&IF_exp},
  {"floor",&IF_floor},
  {"fill",&IF_fill},
  {"getenv",&IF_getenv},
  {"input",&IF_input},
  {"integer",&IF_integer},
  {"lenght",&IF_lenght},
  {"log",&IF_log},
  {"log10",&IF_log10},
  {"pow",&IF_pow},
  {"read",&IF_read},
  {"real",&IF_real},
  {"regexp",&IF_regexp},
  {"scan",&IF_scan},
  {"sin",&IF_sin},
  {"sinh",&IF_sinh},
  {"sqrt",&IF_sqrt},
  {"string",&IF_string},
  {"substitute",&IF_substitute},
  {"substring",&IF_substring},
  {"system",&IF_system},
  {"tan",&IF_tan},
  {"tanh",&IF_tanh},
  {"tell",&IF_tell},
  {"time",&IF_time},
  {"tolower",&IF_tolower},
  {"toupper",&IF_toupper},
  {"unknown",&IF_unknown},
  {"",NULL}
};

I_func_proc I_proc[]=
{
  {"close",&IP_close},
  {"debug",&IP_debug},
  {"delete",&IP_delete},
  {"error",&IP_error},
  {"exit",&IP_exit},
  {"flush",&IP_flush},
  {"opena",&IP_opena},
  {"openr",&IP_openr},
  {"openw",&IP_openw},
  {"pipeclose",&IP_pipeclose},
  {"pipeopenr",&IP_pipeopenr},
  {"pipeopenw",&IP_pipeopenw},
  {"print",&IP_print},
  {"seekb",&IP_seekb},
  {"seekc",&IP_seekc},
  {"seeke",&IP_seeke},
  {"sort",&IP_sort},
  {"sorti",&IP_sorti},
  {"split",&IP_split},
  {"write",&IP_write},
  {"",NULL}
};
