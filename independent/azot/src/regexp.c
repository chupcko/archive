#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "regexp.h"

enum
{
  RE_lex_NISTA,
  RE_lex_ILI,
  RE_lex_ZVEZDICA,
  RE_lex_PLUS,
  RE_lex_OPCIJA,
  RE_lex_KAPA,
  RE_lex_DOLAR,
  RE_lex_L_U_ZAG,
  RE_lex_D_U_ZAG,
  RE_lex_L_ZAG,
  RE_lex_D_ZAG,
  RE_lex_MANJE,
  RE_lex_VECE,
  RE_lex_MINUS,
  RE_lex_AKCIJA,
  RE_lex_SLOVO,
  RE_lex_EOS
} RE_leksema;

RE_tip_ime_akcije RE_vrednost_lekseme;
int RE_duzina_vrednosti_lekseme;
char *RE_ulaz;

int RE_scanner(void)
{
  enum
  {
    ST_0,
    ST_1,
    ST_2,
    ST_3,
    ST_4,
    ST_E
  } st=ST_0;
  RE_leksema=RE_lex_NISTA;
  RE_pos=RE_r_pos;
  do
  {
    switch(st)
    {
      case ST_0:
        switch(*RE_ulaz)
        {
          case '|':
            RE_leksema=RE_lex_ILI;
            st=ST_E;
            break;
          case '*':
            RE_leksema=RE_lex_ZVEZDICA;
            st=ST_E;
            break;
          case '+':
            RE_leksema=RE_lex_PLUS;
            st=ST_E;
            break;
          case '?':
            RE_leksema=RE_lex_OPCIJA;
            st=ST_E;
            break;
          case '^':
            RE_leksema=RE_lex_KAPA;
            st=ST_E;
            break;
          case '$':
            RE_leksema=RE_lex_DOLAR;
            st=ST_E;
            break;
          case '[':
            RE_leksema=RE_lex_L_U_ZAG;
            st=ST_E;
            break;
          case ']':
            RE_leksema=RE_lex_D_U_ZAG;
            st=ST_E;
            break;
          case '(':
            RE_leksema=RE_lex_L_ZAG;
            st=ST_E;
            break;
          case ')':
            RE_leksema=RE_lex_D_ZAG;
            st=ST_E;
            break;
          case '<':
            RE_leksema=RE_lex_MANJE;
            st=ST_E;
            break;
          case '>':
            RE_leksema=RE_lex_VECE;
            st=ST_E;
            break;
          case '-':
            RE_leksema=RE_lex_MINUS;
            st=ST_E;
            break;
          case '\0':
            RE_leksema=RE_lex_EOS;
            st=ST_E;
            break;
          case '{':
            st=ST_2;
            break;
          case '/':
            st=ST_1;
            break;
          default:
            RE_leksema=RE_lex_SLOVO;
            RE_vrednost_lekseme[0]=*RE_ulaz;
            st=ST_E;
        }
        break;
      case ST_1:
        if(*RE_ulaz!='\0')
        {
          RE_leksema=RE_lex_SLOVO;
          RE_vrednost_lekseme[0]=*RE_ulaz;
        }
        else
          RE_error="Posle / ne sme doci kraj ulaza";
        st=ST_E;
        break;
      case ST_2:
        RE_duzina_vrednosti_lekseme=0;
        switch(*RE_ulaz)
        {
          case '/':
            st=ST_3;
            break;
          case '}':
            RE_error="Akcija ne sme biti prazna";
            st=ST_E;
            break;
          case '\0':
            RE_error="Posle { ne sme doci kraj ulaza";
            st=ST_E;
            break;
          default:
            if(RE_duzina_vrednosti_lekseme<RE_MAX_DUZINA_VREDNOSTI_LEKSEME)
              RE_vrednost_lekseme[RE_duzina_vrednosti_lekseme++]=*RE_ulaz;
            st=ST_4;
        }
        break;
      case ST_3:
        if(*RE_ulaz!='\0')
        {
          if(RE_duzina_vrednosti_lekseme<RE_MAX_DUZINA_VREDNOSTI_LEKSEME)
            RE_vrednost_lekseme[RE_duzina_vrednosti_lekseme++]=*RE_ulaz;
          st=ST_4;
        }
        else
        {
          RE_error="Posle / ne sme doci kraj ulaza";
          st=ST_E;
        }
        break;
      case ST_4:
        switch(*RE_ulaz)
        {
          case '/':
            st=ST_3;
            break;
          case '}':
            RE_leksema=RE_lex_AKCIJA;
            RE_vrednost_lekseme[RE_duzina_vrednosti_lekseme]='\0';
            st=ST_E;
          case '\0':
            RE_error="Akcija se mora zavrsiti sa } a ne sa krajem ulaza";
            st=ST_E;
            break;
          default:
            if(RE_duzina_vrednosti_lekseme<RE_MAX_DUZINA_VREDNOSTI_LEKSEME)
              RE_vrednost_lekseme[RE_duzina_vrednosti_lekseme++]=*RE_ulaz;
        }
    }
    if(*RE_ulaz!='\0')
    {
      RE_ulaz++;
      RE_r_pos++;
    }
  }
  while(st!=ST_E);
  return RE_leksema==RE_lex_NISTA;
}

typedef struct
{
  int od_stanja;
  int skup_slova;
  int do_stanja;
} RE_tip_prelaz;

