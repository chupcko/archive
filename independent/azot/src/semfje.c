#include <stdio.h>
#include <string.h>
#include "lexana.h"
#include "semana.h"
#include "semdom.h"

void SF_and(void)
{
  Dubina_steka--;
  Konvertuj_celiju_u_bool(&Stek[Dubina_steka-1]);
  Konvertuj_celiju_u_bool(&Stek[Dubina_steka]);
  Stek[Dubina_steka-1].vrednost.v_bool=Stek[Dubina_steka-1].vrednost.v_bool&&Stek[Dubina_steka].vrednost.v_bool;
}

void SF_bool_false(void)
{
  if(Dubina_steka==MAX_DUBINA_STEKA)
    LA_error("Nema vise mesta na steku");
  Stek[Dubina_steka].tip=Tip_bool;
  Stek[Dubina_steka].vrednost.v_bool=0;
  Dubina_steka++;
}

void SF_bool_true(void)
{
  if(Dubina_steka==MAX_DUBINA_STEKA)
    LA_error("Nema vise mesta na steku");
  Stek[Dubina_steka].tip=Tip_bool;
  Stek[Dubina_steka].vrednost.v_bool=1;
  Dubina_steka++;
}

void SF_break(void)
{
  Radi=R_break;
}

void SF_continue(void)
{
  Radi=R_continue;
}

void SF_def_func_proc(void)
{
  LA_uzmi_poziciju(&Func_proc[Koju_func_proc_definisemo].pozicija);
}

void SF_dodaj_argument(void)
{
  if(Func_proc[Koju_func_proc_definisemo].broj_argumenata==MAX_BROJ_ARGUMENATA)
    LA_error("Mnogo argumenata");
  strncpy(Func_proc[Koju_func_proc_definisemo].argumenti[Func_proc[Koju_func_proc_definisemo].broj_argumenata],LA_vrednost_lekseme,sizeof(Ime));
  Func_proc[Koju_func_proc_definisemo].broj_argumenata++;
}

void SF_dodela(void)
{
  Dubina_steka-=2;
  if(Stek[Dubina_steka].tip!=Tip_celija)
    LA_error("Nije moguce dodeliti vrednost funkciji ili proceduri");
  if
  (
    Stek[Dubina_steka+1].tip!=Tip_celija&&
    Stek[Dubina_steka+1].tip!=Tip_unknown
  )
  {
    if(Celija_nije_prostog_tipa(&Stek[Dubina_steka+1]))
      LA_error("Izraz u dodeli treba biti tipa: bool, integer, real ili string");
    else
      switch(Stek[Dubina_steka].vrednost.v_celija->tip)
      {
        case Tip_bool:
          Konvertuj_celiju_u_bool(&Stek[Dubina_steka+1]);
          Stek[Dubina_steka].vrednost.v_celija->vrednost.v_bool=Stek[Dubina_steka+1].vrednost.v_bool;
          break;
        case Tip_integer:
          Konvertuj_celiju_u_integer(&Stek[Dubina_steka+1]);
          Stek[Dubina_steka].vrednost.v_celija->vrednost.v_integer=Stek[Dubina_steka+1].vrednost.v_integer;
          break;
        case Tip_real:
          Konvertuj_celiju_u_real(&Stek[Dubina_steka+1]);
          Stek[Dubina_steka].vrednost.v_celija->vrednost.v_real=Stek[Dubina_steka+1].vrednost.v_real;
          break;
        case Tip_string:
          Konvertuj_celiju_u_string(&Stek[Dubina_steka+1]);
          Stek[Dubina_steka].vrednost.v_celija->vrednost.v_string=Stek[Dubina_steka+1].vrednost.v_string;
          break;
        case Tip_unknown:
          Kopiraj_celiju(Stek[Dubina_steka].vrednost.v_celija,&Stek[Dubina_steka+1],0);
          break;
        default:
          LA_error("Dodela je moguca samo za promenljive tipa: bool, integer, real, string");
      }
  }
}

