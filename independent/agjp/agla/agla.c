#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POCETNO_STANJE 0
#define EPSILON -1
#define MAX_BR_SS 256 /* slobodno za menjanje */
#define MAX_BR_ST 512 /* slobodno za menjanje */
#define MAX_VL_PR 16384l /* slobodno za menjanje */
#define MAX_BR_LX 128 /* slobodno za menjanje */
#define MAX_BR_SL_IM 16 /* slobodno za menjanje */
#define MAX_BR_VA 128 /* slobodno za menjanje */
#define MAX_VL_PP_ST 256 /* slobodno za menjanje */
#define MAX_VL_PP_SS 4

#define DU_SO_SL UCHAR_MAX/CHAR_BIT+1
#define DU_SO_ST (MAX_BR_ST-1)/CHAR_BIT+1

typedef unsigned char So_sl[DU_SO_SL];
typedef unsigned char So_st[DU_SO_ST];
typedef struct
{
  int od_st;
  int ss;
  int do_st;
} F_ja_pr;

So_sl A_ss[MAX_BR_SS];
int A_br_ss;
So_sl B_ss[MAX_BR_SS];
int B_br_ss;
So_st St;
So_st A_st[MAX_BR_ST];
int A_br_st;
So_st B_st[MAX_BR_ST];
int B_br_st;
F_ja_pr A_pr[MAX_VL_PR];
long int A_vl_pr;
F_ja_pr B_pr[MAX_VL_PR];
long int B_vl_pr;
char Im[MAX_BR_LX][MAX_BR_SL_IM+1];
int Br_im;
struct
{
  int im;
  int do_st;
  int za_st;
} Lx[MAX_BR_LX];
int Br_lx;
struct
{
  char im[MAX_BR_SL_IM+1];
  int od_st;
  int do_st;
  int poziv;
} Va[MAX_BR_VA];
int Br_va;
int Ko_st[MAX_BR_ST];
struct
{
  int od_st;
  int do_st;
} Pp_st[MAX_VL_PP_ST];
int Vl_pp_st;
struct
{
  So_sl ss;
  unsigned char sl;
} Pp_ss[MAX_VL_PP_SS];
int Vl_pp_ss;

enum
{
  NISTA,
  IME,
  VARIJABLA,
  SLOVO,
  JEDNAKO,
  TACKA,
  RAZLIKA,
  LEVA_UGLASTA_ZAGRADA,
  DESNA_UGLASTA_ZAGRADA,
  LEVA_ZAGRADA,
  DESNA_ZAGRADA,
  ILI,
  ZVEZDICA,
  PLUS,
  PITALICA,
  XOR,
  MINUS,
  AGLA_EOF
} AGLA_class;
char AGLA_value[MAX_BR_SL_IM+1];
int AGLA_old_nl;
int AGLA_new_nl;
int AGLA_old_pos;
int AGLA_new_pos;
FILE *AGLA_file;

void error(int i,char *s)
{
  if(i)
    puts(s);
  else
    printf("Red %d , slovo %d - %s\n",AGLA_old_nl,AGLA_old_pos,s);
  exit(1);
}

