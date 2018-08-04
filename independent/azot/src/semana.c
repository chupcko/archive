#include <stdio.h>
#include "lexana.h"
#include "semana.h"
#include "semdom.h"
#include "semfje.h"

void SA_izraz(void);

void SA_o_argumenti(void)
{
  while(LA_leksema==LA_zarez)
  {
    LA_scanner();
    SA_izraz();
  }
  if(LA_leksema!=LA_d_zag)
    LA_error("Ocekivao sam: ) ,");
}

void SA_argumenti(void)
{
  switch(LA_leksema)
  {
    case LA_ime:
    case LA_l_zag:
    case LA_minus:
    case LA_k_not:
    case LA_k_true:
    case LA_k_false:
    case LA_k_sfin:
    case LA_k_sfout:
    case LA_integer:
    case LA_real:
    case LA_string:
      SA_izraz();
      SA_o_argumenti();
      break;
    case LA_d_zag:
      break;
    default:
      LA_error("Ocekivao sam: ime ( ) - not true false sfin sfout integer real string");
  }
}

void SA_niz(void)
{
  while(LA_leksema==LA_l_u_zag)
  {
    LA_scanner();
    SA_izraz();
    if(Radi==R_normal)
      SF_indeks();
    if(LA_leksema!=LA_d_u_zag)
      LA_error("Ocekivao sam: ]");
    LA_scanner();
  }
  if
  (
    LA_leksema!=LA_EOF&&
    LA_leksema!=LA_k_then&&
    LA_leksema!=LA_k_else&&
    LA_leksema!=LA_k_do&&
    LA_leksema!=LA_k_until&&
    LA_leksema!=LA_k_in&&
    LA_leksema!=LA_d_zag&&
    LA_leksema!=LA_k_end&&
    LA_leksema!=LA_dodela&&
    LA_leksema!=LA_zarez&&
    LA_leksema!=LA_separator&&
    LA_leksema!=LA_k_or&&
    LA_leksema!=LA_k_and&&
    LA_leksema!=LA_eq&&
    LA_leksema!=LA_neq&&
    LA_leksema!=LA_lt&&
    LA_leksema!=LA_le&&
    LA_leksema!=LA_gt&&
    LA_leksema!=LA_ge&&
    LA_leksema!=LA_plus&&
    LA_leksema!=LA_minus&&
    LA_leksema!=LA_tacka&&
    LA_leksema!=LA_puta&&
    LA_leksema!=LA_podeljeno&&
    LA_leksema!=LA_k_mod&&
    LA_leksema!=LA_d_u_zag
  )
    LA_error("Ocekivao sam: EOF then else do until in ) end := , ; or and = <> < <= > >= + - . * / mod [ ]");
}

void SA_promenljiva_ili_funkcija(void)
{
  switch(LA_leksema)
  {
    case LA_EOF:
    case LA_k_then:
    case LA_k_else:
    case LA_k_do:
    case LA_k_until:
    case LA_k_in:
    case LA_d_zag:
    case LA_k_end:
    case LA_zarez:
    case LA_separator:
    case LA_k_or:
    case LA_k_and:
    case LA_eq:
    case LA_neq:
    case LA_lt:
    case LA_le:
    case LA_gt:
    case LA_ge:
    case LA_plus:
    case LA_minus:
    case LA_tacka:
    case LA_puta:
    case LA_podeljeno:
    case LA_k_mod:
    case LA_l_u_zag:
    case LA_d_u_zag:
      SA_niz();
      if(Radi==R_normal)
        SF_iz_memorije();
      break;
    case LA_l_zag:
      if(Radi==R_normal)
        SF_funkcija();
      LA_scanner();
      SA_argumenti();
      if(LA_leksema!=LA_d_zag)
        LA_error("Ocekivao sam: )");
      if(Radi==R_normal)
        SF_poziv_funkcije();
      LA_scanner();
      break;
    default:
      LA_error("Ocekivao sam: EOF then else do until in ( ) end , ; or and = <> < <= > >= + - . * / mod [ ]");
  }
}

void SA_varijabla(void)
{
  switch(LA_leksema)
  {
    case LA_ime:
      if(Radi==R_normal)
        SF_varijabla();
      LA_scanner();
      break;
    default:
      LA_error("Ocekivao sam: ime");
  }
}