void SF_eq(void)
{
  int b;
  Dubina_steka--;
  b=Uporedi_celije(&Stek[Dubina_steka-1],&Stek[Dubina_steka]);
  Oslobodi_celiju(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].tip=Tip_bool;
  Stek[Dubina_steka-1].vrednost.v_bool=b==0;
}

void SF_funkcija(void)
{
  Dubina_steka--;
  if(Broj_poziva_func_proc==MAX_BROJ_POZIVA)
    LA_error("Mnogo poziva funkcija");
  if
  (
    Stek[Dubina_steka].tip!=Tip_function&&
    (
      Stek[Dubina_steka].tip!=Tip_func_proc||
      Func_proc[Stek[Dubina_steka].vrednost.v_func_proc].tip!=Tip_FP_function
    )
  )
    LA_error("Ocekivao sam poziv funkcije");
  Pozivi_func_proc[Broj_poziva_func_proc].tip=Stek[Dubina_steka].tip==Tip_function?Tip_POZIV_I:Tip_POZIV_U;
  Pozivi_func_proc[Broj_poziva_func_proc].func_proc=Stek[Dubina_steka].vrednost.v_func_proc;
  Pozivi_func_proc[Broj_poziva_func_proc].stek=Dubina_steka;
  Pozivi_func_proc[Broj_poziva_func_proc].rezultat.tip=Tip_unknown;
  Broj_poziva_func_proc++;
}

void SF_ge(void)
{
  int b;
  Dubina_steka--;
  b=Uporedi_celije(&Stek[Dubina_steka-1],&Stek[Dubina_steka]);
  Oslobodi_celiju(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].tip=Tip_bool;
  Stek[Dubina_steka-1].vrednost.v_bool=b>=0;
}

void SF_gt(void)
{
  int b;
  Dubina_steka--;
  b=Uporedi_celije(&Stek[Dubina_steka-1],&Stek[Dubina_steka]);
  Oslobodi_celiju(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].tip=Tip_bool;
  Stek[Dubina_steka-1].vrednost.v_bool=b>0;
}