void AGLA_scanner(void)
{
  int broj_slova;
  int slovo;
  enum
  {
    POCETNO,
    STANJE_0,
    STANJE_1,
    STANJE_2,
    STANJE_3,
    STANJE_4,
    STANJE_5,
    STANJE_6,
    STANJE_7,
    STANJE_8,
    STANJE_9,
    ZAVRSNO
  } stanje;
  int len_ime;
  int nl_ime;
  int pos_ime;
  int len_varijabla;
  int nl_varijabla;
  int pos_varijabla;
  int len_slovo;
  int nl_slovo;
  int pos_slovo;
  AGLA_class=NISTA;
  stanje=POCETNO;
  len_slovo=0;
  do
  {
    switch(stanje)
    {
      case POCETNO:
        AGLA_old_nl=AGLA_new_nl;
        AGLA_old_pos=AGLA_new_pos;
      case STANJE_1:
      case STANJE_7:
        broj_slova=0;
        break;
      case STANJE_2:
        len_varijabla=broj_slova;
        nl_varijabla=AGLA_new_nl;
        pos_varijabla=AGLA_new_pos;
        break;
      case STANJE_3:
        AGLA_class=SLOVO;
        len_slovo=broj_slova;
        nl_slovo=AGLA_new_nl;
        pos_slovo=AGLA_new_pos;
      case STANJE_4:
        len_ime=broj_slova;
        nl_ime=AGLA_new_nl;
        pos_ime=AGLA_new_pos;
        break;
      case STANJE_8:
        *AGLA_value-='0';
        AGLA_class=SLOVO;
        len_slovo=broj_slova;
        nl_slovo=AGLA_new_nl;
        pos_slovo=AGLA_new_pos;
        break;
      case STANJE_9:
        *AGLA_value<<=3;
        *AGLA_value+=AGLA_value[1]-'0';
        len_slovo=broj_slova;
        nl_slovo=AGLA_new_nl;
        pos_slovo=AGLA_new_pos;
    }
    if((slovo=fgetc(AGLA_file))!=EOF)
    {
      if(slovo==(int)'\n')
      {
        AGLA_new_nl++;
        AGLA_new_pos=0;
      }
      else
        AGLA_new_pos++;
      if(broj_slova<MAX_BR_SL_IM)
        AGLA_value[broj_slova]=(char)slovo;
      broj_slova++;
    }
    switch(stanje)
    {
      case POCETNO:
        switch(slovo)
        {
          case EOF:
            AGLA_class=AGLA_EOF;
            stanje=ZAVRSNO;
            break;
          case (int)'\n':
          case (int)' ':
          case (int)'\f':
          case (int)'\r':
          case (int)'\t':
          case (int)'\v':
            break;
          case (int)'$':
            stanje=STANJE_0;
            break;
          case (int)'#':
            stanje=STANJE_1;
            break;
          case (int)'\\':
            stanje=STANJE_7;
            break;
          case (int)'=':
            AGLA_class=JEDNAKO;
            stanje=ZAVRSNO;
            break;
          case (int)'.':
            AGLA_class=TACKA;
            stanje=ZAVRSNO;
            break;
          case (int)'/':
            AGLA_class=RAZLIKA;
            stanje=ZAVRSNO;
            break;
          case (int)'[':
            AGLA_class=LEVA_UGLASTA_ZAGRADA;
            stanje=ZAVRSNO;
            break;
          case (int)']':
            AGLA_class=DESNA_UGLASTA_ZAGRADA;
            stanje=ZAVRSNO;
            break;
          case (int)'(':
            AGLA_class=LEVA_ZAGRADA;
            stanje=ZAVRSNO;
            break;
          case (int)')':
            AGLA_class=DESNA_ZAGRADA;
            stanje=ZAVRSNO;
            break;
          case (int)'|':
            AGLA_class=ILI;
            stanje=ZAVRSNO;
            break;
          case (int)'*':
            AGLA_class=ZVEZDICA;
            stanje=ZAVRSNO;
            break;
          case (int)'+':
            AGLA_class=PLUS;
            stanje=ZAVRSNO;
            break;
          case (int)'?':
            AGLA_class=PITALICA;
            stanje=ZAVRSNO;
            break;
          case (int)'^':
            AGLA_class=XOR;
            stanje=ZAVRSNO;
            break;
          case (int)'-':
            AGLA_class=MINUS;
            stanje=ZAVRSNO;
            break;
          default:
            if(slovo==(int)'_'||slovo>=(int)'a'&&slovo<=(int)'z'||slovo>=(int)'A'&&slovo<=(int)'Z')
              stanje=STANJE_3;
            else
            {
              AGLA_class=SLOVO;
              stanje=ZAVRSNO;
            }
        }
        break;
      case STANJE_0:
        switch(slovo)
        {
          case EOF:
            stanje=ZAVRSNO;
            break;
          case (int)'$':
            stanje=POCETNO;
        }
        break;
      case STANJE_1:
        stanje=slovo==(int)'_'||slovo>=(int)'a'&&slovo<=(int)'z'||slovo>=(int)'A'&&slovo<=(int)'Z'?STANJE_2:ZAVRSNO;
        break;
      case STANJE_2:
        if(slovo!=(int)'_'&&(slovo<(int)'a'||slovo>(int)'z')&&(slovo<(int)'A'||slovo>(int)'Z')&&(slovo<(int)'0'||slovo>(int)'9'))
        {
          AGLA_class=VARIJABLA;
          stanje=ZAVRSNO;
        }
        break;
      case STANJE_3:
      case STANJE_4:
        switch(slovo)
        {
          case (int)'\n':
          case (int)' ':
          case (int)'\f':
          case (int)'\r':
          case (int)'\t':
          case (int)'\v':
            stanje=STANJE_5;
            break;
          case (int)'$':
            stanje=STANJE_6;
            break;
          case (int)'=':
            AGLA_class=IME;
            stanje=ZAVRSNO;
            break;
          default:
            stanje=slovo==(int)'_'||slovo>=(int)'a'&&slovo<=(int)'z'||slovo>=(int)'A'&&slovo<=(int)'Z'||slovo>=(int)'0'&&slovo<=(int)'9'?STANJE_4:ZAVRSNO;
        }
        break;
      case STANJE_5:
        switch(slovo)
        {
          case (int)'\n':
          case (int)' ':
          case (int)'\f':
          case (int)'\r':
          case (int)'\t':
          case (int)'\v':
            break;
          case (int)'$':
            stanje=STANJE_6;
            break;
          case (int)'=':
            AGLA_class=IME;
            stanje=ZAVRSNO;
            break;
          default:
            stanje=ZAVRSNO;
        }
        break;
      case STANJE_6:
        switch(slovo)
        {
          case EOF:
            stanje=ZAVRSNO;
            break;
          case (int)'$':
            stanje=STANJE_5;
        }
        break;
      case STANJE_7:
        if(slovo>=(int)'0'&&slovo<=(int)'7')
          stanje=STANJE_8;
        else
        {
          if(slovo!=EOF)
          {
            switch(slovo)
            {
              case (int)'f':
                *AGLA_value='\f';
                break;
              case (int)'n':
                *AGLA_value='\n';
                break;
              case (int)'r':
                *AGLA_value='\r';
                break;
              case (int)'s':
                *AGLA_value=' ';
                break;
              case (int)'t':
                *AGLA_value='\t';
                break;
              case (int)'v':
                *AGLA_value='\v';
            }
            AGLA_class=SLOVO;
          }
          stanje=ZAVRSNO;
        }
        break;
      case STANJE_8:
        stanje=slovo>=(int)'0'&&slovo<=(int)'7'?STANJE_9:ZAVRSNO;
        break;
      case STANJE_9:
        if(slovo>=(int)'0'&&slovo<=(int)'7')
        {
          *AGLA_value<<=3;
          *AGLA_value+=AGLA_value[2]-'0';
          len_slovo=0;
        }
        stanje=ZAVRSNO;
    }
  }
  while(stanje!=ZAVRSNO);
  switch(AGLA_class)
  {
    case NISTA:
      error(0,"Nepoznata leksema");
      break;
    case IME:
      fseek(AGLA_file,(long)(len_ime-broj_slova),SEEK_CUR);
      AGLA_new_nl=nl_ime;
      AGLA_new_pos=pos_ime;
      AGLA_value[len_ime<MAX_BR_SL_IM?len_ime:MAX_BR_SL_IM]='\0';
      break;
    case VARIJABLA:
      fseek(AGLA_file,(long)(len_varijabla-broj_slova),SEEK_CUR);
      AGLA_new_nl=nl_varijabla;
      AGLA_new_pos=pos_varijabla;
      AGLA_value[len_varijabla<MAX_BR_SL_IM?len_varijabla:MAX_BR_SL_IM]='\0';
      break;
    case SLOVO:
      if(len_slovo)
      {
        fseek(AGLA_file,(long)(len_slovo-broj_slova),SEEK_CUR);
        AGLA_new_nl=nl_slovo;
        AGLA_new_pos=pos_slovo;
      }
  }
}

