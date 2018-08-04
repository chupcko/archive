#ifndef AZOT_aprcom
#define AZOT_aprcom

#include <limits.h>
#include "setof.h"

SO_tip_def(AC_skup_slova,UCHAR_MAX+1);

typedef struct
{
  int duzina;
  struct AC_struct_slovo
  {
    SO_tip_AC_skup_slova skup_slova;
    int opcija;
    long faktor_c;
    long faktor_d;
    long faktor_i;
    long faktor_m;
    long faktor_s;
    long t[3];
  } *slova;
} AC_uzorak;

int AC_pos;
int AC_r_pos;
char *AC_error;

int AC_parser(char *,AC_uzorak *);
void AC_free_uzorak(AC_uzorak *);

long AC_acs(AC_uzorak *,char *,int);

#endif
