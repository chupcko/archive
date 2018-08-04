#include <setjmp.h> /* jmp_buf longjmp setjmp */
#include <stdio.h> /* FILE NULL EOF fclose fgetc fopen printf */
#include <string.h> /* strcmp strcpy */

#define MAX_BROJ_IMENA 64 /* Slobodno za menjanje */
#define MAX_DUZINA_IMENA 4 /* Slobodno za menjanje */
#define MAX_VELICINA_N_FORMULE 256 /* Slobodno za menjanje */
#define MAX_VELICINA_R_FORMULE 512 /* Slobodno za menjanje */
#define MAX_BROJ_TABLOA 256 /* Slobodno za menjanje */

#define BROJ_SLUZBENIH_RECI 7

#define KONSTANTA -11
#define KRAJ_ULAZA -10
#define OTVORENA_ZAGRADA -9
#define ZATVORENA_ZAGRADA -8
#define NOT -7
#define ALL -6
#define E -5
#define AND -4
#define OR -3
#define THEN -2
#define EQ -1

#define NIL -1

#define FALSE 0
#define TRUE !FALSE

jmp_buf Dugi_skok;
FILE *Datoteka;
int Slovo;
int Leksema;
int Poslednja_leksema;
struct
{
  char ime[MAX_DUZINA_IMENA+1];
  enum
  {
    novo,
    predikat,
    iskaz,
    promenljiva
  } tip;
} Imena[MAX_BROJ_IMENA];
int Broj_imena;
struct
{
  int ime;
  int koristi_se;
} Konstante[MAX_BROJ_IMENA];
int Broj_konstanata;
struct
{
  int ime;
  int konstanta;
} U_dejstvu[MAX_BROJ_IMENA];
int Broj_dejstava;
int N_formula[MAX_VELICINA_N_FORMULE];
int Velicina_n_formule;
int R_formula[MAX_VELICINA_R_FORMULE];
int Velicina_r_formule;
int Redosled_kvantifikatora;
struct
{
  int predikat;
  int konstanta;
  int vrednost;
  int levo;
  int desno;
} Tablo[MAX_BROJ_TABLOA];
int Zadnji_tablo;
int Grana[MAX_BROJ_TABLOA];
int Velicina_grane;

void greska(char *s)
{
  printf("\n\nDoslo je do sledece greske:\n%s\n",s);
  longjmp(Dugi_skok,2);
}

void ucitaj_sledece_slovo_ulaza(void)
{
  Slovo=fgetc(Datoteka);
  if(Slovo==EOF)
    printf("\n");
  else
    printf("%c",(char)Slovo);
}

void ucitaj_sledecu_leksemu_ulaza(void)
{
  static char sluzbene_reci[BROJ_SLUZBENIH_RECI][MAX_DUZINA_IMENA+1]=
  {
    "EQ",
    "THEN",
    "OR",
    "AND",
    "E",
    "ALL",
    "NOT"
  };
  enum
  {
    pocetno,
    srednje,
    krajnje
  } stanje;
  static char ime[MAX_DUZINA_IMENA+1];
  int duzina_imena;
  stanje=pocetno;
  do
    if(stanje==pocetno)
      switch(Slovo)
      {
        case (int)'\n':
        case (int)'\t':
        case (int)' ':
          ucitaj_sledece_slovo_ulaza();
          break;
        case EOF:
          Leksema=KRAJ_ULAZA;
          stanje=krajnje;
          break;
        case (int)'(':
          Leksema=OTVORENA_ZAGRADA;
          ucitaj_sledece_slovo_ulaza();
          stanje=krajnje;
          break;
        case (int)')':
          Leksema=ZATVORENA_ZAGRADA;
          ucitaj_sledece_slovo_ulaza();
          stanje=krajnje;
          break;
        default:
          if(Slovo>=(int)'A'&&Slovo<=(int)'Z'||Slovo>=(int)'a'&&Slovo<=(int)'z')
          {
            ime[0]=(char)Slovo;
            duzina_imena=1;
            ucitaj_sledece_slovo_ulaza();
            stanje=srednje;
          }
          else
            greska("Naisao sam na slovo koji ne prepoznajem.");
      }
    else
      switch(Slovo)
      {
        case (int)'\n':
        case (int)'\t':
        case (int)' ':
        case EOF:
        case (int)'(':
        case (int)')':
          ime[duzina_imena]='\0';
          Leksema=0;
          while(Leksema<BROJ_SLUZBENIH_RECI&&strcmp(sluzbene_reci[Leksema],ime))
            Leksema++;
          if(Leksema==BROJ_SLUZBENIH_RECI)
          {
            Leksema=0;
            while(Leksema<Broj_imena&&strcmp(Imena[Leksema].ime,ime))
              Leksema++;
            if(Leksema==Broj_imena)
            {
              if(Broj_imena==MAX_BROJ_IMENA)
                greska("Mnogo imena.");
              strcpy(Imena[Broj_imena].ime,ime);
              Imena[Broj_imena].tip=novo;
              Broj_imena++;
            }
          }
          else
            Leksema=EQ-Leksema;
          stanje=krajnje;
          break;
        default:
          if(Slovo>=(int)'A'&&Slovo<=(int)'Z'||Slovo>=(int)'a'&&Slovo<=(int)'z'||Slovo>=(int)'0'&&Slovo<=(int)'9')
          {
            if(duzina_imena==MAX_DUZINA_IMENA)
              greska("Ime duze od dozvoljene duzine imena.");
            ime[duzina_imena]=(char)Slovo;
            duzina_imena++;
            ucitaj_sledece_slovo_ulaza();
          }
          else
            greska("Naisao sam na slovo koji ne prepoznajem.");
      }
  while(stanje!=krajnje);
}

