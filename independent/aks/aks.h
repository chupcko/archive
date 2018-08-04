#include <limits.h>
#include <stdio.h>
#include <string.h>

#define AKS_MAX_TOP_STACK 4
#define AKS_LEN_SET UCHAR_MAX/CHAR_BIT+1

/* Slobodno za menjanje */
#define AKS_MAX_LEN_STR 64

typedef unsigned char AKS_set[AKS_LEN_SET];

/* Slobodno za menjanje */
typedef long int AKS_type;

char *AKS_error;
char *AKS_input;
int AKS_old_pos;
int AKS_new_pos;
enum
{
  AKS_LUZ,
  AKS_DUZ,
  AKS_ODO,
  AKS_OPC,
  AKS_NOT,
  AKS_EOI,
  AKS_CHR
} AKS_class;
char AKS_chr;
struct
{
  AKS_set set;
  unsigned char chr;
} AKS_stack[AKS_MAX_TOP_STACK];
int AKS_top_stack;
AKS_set AKS_str[AKS_MAX_LEN_STR];
int AKS_opc[AKS_MAX_LEN_STR];
int AKS_len_str;
AKS_type AKS_ti=1l; /* Slobodno za menjanje */
AKS_type AKS_td=1l; /* Slobodno za menjanje */
AKS_type AKS_tc=1l; /* Slobodno za menjanje */
AKS_type AKS_ts2=1l; /* Slobodno za menjanje */
AKS_type AKS_ts3=1l; /* Slobodno za menjanje */
AKS_type (*AKS_p)(int)=NULL; /* Slobodno za menjanje */

void AKS_scanner(void)
{
  enum
  {
    POCETNO,
    STANJE_1,
    STANJE_2,
    STANJE_3,
    ZAVRSNO
  } stanje;
  char slovo;
  stanje=POCETNO;
  AKS_old_pos=AKS_new_pos;
  do
  {
    slovo=*AKS_input;
    AKS_input++;
    AKS_new_pos++;
    switch(stanje)
    {
      case POCETNO:
        switch(slovo)
        {
          case '[':
            AKS_class=AKS_LUZ;
            stanje=ZAVRSNO;
            break;
          case ']':
            AKS_class=AKS_DUZ;
            stanje=ZAVRSNO;
            break;
          case '-':
            AKS_class=AKS_ODO;
            stanje=ZAVRSNO;
            break;
          case '?':
            AKS_class=AKS_OPC;
            stanje=ZAVRSNO;
            break;
          case '^':
            AKS_class=AKS_NOT;
            stanje=ZAVRSNO;
            break;
          case '\0':
            AKS_class=AKS_EOI;
            stanje=ZAVRSNO;
            break;
          case '/':
            stanje=STANJE_1;
            break;
          default:
            AKS_class=AKS_CHR;
            AKS_chr=slovo;
            stanje=ZAVRSNO;
        }
        break;
      case STANJE_1:
        if(slovo>='0'&&slovo<='7')
        {
          AKS_class=AKS_CHR;
          AKS_chr=slovo-'0';
          stanje=STANJE_2;
        }
        else
        {
          if(slovo)
          {
            AKS_class=AKS_CHR;
            AKS_chr=slovo;
          }
          else
            AKS_class=AKS_EOI;
          stanje=ZAVRSNO;
        }
        break;
      case STANJE_2:
        if(slovo>='0'&&slovo<='7')
        {
          AKS_chr<<=3;
          AKS_chr+=slovo-'0';
          stanje=STANJE_3;
        }
        else
        {
          AKS_input--;
          AKS_new_pos--;
          stanje=ZAVRSNO;
        }
        break;
      case STANJE_3:
        if(slovo>='0'&&slovo<='7')
        {
          AKS_chr<<=3;
          AKS_chr+=slovo-'0';
        }
        else
        {
          AKS_input--;
          AKS_new_pos--;
        }
        stanje=ZAVRSNO;
    }
  }
  while(stanje!=ZAVRSNO);
}

void AKS_set_set_all(unsigned char x[])
{
  int i;
  for(i=0;i<AKS_LEN_SET;i++)
    x[i]=(unsigned char)~0;
}