void SA_izraz_a(void)
{
  switch(LA_leksema)
  {
    case LA_k_true:
      if(Radi==R_normal)
        SF_bool_true();
      LA_scanner();
      break;
    case LA_k_false:
      if(Radi==R_normal)
        SF_bool_false();
      LA_scanner();
      break;
    case LA_k_sfin:
      if(Radi==R_normal)
        SF_sfin();
      LA_scanner();
      break;
    case LA_k_sfout:
      if(Radi==R_normal)
        SF_sfout();
      LA_scanner();
      break;
    case LA_integer:
      if(Radi==R_normal)
        SF_integer();
      LA_scanner();
      break;
    case LA_real:
      if(Radi==R_normal)
        SF_real();
      LA_scanner();
      break;
    case LA_string:
      if(Radi==R_normal)
        SF_string();
      LA_scanner();
      break;
    case LA_ime:
      SA_varijabla();
      SA_promenljiva_ili_funkcija();
      break;
    case LA_l_zag:
      LA_scanner();
      SA_izraz();
      if(LA_leksema!=LA_d_zag)
        LA_error("Ocekivao sam: )");
      LA_scanner();
      break;
    default:
      LA_error("Ocekivao sam: ime ( true false sfin sfout integer real string");
  }
}

void SA_izraz_b(void)
{
  switch(LA_leksema)
  {
    case LA_k_not:
      LA_scanner();
      SA_izraz_b();
      if(Radi==R_normal)
        SF_not();
      break;
    case LA_minus:
      LA_scanner();
      SA_izraz_b();
      if(Radi==R_normal)
        SF_u_minus();
      break;
    case LA_ime:
    case LA_l_zag:
    case LA_k_true:
    case LA_k_false:
    case LA_k_sfin:
    case LA_k_sfout:
    case LA_integer:
    case LA_real:
    case LA_string:
      SA_izraz_a();
      break;
    default:
      LA_error("Ocekivao sam: ime ( - not true false sfin sfout integer real string");
  }
}

void SA_izraz_c_1(void)
{
  while
  (
    LA_leksema==LA_puta||
    LA_podeljeno==LA_puta||
    LA_k_mod==LA_puta
  )
    switch(LA_leksema)
    {
      case LA_puta:
        LA_scanner();
        SA_izraz_b();
        if(Radi==R_normal)
          SF_puta();
        break;
      case LA_podeljeno:
        LA_scanner();
        SA_izraz_b();
        if(Radi==R_normal)
          SF_podeljeno();
        break;
      case LA_k_mod:
        LA_scanner();
        SA_izraz_b();
        if(Radi==R_normal)
          SF_mod();
    }
  if
  (
    LA_leksema!=LA_EOF&&
    LA_leksema!=LA_k_then&&
    LA_leksema!=LA_k_else&&
    LA_leksema!=LA_k_do&&
    LA_leksema!=LA_k_until&&
    LA_leksema!=LA_k_in&&
    LA_leksema!=LA_d_zag&&
    LA_leksema!=LA_k_end&&
    LA_leksema!=LA_zarez&&
    LA_leksema!=LA_separator&&
    LA_leksema!=LA_k_or&&
    LA_leksema!=LA_k_and&&
    LA_leksema!=LA_eq&&
    LA_leksema!=LA_neq&&
    LA_leksema!=LA_lt&&
    LA_leksema!=LA_le&&
    LA_leksema!=LA_gt&&
    LA_leksema!=LA_ge&&
    LA_leksema!=LA_plus&&
    LA_leksema!=LA_minus&&
    LA_leksema!=LA_tacka&&
    LA_leksema!=LA_d_u_zag
  )
    LA_error("Ocekivao sam: EOF then else do until in ) end , ; or and = <> < <= > >= + - . * / mod ]");
}

void SA_izraz_c(void)
{
  switch(LA_leksema)
  {
    case LA_ime:
    case LA_l_zag:
    case LA_minus:
    case LA_k_not:
    case LA_k_true:
    case LA_k_false:
    case LA_k_sfin:
    case LA_k_sfout:
    case LA_integer:
    case LA_real:
    case LA_string:
      SA_izraz_b();
      SA_izraz_c_1();
      break;
    default:
      LA_error("Ocekivao sam: ime ( - not true false sfin sfout integer real string");
  }
}

