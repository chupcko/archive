#include <limits.h>
#include <stdio.h>

#define AGLA_LEN_VALUE 1024 /* duzina vrednosti lekseme (slobodno za menjanje) */
#define AGLA_MAX_CLASS 3 /* broj leksickih klasa */
#define BS 2 /* Broj Skupova slova */
#define BT 4 /* Broj sTanja */

enum
{
  NISTA=-1,
  Word,
  Rest,
  AGLA_EOF
} AGLA_class;
char AGLA_value[AGLA_LEN_VALUE+1];
int AGLA_len;
int AGLA_old_nl;
int AGLA_new_nl=1;
int AGLA_old_pos;
int AGLA_new_pos=1;
FILE *AGLA_file;
char *AGLA_error;

int AGLA_scanner(void)
{
  static int len[AGLA_MAX_CLASS-1];
  static int nl[AGLA_MAX_CLASS-1];
  static int pos[AGLA_MAX_CLASS-1];
  static unsigned char ss[UCHAR_MAX+1]=
  {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
  };
  static int pr[BT][BS]=
  {
    {1,2},
    {3,BT},
    {BT,BT},
    {3,BT}
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
        AGLA_old_nl=AGLA_new_nl;
        AGLA_old_pos=AGLA_new_pos;
        n=0;
        AGLA_class=NISTA;
        break;
      case 1:
        AGLA_class=Word;
        len[Word]=n;
        nl[Word]=AGLA_new_nl;
        pos[Word]=AGLA_new_pos;
        len[Rest]=n;
        nl[Rest]=AGLA_new_nl;
        pos[Rest]=AGLA_new_pos;
        break;
      case 2:
        AGLA_class=Rest;
        len[Rest]=n;
        nl[Rest]=AGLA_new_nl;
        pos[Rest]=AGLA_new_pos;
        break;
      case 3:
        AGLA_class=Word;
        len[Word]=n;
        nl[Word]=AGLA_new_nl;
        pos[Word]=AGLA_new_pos;
    }
    if((c=fgetc(AGLA_file))==EOF)
      switch(st)
      {
        case 0:
          AGLA_class=AGLA_EOF;
        default:
          st=BT;
      }
    else
    {
      if(c==(int)'\n')
      {
        AGLA_new_nl++;
        AGLA_new_pos=1;
      }
      else
        AGLA_new_pos++;
      if(n==AGLA_LEN_VALUE)
      {
        AGLA_error="Predugacka vrednost lekseme";
        return 1;
      }
      AGLA_value[n]=(char)c;
      n++;
      st=ss[c]==BS?BT:pr[st][ss[c]];
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
      fseek(AGLA_file,(long)(AGLA_len-n),SEEK_CUR);
      AGLA_new_nl=nl[AGLA_class];
      AGLA_new_pos=pos[AGLA_class];
    }
    AGLA_value[AGLA_len]='\0';
  }
  return 0;
}