#define RE_MAX_BROJ_AKCIJA 64
RE_tip_ime_akcije RE_imena_akcija[RE_MAX_BROJ_AKCIJA];
int RE_broj_akcija;
#define RE_MAX_DUBINA 64
int RE_dubina;
struct
{
  enum
  {
    RE_va_nista,
    RE_va_akcija,
    RE_va_manje,
    RE_va_vece
  } tip;
  int ime_ili_dubina;
} RE_koja_akcija[RE_MAX_BROJ_STANJA];
int RE_broj_stanja;
#define RE_MAX_BROJ_SKUPOVA_SLOVA 256
SO_tip_RE_skup_slova RE_skupovi_slova[RE_MAX_BROJ_SKUPOVA_SLOVA];
#define RE_slovo_kapa (-1)
#define RE_slovo_dolar (-2)
#define RE_slovo_epsilon (-3)
int RE_broj_skupova_slova;
#define RE_MAX_BROJ_PRELAZA 16384
RE_tip_prelaz RE_prelazi[RE_MAX_BROJ_PRELAZA];
int RE_broj_prelaza;

struct
{
  unsigned char znak;
  SO_tip_RE_skup_slova skup_slova;
} RE_stek_skupova_slova[2];
int RE_velicina_steka_skupova_slova;
#define RE_MAX_VELICINA_STEKA_STANJA (RE_MAX_BROJ_STANJA/2)
struct
{
  int od_stanja;
  int do_stanja;
} RE_stek_stanja[RE_MAX_VELICINA_STEKA_STANJA];
int RE_velicina_steka_stanja;

int RE_novo_stanje(void)
{
  if(RE_broj_stanja==RE_MAX_BROJ_STANJA)
  {
    RE_error="Nema vise mesta za stanja";
    return -1;
  }
  RE_koja_akcija[RE_broj_stanja].tip=RE_va_nista;
  RE_broj_stanja++;
  return RE_broj_stanja-1;
}

int RE_novi_prelaz(int od_stanja,int skup_slova,int do_stanja)
{
  if(RE_broj_prelaza==RE_MAX_BROJ_PRELAZA)
  {
    RE_error="Nema vise mesta za prelaze";
    return 1;
  }
  RE_prelazi[RE_broj_prelaza].od_stanja=od_stanja;
  RE_prelazi[RE_broj_prelaza].skup_slova=skup_slova;
  RE_prelazi[RE_broj_prelaza].do_stanja=do_stanja;
  RE_broj_prelaza++;
  return 0;
}

int RE_smesti_na_stek_stanja(int skup_slova)
{
  int od_stanja;
  int do_stanja;
  if(RE_velicina_steka_stanja==RE_MAX_VELICINA_STEKA_STANJA)
  {
    RE_error="Nema vise mesta na steku stanja";
    return 1;
  }
  if((od_stanja=RE_novo_stanje())==-1)
    return 1;
  if((do_stanja=RE_novo_stanje())==-1)
    return 1;
  if(RE_novi_prelaz(od_stanja,skup_slova,do_stanja)==-1)
    return 1;
  RE_stek_stanja[RE_velicina_steka_stanja].od_stanja=od_stanja;
  RE_stek_stanja[RE_velicina_steka_stanja].do_stanja=do_stanja;
  RE_velicina_steka_stanja++;
  return 0;
}

int RE_f_ili(void)
{
  int od_stanja;
  int do_stanja;
  RE_velicina_steka_stanja--;
  od_stanja=RE_stek_stanja[RE_velicina_steka_stanja-1].od_stanja;
  do_stanja=RE_stek_stanja[RE_velicina_steka_stanja-1].do_stanja;
  if((RE_stek_stanja[RE_velicina_steka_stanja-1].od_stanja=RE_novo_stanje())==-1)
    return 1;
  if((RE_stek_stanja[RE_velicina_steka_stanja-1].do_stanja=RE_novo_stanje())==-1)
    return 1;
  return
    RE_novi_prelaz(RE_stek_stanja[RE_velicina_steka_stanja-1].od_stanja,RE_slovo_epsilon,od_stanja)||
    RE_novi_prelaz(RE_stek_stanja[RE_velicina_steka_stanja-1].od_stanja,RE_slovo_epsilon,RE_stek_stanja[RE_velicina_steka_stanja].od_stanja)||
    RE_novi_prelaz(do_stanja,RE_slovo_epsilon,RE_stek_stanja[RE_velicina_steka_stanja-1].do_stanja)||
    RE_novi_prelaz(RE_stek_stanja[RE_velicina_steka_stanja].do_stanja,RE_slovo_epsilon,RE_stek_stanja[RE_velicina_steka_stanja-1].do_stanja);
}

int RE_f_konkatenacija(void)
{
  int do_stanja;
  RE_velicina_steka_stanja--;
  do_stanja=RE_stek_stanja[RE_velicina_steka_stanja-1].do_stanja;
  RE_stek_stanja[RE_velicina_steka_stanja-1].do_stanja=RE_stek_stanja[RE_velicina_steka_stanja].do_stanja;
  return RE_novi_prelaz(do_stanja,RE_slovo_epsilon,RE_stek_stanja[RE_velicina_steka_stanja].od_stanja);
}

int RE_f_plus(void)
{
  int od_stanja;
  int do_stanja;
  od_stanja=RE_stek_stanja[RE_velicina_steka_stanja-1].od_stanja;
  do_stanja=RE_stek_stanja[RE_velicina_steka_stanja-1].do_stanja;
  if((RE_stek_stanja[RE_velicina_steka_stanja-1].od_stanja=RE_novo_stanje())==-1)
    return 1;
  if((RE_stek_stanja[RE_velicina_steka_stanja-1].do_stanja=RE_novo_stanje())==-1)
    return 1;
  return
    RE_novi_prelaz(do_stanja,RE_slovo_epsilon,od_stanja)||
    RE_novi_prelaz(RE_stek_stanja[RE_velicina_steka_stanja-1].od_stanja,RE_slovo_epsilon,od_stanja)||
    RE_novi_prelaz(do_stanja,RE_slovo_epsilon,RE_stek_stanja[RE_velicina_steka_stanja-1].do_stanja);
}

