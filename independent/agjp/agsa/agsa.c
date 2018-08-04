#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BR_SL_IM 16 /* Slobodno za menjanje */
#define MAX_BR_SL 512 /* Slobodno za menjanje */
#define MAX_BR_PR 1024 /* Slobodno za menjanje */
#define MAX_VL_DS 32768l /* Slobodno za menjanje */
#define EPS -1
#define PO_SL 0
#define EPS_EOF PO_SL

#define DU_SO (MAX_BR_SL-1)/CHAR_BIT+1

typedef unsigned char So_sl[DU_SO];

So_sl Izbor[MAX_BR_PR];
So_sl Prvi[MAX_BR_SL];
So_sl Sled[MAX_BR_SL];
So_sl Medju_rezultat;

struct
{
  char ime[MAX_BR_SL_IM+1];
  enum
  {
    NET_F,
    NET,
    TER,
    FJA
  } tip;
} Sl[MAX_BR_SL];
int Br_sl;
struct
{
  int levo;
  long int desno;
} Pr[MAX_BR_PR];
int Br_pr;
int Ds[MAX_VL_DS];
long int Vl_ds;
int Ima_fja;

int Slovo;
enum
{
  NISTA,
  NETERMINAL,
  TERMINAL,
  FUNKCIJA,
  JEDNAKO,
  TACKA,
  ILI,
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
  switch(i)
  {
    case 0:
      printf("Red %d , slovo %d - %s\n",AGLA_old_nl,AGLA_old_pos,s);
      break;
    case 1:
      printf("Neterminal %s nije opisan\n",s);
      break;
    default:
      puts(s);
  }
  exit(1);
}

void AGLA_scanner(void)
{
  int broj_slova;
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
    ZAVRSNO
  } stanje;
  int citaj;
  AGLA_class=NISTA;
  stanje=POCETNO;
  citaj=1;
  do
  {
    switch(stanje)
    {
      case POCETNO:
        AGLA_old_nl=AGLA_new_nl;
        AGLA_old_pos=AGLA_new_pos;
        broj_slova=0;
        switch(Slovo)
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
          case (int)'<':
            stanje=STANJE_1;
            break;
          case (int)'@':
            stanje=STANJE_4;
            break;
          case (int)':':
            stanje=STANJE_6;
            break;
          case (int)'.':
            AGLA_class=TACKA;
            stanje=ZAVRSNO;
            break;
          case (int)'|':
            AGLA_class=ILI;
            stanje=ZAVRSNO;
            break;
          default:
            stanje=Slovo==(int)'_'||Slovo>=(int)'a'&&Slovo<=(int)'z'||Slovo>=(int)'A'&&Slovo<=(int)'Z'?STANJE_3:ZAVRSNO;
        }
        break;
      case STANJE_0:
        broj_slova=0;
        switch(Slovo)
        {
          case EOF:
            stanje=ZAVRSNO;
            break;
          case (int)'$':
            stanje=POCETNO;
        }
        break;
      case STANJE_1:
        broj_slova=0;
        stanje=Slovo==(int)'_'||Slovo>=(int)'a'&&Slovo<=(int)'z'||Slovo>=(int)'A'&&Slovo<=(int)'Z'?STANJE_2:ZAVRSNO;
        break;
      case STANJE_2:
        if(Slovo==(int)'>')
        {
          AGLA_class=NETERMINAL;
          stanje=ZAVRSNO;
        }
        else
          if(Slovo!=(int)'_'&&(Slovo<(int)'a'||Slovo>(int)'z')&&(Slovo<(int)'A'||Slovo>(int)'Z')&&(Slovo<(int)'0'||Slovo>(int)'9'))
            stanje=ZAVRSNO;
        break;
      case STANJE_3:
      case STANJE_5:
        AGLA_class=stanje==STANJE_3?TERMINAL:FUNKCIJA;
        if(Slovo!=(int)'_'&&(Slovo<(int)'a'||Slovo>(int)'z')&&(Slovo<(int)'A'||Slovo>(int)'Z')&&(Slovo<(int)'0'||Slovo>(int)'9'))
        {
          stanje=ZAVRSNO;
          citaj=0;
        }
       break;
      case STANJE_4:
        broj_slova=0;
        stanje=Slovo==(int)'_'||Slovo>=(int)'a'&&Slovo<=(int)'z'||Slovo>=(int)'A'&&Slovo<=(int)'Z'?STANJE_5:ZAVRSNO;
        break;
      case STANJE_6:
        stanje=Slovo==(int)':'?STANJE_7:ZAVRSNO;
        break;
      case STANJE_7:
        if(Slovo==(int)'=')
          AGLA_class=JEDNAKO;
        stanje=ZAVRSNO;
    }
    if(Slovo!=EOF)
    {
      if(stanje!=ZAVRSNO&&broj_slova<MAX_BR_SL_IM)
      {
        AGLA_value[broj_slova]=(char)Slovo;
        broj_slova++;
      }
      if(citaj)
      {
        if(Slovo==(int)'\n')
        {
          AGLA_new_nl++;
          AGLA_new_pos=0;
        }
        else
          AGLA_new_pos++;
        Slovo=fgetc(AGLA_file);
      }
    }
  }
  while(stanje!=ZAVRSNO);
  switch(AGLA_class)
  {
    case NISTA:
      error(0,"Nepoznata leksema");
      break;
    case NETERMINAL:
    case TERMINAL:
    case FUNKCIJA:
      AGLA_value[broj_slova]='\0';
  }
}