void ubaci_u_n_formulu(int ime)
{
  if(Velicina_n_formule==MAX_VELICINA_N_FORMULE)
    greska("Mnogo dugacka formula.");
  N_formula[Velicina_n_formule]=ime;
  Velicina_n_formule++;
}

void parsiraj_formulu_g(void)
{
  switch(Leksema)
  {
    case OTVORENA_ZAGRADA:
      if(Imena[Poslednja_leksema].tip==iskaz)
        greska("Pomesani predikat i iskaz.");
      Imena[Poslednja_leksema].tip=predikat;
      ucitaj_sledecu_leksemu_ulaza();
      if(Leksema<0)
        greska("Ocekivao sam neko ime.");
      if(Imena[Leksema].tip==predikat||Imena[Leksema].tip==iskaz)
        greska("Pojavilo se isto ime za promenjlivu i predikat.");
      Imena[Leksema].tip=promenljiva;
      {
        int i;
        i=Broj_dejstava-1;
        while(i>=0&&Leksema!=U_dejstvu[i].ime)
          i--;
        if(i>=0)
          ubaci_u_n_formulu(U_dejstvu[i].konstanta);
        else
        {
          i=0;
          while(i<Broj_konstanata&&Leksema!=Konstante[i].ime)
            i++;
          if(i==Broj_konstanata)
          {
            if(Broj_konstanata==MAX_BROJ_IMENA)
              greska("Mnogo konstanata.");
            Konstante[Broj_konstanata].ime=Leksema;
            Konstante[Broj_konstanata].koristi_se=TRUE;
            Broj_konstanata++;
          }
          ubaci_u_n_formulu(i);
        }
      }
      ucitaj_sledecu_leksemu_ulaza();
      if(Leksema!=ZATVORENA_ZAGRADA)
        greska("Ocekivao sam: ).");
      ucitaj_sledecu_leksemu_ulaza();
      break;
    case AND:
    case OR:
    case THEN:
    case EQ:
    case ZATVORENA_ZAGRADA:
    case KRAJ_ULAZA:
      if(Imena[Poslednja_leksema].tip==predikat)
        greska("Pomesani iskaz i predikat.");
      Imena[Poslednja_leksema].tip=iskaz;
      break;
    default:
      greska("Ocekivao sam: (,AND,OR,THEN,EQ,) ili kraj ulaza.");
  }
}

void parsiraj_formulu_a(void);