int RE_f_opcija(void)
{
  return RE_novi_prelaz(RE_stek_stanja[RE_velicina_steka_stanja-1].od_stanja,RE_slovo_epsilon,RE_stek_stanja[RE_velicina_steka_stanja-1].do_stanja);
}

int RE_f_zvezdica(void)
{
  return RE_f_plus()||RE_f_opcija();
}

int RE_f_slovo(void)
{
  int i;
  RE_velicina_steka_skupova_slova--;
  i=0;
  while(i<RE_broj_skupova_slova&&!SO_jednaki(RE_skupovi_slova[i],RE_stek_skupova_slova[RE_velicina_steka_skupova_slova].skup_slova))
    i++;
  if(i==RE_broj_skupova_slova)
  {
    if(RE_broj_skupova_slova==RE_MAX_BROJ_SKUPOVA_SLOVA)
    {
      RE_error="Mnogo skupova slova";
      return -1;
    }
    SO_dodeli(RE_skupovi_slova[RE_broj_skupova_slova],RE_stek_skupova_slova[RE_velicina_steka_skupova_slova].skup_slova);
    RE_broj_skupova_slova++;
  }
  return RE_smesti_na_stek_stanja(i);
}

int RE_f_kapa(void)
{
  return RE_smesti_na_stek_stanja(RE_slovo_kapa);
}

int RE_f_dolar(void)
{
  return RE_smesti_na_stek_stanja(RE_slovo_dolar);
}

int RE_f_znak(void)
{
  SO_izbaci_sve(RE_stek_skupova_slova[RE_velicina_steka_skupova_slova].skup_slova);
  SO_ubaci(RE_stek_skupova_slova[RE_velicina_steka_skupova_slova].skup_slova,(int)(unsigned char)*RE_vrednost_lekseme);
  RE_stek_skupova_slova[RE_velicina_steka_skupova_slova].znak=(unsigned char)*RE_vrednost_lekseme;
  RE_velicina_steka_skupova_slova++;
  return 0;
}

int RE_f_manje_vece(void)
{
  if(RE_dubina==RE_MAX_DUBINA)
  {
    RE_error="Mnogo dubina";
    return 1;
  }
  RE_koja_akcija[RE_stek_stanja[RE_velicina_steka_stanja-1].od_stanja].tip=RE_va_manje;
  RE_koja_akcija[RE_stek_stanja[RE_velicina_steka_stanja-1].od_stanja].ime_ili_dubina=RE_dubina;
  RE_koja_akcija[RE_stek_stanja[RE_velicina_steka_stanja-1].do_stanja].tip=RE_va_vece;
  RE_koja_akcija[RE_stek_stanja[RE_velicina_steka_stanja-1].do_stanja].ime_ili_dubina=RE_dubina;
  RE_dubina++;
  return 0;
}

int RE_f_akcija(void)
{
  int i;
  i=0;
  while(i<RE_broj_akcija&&strncmp(RE_imena_akcija[i],RE_vrednost_lekseme,sizeof(RE_tip_ime_akcije)))
    i++;
  if(i==RE_broj_akcija)
  {
    if(RE_broj_akcija==RE_MAX_BROJ_AKCIJA)
    {
      RE_error="Mnogo akcija";
      return 1;
    }
    strncpy(RE_imena_akcija[RE_broj_akcija],RE_vrednost_lekseme,sizeof(RE_tip_ime_akcije));
    RE_broj_akcija++;
  }
  if(RE_smesti_na_stek_stanja(RE_slovo_epsilon))
    return 1;
  RE_koja_akcija[RE_stek_stanja[RE_velicina_steka_stanja-1].do_stanja].tip=RE_va_akcija;
  RE_koja_akcija[RE_stek_stanja[RE_velicina_steka_stanja-1].do_stanja].ime_ili_dubina=i;
  return 0;
}

int RE_f_unija(void)
{
  RE_velicina_steka_skupova_slova--;
  SO_unija(RE_stek_skupova_slova[RE_velicina_steka_skupova_slova-1].skup_slova,RE_stek_skupova_slova[RE_velicina_steka_skupova_slova].skup_slova);
  return 0;
}

int RE_f_od_do(void)
{
  int i;
  unsigned char s=*RE_vrednost_lekseme;
  if(s>RE_stek_skupova_slova[RE_velicina_steka_skupova_slova-1].znak)
  {
    unsigned char t;
    t=s;
    s=RE_stek_skupova_slova[RE_velicina_steka_skupova_slova-1].znak;
    RE_stek_skupova_slova[RE_velicina_steka_skupova_slova-1].znak=t;
  }
  for(i=(int)s;i<=(int)RE_stek_skupova_slova[RE_velicina_steka_skupova_slova-1].znak;i++)
    SO_ubaci(RE_stek_skupova_slova[RE_velicina_steka_skupova_slova-1].skup_slova,i);
  return 0;
}

int RE_f_komplement(void)
{
  SO_komplement(RE_stek_skupova_slova[RE_velicina_steka_skupova_slova-1].skup_slova);
  SO_izbaci(RE_stek_skupova_slova[RE_velicina_steka_skupova_slova-1].skup_slova,0);
  return 0;
}

int RE_f_sva_slova(void)
{
  SO_ubaci_sve(RE_stek_skupova_slova[RE_velicina_steka_skupova_slova].skup_slova);
  SO_izbaci(RE_stek_skupova_slova[RE_velicina_steka_skupova_slova].skup_slova,0);
  RE_velicina_steka_skupova_slova++;
  return 0;
}