void izbaci_sve(unsigned char x[])
{
  int i;
  for(i=0;i<DU_SO;i++)
    x[i]=(unsigned char)0;
}

void unija(unsigned char d[],unsigned char s[])
{
  int i;
  for(i=0;i<DU_SO;i++)
    d[i]|=s[i];
}

int podskup(unsigned char d[],unsigned char s[])
{
  int n;
  int i;
  n=1;
  for(i=0;n&&i<DU_SO;i++)
    n=!(int)(~d[i]&s[i]);
  return n;
}

int disjunktni(unsigned char d[],unsigned char s[])
{
  int n;
  int i;
  n=1;
  for(i=0;n&&i<DU_SO;i++)
    n=!(int)(d[i]&s[i]);
  return n;
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
  Br_sl=PO_SL;
  Br_pr=0;
  Vl_ds=0l;
  Ima_fja=0;
}

void ubaci_u_pr(int n)
{
  if(Br_pr==MAX_BR_PR)
    error(2,"Nema vise mesta za pravila");
  Pr[Br_pr].levo=n;
  Pr[Br_pr].desno=Vl_ds;
  Br_pr++;
}

void ubaci_u_ds(int n)
{
  if(Vl_ds==MAX_VL_DS)
    error(2,"Nema vise mesta za desnu stranu");
  Ds[Vl_ds]=n;
  Vl_ds++;
}

int pronadji_net(void)
{
  int i;
  i=0;
  while(i<Br_sl&&(Sl[i].tip>NET||strcmp(Sl[i].ime,AGLA_value)))
    i++;
  if(i==Br_sl)
  {
    if(Br_sl==MAX_BR_SL)
      error(2,"Mnogo neterminala medju slovima");
    strcpy(Sl[Br_sl].ime,AGLA_value);
    Sl[Br_sl].tip=NET_F;
    Br_sl++;
  }
  return i;
}

void f_pra(void)
{
  int i;
  i=pronadji_net();
  Sl[i].tip=NET;
  ubaci_u_pr(i);
}

void f_ili(void)
{
  ubaci_u_pr(Pr[Br_pr-1].levo);
}

void f_net(void)
{
  int i;
  i=pronadji_net();
  ubaci_u_ds(i);
}

void f_ter(void)
{
  int i;
  i=0;
  while(i<Br_sl&&(Sl[i].tip!=TER||strcmp(Sl[i].ime,AGLA_value)))
    i++;
  if(i==Br_sl)
  {
    if(Br_sl==MAX_BR_SL)
      error(2,"Mnogo terminala medju slovima");
    strcpy(Sl[Br_sl].ime,AGLA_value);
    Sl[Br_sl].tip=TER;
    Br_sl++;
  }
  ubaci_u_ds(i);
}