void ubaci_sve(int l,unsigned char x[])
{
  int i;
  for(i=0;i<l;i++)
    x[i]=(unsigned char)~0;
}

void izbaci_sve(int l,unsigned char x[])
{
  int i;
  for(i=0;i<l;i++)
    x[i]=(unsigned char)0;
}

void unija(int l,unsigned char d[],unsigned char s[])
{
  int i;
  for(i=0;i<l;i++)
    d[i]|=s[i];
}

void presek(int l,unsigned char d[],unsigned char s[])
{
  int i;
  for(i=0;i<l;i++)
    d[i]&=s[i];
}

void razlika(int l,unsigned char d[],unsigned char s[])
{
  int i;
  for(i=0;i<l;i++)
    d[i]&=~s[i];
}

void komplement(int l,unsigned char x[])
{
  int i;
  for(i=0;i<l;i++)
    x[i]=~x[i];
}

int podskup(int l,unsigned char d[],unsigned char s[])
{
  int n;
  int i;
  n=1;
  for(i=0;n&&i<l;i++)
    n=!(int)(~d[i]&s[i]);
  return n;
}

int disjunktni(int l,unsigned char d[],unsigned char s[])
{
  int n;
  int i;
  n=1;
  for(i=0;n&&i<l;i++)
    n=!(int)(d[i]&s[i]);
  return n;
}

int jednaki(int l,unsigned char d[],unsigned char s[])
{
  int n;
  int i;
  n=1;
  for(i=0;n&&i<l;i++)
    n=(int)(d[i]==s[i]);
  return n;
}

int prazan_skup(int l,unsigned char x[])
{
  int n;
  int i;
  n=1;
  for(i=0;n&&i<l;i++)
    n=!(int)x[i];
  return n;
}

void dodeli(int l,unsigned char d[],unsigned char s[])
{
  int i;
  for(i=0;i<l;i++)
    d[i]=s[i];
}

void ubaci(unsigned char x[],int n)
{
  x[n/CHAR_BIT]|=1u<<n%CHAR_BIT;
}

void izbaci(unsigned char x[],int n)
{
  x[n/CHAR_BIT]&=~(1u<<n%CHAR_BIT);
}

int element(unsigned char x[],int n)
{
  return x[n/CHAR_BIT]&(1u<<n%CHAR_BIT);
}

void pocetni_semanticki_domen(void)
{
  B_br_ss=0;
  izbaci_sve(DU_SO_ST,St);
  ubaci(St,POCETNO_STANJE);
  A_vl_pr=0l;
  Br_im=0;
  Br_lx=0;
  Br_va=0;
  Vl_pp_st=0;
  Vl_pp_ss=0;
}

int indeks_varijable(void)
{
  int i;
  i=0;
  while(i<Br_va&&strcmp(Va[i].im,AGLA_value))
    i++;
  return i;
}

void prebaci_od_st_u_a_f_ji_pr(int st)
{
  long int i;
  for(i=0l;i<A_vl_pr;i++)
    if(A_pr[i].od_st==Pp_st[Vl_pp_st].od_st)
      A_pr[i].od_st=st;
  izbaci(St,Pp_st[Vl_pp_st].od_st);
}

void prebaci_do_st_u_a_f_ji_pr(int st)
{
  long int i;
  for(i=0l;i<A_vl_pr;i++)
    if(A_pr[i].do_st==Pp_st[Vl_pp_st].do_st)
      A_pr[i].do_st=st;
  izbaci(St,Pp_st[Vl_pp_st].do_st);
}

void ubaci_u_a_f_ju_pr(int od_st,int ss,int do_st)
{
  if(A_vl_pr==MAX_VL_PR)
    error(1,"Nema vise mesta za f-ju prelaska");
  A_pr[A_vl_pr].od_st=od_st;
  A_pr[A_vl_pr].ss=ss;
  A_pr[A_vl_pr].do_st=do_st;
  A_vl_pr++;
}

int slobodno_st(void)
{
  int i;
  i=POCETNO_STANJE;
  while(i<MAX_BR_ST&&element(St,i))
    i++;
  if(i==MAX_BR_ST)
    error(1,"Mnogo stanja");
  ubaci(St,i);
  return i;
}

void smesti_na_pp_st(int od_st,int do_st)
{
  if(Vl_pp_st==MAX_VL_PP_ST)
    error(1,"Nema mesta na steku");
  Pp_st[Vl_pp_st].od_st=od_st;
  Pp_st[Vl_pp_st].do_st=do_st;
  Vl_pp_st++;
}