int RE_parser_F(void)
{
  switch(RE_leksema)
  {
    case RE_lex_MINUS:
      if(RE_scanner())
        return 1;
      if(RE_leksema!=RE_lex_SLOVO)
      {
        RE_error="Ocekivao sam: slovo";
        return 1;
      }
      if(RE_f_od_do())
        return 1;
      if(RE_scanner())
        return 1;
      break;
    case RE_lex_SLOVO:
    case RE_lex_L_U_ZAG:
    case RE_lex_D_U_ZAG:
      break;
    default:
      RE_error="Ocekivao sam: slovo [ ] -";
      return 1;
  }
  return 0;
}

int RE_parser_E(void)
{

  while(RE_leksema==RE_lex_SLOVO)
  {
    if(RE_f_znak())
      return 1;
    if(RE_scanner())
      return 1;
    if(RE_parser_F())
      return 1;
    if(RE_f_unija())
      return 1;
  }
  if
  (
    RE_leksema!=RE_lex_L_U_ZAG&&
    RE_leksema!=RE_lex_D_U_ZAG
  )
  {
    RE_error="Ocekivao sam: slovo [ ]";
    return 1;
  }
  return 0;
}

int RE_parser_G(void)
{
  switch(RE_leksema)
  {
    case RE_lex_SLOVO:
      if(RE_f_znak())
        return 1;
      if(RE_scanner())
        return 1;
      if(RE_parser_F())
        return 1;
      if(RE_parser_E())
        return 1;
      if(RE_f_komplement())
        return 1;
      break;
    case RE_lex_L_U_ZAG:
      if(RE_f_sva_slova())
        return 1;
      break;
    default:
      RE_error="Ocekivao sam: slovo [";
      return 1;
  }
  return 0;
}

int RE_parser_C(void)
{
  while
  (
    RE_leksema==RE_lex_ZVEZDICA||
    RE_leksema==RE_lex_PLUS||
    RE_leksema==RE_lex_OPCIJA
  )
  {
    switch(RE_leksema)
    {
      case RE_lex_ZVEZDICA:
        if(RE_f_zvezdica())
          return 1;
        break;
      case RE_lex_PLUS:
        if(RE_f_plus())
          return 1;
        break;
      case RE_lex_OPCIJA:
        if(RE_f_opcija())
          return 1;
    }
    if(RE_scanner())
      return 1;
  }
  if
  (
    RE_leksema!=RE_lex_EOS&&
    RE_leksema!=RE_lex_ILI&&
    RE_leksema!=RE_lex_SLOVO&&
    RE_leksema!=RE_lex_KAPA&&
    RE_leksema!=RE_lex_DOLAR&&
    RE_leksema!=RE_lex_L_U_ZAG&&
    RE_leksema!=RE_lex_D_U_ZAG&&
    RE_leksema!=RE_lex_L_ZAG&&
    RE_leksema!=RE_lex_D_ZAG&&
    RE_leksema!=RE_lex_MANJE&&
    RE_leksema!=RE_lex_VECE&&
    RE_leksema!=RE_lex_AKCIJA
  )
  {
    RE_error="Ocekivao sam: EOS | * + ? slovo ^ $ [ ] ( ) < > akciju";
    return 1;
  }
  return 0;
}

int RE_parser_D(void);

int RE_parser_B(void)
{
  while
  (
    RE_leksema==RE_lex_SLOVO||
    RE_leksema==RE_lex_KAPA||
    RE_leksema==RE_lex_DOLAR||
    RE_leksema==RE_lex_L_U_ZAG||
    RE_leksema==RE_lex_D_U_ZAG||
    RE_leksema==RE_lex_L_ZAG||
    RE_leksema==RE_lex_MANJE||
    RE_leksema==RE_lex_AKCIJA
  )
  {
    if(RE_parser_D())
      return 1;
    if(RE_parser_C())
      return 1;
    if(RE_f_konkatenacija())
      return 1;
  }
  if
  (
    RE_leksema!=RE_lex_EOS&&
    RE_leksema!=RE_lex_ILI&&
    RE_leksema!=RE_lex_D_ZAG&&
    RE_leksema!=RE_lex_VECE
  )
  {
    RE_error="Ocekivao sam: EOS | slovo ^ $ [ ] ( ) < > akciju";
    return 1;
  }
  return 0;
}

int RE_parser_A(void)
{
  while(RE_leksema==RE_lex_ILI)
  {
    if(RE_scanner())
      return 1;
    if(RE_parser_D())
      return 1;
    if(RE_parser_C())
      return 1;
    if(RE_parser_B())
      return 1;
    if(RE_f_ili())
      return 1;
  }
  if
  (
    RE_leksema!=RE_lex_EOS&&
    RE_leksema!=RE_lex_D_ZAG&&
    RE_leksema!=RE_lex_VECE
  )
  {
    RE_error="Ocekivao sam: EOS | ) >";
    return 1;
  }
  return 0;
}