void parsiraj_formulu_f(void)
{
  switch(Leksema)
  {
    case E:
    case ALL:
    {
      int sta;
      int kvantifikovano_ime;
      sta=Leksema;
      ucitaj_sledecu_leksemu_ulaza();
      if(Leksema<0)
        greska("Ocekivao sam neko ime.");
      if(Imena[Leksema].tip==predikat||Imena[Leksema].tip==iskaz)
        greska("Pojavilo se isto ime za promenjlivu i predikat.");
      Imena[Leksema].tip=promenljiva;
      if(Broj_konstanata==MAX_BROJ_IMENA||Broj_dejstava==MAX_BROJ_IMENA)
        greska("Mnogo konstanata ili kvantifikatora.");
      Konstante[Broj_konstanata].ime=KONSTANTA;
      Konstante[Broj_konstanata].koristi_se=FALSE;
      U_dejstvu[Broj_dejstava].ime=Leksema;
      U_dejstvu[Broj_dejstava].konstanta=Broj_konstanata;
      kvantifikovano_ime=Broj_konstanata;
      Broj_konstanata++;
      Broj_dejstava++;
      ucitaj_sledecu_leksemu_ulaza();
      parsiraj_formulu_f();
      Broj_dejstava--;
      ubaci_u_n_formulu(kvantifikovano_ime);
      ubaci_u_n_formulu(sta);
      break;
    }
    case NOT:
      ucitaj_sledecu_leksemu_ulaza();
      parsiraj_formulu_f();
      ubaci_u_n_formulu(NOT);
      break;
    case OTVORENA_ZAGRADA:
      ucitaj_sledecu_leksemu_ulaza();
      parsiraj_formulu_a();
      if(Leksema!=ZATVORENA_ZAGRADA)
        greska("Ocekivao sam: ).");
      ucitaj_sledecu_leksemu_ulaza();
      break;
    default:
      if(Leksema<0)
        greska("Ocekivao sam: E,ALL,NOT,( ili neko ime.");
      if(Imena[Leksema].tip==promenljiva)
        greska("Pojavilo se isto ime za predikat i promenjlivu.");
      Poslednja_leksema=Leksema;
      ucitaj_sledecu_leksemu_ulaza();
      parsiraj_formulu_g();
      ubaci_u_n_formulu(Poslednja_leksema);
  }
}

void parsiraj_formulu_e(void)
{
  switch(Leksema)
  {
    case AND:
      ucitaj_sledecu_leksemu_ulaza();
      parsiraj_formulu_f();
      parsiraj_formulu_e();
      ubaci_u_n_formulu(AND);
      break;
    case OR:
    case THEN:
    case EQ:
    case ZATVORENA_ZAGRADA:
    case KRAJ_ULAZA:
      break;
    default:
      greska("Ocekivao sam: AND,OR,THEN,EQ,) ili kraj ulaza.");
  }
}

void parsiraj_formulu_d(void)
{
  switch(Leksema)
  {
    case OR:
      ucitaj_sledecu_leksemu_ulaza();
      parsiraj_formulu_f();
      parsiraj_formulu_e();
      parsiraj_formulu_d();
      ubaci_u_n_formulu(OR);
      break;
    case THEN:
    case EQ:
    case ZATVORENA_ZAGRADA:
    case KRAJ_ULAZA:
      break;
    default:
      greska("Ocekivao sam: OR,THEN,EQ,) ili kraj ulaza.");
  }
}

void parsiraj_formulu_c(void)
{
  switch(Leksema)
  {
    case THEN:
      ucitaj_sledecu_leksemu_ulaza();
      parsiraj_formulu_f();
      parsiraj_formulu_e();
      parsiraj_formulu_d();
      parsiraj_formulu_c();
      ubaci_u_n_formulu(THEN);
      break;
    case EQ:
    case ZATVORENA_ZAGRADA:
    case KRAJ_ULAZA:
      break;
    default:
      greska("Ocekivao sam: THEN,EQ,) ili kraj ulaza.");
  }
}

void parsiraj_formulu_b(void)
{
  switch(Leksema)
  {
    case EQ:
      ucitaj_sledecu_leksemu_ulaza();
      parsiraj_formulu_f();
      parsiraj_formulu_e();
      parsiraj_formulu_d();
      parsiraj_formulu_c();
      parsiraj_formulu_b();
      ubaci_u_n_formulu(EQ);
      break;
    case ZATVORENA_ZAGRADA:
    case KRAJ_ULAZA:
      break;
    default:
      greska("Ocekivao sam: EQ,) ili kraj ulaza.");
  }
}

void parsiraj_formulu_a(void)
{
  parsiraj_formulu_f();
  parsiraj_formulu_e();
  parsiraj_formulu_d();
  parsiraj_formulu_c();
  parsiraj_formulu_b();
}

void ubaci_u_r_formulu(int ime)
{
  if(Velicina_r_formule==MAX_VELICINA_R_FORMULE)
    greska("Mnogo dugacka formula kad izbacimo THEN i EQ.");
  R_formula[Velicina_r_formule]=ime;
  Velicina_r_formule++;
}