void f_fja(void)
{
  int i;
  i=0;
  while(i<Br_sl&&(Sl[i].tip!=FJA||strcmp(Sl[i].ime,AGLA_value)))
    i++;
  if(i==Br_sl)
  {
    if(Br_sl==MAX_BR_SL)
      error(2,"Mnogo funkcija medju slovima");
    strcpy(Sl[Br_sl].ime,AGLA_value);
    Sl[Br_sl].tip=FJA;
    Br_sl++;
  }
  ubaci_u_ds(i);
  Ima_fja=1;
}

void f_eps(void)
{
  ubaci_u_ds(EPS);
}

void skup_prvih(int i,long int j)
{
  int dalje;
  izbaci_sve(Medju_rezultat);
  dalje=1;
  while(dalje&&Ds[Pr[i].desno+j]!=EPS&&Sl[Ds[Pr[i].desno+j]].tip!=TER)
  {
    if(Sl[Ds[Pr[i].desno+j]].tip==NET)
    {
      unija(Medju_rezultat,Prvi[Ds[Pr[i].desno+j]]);
      if(element(Medju_rezultat,EPS_EOF))
        izbaci(Medju_rezultat,EPS_EOF);
      else
        dalje=0;
    }
    j++;
  }
  if(dalje)
    if(Ds[Pr[i].desno+j]==EPS)
      ubaci(Medju_rezultat,EPS_EOF);
    else
      ubaci(Medju_rezultat,Ds[Pr[i].desno+j]);
}

void izracunaj_prvi(void)
{
  int dalje;
  int i;
  do
  {
    dalje=0;
    for(i=0;i<Br_pr;i++)
    {
      skup_prvih(i,0l);
      if(!podskup(Izbor[i],Medju_rezultat))
      {
        unija(Izbor[i],Medju_rezultat);
        unija(Prvi[Pr[i].levo],Medju_rezultat);
        dalje=1;
      }
    }
  }
  while(dalje);
}

void izracunaj_sled(void)
{
  int dalje;
  int i;
  long int j;
  ubaci(Sled[PO_SL],EPS_EOF);
  do
  {
    dalje=0;
    for(i=0;i<Br_pr;i++)
      for(j=0l;Ds[Pr[i].desno+j]!=EPS;j++)
        if(Sl[Ds[Pr[i].desno+j]].tip==NET)
        {
          skup_prvih(i,j+1);
          if(element(Medju_rezultat,EPS_EOF))
          {
            izbaci(Medju_rezultat,EPS_EOF);
            unija(Medju_rezultat,Sled[Pr[i].levo]);
          }
          if(!podskup(Sled[Ds[Pr[i].desno+j]],Medju_rezultat))
          {
            unija(Sled[Ds[Pr[i].desno+j]],Medju_rezultat);
            dalje=1;
          }
        }
  }
  while(dalje);
}

void izracunaj_izbor(void)
{
  int i;
  for(i=0;i<Br_pr;i++)
    if(element(Izbor[i],EPS_EOF))
    {
      izbaci(Izbor[i],EPS_EOF);
      unija(Izbor[i],Sled[Pr[i].levo]);
    }
}

int jeste_ll1(void)
{
  int n;
  int i;
  int j;
  n=1;
  for(i=0;n&&i<Br_pr-1;i++)
    for(j=i+1;n&&j<Br_pr;j++)
      n=Pr[i].levo!=Pr[j].levo||disjunktni(Izbor[i],Izbor[j]);
  return n;
}