int RE_parser_D(void)
{
  switch(RE_leksema)
  {
    case RE_lex_SLOVO:
      if(RE_f_znak())
        return 1;
      if(RE_f_slovo())
        return 1;
      if(RE_scanner())
        return 1;
      break;
    case RE_lex_KAPA:
      if(RE_f_kapa())
        return 1;
      if(RE_scanner())
        return 1;
      break;
    case RE_lex_DOLAR:
      if(RE_f_dolar())
        return 1;
      if(RE_scanner())
        return 1;
      break;
    case RE_lex_L_U_ZAG:
      if(RE_scanner())
        return 1;
      if(RE_leksema!=RE_lex_SLOVO)
      {
        RE_error="Ocekivao sam: slovo";
        return 1;
      }
      if(RE_f_znak())
        return 1;
      if(RE_scanner())
        return 1;
      if(RE_parser_F())
        return 1;
      if(RE_parser_E())
        return 1;
      if(RE_leksema!=RE_lex_D_U_ZAG)
      {
        RE_error="Ocekivao sam: ]";
        return 1;
      }
      if(RE_f_slovo())
        return 1;
      if(RE_scanner())
        return 1;
      break;
    case RE_lex_D_U_ZAG:
      if(RE_scanner())
        return 1;
      if(RE_parser_G())
        return 1;
      if(RE_leksema!=RE_lex_L_U_ZAG)
      {
        RE_error="Ocekivao sam: [";
        return 1;
      }
      if(RE_f_slovo())
        return 1;
      if(RE_scanner())
        return 1;
      break;
    case RE_lex_L_ZAG:
      if(RE_scanner())
        return 1;
      if(RE_parser_D())
        return 1;
      if(RE_parser_C())
        return 1;
      if(RE_parser_B())
        return 1;
      if(RE_parser_A())
        return 1;
      if(RE_leksema!=RE_lex_D_ZAG)
      {
        RE_error="Ocekivao sam: )";
        return 1;
      }
      if(RE_scanner())
        return 1;
      break;
    case RE_lex_MANJE:
      if(RE_scanner())
        return 1;
      if(RE_parser_D())
        return 1;
      if(RE_parser_C())
        return 1;
      if(RE_parser_B())
        return 1;
      if(RE_parser_A())
        return 1;
      if(RE_leksema!=RE_lex_VECE)
      {
        RE_error="Ocekivao sam: >";
        return 1;
      }
      if(RE_f_manje_vece())
        return 1;
      if(RE_scanner())
        return 1;
      break;
    case RE_lex_AKCIJA:
      if(RE_f_akcija())
        return 1;
      if(RE_scanner())
        return 1;
      break;
    default:
      RE_error="Ocekivao sam: slovo ^ $ [ ] ( < akciju";
      return 1;
  }
  return 0;
}

int RE_broj_D_stanja;
SO_tip_RE_skup_stanja RE_skupovi_stanja[RE_MAX_BROJ_STANJA];
int RE_broj_skupova_stanja;
SO_tip_RE_skup_slova RE_skupovi_D_slova[RE_MAX_BROJ_SKUPOVA_SLOVA];
int RE_broj_skupova_D_slova;
RE_tip_prelaz RE_D_prelazi[RE_MAX_BROJ_PRELAZA];
int RE_broj_D_prelaza;

int RE_novi_skup_D_slova(SO_tip_RE_skup_slova x)
{
  if(RE_broj_skupova_D_slova==RE_MAX_BROJ_SKUPOVA_SLOVA)
  {
    RE_error="Mnogo skupova slova u determinizaciji";
    return 1;
  }
  SO_dodeli(RE_skupovi_D_slova[RE_broj_skupova_D_slova],x);
  RE_broj_skupova_D_slova++;
  return 0;
}

int RE_razdvajanje_skupa_slova(void)
{
  static SO_tip_RE_skup_slova x;
  static SO_tip_RE_skup_slova y;
  int f;
  int n;
  int i;
  int j;
  RE_broj_skupova_D_slova=0;
  for(i=0;i<RE_broj_skupova_slova;i++)
  {
    SO_dodeli(x,RE_skupovi_slova[i]);
    f=1;
    n=RE_broj_skupova_D_slova;
    for(j=0;f&&j<n;j++)
    {
      SO_dodeli(y,x);
      SO_presek(y,RE_skupovi_D_slova[j]);
      if(!SO_prazan_skup(y))
      {
        SO_razlika(RE_skupovi_D_slova[j],y);
        if(!SO_prazan_skup(RE_skupovi_D_slova[j]))
          if(RE_novi_skup_D_slova(RE_skupovi_D_slova[j]))
            return 1;
        SO_dodeli(RE_skupovi_D_slova[j],y);
        SO_razlika(x,y);
        f=!SO_prazan_skup(x);
      }
    }
    if(f)
      if(RE_novi_skup_D_slova(x))
        return 1;
  }
  return 0;
}

void RE_epsilon_zatvorenje(SO_tip_RE_skup_stanja x)
{
  int f;
  int i;
  do
  {
    f=0;
    for(i=0;i<RE_broj_prelaza;i++)
      if(RE_prelazi[i].skup_slova==RE_slovo_epsilon&&SO_element(x,RE_prelazi[i].od_stanja))
        if(!SO_element(x,RE_prelazi[i].do_stanja))
        {
          SO_ubaci(x,RE_prelazi[i].do_stanja);
          f=1;
        }
  }
  while(f);
}

int RE_determinizacija(int pocetno_stanje)
{
  int i;
  int j;
  int k;
  int n;
  static SO_tip_RE_skup_stanja x;
  SO_izbaci_sve(RE_skupovi_stanja[0]);
  SO_ubaci(RE_skupovi_stanja[0],pocetno_stanje);
  RE_epsilon_zatvorenje(RE_skupovi_stanja[0]);
  RE_broj_skupova_stanja=1;
  RE_broj_D_prelaza=0;
  for(i=0;i<RE_broj_skupova_stanja;i++)
    for(j=RE_slovo_dolar;j<RE_broj_skupova_D_slova;j++)
    {
      SO_izbaci_sve(x);
      for(k=0;k<RE_broj_prelaza;k++)
        if(SO_element(RE_skupovi_stanja[i],RE_prelazi[k].od_stanja))
          switch(j)
          {
            case RE_slovo_dolar:
              if(RE_prelazi[k].skup_slova==RE_slovo_dolar)
                SO_ubaci(x,RE_prelazi[k].do_stanja);
              break;
            case RE_slovo_kapa:
              if(RE_prelazi[k].skup_slova==RE_slovo_kapa)
                SO_ubaci(x,RE_prelazi[k].do_stanja);
              break;
            default:
              if(RE_prelazi[k].skup_slova!=RE_slovo_epsilon&&SO_podskup(RE_skupovi_slova[RE_prelazi[k].skup_slova],RE_skupovi_D_slova[j]))
                SO_ubaci(x,RE_prelazi[k].do_stanja);
          }
      if(!SO_prazan_skup(x))
      {
        RE_epsilon_zatvorenje(x);
        n=0;
        while(n<RE_broj_skupova_stanja&&!SO_jednaki(RE_skupovi_stanja[n],x))
          n++;
        if(n==RE_broj_skupova_stanja)
        {
          if(RE_broj_skupova_stanja==RE_MAX_BROJ_STANJA)
          {
            RE_error="Mnogo stanja u determinizaciji";
            return 1;
          }
          SO_dodeli(RE_skupovi_stanja[RE_broj_skupova_stanja],x);
          RE_broj_skupova_stanja++;
        }
        if(RE_broj_D_prelaza==RE_MAX_BROJ_PRELAZA)
        {
          RE_error="Mnogo f-ja prelaska u determinizaciji";
          return 1;
        }
        RE_D_prelazi[RE_broj_D_prelaza].od_stanja=i;
        RE_D_prelazi[RE_broj_D_prelaza].skup_slova=j;
        RE_D_prelazi[RE_broj_D_prelaza].do_stanja=n;
        RE_broj_D_prelaza++;
      }
    }
  return 0;
}