void n_formulu_u_r_formulu(void)
{
  Velicina_n_formule--;
  switch(N_formula[Velicina_n_formule])
  {
    case EQ:
    {
      int polozaj;
      polozaj=Velicina_n_formule;
      ubaci_u_r_formulu(AND);
      ubaci_u_r_formulu(OR);
      n_formulu_u_r_formulu();
      ubaci_u_r_formulu(NOT);
      n_formulu_u_r_formulu();
      Velicina_n_formule=polozaj;
      ubaci_u_r_formulu(OR);
      ubaci_u_r_formulu(NOT);
      n_formulu_u_r_formulu();
      n_formulu_u_r_formulu();
      break;
    }
    case THEN:
      ubaci_u_r_formulu(OR);
      n_formulu_u_r_formulu();
      ubaci_u_r_formulu(NOT);
      n_formulu_u_r_formulu();
      break;
    case OR:
    case AND:
      ubaci_u_r_formulu(N_formula[Velicina_n_formule]);
      n_formulu_u_r_formulu();
      n_formulu_u_r_formulu();
      break;
    case E:
    case ALL:
      ubaci_u_r_formulu(N_formula[Velicina_n_formule]);
      Velicina_n_formule--;
      ubaci_u_r_formulu(N_formula[Velicina_n_formule]);
      n_formulu_u_r_formulu();
      break;
    case NOT:
      ubaci_u_r_formulu(N_formula[Velicina_n_formule]);
      n_formulu_u_r_formulu();
      break;
    default:
      ubaci_u_r_formulu(N_formula[Velicina_n_formule]);
      if(Imena[N_formula[Velicina_n_formule]].tip==predikat)
      {
        Velicina_n_formule--;
        ubaci_u_r_formulu(N_formula[Velicina_n_formule]);
      }
  }
}

void prebroj_konstante(int vrednost)
{
  Velicina_r_formule++;
  switch(R_formula[Velicina_r_formule-1])
  {
    case OR:
    case AND:
      prebroj_konstante(vrednost);
      prebroj_konstante(vrednost);
      break;
    case E:
    case ALL:
      if(R_formula[Velicina_r_formule-1]==ALL==vrednost)
      {
        Velicina_r_formule++;
        Redosled_kvantifikatora=TRUE;
        prebroj_konstante(vrednost);
        Redosled_kvantifikatora=FALSE;
      }
      else
        if(Redosled_kvantifikatora)
          greska("Formula nije u redukovanoj formi.");
        else
        {
          Konstante[R_formula[Velicina_r_formule]].koristi_se=TRUE;
          Velicina_r_formule++;
          prebroj_konstante(vrednost);
        }
      break;
    case NOT:
      prebroj_konstante(!vrednost);
      break;
    default:
      if(Imena[R_formula[Velicina_r_formule-1]].tip==predikat)
        Velicina_r_formule++;
  }
}

void uvecaj_broj_tabloa(void)
{
  Zadnji_tablo++;
  if(Zadnji_tablo==MAX_BROJ_TABLOA)
    greska("Mnogo veliki tablo.");
}

void pravi_tablo(int index)
{
  Velicina_r_formule++;
  switch(R_formula[Velicina_r_formule-1])
  {
    case OR:
    case AND:
      if(R_formula[Velicina_r_formule-1]==OR==Tablo[index].vrednost)
      {
        Tablo[index].predikat=OR;
        uvecaj_broj_tabloa();
        Tablo[Zadnji_tablo].vrednost=Tablo[index].vrednost;
        Tablo[Zadnji_tablo].levo=Tablo[index].levo;
        Tablo[index].desno=Zadnji_tablo;
        pravi_tablo(Zadnji_tablo);
        uvecaj_broj_tabloa();
        Tablo[Zadnji_tablo].vrednost=Tablo[index].vrednost;
        Tablo[Zadnji_tablo].levo=Tablo[index].levo;
        Tablo[index].levo=Zadnji_tablo;
        pravi_tablo(Zadnji_tablo);
      }
      else
      {
        uvecaj_broj_tabloa();
        Tablo[Zadnji_tablo].vrednost=Tablo[index].vrednost;
        Tablo[Zadnji_tablo].levo=Tablo[index].levo;
        Tablo[index].levo=Zadnji_tablo;
        pravi_tablo(Zadnji_tablo);
        pravi_tablo(index);
      }
      break;
    case E:
    case ALL:
      if(R_formula[Velicina_r_formule-1]==ALL==Tablo[index].vrednost)
      {
        int koja_konstanta;
        int trenutni_broj_dejstava;
        int trenutna_velicina_r_formule;
        if(Broj_dejstava==MAX_BROJ_IMENA)
          greska("Mnogo kvantifikatora.");
        U_dejstvu[Broj_dejstava].ime=R_formula[Velicina_r_formule];
        trenutni_broj_dejstava=Broj_dejstava;
        Broj_dejstava++;
        Velicina_r_formule++;
        trenutna_velicina_r_formule=Velicina_r_formule;
        {
          int koliko_konstanata;
          koliko_konstanata=0;
          koja_konstanta=0;
          while(koja_konstanta<Broj_konstanata)
          {
            if(Konstante[koja_konstanta].koristi_se)
              koliko_konstanata++;
            koja_konstanta++;
          }
          koja_konstanta=1;
          while(koja_konstanta<koliko_konstanata)
          {
            uvecaj_broj_tabloa();
            Tablo[Zadnji_tablo].vrednost=Tablo[index].vrednost;
            Tablo[Zadnji_tablo].levo=Tablo[index].levo;
            Tablo[index].levo=Zadnji_tablo;
            koja_konstanta++;
          }
        }
        koja_konstanta=0;
        while(koja_konstanta<Broj_konstanata)
        {
          if(Konstante[koja_konstanta].koristi_se)
          {
            int sledeci;
            U_dejstvu[trenutni_broj_dejstava].konstanta=koja_konstanta;
            Velicina_r_formule=trenutna_velicina_r_formule;
            sledeci=Tablo[index].levo;
            pravi_tablo(index);
            index=sledeci;
          }
          koja_konstanta++;
        }
        Broj_dejstava--;
      }
      else
      {
        Velicina_r_formule++;
        pravi_tablo(index);
      }
      break;
    case NOT:
      Tablo[index].vrednost=!Tablo[index].vrednost;
      pravi_tablo(index);
      break;
    default:
      Tablo[index].predikat=R_formula[Velicina_r_formule-1];
      if(Imena[R_formula[Velicina_r_formule-1]].tip==predikat)
      {
        int i;
        i=0;
        while(i<Broj_dejstava&&R_formula[Velicina_r_formule]!=U_dejstvu[i].ime)
          i++;
        Tablo[index].konstanta=i<Broj_dejstava?U_dejstvu[i].konstanta:R_formula[Velicina_r_formule];
        Velicina_r_formule++;
      }
      else
        Tablo[index].konstanta=NIL;
  }
}

