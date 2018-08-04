#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexana.h"

int LA_nl;
int LA_cur;
int LA_new_nl;
int LA_new_cur;
int LA_slovo;
int LA_duzina_vrednosti_lekseme;
FILE *LA_file;
char *LA_string_begin;
char *LA_string_current;

void LA_error(char *s)
{
  fprintf(stderr,"(%d,%d) %s\n",LA_nl,LA_cur,s);
  exit(1);
}

int LA_getc(void)
{
  return LA_izvor==LA_izvor_file?fgetc(LA_file):*LA_string_current=='\0'?EOF:(int)*LA_string_current++;
}

void LA_scanner(void)
{
  enum
  {
    ST_0,
    ST_1,
    ST_2,
    ST_3,
    ST_4,
    ST_5,
    ST_6,
    ST_7,
    ST_8,
    ST_9,
    ST_10,
    ST_11,
    ST_12,
    ST_13,
    ST_14,
    ST_15,
    ST_16,
    ST_E
  } st;
  static struct
  {
    LA_tip_lekseme leksema;
    char *ime;
  } kljucne_reci[]=
  {
    {LA_k_and,"and"},
    {LA_k_begin,"begin"},
    {LA_k_break,"break"},
    {LA_k_continue,"continue"},
    {LA_k_do,"do"},
    {LA_k_else,"else"},
    {LA_k_end,"end"},
    {LA_k_false,"false"},
    {LA_k_for,"for"},
    {LA_k_function,"function"},
    {LA_k_if,"if"},
    {LA_k_in,"in"},
    {LA_k_is,"is"},
    {LA_k_loop,"loop"},
    {LA_k_mod,"mod"},
    {LA_k_not,"not"},
    {LA_k_or,"or"},
    {LA_k_procedure,"procedure"},
    {LA_k_return,"return"},
    {LA_k_sfin,"sfin"},
    {LA_k_sfout,"sfout"},
    {LA_k_then,"then"},
    {LA_k_true,"true"},
    {LA_k_until,"until"},
    {LA_k_while,"while"},
    {LA_NISTA,NULL}
  };
  st=ST_0;
  do
  {
    switch(st)
    {
      case ST_0:
        LA_leksema=LA_NISTA;
        LA_nl=LA_new_nl;
        LA_cur=LA_new_cur;
        LA_duzina_vrednosti_lekseme=0;
        switch(LA_slovo)
        {
          case EOF:
            LA_leksema=LA_EOF;
            st=ST_E;
            break;
          case (int)' ':
          case (int)'\t':
          case (int)'\n':
            break;
          case (int)'{':
            st=ST_1;
            break;
          case (int)'#':
            st=ST_2;
            break;
          case (int)'.':
            st=ST_4;
            break;
          case (int)'"':
            st=ST_9;
            break;
          case (int)':':
            st=ST_13;
            break;
          case (int)'<':
            st=ST_15;
            break;
          case (int)'>':
            st=ST_16;
            break;
          case (int)'(':
            LA_leksema=LA_l_zag;
            st=ST_E;
            break;
          case (int)')':
            LA_leksema=LA_d_zag;
            st=ST_E;
            break;
          case (int)'[':
            LA_leksema=LA_l_u_zag;
            st=ST_E;
            break;
          case (int)']':
            LA_leksema=LA_d_u_zag;
            st=ST_E;
            break;
          case (int)',':
            LA_leksema=LA_zarez;
            st=ST_E;
            break;
          case (int)';':
            LA_leksema=LA_separator;
            st=ST_E;
            break;
          case (int)'=':
            LA_leksema=LA_eq;
            st=ST_E;
            break;
          case (int)'+':
            LA_leksema=LA_plus;
            st=ST_E;
            break;
          case (int)'-':
            LA_leksema=LA_minus;
            st=ST_E;
            break;
          case (int)'*':
            LA_leksema=LA_puta;
            st=ST_E;
            break;
          case (int)'/':
            LA_leksema=LA_podeljeno;
            st=ST_E;
            break;
          default:
            st=isdigit(LA_slovo)?ST_3:isalpha(LA_slovo)||LA_slovo==(int)'_'?ST_14:ST_E;
        }
        break;
      case ST_1:
        LA_duzina_vrednosti_lekseme=0;
        switch(LA_slovo)
        {
          case EOF:
            LA_error("EOF unutar komentara");
            break;
          case (int)'}':
            st=ST_0;
        }
        break;
      case ST_2:
        LA_duzina_vrednosti_lekseme=0;
        switch(LA_slovo)
        {
          case EOF:
            LA_error("EOF unutar komentara");
            break;
          case (int)'\n':
            st=ST_0;
        }
        break;
      case ST_3:
        LA_leksema=LA_integer;
        switch(LA_slovo)
        {
          case (int)'.':
            st=ST_5;
            break;
          case (int)'E':
          case (int)'e':
            st=ST_6;
            break;
          default:
            if(!isdigit(LA_slovo))
              st=ST_E;
        }
        break;
      case ST_4:
        LA_leksema=LA_tacka;
        st=isdigit(LA_slovo)?ST_5:ST_E;
        break;
      case ST_5:
        LA_leksema=LA_real;
        switch(LA_slovo)
        {
          case (int)'E':
          case (int)'e':
            st=ST_6;
            break;
          default:
            if(!isdigit(LA_slovo))
              st=ST_E;
        }
        break;
      case ST_6:
        LA_leksema=LA_NISTA;
        switch(LA_slovo)
        {
          case (int)'+':
          case (int)'-':
            st=ST_8;
            break;
          default:
            st=isdigit(LA_slovo)?ST_7:ST_E;
        }
        break;
      case ST_7:
        LA_leksema=LA_real;
      case ST_8:
        st=isdigit(LA_slovo)?ST_7:ST_E;
        break;
      case ST_9:
        LA_duzina_vrednosti_lekseme=0;
      case ST_10:
        switch(LA_slovo)
        {
          case EOF:
            LA_error("String se ne sme zavrsavati EOF-om");
            break;
          case (int)'\\':
            st=ST_11;
            break;
          case (int)'"':
            LA_leksema=LA_string;
            st=ST_E;
            break;
          default:
            st=ST_10;
        }
        break;
      case ST_11:
        LA_duzina_vrednosti_lekseme--;
        switch(LA_slovo)
        {
          case EOF:
            LA_error("Posle \\ u stringu ne sme doci EOF");
            break;
          default:
            if(LA_slovo>=(int)'0'&&LA_slovo<=(int)'7')
            {
              LA_slovo-='0';
              st=ST_12;
            }
            else
            {
              switch(LA_slovo)
              {
                case (int)'a':
                  LA_slovo='\a';
                  break;
                case (int)'b':
                  LA_slovo='\b';
                  break;
                case (int)'f':
                  LA_slovo='\f';
                  break;
                case (int)'n':
                  LA_slovo='\n';
                  break;
                case (int)'r':
                  LA_slovo='\r';
                  break;
                case (int)'t':
                  LA_slovo='\t';
                  break;
                case (int)'v':
                  LA_slovo='\v';
              }
              st=ST_10;
            }
        }
        break;
      case ST_12:
        switch(LA_slovo)
        {
          case EOF:
            LA_error("Posle \\ i oktalnih ciffara u stringu ne sme doci EOF");
            break;
          case (int)'\\':
            st=ST_11;
            break;
          case (int)'"':
            LA_leksema=LA_string;
            st=ST_E;
            break;
          default:
            if(LA_slovo>=(int)'0'&&LA_slovo<=(int)'7')
            {
              LA_duzina_vrednosti_lekseme--;
              LA_slovo=LA_vrednost_lekseme[LA_duzina_vrednosti_lekseme]*8+LA_slovo-'0';
            }
            else
              st=ST_10;
        }
        break;
      case ST_13:
        if(LA_slovo==(int)'=')
        {
          LA_leksema=LA_dodela;
          st=ST_E;
        }
        else
          LA_error("Dodela se pise sa :=");
        break;
      case ST_14:
        LA_leksema=LA_ime;
        if(!isalnum(LA_slovo)&&LA_slovo!=(int)'_')
          st=ST_E;
        break;
      case ST_15:
        LA_leksema=LA_slovo==(int)'='?LA_le:LA_slovo==(int)'>'?LA_neq:LA_lt;
        st=ST_E;
        break;
      case ST_16:
        LA_leksema=LA_slovo==(int)'='?LA_ge:LA_gt;
        st=ST_E;
    }
    if(LA_slovo!=EOF)
    {
      if(LA_duzina_vrednosti_lekseme<LA_MAX_DUZINA_VREDNOSTI_LEKSEME)
      {
        LA_vrednost_lekseme[LA_duzina_vrednosti_lekseme]=(char)LA_slovo;
        LA_duzina_vrednosti_lekseme++;
      }
      if
      (
        st!=ST_E||
          LA_leksema!=LA_ime&&
          LA_leksema!=LA_integer&&
          LA_leksema!=LA_real&&
          LA_leksema!=LA_lt&&
          LA_leksema!=LA_gt&&
          LA_leksema!=LA_tacka
      )
      {
        LA_slovo=LA_getc();
        if(LA_slovo==(int)'\n')
        {
          LA_new_nl++;
          LA_new_cur=0;
        }
        else
          LA_new_cur++;
      }
    }
  }
  while(st!=ST_E);
  switch(LA_leksema)
  {
    case LA_NISTA:
      LA_error("Nepoznata leksema");
      break;
    case LA_integer:
    case LA_real:
    case LA_string:
    case LA_ime:
      if(LA_slovo!=EOF)
        LA_duzina_vrednosti_lekseme--;
      LA_vrednost_lekseme[LA_duzina_vrednosti_lekseme]='\0';
      if(LA_leksema==LA_ime)
      {
        int i;
        i=0;
        while
        (
          kljucne_reci[i].leksema!=LA_NISTA&&
          strcmp(LA_vrednost_lekseme,kljucne_reci[i].ime)
        )
          i++;
        if(kljucne_reci[i].leksema!=LA_NISTA)
          LA_leksema=kljucne_reci[i].leksema;
      }
  }
}

void LA_uzmi_poziciju(LA_pozicija *p)
{
  p->nl=LA_new_nl;
  p->cur=LA_new_cur;
  p->slovo=LA_slovo;
  p->pos=LA_izvor==LA_izvor_file?ftell(LA_file):(long)(LA_string_current-LA_string_begin);
}

void LA_idi_na_poziciju(LA_pozicija *p)
{
  if(LA_izvor==LA_izvor_file)
    fseek(LA_file,p->pos,SEEK_SET);
  else
    LA_string_current=LA_string_begin+p->pos;
  LA_slovo=p->slovo;
  LA_new_cur=p->cur;
  LA_new_nl=p->nl;
}

void LA_file_init(FILE *f)
{
  LA_izvor=LA_izvor_file;
  LA_file=f;
  LA_slovo=LA_getc();
  LA_new_nl=1;
  LA_new_cur=1;
  LA_scanner();
}

void LA_string_init(char *s)
{
  LA_izvor=LA_izvor_string;
  LA_string_begin=s;
  LA_string_current=LA_string_begin;
  LA_slovo=LA_getc();
  LA_new_nl=1;
  LA_new_cur=1;
  LA_scanner();
}