#define RE_prazan_prelaz (-1)

int RE_nadji_D_prelaz(int stanje,int skup_slova)
{
  int i;
  i=0;
  while(i<RE_broj_D_prelaza&&(RE_D_prelazi[i].od_stanja!=stanje||RE_D_prelazi[i].skup_slova!=skup_slova))
    i++;
  return i==RE_broj_D_prelaza?RE_prazan_prelaz:RE_D_prelazi[i].do_stanja;
}

#define RE_kapa(ka) ((ka)->broj_skupova_slova)
#define RE_dolar(ka) ((ka)->broj_skupova_slova+1)
#define RE_f_ja_prelaza(ka,stanje,skup_slova) ((ka)->prelazi[(ka)->broj_stanja*(skup_slova)+(stanje)])

int RE_parser(char *text,RE_KA *ka)
{
  int i;
  int j;
  int k;
  RE_ulaz=text;
  RE_r_pos=0;
  if(RE_scanner())
    return 1;
  RE_broj_akcija=0;
  RE_dubina=0;
  RE_broj_stanja=0;
  RE_broj_skupova_slova=0;
  RE_broj_prelaza=0;
  RE_velicina_steka_skupova_slova=0;
  RE_velicina_steka_stanja=0;
  if(RE_parser_D())
    return 1;
  if(RE_parser_C())
    return 1;
  if(RE_parser_B())
    return 1;
  if(RE_parser_A())
    return 1;
  if(RE_leksema!=RE_lex_EOS)
  {
    RE_error="Prepoznao sam rec ali ima jos na ulazu";
    return 1;
  }
  RE_velicina_steka_stanja--;
  RE_broj_D_stanja=0;
  RE_broj_skupova_stanja=0;
  RE_broj_skupova_D_slova=0;
  RE_broj_D_prelaza=0;
  if(RE_razdvajanje_skupa_slova())
    return 1;
  if(RE_determinizacija(RE_stek_stanja[RE_velicina_steka_stanja].od_stanja))
    return 1;
  ka->broj_skupova_slova=RE_broj_skupova_D_slova;
  if((ka->skupovi_slova=(SO_tip_RE_skup_slova *)calloc(RE_broj_skupova_slova,sizeof(SO_tip_RE_skup_slova)))==NULL)
  {
    RE_error="Nema memorije";
    return 1;
  }
  for(i=0;i<RE_broj_skupova_D_slova;i++)
    SO_dodeli(ka->skupovi_slova[i],RE_skupovi_D_slova[i]);
  ka->broj_stanja=RE_broj_skupova_stanja;
  ka->broj_akcija=RE_broj_akcija;
  if((ka->akcije=(struct RE_struct_KA_akcija *)calloc(RE_broj_akcija,sizeof(struct RE_struct_KA_akcija)))==NULL)
  {
    RE_error="Nema memorije";
    return 1;
  }
  for(i=0;i<RE_broj_akcija;i++)
  {
    strncpy(ka->akcije[i].ime,RE_imena_akcija[i],sizeof(RE_tip_ime_akcije));
    SO_izbaci_sve(ka->akcije[i].stanja);
    for(j=0;j<RE_broj_stanja;j++)
      if(RE_koja_akcija[j].tip==RE_va_akcija&&RE_koja_akcija[j].ime_ili_dubina==i)
        for(k=0;k<RE_broj_skupova_stanja;k++)
          if(SO_element(RE_skupovi_stanja[k],j))
            SO_ubaci(ka->akcije[i].stanja,k);
  }
  ka->broj_manje_vece=RE_dubina;
  if((ka->manje_vece=(struct RE_struct_KA_manje_vece *)calloc(RE_dubina,sizeof(struct RE_struct_KA_manje_vece)))==NULL)
  {
    RE_error="Nema memorije";
    return 1;
  }
  for(i=0;i<RE_dubina;i++)
  {
    SO_izbaci_sve(ka->manje_vece[i].manje);
    SO_izbaci_sve(ka->manje_vece[i].vece);
    for(j=0;j<RE_broj_stanja;j++)
    {
      if(RE_koja_akcija[j].tip==RE_va_manje&&RE_koja_akcija[j].ime_ili_dubina==i)
        for(k=0;k<RE_broj_skupova_stanja;k++)
          if(SO_element(RE_skupovi_stanja[k],j))
            SO_ubaci(ka->manje_vece[i].manje,k);
      if(RE_koja_akcija[j].tip==RE_va_vece&&RE_koja_akcija[j].ime_ili_dubina==i)
        for(k=0;k<RE_broj_skupova_stanja;k++)
          if(SO_element(RE_skupovi_stanja[k],j))
            SO_ubaci(ka->manje_vece[i].vece,k);
    }
  }
  SO_izbaci_sve(ka->akcija_zavrsna);
  for(i=0;i<RE_broj_skupova_stanja;i++)
    if(SO_element(RE_skupovi_stanja[i],RE_stek_stanja[RE_velicina_steka_stanja].do_stanja))
      SO_ubaci(ka->akcija_zavrsna,i);
  if((ka->prelazi=(int *)calloc(RE_broj_skupova_stanja*(RE_broj_skupova_D_slova+2),sizeof(int)))==NULL)
  {
    RE_error="Nema memorije";
    return 1;
  }
  for(i=0;i<RE_broj_skupova_stanja;i++)
  {
    for(j=0;j<RE_broj_skupova_D_slova;j++)
      RE_f_ja_prelaza(ka,i,j)=RE_nadji_D_prelaz(i,j);
    RE_f_ja_prelaza(ka,i,RE_kapa(ka))=RE_nadji_D_prelaz(i,RE_slovo_kapa);
    RE_f_ja_prelaza(ka,i,RE_dolar(ka))=RE_nadji_D_prelaz(i,RE_slovo_dolar);
  }
  return 0;
}