void SA_izraz_d_1(void)
{
  while
  (
    LA_leksema==LA_plus||
    LA_leksema==LA_minus||
    LA_leksema==LA_tacka
  )
    switch(LA_leksema)
    {
      case LA_plus:
        LA_scanner();
        SA_izraz_c();
        if(Radi==R_normal)
          SF_plus();
        break;
      case LA_minus:
        LA_scanner();
        SA_izraz_c();
        if(Radi==R_normal)
          SF_minus();
        break;
      case LA_tacka:
        LA_scanner();
        SA_izraz_c();
        if(Radi==R_normal)
          SF_konkatenacija();
    }
  if
  (
    LA_leksema!=LA_EOF&&
    LA_leksema!=LA_k_then&&
    LA_leksema!=LA_k_else&&
    LA_leksema!=LA_k_do&&
    LA_leksema!=LA_k_until&&
    LA_leksema!=LA_k_in&&
    LA_leksema!=LA_d_zag&&
    LA_leksema!=LA_k_end&&
    LA_leksema!=LA_zarez&&
    LA_leksema!=LA_separator&&
    LA_leksema!=LA_k_or&&
    LA_leksema!=LA_k_and&&
    LA_leksema!=LA_eq&&
    LA_leksema!=LA_neq&&
    LA_leksema!=LA_lt&&
    LA_leksema!=LA_le&&
    LA_leksema!=LA_gt&&
    LA_leksema!=LA_ge&&
    LA_leksema!=LA_d_u_zag
  )
    LA_error("Ocekivao sam: EOF then else do until in ) end , ; or and = <> < <= > >= + - . ]");
}

void SA_izraz_d(void)
{
  switch(LA_leksema)
  {
    case LA_ime:
    case LA_l_zag:
    case LA_minus:
    case LA_k_not:
    case LA_k_true:
    case LA_k_false:
    case LA_k_sfin:
    case LA_k_sfout:
    case LA_integer:
    case LA_real:
    case LA_string:
      SA_izraz_c();
      SA_izraz_d_1();
      break;
    default:
      LA_error("Ocekivao sam: ime ( - not true false sfin sfout integer real string");
  }
}

void SA_izraz_e_1(void)
{
  while
  (
    LA_leksema==LA_lt||
    LA_leksema==LA_le||
    LA_leksema==LA_gt||
    LA_leksema==LA_ge||
    LA_leksema==LA_k_in
  )
    switch(LA_leksema)
    {
      case LA_lt:
        LA_scanner();
        SA_izraz_d();
        if(Radi==R_normal)
          SF_lt();
        break;
      case LA_le:
        LA_scanner();
        SA_izraz_d();
        if(Radi==R_normal)
          SF_le();
        break;
      case LA_gt:
        LA_scanner();
        SA_izraz_d();
        if(Radi==R_normal)
          SF_gt();
        break;
      case LA_ge:
        LA_scanner();
        SA_izraz_d();
        if(Radi==R_normal)
          SF_ge();
        break;
      case LA_k_in:
        LA_scanner();
        SA_izraz_d();
        if(Radi==R_normal)
          SF_in();
    }
  if
  (
    LA_leksema!=LA_EOF&&
    LA_leksema!=LA_k_then&&
    LA_leksema!=LA_k_else&&
    LA_leksema!=LA_k_do&&
    LA_leksema!=LA_k_until&&
    LA_leksema!=LA_d_zag&&
    LA_leksema!=LA_k_end&&
    LA_leksema!=LA_zarez&&
    LA_leksema!=LA_separator&&
    LA_leksema!=LA_k_or&&
    LA_leksema!=LA_k_and&&
    LA_leksema!=LA_eq&&
    LA_leksema!=LA_neq&&
    LA_leksema!=LA_d_u_zag
  )
    LA_error("Ocekivao sam: EOF then else do until in ) end , ; or and = <> < <= > >= ]");
}

void SA_izraz_e(void)
{
  switch(LA_leksema)
  {
    case LA_ime:
    case LA_l_zag:
    case LA_minus:
    case LA_k_not:
    case LA_k_true:
    case LA_k_false:
    case LA_k_sfin:
    case LA_k_sfout:
    case LA_integer:
    case LA_real:
    case LA_string:
      SA_izraz_d();
      SA_izraz_e_1();
      break;
    default:
      LA_error("Ocekivao sam: ime ( - not true false sfin sfout integer real string");
  }
}