void izdvoji_grane(int index)
{
  if(index==NIL)
  {
    int i;
    int j;
    int nije_kontradikcija;
    nije_kontradikcija=TRUE;
    for(i=0;nije_kontradikcija&&i<Velicina_grane-1;i++)
      for(j=i+1;nije_kontradikcija&&j<Velicina_grane;j++)
        if(Tablo[Grana[i]].predikat==Tablo[Grana[j]].predikat&&Tablo[Grana[i]].konstanta==Tablo[Grana[j]].konstanta)
          nije_kontradikcija=Tablo[Grana[i]].vrednost==Tablo[Grana[j]].vrednost;
    if(nije_kontradikcija)
      longjmp(Dugi_skok,1);
  }
  else
    if(Tablo[index].predikat==OR)
    {
      izdvoji_grane(Tablo[index].levo);
      izdvoji_grane(Tablo[index].desno);
    }
    else
    {
      Grana[Velicina_grane]=index;
      Velicina_grane++;
      izdvoji_grane(Tablo[index].levo);
      Velicina_grane--;
    }
}

int main(int argc,char *argv[])
{
  if(argc==2)
  {
    int i;
    Datoteka=fopen(argv[1],"r");
    if(Datoteka!=NULL)
    {
      switch(setjmp(Dugi_skok))
      {
        case 0:
          ucitaj_sledece_slovo_ulaza();
          Broj_imena=0;
          ucitaj_sledecu_leksemu_ulaza();
          Broj_konstanata=0;
          Broj_dejstava=0;
          Velicina_n_formule=0;
          parsiraj_formulu_a();
          Velicina_r_formule=0;
          n_formulu_u_r_formulu();
          Velicina_r_formule=0;
          prebroj_konstante(FALSE);
          i=0;
          while(i<Broj_konstanata&&!Konstante[i].koristi_se)
            i++;
          if(i==Broj_konstanata)
          {
            if(Broj_konstanata==MAX_BROJ_IMENA)
              greska("Mnogo konstanata");
            Konstante[Broj_konstanata].ime=KONSTANTA;
            Konstante[Broj_konstanata].koristi_se=TRUE;
            Broj_konstanata++;
          }
          Velicina_r_formule=0;
          Tablo[0].vrednost=FALSE;
          Tablo[0].levo=NIL;
          Zadnji_tablo=0;
          pravi_tablo(0);
          Velicina_grane=0;
          izdvoji_grane(0);
          printf("jeste valjana formula monadickog racuna.\n");
          break;
        case 1:
          printf("nije valjana formula monadickog racuna.\n");
      }
      fclose(Datoteka);
    }
    else
      printf("Ne mogu otvoriti tu datoteku.\n");
  }
  else
    printf("Kao parametar prosledi ime datoteke sa formulom monadickog racuna.\n");
  return 0;
}
