#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "aprcom.h"

enum
{
  AC_lex_NISTA,
  AC_lex_L_U_ZAG,
  AC_lex_D_U_ZAG,
  AC_lex_OPCIJA,
  AC_lex_MINUS,
  AC_lex_AKCIJA,
  AC_lex_SLOVO,
  AC_lex_EOS
} AC_leksema;

char AC_vrednost_lekseme_slovo;
long AC_vrednost_lekseme_broj;
char *AC_ulaz;

int AC_scanner(void)
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
    ST_E
  } st=ST_0;
  int negativan;
  AC_leksema=AC_lex_NISTA;
  AC_pos=AC_r_pos;
  do
  {
    switch(st)
    {
      case ST_0:
        switch(*AC_ulaz)
        {
          case '/':
            st=ST_1;
            break;
          case '{':
            st=ST_2;
            break;
          case '[':
            AC_leksema=AC_lex_L_U_ZAG;
            st=ST_E;
            break;
          case ']':
            AC_leksema=AC_lex_D_U_ZAG;
            st=ST_E;
            break;
          case '?':
            AC_leksema=AC_lex_OPCIJA;
            st=ST_E;
            break;
          case '-':
            AC_leksema=AC_lex_MINUS;
            st=ST_E;
            break;
          case '\0':
            AC_leksema=AC_lex_EOS;
            st=ST_E;
            break;
          default:
            AC_leksema=AC_lex_SLOVO;
            AC_vrednost_lekseme_slovo=*AC_ulaz;
            st=ST_E;
        }
        break;
      case ST_1:
        if(*AC_ulaz!='\0')
        {
          AC_leksema=AC_lex_SLOVO;
          AC_vrednost_lekseme_slovo=*AC_ulaz;
        }
        else
          AC_error="Posle / ne sme doci kraj ulaza";
        st=ST_E;
        break;
      case ST_2:
        switch(*AC_ulaz)
        {
          case 'c':
          case 'C':
          case 'd':
          case 'D':
          case 'i':
          case 'I':
          case 'm':
          case 'M':
          case 's':
          case 'S':
            AC_vrednost_lekseme_slovo=*AC_ulaz;
            st=ST_3;
            break;
          default:
            AC_error="Posle { dodju slova: c C d D i I m M s S";
            st=ST_E;
        }
        break;
      case ST_3:
        negativan=0;
        if(*AC_ulaz=='=')
          st=ST_4;
        else
        {
          AC_error="Posle { i slova dodje =";
          st=ST_E;
        }
        break;
      case ST_4:
        switch(*AC_ulaz)
        {
          case '-':
            negativan=1;
          case '+':
            st=ST_5;
            break;
          default:
            if(isdigit((int)*AC_ulaz))
            {
              AC_vrednost_lekseme_broj=(long)(*AC_ulaz-'0');
              st=ST_6;
            }
            else
            {
              AC_error="Broj pocinje sa: + - cifra";
              st=ST_E;
            }
        }
        break;
      case ST_5:
        if(isdigit((int)*AC_ulaz))
        {
          AC_vrednost_lekseme_broj=(long)(*AC_ulaz-'0');
          st=ST_6;
        }
        else
        {
          AC_error="Broj pocinje cifrom";
          st=ST_E;
        }
        break;
      case ST_6:
        if(*AC_ulaz=='}')
        {
          AC_leksema=AC_lex_AKCIJA;
          if(negativan)
            AC_vrednost_lekseme_broj=-AC_vrednost_lekseme_broj;
          st=ST_E;
        }
        else
          if(isdigit((int)*AC_ulaz))
            AC_vrednost_lekseme_broj=AC_vrednost_lekseme_broj*10l+(long)(*AC_ulaz-'0');
          else
          {
            AC_error="Akcija se zavrsava sa }";
            st=ST_E;
          }
    }
    if(*AC_ulaz!='\0')
    {
      AC_ulaz++;
      AC_r_pos++;
    }
  }
  while(st!=ST_E);
  return AC_leksema==AC_lex_NISTA;
}

#define AC_MAX_DUZINA_UZORKA 256
SO_tip_AC_skup_slova AC_skupovi_slova[AC_MAX_DUZINA_UZORKA];
int AC_opcije[AC_MAX_DUZINA_UZORKA];
long AC_faktori_c[AC_MAX_DUZINA_UZORKA];
long AC_faktori_d[AC_MAX_DUZINA_UZORKA];
long AC_faktori_i[AC_MAX_DUZINA_UZORKA];
long AC_faktori_m[AC_MAX_DUZINA_UZORKA];
long AC_faktori_s[AC_MAX_DUZINA_UZORKA];
int AC_duzina;
long AC_tekuce_c;
long AC_tekuce_d;
long AC_tekuce_i;
long AC_tekuce_m;
long AC_tekuce_s;
struct
{
  unsigned char znak;
  SO_tip_AC_skup_slova skup_slova;
} AC_stek_skupova_slova[2];
int AC_velicina_steka_skupova_slova;