void SA_izraz_f_1(void)
{
  while
  (
    LA_leksema==LA_eq||
    LA_leksema==LA_neq
  )
    switch(LA_leksema)
    {
      case LA_eq:
        LA_scanner();
        SA_izraz_e();
        if(Radi==R_normal)
          SF_eq();
        break;
      case LA_neq:
        LA_scanner();
        SA_izraz_e();
        if(Radi==R_normal)
          SF_neq();
    }
  if
  (
    LA_leksema!=LA_EOF&&
    LA_leksema!=LA_k_then&&
    LA_leksema!=LA_k_else&&
    LA_leksema!=LA_k_do&&
    LA_leksema!=LA_k_until&&
    LA_leksema!=LA_d_zag&&
    LA_leksema!=LA_k_end&&
    LA_leksema!=LA_zarez&&
    LA_leksema!=LA_separator&&
    LA_leksema!=LA_k_or&&
    LA_leksema!=LA_k_and&&
    LA_leksema!=LA_d_u_zag
  )
    LA_error("Ocekivao sam: EOF then else do until ) end , ; or and = <> ]");
}

void SA_izraz_f(void)
{
  switch(LA_leksema)
  {
    case LA_ime:
    case LA_l_zag:
    case LA_minus:
    case LA_k_not:
    case LA_k_true:
    case LA_k_false:
    case LA_k_sfin:
    case LA_k_sfout:
    case LA_integer:
    case LA_real:
    case LA_string:
      SA_izraz_e();
      SA_izraz_f_1();
      break;
    default:
      LA_error("Ocekivao sam: ime ( - not true false sfin sfout integer real string");
  }
}

void SA_izraz_1(void)
{
  while
  (
    LA_leksema==LA_k_or||
    LA_leksema==LA_k_and
  )
    switch(LA_leksema)
    {
      case LA_k_or:
        LA_scanner();
        SA_izraz_f();
        if(Radi==R_normal)
          SF_or();
        break;
      case LA_k_and:
        LA_scanner();
        SA_izraz_f();
        if(Radi==R_normal)
          SF_and();
    }
  if
  (
    LA_leksema!=LA_EOF&&
    LA_leksema!=LA_k_then&&
    LA_leksema!=LA_k_else&&
    LA_leksema!=LA_k_do&&
    LA_leksema!=LA_k_until&&
    LA_leksema!=LA_d_zag&&
    LA_leksema!=LA_k_end&&
    LA_leksema!=LA_zarez&&
    LA_leksema!=LA_separator&&
    LA_leksema!=LA_d_u_zag
  )
    LA_error("Ocekivao sam: EOF then else do until ) end , ; or and ]");
}

void SA_izraz(void)
{
  switch(LA_leksema)
  {
    case LA_ime:
    case LA_l_zag:
    case LA_minus:
    case LA_k_not:
    case LA_k_true:
    case LA_k_false:
    case LA_k_sfin:
    case LA_k_sfout:
    case LA_integer:
    case LA_real:
    case LA_string:
      SA_izraz_f();
      SA_izraz_1();
      break;
    default:
      LA_error("Ocekivao sam: ime ( - not true false sfin sfout integer real string");
  }
}

void SA_mozda_izraz(void)
{
  switch(LA_leksema)
  {
    case LA_ime:
    case LA_l_zag:
    case LA_minus:
    case LA_k_not:
    case LA_k_true:
    case LA_k_false:
    case LA_k_sfin:
    case LA_k_sfout:
    case LA_integer:
    case LA_real:
    case LA_string:
      SA_izraz();
      if(Radi==R_normal)
        SF_return_func();
      break;
    case LA_EOF:
    case LA_k_else:
    case LA_k_until:
    case LA_k_end:
    case LA_separator:
      if(Radi==R_normal)
        SF_return_proc();
      break;
    default:
      LA_error("Ocekivao sam: EOF else until ime ( end ; - not true false sfin sfout integer real string");
  }
}

void SA_naredbe(void)
{
  while(LA_leksema==LA_separator)
  {
      LA_scanner();
      SA_naredba();
  }
  if
  (
    LA_leksema!=LA_EOF&&
    LA_leksema!=LA_k_end
  )
    LA_error("Ocekivao sam: EOF end ;");
}

void SA_o_imena(void)
{
  while(LA_leksema==LA_zarez)
  {
    LA_scanner();
    if(LA_leksema!=LA_ime)
      LA_error("Ocekivao sam: ime");
    if(Radi==R_normal)
      SF_dodaj_argument();
    LA_scanner();
  }
  if(LA_leksema!=LA_d_zag)
    LA_error("Ocekivao sam: ) ,");
}

void SA_imena(void)
{
  switch(LA_leksema)
  {
    case LA_ime:
      if(Radi==R_normal)
        SF_dodaj_argument();
      LA_scanner();
      SA_o_imena();
      break;
    case LA_d_zag:
      break;
    default:
      LA_error("Ocekivao sam: ime )");
  }
}