void prepisi_st(int st)
{
  long int i;
  Ko_st[st]=slobodno_st();
  for(i=0l;i<A_vl_pr;i++)
    if(A_pr[i].od_st==st)
    {
      if(Ko_st[A_pr[i].do_st]==POCETNO_STANJE)
        prepisi_st(A_pr[i].do_st);
      ubaci_u_a_f_ju_pr(Ko_st[st],A_pr[i].ss,Ko_st[A_pr[i].do_st]);
    }
}

void g_ime(void)
{
  int i;
  if(Br_lx==MAX_BR_LX)
    error(1,"Nema vise mesta za leksicke klase");
  i=0;
  while(i<Br_im&&strcmp(Im[i],AGLA_value))
    i++;
  if(i==Br_im)
  {
    strcpy(Im[Br_im],AGLA_value);
    Br_im++;
  }
  Lx[Br_lx].im=i;
}

void g_dokle(void)
{
  Lx[Br_lx].do_st=Pp_st[Vl_pp_st-1].do_st;
}

void g_zavrsi_spoji(void)
{
  Vl_pp_st--;
  Lx[Br_lx].za_st=Pp_st[Vl_pp_st].do_st;
  Br_lx++;
  prebaci_od_st_u_a_f_ji_pr(POCETNO_STANJE);
}

void g_varijabla(void)
{
  if(indeks_varijable()<Br_va)
    error(0,"Dva puta definisana varijabla");
  if(Br_va==MAX_BR_VA)
    error(1,"Nema vise mesta za varijable");
  strcpy(Va[Br_va].im,AGLA_value);
  Va[Br_va].poziv=1;
}

void g_zapamti(void)
{
  Vl_pp_st--;
  Va[Br_va].od_st=Pp_st[Vl_pp_st].od_st;
  Va[Br_va].do_st=Pp_st[Vl_pp_st].do_st;
  Br_va++;
}

void g_spoji_del(void)
{
  Vl_pp_st--;
  prebaci_od_st_u_a_f_ji_pr(POCETNO_STANJE);
  prebaci_do_st_u_a_f_ji_pr(POCETNO_STANJE);
}

void r_tacka(void)
{
  Vl_pp_st--;
  prebaci_od_st_u_a_f_ji_pr(Pp_st[Vl_pp_st-1].do_st);
  Pp_st[Vl_pp_st-1].do_st=Pp_st[Vl_pp_st].do_st;
}

void r_varijable(void)
{
  int i;
  for(i=POCETNO_STANJE;i<MAX_BR_ST;i++)
    Ko_st[i]=POCETNO_STANJE;
  i=indeks_varijable();
  if(i==Br_va)
    error(0,"Nedefinisana Varijabla");
  Va[i].poziv=0;
  prepisi_st(Va[i].od_st);
  smesti_na_pp_st(Ko_st[Va[i].od_st],Ko_st[Va[i].do_st]);
}

void r_slova(void)
{
  int i;
  Vl_pp_ss--;
  i=0;
  while(i<B_br_ss&&!jednaki(DU_SO_SL,B_ss[i],Pp_ss[Vl_pp_ss].ss))
    i++;
  if(i==B_br_ss)
  {
    if(B_br_ss==MAX_BR_SS)
      error(1,"Mnogo skupova slova");
    dodeli(DU_SO_SL,B_ss[B_br_ss],Pp_ss[Vl_pp_ss].ss);
    B_br_ss++;
  }
  smesti_na_pp_st(slobodno_st(),slobodno_st());
  ubaci_u_a_f_ju_pr(Pp_st[Vl_pp_st-1].od_st,i,Pp_st[Vl_pp_st-1].do_st);
}

void r_ili(void)
{
  Vl_pp_st--;
  prebaci_od_st_u_a_f_ji_pr(Pp_st[Vl_pp_st-1].od_st);
  prebaci_do_st_u_a_f_ji_pr(Pp_st[Vl_pp_st-1].do_st);
}

void r_plus(void)
{
  int i;
  i=slobodno_st();
  ubaci_u_a_f_ju_pr(i,EPSILON,Pp_st[Vl_pp_st-1].od_st);
  ubaci_u_a_f_ju_pr(Pp_st[Vl_pp_st-1].do_st,EPSILON,Pp_st[Vl_pp_st-1].od_st);
  Pp_st[Vl_pp_st-1].od_st=i;
  i=slobodno_st();
  ubaci_u_a_f_ju_pr(Pp_st[Vl_pp_st-1].do_st,EPSILON,i);
  Pp_st[Vl_pp_st-1].do_st=i;
}

void r_pitalica(void)
{
  ubaci_u_a_f_ju_pr(Pp_st[Vl_pp_st-1].od_st,EPSILON,Pp_st[Vl_pp_st-1].do_st);
}

void s_slovo(void)
{
  izbaci_sve(DU_SO_SL,Pp_ss[Vl_pp_ss].ss);
  ubaci(Pp_ss[Vl_pp_ss].ss,(int)(unsigned char)*AGLA_value);
  Pp_ss[Vl_pp_ss].sl=(unsigned char)*AGLA_value;
  Vl_pp_ss++;
}

void s_razlika(void)
{
  Vl_pp_ss--;
  razlika(DU_SO_SL,Pp_ss[Vl_pp_ss-1].ss,Pp_ss[Vl_pp_ss].ss);
}

void s_komplement(void)
{
  komplement(DU_SO_SL,Pp_ss[Vl_pp_ss-1].ss);
}

void s_sva_slova(void)
{
  ubaci_sve(DU_SO_SL,Pp_ss[Vl_pp_ss].ss);
  Vl_pp_ss++;
}

