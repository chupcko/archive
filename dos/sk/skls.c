
/*********************************************************
//
//  SKLS.C
//
//  SK-Machine
//  Kombinatorska SK masina
//
//  LS - sintaksna analiza i prevodjenje do grafa
//
//  Copyright (c) 1995 by Goran Lazic
//  All Rights Reserved.
//
//*********************************************************/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "sknode.h"
#include "skmemory.h"
#include "skoper.h"

#include "skls.h"

#define LS_MAX_CLASS 8
#define BS 9
#define BT 10

enum
{
  NISTA=-1,
  LS_taraba,
  LS_ime,
  LS_jednako,
  LS_tacka,
  LS_broj,
  LS_lz,
  LS_dz,
  LS_EOF
} LS_class;
char LS_value[LS_LEN_VALUE+1];
int LS_len;
int LS_old_nl;
int LS_new_nl;
int LS_old_pos;
int LS_new_pos;
FILE *LS_file;
char *LS_error;
Cell *LS_top;
int LS_userop;

int LS_scanner(void)
{
  static int len[LS_MAX_CLASS-1];
  static int nl[LS_MAX_CLASS-1];
  static int pos[LS_MAX_CLASS-1];
  static unsigned char ss[UCHAR_MAX+1]=
  {
    8,8,8,8,8,8,8,8,8,0,0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    0,8,8,2,1,8,8,8,6,7,8,8,8,8,4,8,5,5,5,5,5,5,5,5,5,5,8,8,8,3,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
    8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
  };
  static int pr[BT][BS]=
  {
    {0,1,2,3,4,5,6,7,8},
    {1,0,1,1,1,1,1,1,1},
    {BT,BT,BT,BT,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,BT,5,BT,BT,8},
    {BT,BT,BT,BT,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,BT,BT,BT,BT,BT},
    {BT,BT,BT,BT,BT,8,BT,BT,8}
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
        LS_old_nl=LS_new_nl;
        LS_old_pos=LS_new_pos;
        n=0;
        LS_class=NISTA;
        break;
      case 2:
        LS_class=LS_taraba;
        len[LS_taraba]=n;
        nl[LS_taraba]=LS_new_nl;
        pos[LS_taraba]=LS_new_pos;
        break;
      case 3:
        LS_class=LS_jednako;
        len[LS_jednako]=n;
        nl[LS_jednako]=LS_new_nl;
        pos[LS_jednako]=LS_new_pos;
        break;
      case 4:
        LS_class=LS_tacka;
        len[LS_tacka]=n;
        nl[LS_tacka]=LS_new_nl;
        pos[LS_tacka]=LS_new_pos;
        break;
      case 5:
        LS_class=LS_broj;
        len[LS_broj]=n;
        nl[LS_broj]=LS_new_nl;
        pos[LS_broj]=LS_new_pos;
        len[LS_ime]=n;
        nl[LS_ime]=LS_new_nl;
        pos[LS_ime]=LS_new_pos;
        break;
      case 6:
        LS_class=LS_lz;
        len[LS_lz]=n;
        nl[LS_lz]=LS_new_nl;
        pos[LS_lz]=LS_new_pos;
        break;
      case 7:
        LS_class=LS_dz;
        len[LS_dz]=n;
        nl[LS_dz]=LS_new_nl;
        pos[LS_dz]=LS_new_pos;
        break;
      case 8:
        LS_class=LS_ime;
        len[LS_ime]=n;
        nl[LS_ime]=LS_new_nl;
        pos[LS_ime]=LS_new_pos;
    }
    if((c=fgetc(LS_file))==EOF)
      switch(st)
      {
        case 0:
          LS_class=LS_EOF;
        default:
          st=BT;
      }
    else
    {
      if(c==(int)'\n')
      {
        LS_new_nl++;
        LS_new_pos=0;
      }
      else
        LS_new_pos++;
      if(n<LS_LEN_VALUE)
        LS_value[n]=(char)c;
      n++;
      st=ss[c]==BS?BT:pr[st][ss[c]];
    }
  }
  while(st!=BT);
  if(LS_class==NISTA)
  {
    LS_error="Nepoznata leksema";
    return 1;
  }
  else
  {
    if(LS_class==LS_EOF)
      LS_len=0;
    else
    {
      LS_len=len[LS_class];
      fseek(LS_file,(long)(LS_len-n),SEEK_CUR);
      if(LS_len>LS_LEN_VALUE)
        LS_len=LS_LEN_VALUE;
      LS_new_nl=nl[LS_class];
      LS_new_pos=pos[LS_class];
    }
    LS_value[LS_len]='\0';
  }
  return 0;
}

void LS_f_init(void)
{
  LS_top=NULL;
}

int LS_f_provera(void)
{
  if(sk_op_veruserop())
  {
    LS_error="Nije definisan neki operator";
    return 1;
  }
  return 0;
}

void LS_f_vrh(void)
{
  if(LS_top->righttype==SKTYPE_POINTER)
  {
    Cell *p;
    p=get_right_ptr(LS_top);
    LS_top->lefttype=SKTYPE_EMPTY;
    LS_top->righttype=SKTYPE_EMPTY;
    sk_heap_freecell(LS_top);
    LS_top=p;
  }
  else
  {
    LS_top->left=LS_top->right;
    LS_top->lefttype=LS_top->righttype;
    LS_top->righttype=SKTYPE_EMPTY;
  }
}