int AC_f_slovo(void)
{
  AC_velicina_steka_skupova_slova--;
  if(AC_duzina==AC_MAX_DUZINA_UZORKA)
  {
    AC_error="Mnogo dugacka niska uzorka";
    return 1;
  }
  SO_dodeli(AC_skupovi_slova[AC_duzina],AC_stek_skupova_slova[AC_velicina_steka_skupova_slova].skup_slova);
  AC_faktori_c[AC_duzina]=AC_tekuce_c;
  AC_faktori_d[AC_duzina]=AC_tekuce_d;
  AC_faktori_i[AC_duzina]=AC_tekuce_i;
  AC_faktori_m[AC_duzina]=AC_tekuce_m;
  AC_faktori_s[AC_duzina]=AC_tekuce_s;
  return 0;
}

int AC_f_znak(void)
{
  SO_izbaci_sve(AC_stek_skupova_slova[AC_velicina_steka_skupova_slova].skup_slova);
  SO_ubaci(AC_stek_skupova_slova[AC_velicina_steka_skupova_slova].skup_slova,(int)(unsigned char)AC_vrednost_lekseme_slovo);
  AC_stek_skupova_slova[AC_velicina_steka_skupova_slova].znak=(unsigned char)AC_vrednost_lekseme_slovo;
  AC_velicina_steka_skupova_slova++;
  return 0;
}

int AC_f_akcija(void)
{
  switch(AC_vrednost_lekseme_slovo)
  {
    case'C':
      AC_tekuce_c=AC_vrednost_lekseme_broj;
    case'c':
      AC_faktori_c[AC_duzina]=AC_vrednost_lekseme_broj;
      break;
    case'D':
      AC_tekuce_d=AC_vrednost_lekseme_broj;
    case'd':
      AC_faktori_d[AC_duzina]=AC_vrednost_lekseme_broj;
      break;
    case'I':
      AC_tekuce_i=AC_vrednost_lekseme_broj;
    case'i':
      AC_faktori_i[AC_duzina]=AC_vrednost_lekseme_broj;
      break;
    case'M':
      AC_tekuce_m=AC_vrednost_lekseme_broj;
    case'm':
      AC_faktori_m[AC_duzina]=AC_vrednost_lekseme_broj;
      break;
    case'S':
      AC_tekuce_s=AC_vrednost_lekseme_broj;
    case's':
      AC_faktori_s[AC_duzina]=AC_vrednost_lekseme_broj;
  }
  return 0;
}

int AC_f_opcija_true(void)
{
  AC_opcije[AC_duzina]=1;
  AC_duzina++;
  return 0;
}

int AC_f_opcija_false(void)
{
  AC_opcije[AC_duzina]=0;
  AC_duzina++;
  return 0;
}

int AC_f_unija(void)
{
  AC_velicina_steka_skupova_slova--;
  SO_unija(AC_stek_skupova_slova[AC_velicina_steka_skupova_slova-1].skup_slova,AC_stek_skupova_slova[AC_velicina_steka_skupova_slova].skup_slova);
  return 0;
}

int AC_f_komplement(void)
{
  SO_komplement(AC_stek_skupova_slova[AC_velicina_steka_skupova_slova-1].skup_slova);
  SO_izbaci(AC_stek_skupova_slova[AC_velicina_steka_skupova_slova-1].skup_slova,0);
  return 0;
}

int AC_f_sva_slova(void)
{
  SO_ubaci_sve(AC_stek_skupova_slova[AC_velicina_steka_skupova_slova].skup_slova);
  SO_izbaci(AC_stek_skupova_slova[AC_velicina_steka_skupova_slova].skup_slova,0);
  AC_velicina_steka_skupova_slova++;
  return 0;
}

int AC_f_od_do(void)
{
  int i;
  unsigned char s=AC_vrednost_lekseme_slovo;
  if(s>AC_stek_skupova_slova[AC_velicina_steka_skupova_slova-1].znak)
  {
    unsigned char t;
    t=s;
    s=AC_stek_skupova_slova[AC_velicina_steka_skupova_slova-1].znak;
    AC_stek_skupova_slova[AC_velicina_steka_skupova_slova-1].znak=t;
  }
  for(i=(int)s;i<=(int)AC_stek_skupova_slova[AC_velicina_steka_skupova_slova-1].znak;i++)
    SO_ubaci(AC_stek_skupova_slova[AC_velicina_steka_skupova_slova-1].skup_slova,i);
  return 0;
}