void s_unija(void)
{
  Vl_pp_ss--;
  unija(DU_SO_SL,Pp_ss[Vl_pp_ss-1].ss,Pp_ss[Vl_pp_ss].ss);
}

void s_od_do(void)
{
  int i;
  Vl_pp_ss--;
  if(Pp_ss[Vl_pp_ss-1].sl>Pp_ss[Vl_pp_ss].sl)
  {
    unsigned char t;
    t=Pp_ss[Vl_pp_ss-1].sl;
    Pp_ss[Vl_pp_ss-1].sl=Pp_ss[Vl_pp_ss].sl;
    Pp_ss[Vl_pp_ss].sl=t;
  }
  for(i=(int)Pp_ss[Vl_pp_ss-1].sl;i<=(int)Pp_ss[Vl_pp_ss].sl;i++)
    ubaci(Pp_ss[Vl_pp_ss-1].ss,i);
}

void ubaci_u_a_ss(unsigned char x[])
{
  if(A_br_ss==MAX_BR_SS)
    error(1,"Mnogo skupova slova u determinizaciji");
  dodeli(DU_SO_SL,A_ss[A_br_ss],x);
  A_br_ss++;
}

void razdvajanje_ss(void)
{
  static So_sl x;
  static So_sl y;
  int f;
  int n;
  int i;
  int j;
  A_br_ss=0;
  for(i=0;i<B_br_ss;i++)
  {
    dodeli(DU_SO_SL,x,B_ss[i]);
    f=1;
    n=A_br_ss;
    for(j=0;f&&j<n;j++)
    {
      dodeli(DU_SO_SL,y,x);
      presek(DU_SO_SL,y,A_ss[j]);
      if(!prazan_skup(DU_SO_SL,y))
      {
        razlika(DU_SO_SL,A_ss[j],y);
        if(!prazan_skup(DU_SO_SL,A_ss[j]))
          ubaci_u_a_ss(A_ss[j]);
        dodeli(DU_SO_SL,A_ss[j],y);
        razlika(DU_SO_SL,x,y);
        f=!prazan_skup(DU_SO_SL,x);
      }
    }
    if(f)
      ubaci_u_a_ss(x);
  }
}

void epsilon_zatvorenje(unsigned char x[])
{
  int f;
  long int i;
  do
  {
    f=0;
    for(i=0l;i<A_vl_pr;i++)
      if(A_pr[i].ss==EPSILON&&element(x,A_pr[i].od_st))
        if(!element(x,A_pr[i].do_st))
        {
          ubaci(x,A_pr[i].do_st);
          f=1;
        }
  }
  while(f);
}

void determinizacija(void)
{
  int i;
  int j;
  long int k;
  int n;
  izbaci_sve(DU_SO_ST,B_st[POCETNO_STANJE]);
  ubaci(B_st[POCETNO_STANJE],POCETNO_STANJE);
  epsilon_zatvorenje(B_st[POCETNO_STANJE]);
  B_br_st=POCETNO_STANJE+1;
  B_vl_pr=0l;
  for(i=POCETNO_STANJE;i<B_br_st;i++)
    for(j=0;j<A_br_ss;j++)
    {
      izbaci_sve(DU_SO_ST,St);
      for(k=0l;k<A_vl_pr;k++)
        if(element(B_st[i],A_pr[k].od_st)&&A_pr[k].ss!=EPSILON&&podskup(DU_SO_SL,B_ss[A_pr[k].ss],A_ss[j]))
          ubaci(St,A_pr[k].do_st);
      if(!prazan_skup(DU_SO_ST,St))
      {
        epsilon_zatvorenje(St);
        n=POCETNO_STANJE;
        while(n<B_br_st&&!jednaki(DU_SO_ST,B_st[n],St))
          n++;
        if(n==B_br_st)
        {
          if(B_br_st==MAX_BR_ST)
            error(1,"Mnogo stanja u determinizaciji");
          dodeli(DU_SO_ST,B_st[B_br_st],St);
          B_br_st++;
        }
        if(B_vl_pr==MAX_VL_PR)
          error(1,"Mnogo f-ja prelaska u determinizaciji");
        B_pr[B_vl_pr].od_st=i;
        B_pr[B_vl_pr].ss=j;
        B_pr[B_vl_pr].do_st=n;
        B_vl_pr++;
      }
    }
}

int koja_lx_pripada(unsigned char st[])
{
  int i;
  i=0;
  while(i<Br_lx&&!element(st,Lx[i].za_st))
    i++;
  return i;
}

int pripada_do_st(unsigned char st[],int n)
{
  int f;
  int i;
  f=0;
  for(i=0;!f&&i<Br_lx;i++)
    f=Lx[i].im==n&&element(st,Lx[i].do_st);
  return f;
}

int imaju_ista_tumacenja(unsigned char st_a[],unsigned char st_b[])
{
  int f;
  int i;
  int j;
  i=koja_lx_pripada(st_a);
  j=koja_lx_pripada(st_b);
  f=i==j||i!=Br_lx&&j!=Br_lx&&Lx[i].im==Lx[j].im?!element(st_a,POCETNO_STANJE)==!element(st_b,POCETNO_STANJE):0;
  for(i=0;f&&i<Br_im;i++)
    f=!pripada_do_st(st_a,i)==!pripada_do_st(st_b,i);
  return f;
}

int prvi_u_a_st(int st)
{
  int i;
  i=0;
  while(!element(A_st[st],i))
    i++;
  return i;
}