void AKS_set_reset_all(unsigned char x[])
{
  int i;
  for(i=0;i<AKS_LEN_SET;i++)
    x[i]=(unsigned char)0;
}

void AKS_set_union(unsigned char d[],unsigned char s[])
{
  int i;
  for(i=0;i<AKS_LEN_SET;i++)
    d[i]|=s[i];
}

void AKS_set_intersec(unsigned char d[],unsigned char s[])
{
  int i;
  for(i=0;i<AKS_LEN_SET;i++)
    d[i]&=s[i];
}

void AKS_set_minus(unsigned char d[],unsigned char s[])
{
  int i;
  for(i=0;i<AKS_LEN_SET;i++)
    d[i]&=~s[i];
}

void AKS_set_complement(unsigned char x[])
{
  int i;
  for(i=0;i<AKS_LEN_SET;i++)
    x[i]=~x[i];
}

void AKS_set_copy(unsigned char d[],unsigned char s[])
{
  int i;
  for(i=0;i<AKS_LEN_SET;i++)
    d[i]=s[i];
}

void AKS_set_set(unsigned char x[],unsigned char n)
{
  x[n/CHAR_BIT]|=1u<<n%CHAR_BIT;
}

void AKS_set_reset(unsigned char x[],unsigned char n)
{
  x[n/CHAR_BIT]&=~(1u<<n%CHAR_BIT);
}

int AKS_set_in(unsigned char x[],unsigned char n)
{
  return x[n/CHAR_BIT]&(1u<<n%CHAR_BIT);
}

void AKS_f_chr(void)
{
  AKS_set_reset_all(AKS_stack[AKS_top_stack].set);
  AKS_set_set(AKS_stack[AKS_top_stack].set,(unsigned char)AKS_chr);
  AKS_stack[AKS_top_stack].chr=(unsigned char)AKS_chr;
  AKS_top_stack++;
}

void AKS_f_to(void)
{
  unsigned char i;
  AKS_top_stack--;
  if(AKS_stack[AKS_top_stack-1].chr>AKS_stack[AKS_top_stack].chr)
  {
    i=AKS_stack[AKS_top_stack-1].chr;
    AKS_stack[AKS_top_stack-1].chr=AKS_stack[AKS_top_stack].chr;
    AKS_stack[AKS_top_stack].chr=i;
  }
  for(i=AKS_stack[AKS_top_stack-1].chr;i<=AKS_stack[AKS_top_stack].chr;i++)
    AKS_set_set(AKS_stack[AKS_top_stack-1].set,i);
}

void AKS_f_union(void)
{
  AKS_top_stack--;
  AKS_set_union(AKS_stack[AKS_top_stack-1].set,AKS_stack[AKS_top_stack].set);
}

void AKS_f_complement(void)
{
  AKS_set_complement(AKS_stack[AKS_top_stack-1].set);
}

void AKS_f_all_chr(void)
{
  AKS_set_set_all(AKS_stack[AKS_top_stack].set);
  AKS_top_stack++;
}

void AKS_f_minus(void)
{
  AKS_top_stack--;
  AKS_set_minus(AKS_stack[AKS_top_stack-1].set,AKS_stack[AKS_top_stack].set);
}

void AKS_f_opc_true(void)
{
  AKS_opc[AKS_len_str]=1;
  AKS_len_str++;
}

void AKS_f_opc_false(void)
{
  AKS_opc[AKS_len_str]=0;
  AKS_len_str++;
}

int AKS_f_in(void)
{
  if(AKS_len_str==AKS_MAX_LEN_STR)
  {
    AKS_error="Niska se sastoji od mnogo slova";
    return 1;
  }
  AKS_top_stack--;
  AKS_set_copy(AKS_str[AKS_len_str],AKS_stack[AKS_top_stack].set);
  return 0;
}