int AC_parser_G(void)
{
  switch(AC_leksema)
  {
    case AC_lex_MINUS:
      if(AC_scanner())
        return 1;
      if(AC_leksema!=AC_lex_SLOVO)
      {
        AC_error="Ocekivao sam: slovo";
        return 1;
      }
      if(AC_f_od_do())
        return 1;
      if(AC_scanner())
        return 1;
      break;
    case AC_lex_SLOVO:
    case AC_lex_L_U_ZAG:
    case AC_lex_D_U_ZAG:
      break;
    default:
      AC_error="Ocekivao sam: slovo [ ] -";
      return 1;
  }
  return 0;
}

int AC_parser_E(void)
{
  while(AC_leksema==AC_lex_SLOVO)
  {
    if(AC_f_znak())
      return 1;
    if(AC_scanner())
      return 1;
    if(AC_parser_G())
      return 1;
    if(AC_f_unija())
      return 1;
  }
  if
  (
    AC_leksema!=AC_lex_L_U_ZAG&&
    AC_leksema!=AC_lex_D_U_ZAG
  )
  {
    AC_error="Ocekivao sam: slovo [ ]";
    return 1;
  }
  return 0;
}

int AC_parser_F(void)
{
  switch(AC_leksema)
  {
    case AC_lex_SLOVO:
      if(AC_f_znak())
        return 1;
      if(AC_scanner())
        return 1;
      if(AC_parser_G())
        return 1;
      if(AC_parser_E())
        return 1;
      if(AC_f_komplement())
        return 1;
      break;
    case AC_lex_L_U_ZAG:
      if(AC_f_sva_slova())
        return 1;
      break;
    default:
      AC_error="Ocekivao sam: slovo [";
      return 1;
  }
  return 0;
}

int AC_parser_D(void)
{
  switch(AC_leksema)
  {
    case AC_lex_OPCIJA:
      if(AC_f_opcija_true())
        return 1;
      if(AC_scanner())
        return 1;
      break;
    case AC_lex_EOS:
    case AC_lex_SLOVO:
    case AC_lex_L_U_ZAG:
    case AC_lex_D_U_ZAG:
      if(AC_f_opcija_false())
        return 1;
      break;
    default:
      AC_error="Ocekivao sam: EOS slovo [ ] ?";
      return 1;
  }
  return 0;
}

int AC_parser_C(void)
{
  while(AC_leksema==AC_lex_AKCIJA)
  {
    if(AC_f_akcija())
      return 1;
    if(AC_scanner())
      return 1;
  }
  if
  (
    AC_leksema!=AC_lex_EOS&&
    AC_leksema!=AC_lex_SLOVO&&
    AC_leksema!=AC_lex_L_U_ZAG&&
    AC_leksema!=AC_lex_D_U_ZAG&&
    AC_leksema!=AC_lex_OPCIJA
  )
  {
    AC_error="Ocekivao sam: EOS slovo [ ] akciju ?";
    return 1;
  }
  return 0;
}

int AC_parser_B(void)
{
  switch(AC_leksema)
  {
    case AC_lex_SLOVO:
      if(AC_f_znak())
        return 1;
      if(AC_scanner())
        return 1;
      break;
    case AC_lex_L_U_ZAG:
      if(AC_scanner())
        return 1;
      if(AC_leksema!=AC_lex_SLOVO)
      {
        AC_error="Ocekivao sam: slovo";
        return 1;
      }
      if(AC_f_znak())
        return 1;
      if(AC_scanner())
        return 1;
      if(AC_parser_G())
        return 1;
      if(AC_parser_E())
        return 1;
      if(AC_leksema!=AC_lex_D_U_ZAG)
      {
        AC_error="Ocekivao sam: ]";
        return 1;
      }
      if(AC_scanner())
        return 1;
      break;
    case AC_lex_D_U_ZAG:
      if(AC_scanner())
        return 1;
      if(AC_parser_F())
        return 1;
      if(AC_leksema!=AC_lex_L_U_ZAG)
      {
        AC_error="Ocekivao sam: [";
        return 1;
      }
      if(AC_scanner())
        return 1;
      break;
    default:
      AC_error="Ocekivao sam: slovo [ ]";
      return 1;
  }
  return 0;
}

int AC_parser_A(void)
{
  while
  (
    AC_leksema==AC_lex_SLOVO||
    AC_leksema==AC_lex_L_U_ZAG||
    AC_leksema==AC_lex_D_U_ZAG
  )
  {
    if(AC_parser_B())
      return 1;
    if(AC_f_slovo())
      return 1;
    if(AC_parser_C())
      return 1;
    if(AC_parser_D())
      return 1;
  }
  if(AC_leksema!=AC_lex_EOS)
  {
    AC_error="Ocekivao sam: EOS slovo [ ]";
    return 1;
  }
  return 0;
}