int gde_ide(int st,int ss)
{
  long int i;
  int j;
  int k;
  i=0l;
  while(i<B_vl_pr&&(B_pr[i].od_st!=st||B_pr[i].ss!=ss))
    i++;
  j=i==B_vl_pr?B_br_st:B_pr[i].do_st;
  k=0;
  while(k<A_br_st&&!element(A_st[k],j))
    k++;
  return k;
}

int idu_u_iste_a_st(int st_a,int st_b)
{
  int f;
  int i;
  f=1;
  for(i=0;f&&i<A_br_ss;i++)
    f=gde_ide(st_a,i)==gde_ide(st_b,i);
  return f;
}

void minimizacija(void)
{
  int f;
  int i;
  int j;
  int k;
  A_br_st=POCETNO_STANJE;
  izbaci_sve(DU_SO_ST,St);
  for(i=POCETNO_STANJE;i<B_br_st;i++)
    if(!element(St,i))
    {
      izbaci_sve(DU_SO_ST,A_st[A_br_st]);
      ubaci(A_st[A_br_st],i);
      for(j=i+1;j<B_br_st;j++)
        if(!element(St,j)&&imaju_ista_tumacenja(B_st[i],B_st[j]))
        {
          ubaci(A_st[A_br_st],j);
          ubaci(St,j);
        }
      A_br_st++;
    }
  do
  {
    f=0;
    for(i=POCETNO_STANJE;i<A_br_st;i++)
    {
      j=prvi_u_a_st(i);
      izbaci_sve(DU_SO_ST,St);
      for(k=j+1;k<B_br_st;k++)
        if(element(A_st[i],k)&&!idu_u_iste_a_st(j,k))
        {
          ubaci(St,k);
          izbaci(A_st[i],k);
        }
      if(!prazan_skup(DU_SO_ST,St))
      {
        dodeli(DU_SO_ST,A_st[A_br_st],St);
        A_br_st++;
        f=1;
      }
    }
  }
  while(f);
  A_vl_pr=0l;
  for(i=0;i<A_br_st;i++)
    for(j=0;j<A_br_ss;j++)
    {
      f=gde_ide(prvi_u_a_st(i),j);
      if(f!=A_br_st)
      {
        A_pr[A_vl_pr].od_st=i;
        A_pr[A_vl_pr].ss=j;
        A_pr[A_vl_pr].do_st=f;
        A_vl_pr++;
      }
    }
  for(i=0;i<A_br_st;i++)
    dodeli(DU_SO_ST,A_st[i],B_st[prvi_u_a_st(i)]);
}

void ispisi_case(int n)
{
  int i;
  if(n)
    fputs("        break;\n",AGLA_file);
  fprintf(AGLA_file,"      case %d:\n",n);
  for(i=n+1;i<A_br_st;i++)
    if(!element(St,i)&&imaju_ista_tumacenja(A_st[n],A_st[i]))
    {
      fprintf(AGLA_file,"      case %d:\n",i);
      ubaci(St,i);
    }
}