int AKS_parser_h(void)
{
  switch(AKS_class)
  {
    case AKS_ODO:
      AKS_scanner();
      if(AKS_class!=AKS_CHR)
      {
        AKS_error="Ocekivao sam slovo";
        return 1;
      }
      AKS_f_chr();
      AKS_f_to();
      AKS_scanner();
      break;
    case AKS_CHR:
    case AKS_DUZ:
    case AKS_NOT:
      break;
    default:
      AKS_error="Ocekivao sam slovo ili ] ili ^ ili -";
      return 1;
  }
  return 0;
}

int AKS_parser_g(void)
{
  while(AKS_class==AKS_CHR)
  {
    AKS_f_chr();
    AKS_scanner();
    if(AKS_parser_h())
      return 1;
    AKS_f_union();
  }
  if(AKS_class!=AKS_DUZ&&AKS_class!=AKS_NOT)
  {
    AKS_error="Ocekivao sam slovo ili ] ili ^";
    return 1;
  }
  return 0;
}

int AKS_parser_f(void)
{
  switch(AKS_class)
  {
    case AKS_CHR:
      AKS_f_chr();
      AKS_scanner();
      if(AKS_parser_h())
        return 1;
      if(AKS_parser_g())
        return 1;
      AKS_f_complement();
      break;
    case AKS_DUZ:
      AKS_f_all_chr();
      break;
    default:
      AKS_error="Ocekivao sam slovo ili ]";
      return 1;
  }
  return 0;
}

int AKS_parser_e(void)
{
  switch(AKS_class)
  {
    case AKS_NOT:
      AKS_scanner();
      if(AKS_class!=AKS_CHR)
      {
        AKS_error="Ocekivao sam slovo";
        return 1;
      }
      AKS_f_chr();
      AKS_scanner();
      if(AKS_parser_h())
        return 1;
      if(AKS_parser_g())
        return 1;
      AKS_f_minus();
      break;
    case AKS_DUZ:
      break;
    default:
      AKS_error="Ocekivao sam ] ili ^";
      return 1;
  }
  return 0;
}

int AKS_parser_d(void)
{
  switch(AKS_class)
  {
    case AKS_CHR:
      AKS_f_chr();
      AKS_scanner();
      if(AKS_parser_h())
        return 1;
      if(AKS_parser_g())
        return 1;
      if(AKS_parser_e())
        return 1;
      break;
    case AKS_NOT:
      AKS_scanner();
      if(AKS_parser_f())
        return 1;
      break;
    default:
      AKS_error="Ocekivao sam slovo ili ^";
      return 1;
  }
  return 0;
}

int AKS_parser_c(void)
{
  switch(AKS_class)
  {
    case AKS_CHR:
      AKS_f_chr();
      AKS_scanner();
      break;
    case AKS_LUZ:
      AKS_scanner();
      if(AKS_parser_d())
        return 1;
      if(AKS_class!=AKS_DUZ)
      {
        AKS_error="Ocekivao sam ]";
        return 1;
      }
      AKS_scanner();
      break;
    default:
      AKS_error="Ocekivao sam slovo ili [";
      return 1;
  }
  return 0;
}

int AKS_parser_b(void)
{
  switch(AKS_class)
  {
    case AKS_OPC:
      AKS_f_opc_true();
      AKS_scanner();
      break;
    case AKS_CHR:
    case AKS_LUZ:
    case AKS_EOI:
      AKS_f_opc_false();
      break;
    default:
      AKS_error="Ocekivao sam slovo ili [ ili ? ili kraj niske";
      return 1;
  }
  return 0;
}

int AKS_parser_a(void)
{
  while(AKS_class==AKS_CHR||AKS_class==AKS_LUZ)
  {
    if(AKS_parser_c())
      return 1;
    if(AKS_f_in())
      return 1;
    if(AKS_parser_b())
      return 1;
  }
  if(AKS_class!=AKS_EOI)
  {
    AKS_error="Ocekivao sam slovo ili [ ili kraj niske";
    return 1;
  }
  return 0;
}

int AKS_parser(char *s)
{
  AKS_input=s;
  AKS_new_pos=1;
  AKS_scanner();
  AKS_len_str=0;
  return AKS_parser_a();
}