void ispis_izvestaja(void)
{
  int i;
  long int j;
  int k;
  AGLA_file=fopen("lst","w");
  for(i=0;i<Br_pr;i++)
  {
    fprintf(AGLA_file,"<%s> ::= ",Sl[Pr[i].levo].ime);
    for(j=Pr[i].desno;Ds[j]!=EPS;j++)
    {
      switch(Sl[Ds[j]].tip)
      {
        case NET:
          fputc((int)'<',AGLA_file);
          break;
        case FJA:
          fputc((int)'@',AGLA_file);
      }
      fputs(Sl[Ds[j]].ime,AGLA_file);
      if(Sl[Ds[j]].tip==NET)
        fputc((int)'>',AGLA_file);
      fputc((int)' ',AGLA_file);
    }
    fputc((int)'.',AGLA_file);
    for(k=PO_SL;k<Br_sl;k++)
      if(element(Izbor[i],k))
        fprintf(AGLA_file,"\n  %s",k==EPS_EOF?"AGLA_EOF":Sl[k].ime,AGLA_file);
    fputc((int)'\n',AGLA_file);
    fputc((int)'\n',AGLA_file);
  }
  fputs(jeste_ll1()?"Jeste":"Nije",AGLA_file);
  fputs(" LL(1) gramatika\n",AGLA_file);
  fclose(AGLA_file);
}

void generisi_program(void)
{
  int i;
  AGLA_file=fopen("out.c","w");
  fputs
  (
    "#include <stdio.h>\n"
    "#include \"out.h\"\n",
    AGLA_file
  );
  if(Ima_fja)
    fputs("#include \"function.h\"\n",AGLA_file);
  fputc((int)'\n',AGLA_file);
  for(i=PO_SL+1;i<Br_sl;i++)
    if(Sl[i].tip==NET)
      fprintf(AGLA_file,"int AGSA_%s(void);\n",Sl[i].ime);
  for(i=PO_SL;i<Br_sl;i++)
    if(Sl[i].tip==NET)
    {
      int j;
      fprintf
      (
        AGLA_file,
        "\n"
        "int AGSA_%s(void)\n"
        "{\n"
        "  switch(AGLA_class)\n"
        "  {\n",
        Sl[i].ime
      );
      izbaci_sve(Medju_rezultat);
      for(j=0;j<Br_pr;j++)
        if(Pr[j].levo==i)
        {
          int ima_case;
          int k;
          ima_case=0;
          for(k=PO_SL;k<Br_sl;k++)
            if(element(Izbor[j],k)&&!element(Medju_rezultat,k))
            {
              fprintf(AGLA_file,"    case %s:\n",k==EPS_EOF?"AGLA_EOF":Sl[k].ime);
              ubaci(Medju_rezultat,k);
              ima_case=1;
            }
          if(ima_case)
          {
            long int l;
            enum
            {
              POC,
              NOR,
              GET,
              END
            } st;
            l=Pr[j].desno;
            st=POC;
            do
            {
              if(st==GET&&Sl[Ds[l]].tip!=FJA)
                fputs
                (
                  "      if(AGLA_scanner())\n"
                  "        return 1;\n",
                  AGLA_file
                );
              if(Ds[l]==EPS)
                st=END;
              else
                switch(Sl[Ds[l]].tip)
                {
                  case NET:
                    fprintf
                    (
                      AGLA_file,
                      "      if(AGSA_%s())\n"
                      "        return 1;\n",
                      Sl[Ds[l]].ime
                    );
                    st=NOR;
                    break;
                  case TER:
                    if(st!=POC)
                      fprintf
                      (
                        AGLA_file,
                        "      if(AGLA_class!=%s)\n"
                        "      {\n"
                        "        AGLA_error=\"Ocekivao sam leksemu %s\";\n"
                        "        return 1;\n"
                        "      }\n",
                        Sl[Ds[l]].ime,Sl[Ds[l]].ime
                      );
                    st=GET;
                    break;
                  case FJA:
                    fprintf
                    (
                      AGLA_file,
                      "      if(%s())\n"
                      "        return 1;\n",
                      Sl[Ds[l]].ime
                    );
                }
              l++;
            }
            while(st!=END);
            fputs("      break;\n",AGLA_file);
          }
        }
      fputs
      (
        "    default:\n"
        "      AGLA_error=\"Ocekivao sam lekseme :",
        AGLA_file
      );
      for(j=PO_SL;j<Br_sl;j++)
        if(element(Medju_rezultat,j))
          fprintf(AGLA_file," %s",j==EPS_EOF?"AGLA_EOF":Sl[j].ime);
      fputs
      (
        "\";\n"
        "      return 1;\n"
        "  }\n"
        "  return 0;\n"
        "}\n",
        AGLA_file
      );
    }
  fprintf
  (
    AGLA_file,
    "\n"
    "int AGSA_parser(void)\n"
    "{\n"
    "  if(AGLA_scanner())\n"
    "    return 1;\n"
    "  if(AGSA_%s())\n"
    "    return 1;\n"
    "  if(AGLA_class!=AGLA_EOF)\n"
    "  {\n"
    "    AGLA_error=\"Prepoznao sam rec ali ima jos na ulazu\";\n"
    "    return 1;\n"
    "  }\n"
    "  return 0;\n"
    "}\n"
    "\n"
    "int main(int argc,char *argv[])\n"
    "{\n"
    "  if(argc==2)\n"
    "    if((AGLA_file=fopen(argv[1],\"r\"))!=NULL)\n"
    "    {\n"
    "      if(AGSA_parser())\n"
    "        printf(\"Red %%d, slovo %%d - %%s\\n\",AGLA_old_nl,AGLA_old_pos,AGLA_error);\n"
    "      else\n"
    "        puts(\"Sve je u redu\");\n"
    "      fclose(AGLA_file);\n"
    "    }\n"
    "    else\n"
    "      puts(\"Neispravan ulazni fajl\");\n"
    "  else\n"
    "    puts(\"Prosledi parametar sa imenom ulaznog fajla\");\n"
    "  return 0;\n"
    "}\n",
    Sl[PO_SL].ime
  );
  fclose(AGLA_file);
}