void SF_in(void)
{
  int i;
  Dubina_steka--;
  Konvertuj_celiju_u_niz(&Stek[Dubina_steka]);
  i=Pronadji_indeks(Stek[Dubina_steka].vrednost.v_array,&Stek[Dubina_steka-1]);
  Konvertuj_celiju_u_bool(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_bool=i!=Stek[Dubina_steka].vrednost.v_array->broj_indeksa;
}

void SF_indeks(void)
{
  int i;
  Dubina_steka--;
  if
  (
    Stek[Dubina_steka-1].tip!=Tip_celija||
    (
      Stek[Dubina_steka-1].vrednost.v_celija->tip!=Tip_unknown&&
      Stek[Dubina_steka-1].vrednost.v_celija->tip!=Tip_array
    )
  )
    LA_error("Indeks moze doci samo posle niza");
  if(Stek[Dubina_steka-1].vrednost.v_celija->tip==Tip_unknown)
  {
    Stek[Dubina_steka-1].vrednost.v_celija->tip=Tip_array;
    Stek[Dubina_steka-1].vrednost.v_celija->vrednost.v_array=Novi_niz();
  }
  Stek[Dubina_steka-1].vrednost.v_celija=Ubaci_indeks(Stek[Dubina_steka-1].vrednost.v_celija->vrednost.v_array,&Stek[Dubina_steka]);
}

void SF_integer(void)
{
  if(Dubina_steka==MAX_DUBINA_STEKA)
    LA_error("Nema vise mesta na steku");
  Stek[Dubina_steka].tip=Tip_integer;
  sscanf(LA_vrednost_lekseme,"%ld",&Stek[Dubina_steka].vrednost.v_integer);
  Dubina_steka++;
}

void SF_iz_memorije(void)
{
  if(Stek[Dubina_steka-1].tip!=Tip_celija)
    LA_error("Funkcija, promenljiva nisu varijable");
  if(Stek[Dubina_steka-1].vrednost.v_celija->tip!=Tip_unknown)
    Kopiraj_celiju(&Stek[Dubina_steka-1],Stek[Dubina_steka-1].vrednost.v_celija,1);
}

void SF_konkatenacija(void)
{
  Dubina_steka--;
  Konvertuj_celiju_u_string(&Stek[Dubina_steka-1]);
  Konvertuj_celiju_u_string(&Stek[Dubina_steka]);
  Konkatenacija(*Stek[Dubina_steka-1].vrednost.v_string,*Stek[Dubina_steka].vrednost.v_string);
  Oslobodi_celiju(&Stek[Dubina_steka]);
}

void SF_le(void)
{
  int b;
  Dubina_steka--;
  b=Uporedi_celije(&Stek[Dubina_steka-1],&Stek[Dubina_steka]);
  Oslobodi_celiju(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].tip=Tip_bool;
  Stek[Dubina_steka-1].vrednost.v_bool=b<=0;
}

void SF_lt(void)
{
  int b;
  Dubina_steka--;
  b=Uporedi_celije(&Stek[Dubina_steka-1],&Stek[Dubina_steka]);
  Oslobodi_celiju(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].tip=Tip_bool;
  Stek[Dubina_steka-1].vrednost.v_bool=b<0;
}

void SF_minus(void)
{
  Dubina_steka--;
  switch(Stek[Dubina_steka-1].tip)
  {
    case Tip_integer:
      Konvertuj_celiju_u_integer(&Stek[Dubina_steka]);
      Stek[Dubina_steka-1].vrednost.v_integer-=Stek[Dubina_steka].vrednost.v_integer;
      break;
    case Tip_real:
      Konvertuj_celiju_u_real(&Stek[Dubina_steka]);
      Stek[Dubina_steka-1].vrednost.v_real-=Stek[Dubina_steka].vrednost.v_real;
      break;
    default:
      switch(Stek[Dubina_steka].tip)
      {
        case Tip_integer:
          Konvertuj_celiju_u_integer(&Stek[Dubina_steka-1]);
          Stek[Dubina_steka-1].vrednost.v_integer-=Stek[Dubina_steka].vrednost.v_integer;
          break;
        case Tip_real:
          Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
          Stek[Dubina_steka-1].vrednost.v_real-=Stek[Dubina_steka].vrednost.v_real;
          break;
        default:
          Konvertuj_celiju_u_integer(&Stek[Dubina_steka-1]);
          Konvertuj_celiju_u_integer(&Stek[Dubina_steka]);
          Stek[Dubina_steka-1].vrednost.v_integer-=Stek[Dubina_steka].vrednost.v_integer;
      }
  }
}

void SF_mod(void)
{
  Dubina_steka--;
  Konvertuj_celiju_u_integer(&Stek[Dubina_steka-1]);
  Konvertuj_celiju_u_integer(&Stek[Dubina_steka]);
  if(Stek[Dubina_steka].vrednost.v_integer==0)
    LA_error("Ostataka pri deljenju nulom");
  Stek[Dubina_steka-1].vrednost.v_integer%=Stek[Dubina_steka].vrednost.v_integer;
}

void SF_neq(void)
{
  int b;
  Dubina_steka--;
  b=Uporedi_celije(&Stek[Dubina_steka-1],&Stek[Dubina_steka]);
  Oslobodi_celiju(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].tip=Tip_bool;
  Stek[Dubina_steka-1].vrednost.v_bool=b!=0;
}

void SF_not(void)
{
  Konvertuj_celiju_u_bool(&Stek[Dubina_steka-1]);
  Stek[Dubina_steka-1].vrednost.v_integer=!Stek[Dubina_steka-1].vrednost.v_integer;
}

void SF_nova_funkcije(void)
{
  Koju_func_proc_definisemo=0;
  while
  (
    Koju_func_proc_definisemo<Broj_func_proc&&
    strncmp(Func_proc[Koju_func_proc_definisemo].ime,LA_vrednost_lekseme,sizeof(Ime))
  )
    Koju_func_proc_definisemo++;
  if(Koju_func_proc_definisemo==Broj_func_proc)
  {
    if(Broj_func_proc==MAX_BROJ_FUNC_PROC)
      LA_error("Mnogo funkcija");
    strncpy(Func_proc[Broj_func_proc].ime,LA_vrednost_lekseme,sizeof(Ime));
    Broj_func_proc++;
  }
  Func_proc[Koju_func_proc_definisemo].tip=Tip_FP_function;
  Func_proc[Koju_func_proc_definisemo].broj_argumenata=0;
}

void SF_nova_procedure(void)
{
  Koju_func_proc_definisemo=0;
  while
  (
    Koju_func_proc_definisemo<Broj_func_proc&&
    strncmp(Func_proc[Koju_func_proc_definisemo].ime,LA_vrednost_lekseme,sizeof(Ime))
  )
    Koju_func_proc_definisemo++;
  if(Koju_func_proc_definisemo==Broj_func_proc)
  {
    if(Broj_func_proc==MAX_BROJ_FUNC_PROC)
      LA_error("Mnogo procedura");
    strncpy(Func_proc[Broj_func_proc].ime,LA_vrednost_lekseme,sizeof(Ime));
    Broj_func_proc++;
  }
  Func_proc[Koju_func_proc_definisemo].tip=Tip_FP_procedure;
  Func_proc[Koju_func_proc_definisemo].broj_argumenata=0;
}

void SF_or(void)
{
  Dubina_steka--;
  Konvertuj_celiju_u_bool(&Stek[Dubina_steka-1]);
  Konvertuj_celiju_u_bool(&Stek[Dubina_steka]);
  Stek[Dubina_steka-1].vrednost.v_bool=Stek[Dubina_steka-1].vrednost.v_bool||Stek[Dubina_steka].vrednost.v_bool;
}

void SF_plus(void)
{
  Dubina_steka--;
  switch(Stek[Dubina_steka-1].tip)
  {
    case Tip_integer:
      Konvertuj_celiju_u_integer(&Stek[Dubina_steka]);
      Stek[Dubina_steka-1].vrednost.v_integer+=Stek[Dubina_steka].vrednost.v_integer;
      break;
    case Tip_real:
      Konvertuj_celiju_u_real(&Stek[Dubina_steka]);
      Stek[Dubina_steka-1].vrednost.v_real+=Stek[Dubina_steka].vrednost.v_real;
      break;
    default:
      switch(Stek[Dubina_steka].tip)
      {
        case Tip_integer:
          Konvertuj_celiju_u_integer(&Stek[Dubina_steka-1]);
          Stek[Dubina_steka-1].vrednost.v_integer+=Stek[Dubina_steka].vrednost.v_integer;
          break;
        case Tip_real:
          Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
          Stek[Dubina_steka-1].vrednost.v_real+=Stek[Dubina_steka].vrednost.v_real;
          break;
        default:
          Konvertuj_celiju_u_integer(&Stek[Dubina_steka-1]);
          Konvertuj_celiju_u_integer(&Stek[Dubina_steka]);
          Stek[Dubina_steka-1].vrednost.v_integer+=Stek[Dubina_steka].vrednost.v_integer;
      }
  }
}

void SF_podeljeno(void)
{
  Dubina_steka--;
  switch(Stek[Dubina_steka-1].tip)
  {
    case Tip_integer:
      Konvertuj_celiju_u_integer(&Stek[Dubina_steka]);
      if(Stek[Dubina_steka].vrednost.v_integer==0)
        LA_error("Deljenje nulom");
      Stek[Dubina_steka-1].vrednost.v_integer/=Stek[Dubina_steka].vrednost.v_integer;
      break;
    case Tip_real:
      Konvertuj_celiju_u_real(&Stek[Dubina_steka]);
      if(Stek[Dubina_steka].vrednost.v_real==0.0);
        LA_error("Deljenje nulom");
      Stek[Dubina_steka-1].vrednost.v_real/=Stek[Dubina_steka].vrednost.v_real;
      break;
    default:
      switch(Stek[Dubina_steka].tip)
      {
        case Tip_integer:
          Konvertuj_celiju_u_integer(&Stek[Dubina_steka-1]);
          if(Stek[Dubina_steka].vrednost.v_integer==0)
            LA_error("Deljenje nulom");
          Stek[Dubina_steka-1].vrednost.v_integer/=Stek[Dubina_steka].vrednost.v_integer;
          break;
        case Tip_real:
          Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
          if(Stek[Dubina_steka].vrednost.v_real==0.0)
            LA_error("Deljenje nulom");
          Stek[Dubina_steka-1].vrednost.v_real/=Stek[Dubina_steka].vrednost.v_real;
          break;
        default:
          Konvertuj_celiju_u_integer(&Stek[Dubina_steka-1]);
          Konvertuj_celiju_u_integer(&Stek[Dubina_steka]);
          if(Stek[Dubina_steka].vrednost.v_integer==0)
            LA_error("Deljenje nulom");
          Stek[Dubina_steka-1].vrednost.v_integer/=Stek[Dubina_steka].vrednost.v_integer;
      }
  }
}

void SF_poziv_funkcije(void)
{
  if(Pozivi_func_proc[Broj_poziva_func_proc-1].tip==Tip_POZIV_I)
    I_func[Pozivi_func_proc[Broj_poziva_func_proc-1].func_proc].f();
  else
  {
    LA_pozicija pozicija;
    int pp;
    pp=Pravi_poziv_func_proc;
    Pravi_poziv_func_proc=Broj_poziva_func_proc-1;
    Proveri_broj_argumenata(Func_proc[Pozivi_func_proc[Pravi_poziv_func_proc].func_proc].broj_argumenata);
    LA_uzmi_poziciju(&pozicija);
    LA_idi_na_poziciju(&Func_proc[Pozivi_func_proc[Pravi_poziv_func_proc].func_proc].pozicija);
    LA_scanner();
    SA_naredba();
    Radi=R_normal;
    LA_idi_na_poziciju(&pozicija);
    while(Dubina_steka>Pozivi_func_proc[Pravi_poziv_func_proc].stek)
    {
      Dubina_steka--;
      Oslobodi_celiju(&Stek[Dubina_steka]);
    }
    Kopiraj_celiju(&Stek[Dubina_steka],&Pozivi_func_proc[Pravi_poziv_func_proc].rezultat,0);
    Dubina_steka++;
    Pravi_poziv_func_proc=pp;
  }
  Broj_poziva_func_proc--;
}

void SF_poziv_procedure(void)
{
  if(Pozivi_func_proc[Broj_poziva_func_proc-1].tip==Tip_POZIV_I)
    I_proc[Pozivi_func_proc[Broj_poziva_func_proc-1].func_proc].f();
  else
  {
    LA_pozicija pozicija;
    int pp;
    pp=Pravi_poziv_func_proc;
    Pravi_poziv_func_proc=Broj_poziva_func_proc-1;
    Proveri_broj_argumenata(Func_proc[Pozivi_func_proc[Pravi_poziv_func_proc].func_proc].broj_argumenata);
    LA_uzmi_poziciju(&pozicija);
    LA_idi_na_poziciju(&Func_proc[Pozivi_func_proc[Pravi_poziv_func_proc].func_proc].pozicija);
    LA_scanner();
    SA_naredba();
    Radi=R_normal;
    LA_idi_na_poziciju(&pozicija);
    while(Dubina_steka>Pozivi_func_proc[Pravi_poziv_func_proc].stek)
    {
      Dubina_steka--;
      Oslobodi_celiju(&Stek[Dubina_steka]);
    }
    Pravi_poziv_func_proc=pp;
  }
  Broj_poziva_func_proc--;
}

void SF_procedura(void)
{
  Dubina_steka--;
  if(Broj_poziva_func_proc==MAX_BROJ_POZIVA)
    LA_error("Mnogo poziva procedura");
  if
  (
    Stek[Dubina_steka].tip!=Tip_procedure&&
    (
      Stek[Dubina_steka].tip!=Tip_func_proc||
      Func_proc[Stek[Dubina_steka].vrednost.v_func_proc].tip!=Tip_FP_procedure
    )
  )
    LA_error("Ocekivao sam poziv procedure");
  Pozivi_func_proc[Broj_poziva_func_proc].tip=Stek[Dubina_steka].tip==Tip_procedure?Tip_POZIV_I:Tip_POZIV_U;
  Pozivi_func_proc[Broj_poziva_func_proc].func_proc=Stek[Dubina_steka].vrednost.v_func_proc;
  Pozivi_func_proc[Broj_poziva_func_proc].stek=Dubina_steka;
  Broj_poziva_func_proc++;
}

void SF_puta(void)
{
  Dubina_steka--;
  switch(Stek[Dubina_steka-1].tip)
  {
    case Tip_integer:
      Konvertuj_celiju_u_integer(&Stek[Dubina_steka]);
      Stek[Dubina_steka-1].vrednost.v_integer*=Stek[Dubina_steka].vrednost.v_integer;
      break;
    case Tip_real:
      Konvertuj_celiju_u_real(&Stek[Dubina_steka]);
      Stek[Dubina_steka-1].vrednost.v_real*=Stek[Dubina_steka].vrednost.v_real;
      break;
    default:
      switch(Stek[Dubina_steka].tip)
      {
        case Tip_integer:
          Konvertuj_celiju_u_integer(&Stek[Dubina_steka-1]);
          Stek[Dubina_steka-1].vrednost.v_integer*=Stek[Dubina_steka].vrednost.v_integer;
          break;
        case Tip_real:
          Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
          Stek[Dubina_steka-1].vrednost.v_real*=Stek[Dubina_steka].vrednost.v_real;
          break;
        default:
          Konvertuj_celiju_u_integer(&Stek[Dubina_steka-1]);
          Konvertuj_celiju_u_integer(&Stek[Dubina_steka]);
          Stek[Dubina_steka-1].vrednost.v_integer*=Stek[Dubina_steka].vrednost.v_integer;
      }
  }
}

void SF_real(void)
{
  if(Dubina_steka==MAX_DUBINA_STEKA)
    LA_error("Nema vise mesta na steku");
  Stek[Dubina_steka].tip=Tip_real;
  sscanf(LA_vrednost_lekseme,"%lg",&Stek[Dubina_steka].vrednost.v_real);
  Dubina_steka++;
}

void SF_return_func(void)
{
  Dubina_steka--;
  if(Pravi_poziv_func_proc==-1)
  {
    Konvertuj_celiju_u_integer(&Stek[Dubina_steka]);
    exit((int)Stek[Dubina_steka].vrednost.v_integer);
  }
  if(Func_proc[Pozivi_func_proc[Pravi_poziv_func_proc].func_proc].tip!=Tip_FP_function)
    LA_error("return sa vrednoscu je moguc samo za funkcije");
  Kopiraj_celiju(&Pozivi_func_proc[Pravi_poziv_func_proc].rezultat,&Stek[Dubina_steka],0);
  Radi=R_return;
}

void SF_return_proc(void)
{
  if(Pravi_poziv_func_proc==-1)
    exit(1);
  if(Func_proc[Pozivi_func_proc[Pravi_poziv_func_proc].func_proc].tip!=Tip_FP_procedure)
    LA_error("return bez vrednosti je moguc samo za procedure");
  Radi=R_return;
}

void SF_sfin(void)
{
  if(Dubina_steka==MAX_DUBINA_STEKA)
    LA_error("Nema vise mesta na steku");
  Stek[Dubina_steka].tip=Tip_file;
  Stek[Dubina_steka].vrednost.v_file=0;
  Dubina_steka++;
}

void SF_sfout(void)
{
  if(Dubina_steka==MAX_DUBINA_STEKA)
    LA_error("Nema vise mesta na steku");
  Stek[Dubina_steka].tip=Tip_file;
  Stek[Dubina_steka].vrednost.v_file=1;
  Dubina_steka++;
}

void SF_string(void)
{
  if(Dubina_steka==MAX_DUBINA_STEKA)
    LA_error("Nema vise mesta na steku");
  Stek[Dubina_steka].tip=Tip_string;
  Stek[Dubina_steka].vrednost.v_string=Novi_string();
  strncpy(*Stek[Dubina_steka].vrednost.v_string,LA_vrednost_lekseme,sizeof(String));
  Dubina_steka++;
}

void SF_u_minus(void)
{
  switch(Stek[Dubina_steka-1].tip)
  {
    case Tip_integer:
      Stek[Dubina_steka-1].vrednost.v_integer=-Stek[Dubina_steka-1].vrednost.v_integer;
      break;
    case Tip_real:
      Stek[Dubina_steka-1].vrednost.v_real=-Stek[Dubina_steka-1].vrednost.v_real;
      break;
    default:
      Konvertuj_celiju_u_real(&Stek[Dubina_steka-1]);
      Stek[Dubina_steka-1].vrednost.v_real=-Stek[Dubina_steka-1].vrednost.v_real;
  }
}

void SF_varijabla(void)
{
  int i;
  if(Dubina_steka==MAX_DUBINA_STEKA)
    LA_error("Nema vise mesta na steku");
  i=0;
  while(I_proc[i].f!=NULL&&strncmp(I_proc[i].ime,LA_vrednost_lekseme,sizeof(Ime)))
    i++;
  if(I_proc[i].f!=NULL)
  {
    Stek[Dubina_steka].tip=Tip_procedure;
    Stek[Dubina_steka].vrednost.v_func_proc=i;
    Dubina_steka++;
  }
  else
  {
    i=0;
    while(I_func[i].f!=NULL&&strncmp(I_func[i].ime,LA_vrednost_lekseme,sizeof(Ime)))
      i++;
    if(I_func[i].f!=NULL)
    {
      Stek[Dubina_steka].tip=Tip_function;
      Stek[Dubina_steka].vrednost.v_func_proc=i;
      Dubina_steka++;
    }
    else
    {
      i=0;
      while(i<Broj_func_proc&&strncmp(Func_proc[i].ime,LA_vrednost_lekseme,sizeof(Ime)))
        i++;
      if(i<Broj_func_proc)
      {
        Stek[Dubina_steka].tip=Tip_func_proc;
        Stek[Dubina_steka].vrednost.v_func_proc=i;
        Dubina_steka++;
      }
      else
      {
        i=0;
        while
        (
          Pravi_poziv_func_proc>=0&&
          i<Func_proc[Pozivi_func_proc[Pravi_poziv_func_proc].func_proc].broj_argumenata&&
          strncmp(Func_proc[Pozivi_func_proc[Pravi_poziv_func_proc].func_proc].argumenti[i],LA_vrednost_lekseme,sizeof(Ime))
        )
          i++;
        if(Pravi_poziv_func_proc>=0&&i<Func_proc[Pozivi_func_proc[Pravi_poziv_func_proc].func_proc].broj_argumenata)
        {
          Stek[Dubina_steka].tip=Tip_celija;
          Stek[Dubina_steka].vrednost.v_celija=&Stek[Pozivi_func_proc[Pravi_poziv_func_proc].stek+i];
          Dubina_steka++;
        }
        else
        {
          i=0;
          while(i<Broj_varijabli&&strncmp(Varijable[i].ime,LA_vrednost_lekseme,sizeof(Ime)))
            i++;
          if(i==Broj_varijabli)
          {
            if(Broj_varijabli==MAX_BROJ_VARIJABLI)
              LA_error("Mnogo varijabli");
            strncpy(Varijable[i].ime,LA_vrednost_lekseme,sizeof(Ime));
            Varijable[i].celija.tip=Tip_unknown;
            Broj_varijabli++;
          }
          Stek[Dubina_steka].tip=Tip_celija;
          Stek[Dubina_steka].vrednost.v_celija=&Varijable[i].celija;
          Dubina_steka++;
        }
      }
    }
  }
}