int AC_parser(char *text,AC_uzorak *u)
{
  int i;
  AC_ulaz=text;
  AC_r_pos=0;
  if(AC_scanner())
    return 1;
  AC_duzina=0;
  AC_tekuce_c=1l;
  AC_tekuce_d=1l;
  AC_tekuce_i=1l;
  AC_tekuce_m=1l;
  AC_tekuce_s=1l;
  SO_izbaci_sve(AC_skupovi_slova[0]);
  AC_faktori_c[0]=AC_tekuce_c;
  AC_faktori_d[0]=AC_tekuce_d;
  AC_faktori_i[0]=AC_tekuce_i;
  AC_faktori_m[0]=AC_tekuce_m;
  AC_faktori_s[0]=AC_tekuce_s;
  AC_velicina_steka_skupova_slova=0;
  if
  (
    AC_leksema==AC_lex_EOS||
    AC_leksema==AC_lex_SLOVO||
    AC_leksema==AC_lex_L_U_ZAG||
    AC_leksema==AC_lex_D_U_ZAG||
    AC_leksema==AC_lex_AKCIJA
  )
  {
    if(AC_parser_C())
      return 1;
    if(AC_f_opcija_false())
      return 1;
    if(AC_parser_A())
      return 1;
  }
  else
  {
    AC_error="Ocekivao: EOS slovo [ ] akciju";
    return 1;
  }
  u->duzina=AC_duzina;
  if((u->slova=(struct AC_struct_slovo *)calloc(AC_duzina,sizeof(struct AC_struct_slovo)))==NULL)
  {
    AC_error="Nema memorije";
    return 1;
  }
  for(i=0;i<AC_duzina;i++)
  {
    SO_dodeli(u->slova[i].skup_slova,AC_skupovi_slova[i]);
    u->slova[i].opcija=AC_opcije[i];
    u->slova[i].faktor_c=AC_faktori_c[i];
    u->slova[i].faktor_d=AC_faktori_d[i];
    u->slova[i].faktor_i=AC_faktori_i[i];
    u->slova[i].faktor_m=AC_faktori_m[i];
    u->slova[i].faktor_s=AC_faktori_s[i];
  }
  return 0;
}

void AC_free_uzorak(AC_uzorak *u)
{
  free(u->slova);
}

int AC_i_element(SO_tip_AC_skup_slova ss,char c,int ignore)
{
  return
    ignore?
      SO_element(ss,toupper((int)(unsigned char)c))||
      SO_element(ss,tolower((int)(unsigned char)c)):
    SO_element(ss,(int)(unsigned char)c);
}

long AC_acs(AC_uzorak *u,char *text,int ignore)
{
  int i;
  int j;
  int m;
  m=strlen(text);
  u->slova[0].t[0]=0;
  for(i=1;i<u->duzina;i++)
  {
    u->slova[i].t[0]=u->slova[i-1].t[0];
    if(!u->slova[i-1].opcija)
      u->slova[i].t[0]+=u->slova[i].faktor_d*u->slova[i].faktor_m;
  }
  for(j=1;j<=m;j++)
  {
    long x;
    u->slova[0].t[j%3]=u->slova[0].t[(j-1)%3]+u->slova[0].faktor_i*u->slova[0].faktor_m;
    for(i=1;i<u->duzina;i++)
    {
      long y;
      x=u->slova[i].t[(j-1)%3]+u->slova[i].faktor_i*u->slova[i].faktor_m;;
      y=u->slova[i-1].t[j%3];
      if(!u->slova[i].opcija)
        y+=u->slova[i].faktor_d*u->slova[i].faktor_m;
      if(y<x)
        x=y;
      y=u->slova[i-1].t[(j-1)%3];
      if(!AC_i_element(u->slova[i].skup_slova,text[j-1],ignore))
        y+=u->slova[i].faktor_c*u->slova[i].faktor_m;
      if(y<x)
        x=y;
      if(i>=2&&j>=2)
      {
        if
        (
          AC_i_element(u->slova[i].skup_slova,text[j-2],ignore)&&
          AC_i_element(u->slova[i-1].skup_slova,text[j-1],ignore)
        )
        {
          y=u->slova[i-2].t[(j-2)%3]+u->slova[i].faktor_s*u->slova[i].faktor_m;
          if(y<x)
            x=y;
        }
      }
      u->slova[i].t[j%3]=x;
    }
  }
  return u->slova[u->duzina-1].t[m%3];
}
