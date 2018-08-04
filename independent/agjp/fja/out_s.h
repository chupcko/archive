#include <limits.h>
#include <stdio.h>

#define AGLA_LEN_VALUE 32
#define AGLA_MAX_CLASS 11
#define BS 13
#define BT 16

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
int AGLA_old_nl;
int AGLA_new_nl=1;
int AGLA_old_pos;
int AGLA_new_pos=1;
char *AGLA_string;
char *AGLA_error;

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
        AGLA_old_pos=AGLA_new_pos;
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
        AGLA_error="Predugacka vrednost lekseme";
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
    AGLA_error="Nepoznata leksema";
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