void RE_free_KA(RE_KA *ka)
{
  free(ka->akcije);
  free(ka->manje_vece);
  free(ka->prelazi);
}

#define RE_MAX_VELICINA_CACHE 32
struct
{
  char *ulaz;
  int broj_poziva;
  RE_KA ka;
} RE_cache[RE_MAX_VELICINA_CACHE];
int RE_velicina_cache;

void RE_cache_init(void)
{
  RE_velicina_cache=0;
}

RE_KA *RE_cache_find(char *s)
{
  int i;
  i=0;
  while(i<RE_velicina_cache&&strcmp(RE_cache[i].ulaz,s))
    i++;
  if(i<RE_velicina_cache)
  {
    RE_cache[i].broj_poziva++;
    return &RE_cache[i].ka;
  }
  else
  {
    int koji;
    if(RE_velicina_cache==RE_MAX_VELICINA_CACHE)
    {
      int min;
      min=RE_cache[0].broj_poziva;
      koji=0;
      for(i=1;i<RE_MAX_VELICINA_CACHE;i++)
        if(RE_cache[i].broj_poziva<=min)
        {
          min=RE_cache[i].broj_poziva;
          koji=i;
        }
      free(RE_cache[koji].ulaz);
      RE_free_KA(&RE_cache[koji].ka);
    }
    else
    {
      koji=RE_velicina_cache;
      RE_velicina_cache++;
    }
    RE_cache[koji].ulaz=(char *)malloc(strlen(s)+1);
    if(RE_cache[koji].ulaz==NULL)
    {
      RE_error="Nedovoljno memorije";
      return NULL;
    }
    strcpy(RE_cache[koji].ulaz,s);
    RE_cache[koji].broj_poziva=1;
    if(RE_parser(RE_cache[koji].ulaz,&RE_cache[koji].ka))
      return NULL;
    return &RE_cache[koji].ka;
  }
}

int RE_run_init(RE_KA *ka,RE_run_results *rr)
{
  rr->max_broj_akcija=ka->broj_stanja<<4;
  if((rr->akcije=(int *)calloc(rr->max_broj_akcija,sizeof(int)))==NULL)
  {
    RE_error="Nema memorije";
    return 1;
  }
  rr->broj_manje_vece=ka->broj_manje_vece;
  if((rr->manje_vece=(RE_tip_manje_vece *)calloc(rr->broj_manje_vece,sizeof(RE_tip_manje_vece)))==NULL)
  {
    RE_error="Nema memorije";
    return 1;
  }
  return 0;
}

int RE_i_element(SO_tip_RE_skup_slova ss,int c,int ignore)
{
  return
    ignore?
      SO_element(ss,toupper(c))||
      SO_element(ss,tolower(c)):
    SO_element(ss,c);
}

#define RE_pocetak_texta (-1)

int RE_run(RE_KA *ka,char *text,RE_run_results *rr,int ignore)
{
  int radi;
  if(ka->broj_manje_vece>rr->broj_manje_vece)
  {
    RE_error="Nije usaglasen konacni automat sa rezultatima";
    return 1;
  }
  rr->pocetak=RE_pocetak_texta;
  rr->nasao=0;
  radi=1;
  do
  {
    int stanje;
    int slovo;
    int i;
    if(rr->pocetak!=RE_pocetak_texta&&text[rr->pocetak]=='\0')
      radi=0;
    stanje=0;
    rr->broj_akcija=0;
    for(i=0;i<ka->broj_manje_vece;i++)
      rr->manje_vece[i].nasao=0;
    slovo=rr->pocetak;
    do
    {
      for(i=0;i<ka->broj_akcija;i++)
        if(SO_element(ka->akcije[i].stanja,stanje))
        {
          if(rr->broj_akcija==rr->max_broj_akcija)
          {
            RE_error="Mnogo akcija";
            return 1;
          }
          rr->akcije[rr->broj_akcija]=i;
          rr->broj_akcija++;
        }
      for(i=0;i<ka->broj_manje_vece;i++)
      {
        if(SO_element(ka->manje_vece[i].manje,stanje))
          rr->manje_vece[i].pocetak=slovo==RE_pocetak_texta?0:slovo;
        if(SO_element(ka->manje_vece[i].vece,stanje))
        {
          rr->manje_vece[i].nasao=1;
          rr->manje_vece[i].kraj=slovo==RE_pocetak_texta?0:slovo;
        }
      }
      if(SO_element(ka->akcija_zavrsna,stanje))
      {
        rr->nasao=1;
        rr->kraj=slovo==RE_pocetak_texta?0:slovo;
      }
      if(slovo==RE_pocetak_texta)
        stanje=RE_f_ja_prelaza(ka,stanje,RE_kapa(ka));
      else
        if(text[slovo]=='\0')
          stanje=RE_f_ja_prelaza(ka,stanje,RE_dolar(ka));
        else
        {
          i=0;
          while(i<ka->broj_skupova_slova&&!RE_i_element(ka->skupovi_slova[i],(int)(unsigned char)text[slovo],ignore))
            i++;
          stanje=i==ka->broj_skupova_slova?RE_prazan_prelaz:RE_f_ja_prelaza(ka,stanje,i);
        }
      if(stanje!=RE_prazan_prelaz&&(slovo==RE_pocetak_texta||text[slovo]!='\0'))
        slovo++;
    }
    while(stanje!=RE_prazan_prelaz);
    rr->pocetak++;
  }
  while(!rr->nasao&&radi);
  rr->pocetak--;
  if(rr->pocetak==RE_pocetak_texta)
    rr->pocetak=0;
  return 0;
}