void generisi_program(void)
{
  int f;
  int i;
  int j;
  long int k;
  AGLA_file=fopen("out.h","w");
  fprintf
  (
    AGLA_file,
    "#include <limits.h>\n"
    "#include <stdio.h>\n"
    "\n"
    "#define AGLA_LEN_VALUE 1024 /* duzina vrednosti lekseme (slobodno za menjanje) */\n"
    "#define AGLA_MAX_CLASS %d /* broj leksickih klasa */\n"
    "#define BS %d /* Broj Skupova slova */\n"
    "#define BT %d /* Broj sTanja */\n"
    "\n"
    "enum\n"
    "{\n"
    "  NISTA=-1,\n",
    Br_im+1,A_br_ss,A_br_st
  );
  for(i=0;i<Br_im;i++)
    fprintf(AGLA_file,"  %s,\n",Im[i]);
  fputs
  (
    "  AGLA_EOF\n"
    "} AGLA_class;\n"
    "char AGLA_value[AGLA_LEN_VALUE+1];\n"
    "int AGLA_len;\n"
    "int AGLA_old_nl;\n"
    "int AGLA_new_nl=1;\n"
    "int AGLA_old_pos;\n"
    "int AGLA_new_pos=1;\n"
    "FILE *AGLA_file;\n"
    "char *AGLA_error;\n"
    "\n"
    "int AGLA_scanner(void)\n"
    "{\n"
    "  static int len[AGLA_MAX_CLASS-1];\n"
    "  static int nl[AGLA_MAX_CLASS-1];\n"
    "  static int pos[AGLA_MAX_CLASS-1];\n"
    "  static unsigned char ss[UCHAR_MAX+1]=\n"
    "  {",
    AGLA_file
  );
  for(i=0;i<=UCHAR_MAX;i++)
  {
    if(i)
      fputc((int)',',AGLA_file);
    if(!(i%32))
      fputs("\n    ",AGLA_file);
    j=0;
    while(j<A_br_ss&&!element(A_ss[j],i))
      j++;
    if(j==A_br_ss)
      fputs("BS",AGLA_file);
    else
      fprintf(AGLA_file,"%d",j);
  }
  fputs
  (
    "\n"
    "  };\n"
    "  static int pr[BT][BS]=\n"
    "  {",
    AGLA_file
  );
  for(i=POCETNO_STANJE;i<A_br_st;i++)
  {
    if(i)
      fputc((int)',',AGLA_file);
    fputs("\n    {",AGLA_file);
    for(j=0;j<A_br_ss;j++)
    {
      if(j)
        fputc((int)',',AGLA_file);
      k=0l;
      while(k<A_vl_pr&&(A_pr[k].od_st!=i||A_pr[k].ss!=j))
        k++;
      if(k==A_vl_pr)
        fputs("BT",AGLA_file);
      else
        fprintf(AGLA_file,"%d",A_pr[k].do_st);
    }
    fputc((int)'}',AGLA_file);
  }
  fputs
  (
    "\n"
    "  };\n"
    "  int c;\n"
    "  int n;\n"
    "  int st;\n"
    "  st=0;\n"
    "  do\n"
    "  {\n"
    "    switch(st)\n"
    "    {\n",
    AGLA_file
  );
  izbaci_sve(DU_SO_ST,St);
  for(i=POCETNO_STANJE;i<A_br_st;i++)
    if(!element(St,i))
    {
      if(element(A_st[i],POCETNO_STANJE))
      {
        ispisi_case(i);
        f=0;
        fputs(
          "        AGLA_old_nl=AGLA_new_nl;\n"
          "        AGLA_old_pos=AGLA_new_pos;\n"
          "        n=0;\n"
          ,AGLA_file
        );
      }
      else
        f=1;
      j=koja_lx_pripada(A_st[i]);
      if(j!=Br_lx)
      {
        if(f)
        {
          ispisi_case(i);
          f=0;
        }
        fprintf(AGLA_file,"        AGLA_class=%s;\n",Im[Lx[j].im]);
      }
      else
        if(!f)
          fputs("        AGLA_class=NISTA;\n",AGLA_file);
      for(j=0;j<Br_lx;j++)
        if(element(A_st[i],Lx[j].do_st))
        {
          if(f)
          {
            ispisi_case(i);
            f=0;
          }
          fprintf
          (
            AGLA_file,
            "        len[%s]=n;\n"
            "        nl[%s]=AGLA_new_nl;\n"
            "        pos[%s]=AGLA_new_pos;\n",
            Im[Lx[j].im],Im[Lx[j].im],Im[Lx[j].im]
          );
        }
    }
  fputs
  (
    "    }\n"
    "    if((c=fgetc(AGLA_file))==EOF)\n"
    "      switch(st)\n"
    "      {\n",
    AGLA_file
  );
  for(i=POCETNO_STANJE;i<A_br_st;i++)
    if(element(A_st[i],POCETNO_STANJE))
      fprintf(AGLA_file,"        case %d:\n",i);
  fputs
  (
    "          AGLA_class=AGLA_EOF;\n"
    "        default:\n"
    "          st=BT;\n"
    "      }\n"
    "    else\n"
    "    {\n"
    "      if(c==(int)\'\\n\')\n"
    "      {\n"
    "        AGLA_new_nl++;\n"
    "        AGLA_new_pos=0;\n"
    "      }\n"
    "      else\n"
    "        AGLA_new_pos++;\n"
    "      if(n==AGLA_LEN_VALUE)\n"
    "      {\n"
    "        AGLA_error=\"Predugacka vrednost lekseme\";\n"
    "        return 1;\n"
    "      }\n"
    "      AGLA_value[n]=(char)c;\n"
    "      n++;\n"
    "      st=ss[c]==BS?BT:pr[st][ss[c]];\n"
    "    }\n"
    "  }\n"
    "  while(st!=BT);\n"
    "  if(AGLA_class==NISTA)\n"
    "  {\n"
    "    AGLA_error=\"Nepoznata leksema\";\n"
    "    return 1;\n"
    "  }\n"
    "  else\n"
    "  {\n"
    "    if(AGLA_class==AGLA_EOF)\n"
    "      AGLA_len=0;\n"
    "    else\n"
    "    {\n"
    "      AGLA_len=len[AGLA_class];\n"
    "      fseek(AGLA_file,(long)(AGLA_len-n),SEEK_CUR);\n"
    "      AGLA_new_nl=nl[AGLA_class];\n"
    "      AGLA_new_pos=pos[AGLA_class];\n"
    "    }\n"
    "    AGLA_value[AGLA_len]=\'\\0\';\n"
    "  }\n"
    "  return 0;\n"
    "}\n",
    AGLA_file
  );
  fclose(AGLA_file);
}

void zavrsna_semanticka_f_ja(void)
{
  int i;
  for(i=0;i<Br_va;i++)
    if(Va[i].poziv)
      printf("Upozorenje : varijabla %s se nikada ne koristi\n",Va[i].im);
  razdvajanje_ss();
  determinizacija();
  minimizacija();
  generisi_program();
}

void AGSA_get_SLOVO_s_slovo_get(void)
{
  AGLA_scanner();
  if(AGLA_class!=SLOVO)
    error(0,"Ocekivao sam : slovo");
  s_slovo();
  AGLA_scanner();
}

void AGSA_K(void)
{
  switch(AGLA_class)
  {
    case MINUS:
      AGSA_get_SLOVO_s_slovo_get();
      s_od_do();
      break;
    case SLOVO:
    case DESNA_UGLASTA_ZAGRADA:
    case XOR:
      break;
    default:
      error(0,"Ocekivao sam : slovo ] ^ -");
  }
}

void AGSA_J(void)
{
  while(AGLA_class==SLOVO)
  {
    s_slovo();
    AGLA_scanner();
    AGSA_K();
    s_unija();
  }
  if(AGLA_class!=DESNA_UGLASTA_ZAGRADA&&AGLA_class!=XOR)
    error(0,"Ocekivao sam : slovo ] ^");
}

void AGSA_I(void)
{
  switch(AGLA_class)
  {
    case SLOVO:
      s_slovo();
      AGLA_scanner();
      AGSA_K();
      AGSA_J();
      s_komplement();
      break;
    case DESNA_UGLASTA_ZAGRADA:
      s_sva_slova();
      break;
    default:
      error(0,"Ocekivao sam : slovo ]");
  }
}