void SA_dodela_ili_procedura(void)
{
  switch(LA_leksema)
  {
    case LA_dodela:
    case LA_l_u_zag:
      SA_niz();
      if(LA_leksema!=LA_dodela)
        LA_error("Ocekivao sam: :=");
      LA_scanner();
      SA_izraz();
      if(Radi==R_normal)
        SF_dodela();
      break;
    case LA_l_zag:
      if(Radi==R_normal)
        SF_procedura();
      LA_scanner();
      SA_argumenti();
      if(LA_leksema!=LA_d_zag)
        LA_error("Ocekivao sam: )");
      if(Radi==R_normal)
        SF_poziv_procedure();
      LA_scanner();
      break;
    default:
      LA_error("Ocekivao sam: ( := [");
  }
}

void SA_naredba(void)
{
  int radi;
  switch(LA_leksema)
  {
    case LA_k_if:
      LA_scanner();
      SA_izraz();
      if(LA_leksema!=LA_k_then)
        LA_error("Ocekivao sam: then");
      LA_scanner();
      if(Radi==R_normal)
      {
        Dubina_steka--;
        Konvertuj_celiju_u_bool(&Stek[Dubina_steka]);
        if(Stek[Dubina_steka].vrednost.v_bool)
        {
          SA_naredba();
          if(LA_leksema==LA_k_else)
          {
            LA_scanner();
            radi=Radi;
            Radi=R_stop;
            SA_naredba();
            Radi=radi;
          }
        }
        else
        {
          Radi=R_stop;
          SA_naredba();
          Radi=R_normal;
          if(LA_leksema==LA_k_else)
          {
            LA_scanner();
            SA_naredba();
          }
        }
      }
      else
      {
        SA_naredba();
        if(LA_leksema==LA_k_else)
        {
          LA_scanner();
          SA_naredba();
        }
      }
      break;
    case LA_k_while:
      if(Radi==R_normal)
      {
        LA_pozicija pozicija;
        LA_uzmi_poziciju(&pozicija);
        do
        {
          LA_idi_na_poziciju(&pozicija);
          LA_scanner();
          SA_izraz();
          Dubina_steka--;
          Konvertuj_celiju_u_bool(&Stek[Dubina_steka]);
          if(!Stek[Dubina_steka].vrednost.v_bool)
            Radi=R_stop;
          if(LA_leksema!=LA_k_do)
            LA_error("Ocekivao sam: do");
          LA_scanner();
          SA_naredba();
          if(Radi==R_continue)
            Radi=R_normal;
        }
        while(Radi==R_normal);
        if(Radi!=R_return)
          Radi=R_normal;
      }
      else
      {
        LA_scanner();
        SA_izraz();
        if(LA_leksema!=LA_k_do)
          LA_error("Ocekivao sam: do");
        LA_scanner();
        SA_naredba();
      }
      break;
    case LA_k_do:
      if(Radi==R_normal)
      {
        LA_pozicija pozicija;
        LA_uzmi_poziciju(&pozicija);
        do
        {
          LA_idi_na_poziciju(&pozicija);
          LA_scanner();
          SA_naredba();
          if(Radi==R_continue)
            Radi=R_normal;
          if(LA_leksema!=LA_k_until)
            LA_error("Ocekivao sam: until");
          LA_scanner();
          SA_izraz();
          Dubina_steka--;
          Konvertuj_celiju_u_bool(&Stek[Dubina_steka]);
          if(Stek[Dubina_steka].vrednost.v_bool)
            Radi=R_stop;
        }
        while(Radi==R_normal);
        if(Radi!=R_return)
          Radi=R_normal;
      }
      else
      {
        LA_scanner();
        SA_naredba();
        if(LA_leksema!=LA_k_until)
          LA_error("Ocekivao sam: until");
        LA_scanner();
        SA_izraz();
      }
      break;
    case LA_k_loop:
      if(Radi==R_normal)
      {
        LA_pozicija pozicija;
        LA_uzmi_poziciju(&pozicija);
        do
        {
          LA_idi_na_poziciju(&pozicija);
          LA_scanner();
          SA_naredba();
          if(Radi==R_continue)
            Radi=R_normal;
        }
        while(Radi==R_normal);
        if(Radi!=R_return)
          Radi=R_normal;
      }
      else
      {
        LA_scanner();
        SA_naredba();
      }
      break;
    case LA_k_for:
      if(Radi==R_normal)
      {
        LA_pozicija pozicija;
        Celija *celija;
        Array *niz;
        int i;
        LA_scanner();
        SA_varijabla();
        SA_niz();
        if(LA_leksema!=LA_k_in)
          LA_error("Ocekivao sam: in");
        LA_scanner();
        SA_varijabla();
        SA_niz();
        SF_iz_memorije();
        Dubina_steka-=2;
        celija=Stek[Dubina_steka].vrednost.v_celija;
        Konvertuj_celiju_u_indeks(celija);
        Konvertuj_celiju_u_niz(&Stek[Dubina_steka+1]);
        niz=Stek[Dubina_steka+1].vrednost.v_array;
        if(LA_leksema!=LA_k_do)
          LA_error("Ocekivao sam: do");
        LA_uzmi_poziciju(&pozicija);
        i=0;
        do
        {
          LA_idi_na_poziciju(&pozicija);
          LA_scanner();
          if(i==niz->broj_indeksa)
            Radi=R_stop;
          else
          {
            Oslobodi_celiju(celija);
            Kopiraj_celiju(celija,&niz->indeksi[i].indeks,1);
            i++;
          }
          SA_naredba();
          if(Radi==R_continue)
            Radi=R_normal;
        }
        while(Radi==R_normal);
        if(Radi!=R_return)
          Radi=R_normal;
      }
      else
      {
        LA_scanner();
        SA_varijabla();
        SA_niz();
        if(LA_leksema!=LA_k_in)
          LA_error("Ocekivao sam: in");
        LA_scanner();
        SA_varijabla();
        SA_niz();
        if(LA_leksema!=LA_k_do)
          LA_error("Ocekivao sam: do");
        LA_scanner();
        SA_naredba();
      }
      break;
    case LA_ime:
      SA_varijabla();
      SA_dodela_ili_procedura();
      break;
    case LA_k_procedure:
      LA_scanner();
      if(LA_leksema!=LA_ime)
        LA_error("Ocekivao sam: ime");
      if(Radi==R_normal)
        SF_nova_procedure();
      LA_scanner();
      if(LA_leksema!=LA_l_zag)
        LA_error("Ocekivao sam: (");
      LA_scanner();
      SA_imena();
      if(LA_leksema!=LA_d_zag)
        LA_error("Ocekivao sam: )");
      LA_scanner();
      if(LA_leksema!=LA_k_is)
        LA_error("Ocekivao sam: is");
      if(Radi==R_normal)
        SF_def_func_proc();
      LA_scanner();
      radi=Radi;
      Radi=R_stop;
      SA_naredba();
      Radi=radi;
      break;
    case LA_k_function:
      LA_scanner();
      if(LA_leksema!=LA_ime)
        LA_error("Ocekivao sam: ime");
      if(Radi==R_normal)
        SF_nova_funkcije();
      LA_scanner();
      if(LA_leksema!=LA_l_zag)
        LA_error("Ocekivao sam: (");
      LA_scanner();
      SA_imena();
      if(LA_leksema!=LA_d_zag)
        LA_error("Ocekivao sam: )");
      LA_scanner();
      if(LA_leksema!=LA_k_is)
        LA_error("Ocekivao sam: is");
      if(Radi==R_normal)
        SF_def_func_proc();
      LA_scanner();
      radi=Radi;
      Radi=R_stop;
      SA_naredba();
      Radi=radi;
      break;
    case LA_k_begin:
      LA_scanner();
      SA_naredba();
      SA_naredbe();
      if(LA_leksema!=LA_k_end)
        LA_error("Ocekivao sam: end");
      LA_scanner();
      break;
    case LA_k_break:
      if(Radi==R_normal)
        SF_break();
      LA_scanner();
      break;
    case LA_k_continue:
      if(Radi==R_normal)
        SF_continue();
      LA_scanner();
      break;
    case LA_k_return:
      LA_scanner();
      SA_mozda_izraz();
      break;
    case LA_EOF:
    case LA_k_else:
    case LA_k_until:
    case LA_k_end:
    case LA_separator:
      break;
    default:
      LA_error("Ocekivao sam: EOF if else while do until loop for procedure ime function begin end break continue return ;");
  }
}

void SA_file_parser(FILE *f)
{
  LA_file_init(f);
  SD_init();
  SA_naredba();
  SA_naredbe();
  if(LA_leksema!=LA_EOF)
    LA_error("Ima jos na ulazu");
}

void SA_string_parser(char *s)
{
  LA_string_init(s);
  SD_init();
  SA_naredba();
  SA_naredbe();
  if(LA_leksema!=LA_EOF)
    LA_error("Ima jos na ulazu");
}