int LS_f_n_ime(void)
{
  int i;
  if(sk_op_findsysop(LS_value)!=-1)
  {
    LS_error="Nemoze se definisati sistemski operator";
    return 1;
  }
  LS_userop=sk_op_finduserop(LS_value);
  if(LS_userop==-1)
  {
    LS_userop=sk_op_putuserop(LS_value);
    if(LS_userop==-1)
    {
      LS_error="Ima mnogo definicija operatora";
      return 1;
    }
  }
  else
    if(sk_op_getuseropcell(i)!=NULL)
    {
      LS_error="Operator je dva puta definisan";
      return 1;
    }
  return 0;
}

void LS_f_n_vrh(void)
{
  if(LS_top->righttype==SKTYPE_POINTER)
  {
    sk_op_putuseropcell(LS_userop,get_right_ptr(LS_top));
    LS_top->lefttype=SKTYPE_EMPTY;
    LS_top->righttype=SKTYPE_EMPTY;
    sk_heap_freecell(LS_top);
  }
  else
  {
    LS_top->left=LS_top->right;
    LS_top->lefttype=LS_top->righttype;
    LS_top->righttype=SKTYPE_EMPTY;
    sk_op_putuseropcell(LS_userop,LS_top);
  }
  LS_top=NULL;
}

void LS_f_app(void)
{
  Cell *p;
  p=get_left_ptr(LS_top);
  LS_top->left=p->right;
  LS_top->lefttype=p->righttype;
  p->right=(long)LS_top;
  p->righttype=SKTYPE_POINTER;
  LS_top=p;
}

int LS_f_broj(void)
{
  Cell *p;
  p=sk_heap_alloccell();
  if(p==NULL)
  {
    LS_error="Nema vise memorije";
    return 1;
  }
  p->left=(long)LS_top;
  p->right=atol(LS_value);
  p->righttype=SKTYPE_NUMBER;
  LS_top=p;
  return 0;
}

int LS_f_ime(void)
{
  Cell *p;
  int i;
  p=sk_heap_alloccell();
  if(p==NULL)
  {
    LS_error="Nema vise memorije";
    return 1;
  }
  p->left=(long)LS_top;
  i=sk_op_findsysop(LS_value);
  if(i==-1)
  {
    i=sk_op_finduserop(LS_value);
    if(i==-1)
    {
      i=sk_op_putuserop(LS_value);
      if(i==-1)
      {
        LS_error="Ima mnogo definicija operatora";
        return 1;
      }
    }
    p->righttype=SKTYPE_USEROP;
  }
  else
    p->righttype=SKTYPE_SYSTEMOP;
  p->right=i;
  LS_top=p;
  return 0;
}

int LS_p_k(void);

int LS_p_f(void)
{
  switch(LS_class)
  {
    case LS_broj:
      if(LS_f_broj())
        return 1;
      if(LS_scanner())
        return 1;
      break;
    case LS_ime:
      if(LS_f_ime())
        return 1;
      if(LS_scanner())
        return 1;
      break;
    case LS_lz:
      if(LS_scanner())
        return 1;
      if(LS_p_k())
        return 1;
      if(LS_class!=LS_dz)
      {
        LS_error="Ocekivao sam \')\'";
        return 1;
      }
      if(LS_scanner())
        return 1;
  }
  return 0;
}

int LS_p_l(void)
{
  while(LS_class==LS_ime||LS_class==LS_broj||LS_class==LS_lz)
  {
    if(LS_p_f())
      return 1;
    LS_f_app();
  }
  if(LS_class!=LS_tacka&&LS_class!=LS_dz)
  {
    LS_error="Ocekivao sam: ime, broj, \'(\' ili \'.\'";
    return 1;
  }
  return 0;
}

int LS_p_k(void)
{
  if(LS_class==LS_ime||LS_class==LS_broj||LS_class==LS_lz)
  {
    if(LS_p_f())
      return 1;
    if(LS_p_l())
      return 1;
  }
  else
  {
    LS_error="Ocekivao sam: ime, broj, \'(\'";
    return 1;
  }
  return 0;
}

int LS_p_d(void)
{
  while(LS_class==LS_taraba)
  {
    if(LS_scanner())
      return 1;
    if(LS_class!=LS_ime)
    {
      LS_error="Ocekivao sam ime";
      return 1;
    }
    if(LS_f_n_ime())
      return 1;
    if(LS_scanner())
      return 1;
    if(LS_class!=LS_jednako)
    {
      LS_error="Ocekivao sam \'=\'";
      return 1;
    }
    if(LS_scanner())
      return 1;
    if(LS_p_k())
      return 1;
    LS_f_n_vrh();
    if(LS_class!=LS_tacka)
    {
      LS_error="Ocekivao sam \'.\'";
      return 1;
    }
    if(LS_scanner())
      return 1;
  }
  if(LS_class!=LS_ime&&LS_class!=LS_broj&&LS_class!=LS_lz)
  {
    LS_error="Ocekivao sam: ime, broj, \'#\' ili \'(\'";
    return 1;
  }
  return 0;
}

int LS_parser(FILE * f)
{
  LS_file=f;
  LS_new_nl=1;
  LS_new_pos=1;
  if(LS_scanner())
    return 1;
  LS_f_init();
  if(LS_p_d())
    return 1;
  if(LS_f_provera())
    return 1;
  if(LS_p_k())
    return 1;
  LS_f_vrh();
  if(LS_class!=LS_tacka)
  {
    LS_error="Ocekivao sam \'.\'";
    return 1;
  }
  if(LS_scanner())
    return 1;
  if(LS_class!=LS_EOF)
  {
    LS_error="Nalazi se jos nesto na ulazu";
    return 1;
  }
  return 0;
}