void AGSA_H(void)
{
  switch(AGLA_class)
  {
    case XOR:
      AGSA_get_SLOVO_s_slovo_get();
      AGSA_K();
      AGSA_J();
      s_razlika();
      break;
    case DESNA_UGLASTA_ZAGRADA:
      break;
    default:
      error(0,"Ocekivao sam : ] ^");
  }
}

void AGSA_G(void)
{
  switch(AGLA_class)
  {
    case SLOVO:
      s_slovo();
      AGLA_scanner();
      AGSA_K();
      AGSA_J();
      AGSA_H();
      break;
    case XOR:
      AGLA_scanner();
      AGSA_I();
      break;
    default:
      error(0,"Ocekivao sam : slovo ^");
  }
}

void AGSA_F(void)
{
  while(AGLA_class==ZVEZDICA||AGLA_class==PLUS||AGLA_class==PITALICA)
  {
    if(AGLA_class==ZVEZDICA||AGLA_class==PLUS)
      r_plus();
    if(AGLA_class==ZVEZDICA||AGLA_class==PITALICA)
      r_pitalica();
    AGLA_scanner();
  }
  if(AGLA_class!=VARIJABLA&&AGLA_class!=SLOVO&&AGLA_class!=TACKA&&AGLA_class!=RAZLIKA&&AGLA_class!=LEVA_UGLASTA_ZAGRADA&&AGLA_class!=LEVA_ZAGRADA&&AGLA_class!=DESNA_ZAGRADA&&AGLA_class!=ILI)
    error(0,"Ocekivao sam : varijablu slovo . / [ ( ) | * + ?");
}

void AGSA_C(void);

void AGSA_E(void)
{
  while(AGLA_class==VARIJABLA||AGLA_class==SLOVO||AGLA_class==LEVA_UGLASTA_ZAGRADA||AGLA_class==LEVA_ZAGRADA)
  {
    AGSA_C();
    AGSA_F();
    r_tacka();
  }
  if(AGLA_class!=TACKA&&AGLA_class!=RAZLIKA&&AGLA_class!=DESNA_ZAGRADA&&AGLA_class!=ILI)
    error(0,"Ocekivao sam : varijablu slovo . / [ ( ) |");
}

void AGSA_D(void)
{
  while(AGLA_class==ILI)
  {
    AGLA_scanner();
    AGSA_C();
    AGSA_F();
    AGSA_E();
    r_ili();
  }
  if(AGLA_class!=TACKA&&AGLA_class!=RAZLIKA&&AGLA_class!=DESNA_ZAGRADA)
    error(0,"Ocekivao sam : . / ) |");
}

void AGSA_get_C_F_E_D(void)
{
  AGLA_scanner();
  AGSA_C();
  AGSA_F();
  AGSA_E();
  AGSA_D();
}

void AGSA_C(void)
{
  switch(AGLA_class)
  {
    case VARIJABLA:
      r_varijable();
      AGLA_scanner();
      break;
    case SLOVO:
      s_slovo();
      r_slova();
      AGLA_scanner();
      break;
    case LEVA_UGLASTA_ZAGRADA:
      AGLA_scanner();
      AGSA_G();
      if(AGLA_class!=DESNA_UGLASTA_ZAGRADA)
        error(0,"Ocekivao sam : ]");
      r_slova();
      AGLA_scanner();
      break;
    case LEVA_ZAGRADA:
      AGSA_get_C_F_E_D();
      if(AGLA_class!=DESNA_ZAGRADA)
        error(0,"Ocekivao sam : )");
      AGLA_scanner();
      break;
    default:
      error(0,"Ocekivao sam : varijablu slovo [ (");
  }
}

void AGSA_B(void)
{
  switch(AGLA_class)
  {
    case RAZLIKA:
      AGSA_get_C_F_E_D();
      r_tacka();
      break;
    case TACKA:
      break;
    default:
      error(0,"Ocekivao sam : . /");
  }
}

void AGSA_get_JEDNAKO_get_C_F_E_D(void)
{
  AGLA_scanner();
  if(AGLA_class!=JEDNAKO)
    error(0,"Ocekivao sam : =");
  AGSA_get_C_F_E_D();
}

void AGSA_A(void)
{
  while(AGLA_class==IME||AGLA_class==VARIJABLA||AGLA_class==JEDNAKO)
  {
    switch(AGLA_class)
    {
      case IME:
        g_ime();
        AGSA_get_JEDNAKO_get_C_F_E_D();
        g_dokle();
        AGSA_B();
        g_zavrsi_spoji();
        break;
      case VARIJABLA:
        g_varijabla();
        AGSA_get_JEDNAKO_get_C_F_E_D();
        g_zapamti();
        break;
      case JEDNAKO:
        AGSA_get_C_F_E_D();
        g_spoji_del();
    }
    if(AGLA_class!=TACKA)
      error(0,"Ocekivao sam : .");
    AGLA_scanner();
  }
  if(AGLA_class!=AGLA_EOF)
    error(0,"Ocekivao sam : kraj_datoteke ime varijablu =");
}

int main(int argc,char *argv[])
{
  if(argc==2)
    if((AGLA_file=fopen(argv[1],"r"))!=NULL)
    {
      AGLA_new_nl=1;
      AGLA_new_pos=1;
      AGLA_scanner();
      pocetni_semanticki_domen();
      AGSA_A();
      fclose(AGLA_file);
      zavrsna_semanticka_f_ja();
    }
    else
      puts("Neispravan ulazni fajl");
  else
    puts("Prosledi parametar sa imenom ulaznog fajla");
  return 0;
}