void zavrsna_semanticka_f_ja(void)
{
  int i;
  for(i=PO_SL;i<Br_sl;i++)
  {
    if(Sl[i].tip==NET_F)
      error(1,Sl[i].ime);
    izbaci_sve(Prvi[i]);
    izbaci_sve(Sled[i]);
  }
  for(i=0;i<Br_pr;i++)
    izbaci_sve(Izbor[i]);
  izracunaj_prvi();
  izracunaj_sled();
  izracunaj_izbor();
  ispis_izvestaja();
  generisi_program();
}

void AGSA_E(void)
{
  while(AGLA_class==NETERMINAL||AGLA_class==TERMINAL||AGLA_class==FUNKCIJA)
  {
    switch(AGLA_class)
    {
      case NETERMINAL:
        f_net();
        break;
      case TERMINAL:
        f_ter();
        break;
      case FUNKCIJA:
        f_fja();
    }
    AGLA_scanner();
  }
  if(AGLA_class==TACKA||AGLA_class==ILI)
    f_eps();
  else
    error(0,"Ocekivao sam : neterminal terminal funkciju . |");
}

void AGSA_D(void)
{
  while(AGLA_class==ILI)
  {
    f_ili();
    AGLA_scanner();
    AGSA_E();
  }
  if(AGLA_class!=TACKA)
    error(0,"Ocekivao sam : . |");
}

void AGSA_C(void)
{
  f_pra();
  AGLA_scanner();
  if(AGLA_class!=JEDNAKO)
    error(0,"Ocekivao sam : ::=");
  AGLA_scanner();
  AGSA_E();
  AGSA_D();
  if(AGLA_class!=TACKA)
    error(0,"Ocekivao sam : .");
  AGLA_scanner();
}

void AGSA_B(void)
{
  while(AGLA_class==NETERMINAL)
    AGSA_C();
  if(AGLA_class!=AGLA_EOF)
    error(0,"Ocekivao sam : kraj_datoteke neterminal");
}

void AGSA_A(void)
{
  if(AGLA_class==NETERMINAL)
  {
    AGSA_C();
    AGSA_B();
  }
  else
    error(0,"Ocekivao sam : neterminal");
}

int main(int argc,char *argv[])
{
  if(argc==2)
    if((AGLA_file=fopen(argv[1],"r"))!=NULL)
    {
      AGLA_new_nl=1;
      AGLA_new_pos=1;
      Slovo=fgetc(AGLA_file);
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