void RE_free_run_results(RE_run_results *rr)
{
  free(rr->akcije);
  free(rr->manje_vece);
}

int RE_frun_init(RE_KA *ka,int max,RE_frun_results *rr)
{
  rr->max_duzina=max;
  if((rr->vrednost=(char *)calloc(rr->max_duzina,sizeof(char)))==NULL)
  {
    RE_error="Nema memorije";
    return 1;
  }
  rr->max_broj_akcija=ka->broj_stanja<<4;
  if((rr->akcije=(int *)calloc(rr->max_broj_akcija,sizeof(int)))==NULL)
  {
    RE_error="Nema memorije";
    return 1;
  }
  rr->broj_manje_vece=ka->broj_manje_vece;
  if((rr->manje_vece=(RE_tip_manje_vece *)calloc(rr->broj_manje_vece,sizeof(RE_tip_manje_vece)))==NULL)
  {
    RE_error="Nema memorije";
    return 1;
  }
  return 0;
}

int RE_frun(RE_KA *ka,FILE *dat,RE_frun_results *rr,int ignore)
{
  fpos_t pos_pocetak;
  fpos_t pos_kraj;
  int pocetak;
  int slovo;
  if(ka->broj_manje_vece>rr->broj_manje_vece)
  {
    RE_error="Nije usaglasen konacni automat sa rezultatima";
    return 1;
  }
  fgetpos(dat,&pos_pocetak);
  rr->nasao=0;
  pocetak=RE_pocetak_texta;
  do
  {
    int znak;
    if(pocetak!=RE_pocetak_texta)
    {
      if(slovo!=RE_pocetak_texta)
        fsetpos(dat,&pos_pocetak);
      znak=fgetc(dat);
    }
    if(pocetak!=RE_pocetak_texta||ftell(dat)==0)
    {
      int stanje;
      int i;
      stanje=0;
      rr->broj_akcija=0;
      for(i=0;i<ka->broj_manje_vece;i++)
        rr->manje_vece[i].nasao=0;
      slovo=pocetak;
      rr->duzina=0;
      do
      {
        for(i=0;i<ka->broj_akcija;i++)
          if(SO_element(ka->akcije[i].stanja,stanje))
          {
            if(rr->broj_akcija==rr->max_broj_akcija)
            {
              RE_error="Mnogo akcija";
              return 1;
            }
            rr->akcije[rr->broj_akcija]=i;
            rr->broj_akcija++;
          }
        for(i=0;i<ka->broj_manje_vece;i++)
        {
          if(SO_element(ka->manje_vece[i].manje,stanje))
            rr->manje_vece[i].pocetak=slovo==RE_pocetak_texta?0:slovo;
          if(SO_element(ka->manje_vece[i].vece,stanje))
          {
            rr->manje_vece[i].nasao=1;
            rr->manje_vece[i].kraj=slovo==RE_pocetak_texta?0:slovo;
          }
        }
        rr->nasao=SO_element(ka->akcija_zavrsna,stanje);
        if(slovo==RE_pocetak_texta)
          stanje=RE_f_ja_prelaza(ka,stanje,RE_kapa(ka));
        else
          if(znak==EOF)
            stanje=RE_f_ja_prelaza(ka,stanje,RE_dolar(ka));
          else
          {
            i=0;
            while(i<ka->broj_skupova_slova&&!RE_i_element(ka->skupovi_slova[i],znak,ignore))
              i++;
            stanje=i==ka->broj_skupova_slova?RE_prazan_prelaz:RE_f_ja_prelaza(ka,stanje,i);
          }
        if(stanje!=RE_prazan_prelaz)
        {
          fgetpos(dat,&pos_kraj);
          if(znak!=EOF)
          {
            if(slovo!=RE_pocetak_texta&&rr->duzina<rr->max_duzina-1)
            {
              rr->vrednost[rr->duzina]=(char)znak;
              rr->duzina++;
            }
            slovo++;
            znak=fgetc(dat);
          }
        }
      }
      while(stanje!=RE_prazan_prelaz);
    }
    pocetak++;
  }
  while(!rr->nasao&&pocetak<1);
  if(rr->nasao)
  {
    fsetpos(dat,&pos_kraj);
    rr->vrednost[rr->duzina]='\0';
  }
  else
    if(slovo!=RE_pocetak_texta)
      fsetpos(dat,&pos_pocetak);
  return 0;
}

void RE_free_frun_results(RE_frun_results *rr)
{
  free(rr->vrednost);
  free(rr->akcije);
  free(rr->manje_vece);
}