AKS_type AKS_df(char *s)
{
  static AKS_type t[AKS_MAX_LEN_STR+1][4];
  int i;
  int j;
  int m;
  AKS_type x;
  AKS_type y;
  m=strlen(s);
  if(m>AKS_MAX_LEN_STR)
    m=AKS_MAX_LEN_STR;
  t[0][0]=0;
  if(AKS_p==NULL)
  {
    for(i=1;i<=AKS_len_str;i++)
    {
      t[i][0]=t[i-1][0];
      if(!AKS_opc[i-1])
        t[i][0]+=AKS_td;
    }
    for(j=1;j<=m;j++)
    {
      t[0][j%4]=t[0][(j-1)%4]+AKS_ti;
      for(i=1;i<=AKS_len_str;i++)
      {
        x=t[i][(j-1)%4]+AKS_ti;
        y=t[i-1][j%4];
        if(!AKS_opc[i-1])
          y+=AKS_td;
        if(y<x)
          x=y;
        y=t[i-1][(j-1)%4];
        if(!AKS_set_in(AKS_str[i-1],(unsigned char)s[j-1]))
          y+=AKS_tc;
        if(y<x)
          x=y;
        if(i>=2&&j>=2)
        {
          if(AKS_set_in(AKS_str[i-1],(unsigned char)s[j-2])&&AKS_set_in(AKS_str[i-2],(unsigned char)s[j-1]))
          {
            y=t[i-2][(j-2)%4]+AKS_ts2;
            if(y<x)
              x=y;
          }
          if(i>=3&&j>=3&&AKS_set_in(AKS_str[i-1],(unsigned char)s[j-3])&&AKS_set_in(AKS_str[i-3],(unsigned char)s[j-1]))
          {
            y=t[i-3][(j-3)%4]+AKS_ts3;
            if(!AKS_set_in(AKS_str[i-2],(unsigned char)s[j-2]))
              y+=AKS_tc;
            if(y<x)
              x=y;
          }
        }
        t[i][j%4]=x;
      }
    }
  }
  else
  {
    for(i=1;i<=AKS_len_str;i++)
    {
      t[i][0]=t[i-1][0];
      if(!AKS_opc[i-1])
        t[i][0]+=AKS_td*(*AKS_p)(i);
    }
    for(j=1;j<=m;j++)
    {
      t[0][j%4]=t[0][(j-1)%4]+AKS_ti*(*AKS_p)(0);
      for(i=1;i<=AKS_len_str;i++)
      {
        AKS_type p;
        p=(*AKS_p)(i);
        x=t[i][(j-1)%4]+AKS_ti*p;
        y=t[i-1][j%4];
        if(!AKS_opc[i-1])
          y+=AKS_td*p;
        if(y<x)
          x=y;
        y=t[i-1][(j-1)%4];
        if(!AKS_set_in(AKS_str[i-1],(unsigned char)s[j-1]))
          y+=AKS_tc*p;
        if(y<x)
          x=y;
        if(i>=2&&j>=2)
        {
          if(AKS_set_in(AKS_str[i-1],(unsigned char)s[j-2])&&AKS_set_in(AKS_str[i-2],(unsigned char)s[j-1]))
          {
            y=t[i-2][(j-2)%4]+AKS_ts2*p;
            if(y<x)
              x=y;
          }
          if(i>=3&&j>=3&&AKS_set_in(AKS_str[i-1],(unsigned char)s[j-3])&&AKS_set_in(AKS_str[i-3],(unsigned char)s[j-1]))
          {
            y=AKS_ts3;
            if(!AKS_set_in(AKS_str[i-2],(unsigned char)s[j-2]))
              y+=AKS_tc;
            y=t[i-3][(j-3)%4]+y*p;
            if(y<x)
              x=y;
          }
        }
        t[i][j%4]=x;
      }
    }
  }
  return t[AKS_len_str][m%4];
}

/*

int main(int argc,char *argv[])
{
  if(argc==3)
    if(AKS_parser(argv[1]))
      printf("Na mestu %d je greska: %s\n",AKS_old_pos,AKS_error);
    else
      printf("Tezina greske je %ld\n",AKS_df(argv[2]));
  else
    puts("Prosledi skupovnu nisku uzorka i originalnu nisku");
  return 0;
}

*/
