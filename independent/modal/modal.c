#include <setjmp.h> /* jmp_buf longjmp setjmp */
#include <stdio.h> /* FILE NULL EOF fclose fgetc fopen gets printf */
#include <stdlib.h> /* system */
#include <string.h> /* strcat strcmp strcpy */

#define MAX_BROJ_IMENA 64 /* Slobodno za menjanje */
#define MAX_DUZINA_IMENA 4 /* Slobodno za menjanje */
#define MAX_VELICINA_N_FORMULE 256 /* Slobodno za menjanje */
#define MAX_VELICINA_R_FORMULE 512 /* Slobodno za menjanje */
#define MAX_BROJ_DECE 128 /* Slobodno za menjanje */
#define MAX_BROJ_SVETOVA 64 /* Slobodno za menjanje */
#define MAX_BROJ_TABLOA 256 /* Slobodno za menjanje */

#define BROJ_SLUZBENIH_RECI 7

#define KRAJ_ULAZA -10
#define OTVORENA_ZAGRADA -9
#define ZATVORENA_ZAGRADA -8
#define NOT -7
#define L -6
#define M -5
#define AND -4
#define OR -3
#define THEN -2
#define EQ -1

#define RACUN_T 0
#define RACUN_B 1
#define RACUN_S4 2
#define RACUN_S5 3

#define NIL -1

#define FALSE 0
#define TRUE !FALSE

#define DUZINA_ULAZA 80

jmp_buf Dugi_skok;
FILE *Datoteka;
int Slovo;
int Leksema;
char Imena[MAX_BROJ_IMENA][MAX_DUZINA_IMENA+1];
int Broj_imena;
int N_formula[MAX_VELICINA_N_FORMULE];
int Velicina_n_formule;
int R_formula[MAX_VELICINA_R_FORMULE];
int Velicina_r_formule;
int Broj_svetova;
struct
{
  int dete;
  int roditelj;
  int broj_naslednika;
} Deca[MAX_BROJ_DECE];
int Broj_dece;
int Vidik[MAX_BROJ_SVETOVA][MAX_BROJ_SVETOVA];
int Naslednici[MAX_BROJ_SVETOVA];
int Broj_naslednika;
struct
{
  int ime;
  int svet;
  int broj_naslednika;
  int vrednost;
  int levo;
  int desno;
} Tablo[MAX_BROJ_TABLOA];
int Zadnji_tablo;
int Broj_obradenih_svetova;
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
    "M",
    "L",
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
            while(Leksema<Broj_imena&&strcmp(Imena[Leksema],ime))
              Leksema++;
            if(Leksema==Broj_imena)
            {
              if(Broj_imena==MAX_BROJ_IMENA)
                greska("Mnogo imena.");
              strcpy(Imena[Broj_imena],ime);
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

void parsiraj_formulu_a(void);

void parsiraj_formulu_f(void)
{
  switch(Leksema)
  {
    case M:
      ucitaj_sledecu_leksemu_ulaza();
      parsiraj_formulu_f();
      ubaci_u_n_formulu(M);
      break;
    case L:
      ucitaj_sledecu_leksemu_ulaza();
      parsiraj_formulu_f();
      ubaci_u_n_formulu(L);
      break;
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
        greska("Ocekivao sam: M,L,NOT,( ili neko ime.");
      ubaci_u_n_formulu(Leksema);
      ucitaj_sledecu_leksemu_ulaza();
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
    case M:
    case L:
    case NOT:
      ubaci_u_r_formulu(N_formula[Velicina_n_formule]);
      n_formulu_u_r_formulu();
      break;
    default:
      ubaci_u_r_formulu(N_formula[Velicina_n_formule]);
  }
}

void prebroj_svetove(int svet,int broj_naslednika,int vrednost)
{
  Velicina_r_formule++;
  switch(R_formula[Velicina_r_formule-1])
  {
    case OR:
    case AND:
      prebroj_svetove(svet,broj_naslednika,vrednost);
      prebroj_svetove(svet,broj_naslednika,vrednost);
      break;
    case M:
    case L:
      if(R_formula[Velicina_r_formule-1]==L==vrednost)
        prebroj_svetove(svet,broj_naslednika+1,vrednost);
      else
      {
        if(Broj_svetova==MAX_BROJ_SVETOVA||Broj_dece==MAX_BROJ_DECE)
          greska("Mnogo svetova ili relacija vidljivosti izmedu svetova.");
        Deca[Broj_dece].dete=Broj_svetova;
        Deca[Broj_dece].roditelj=svet;
        Deca[Broj_dece].broj_naslednika=broj_naslednika;
        Broj_dece++;
        Broj_svetova++;
        prebroj_svetove(Broj_svetova-1,0,vrednost);
      }
      break;
    case NOT:
      prebroj_svetove(svet,broj_naslednika,!vrednost);
  }
}

void odredi_naslednike(int svet,int koliko)
{
  int i;
  i=0;
  while(i<Broj_naslednika&&Naslednici[i]!=svet)
    i++;
  if(i==Broj_naslednika)
  {
    Naslednici[Broj_naslednika]=svet;
    Broj_naslednika++;
  }
  if(koliko)
    for(i=0;i<Broj_svetova;i++)
      if(i!=svet&&Vidik[svet][i])
        odredi_naslednike(i,koliko-1);
}

void uvecaj_broj_tabloa(void)
{
  Zadnji_tablo++;
  if(Zadnji_tablo==MAX_BROJ_TABLOA)
    greska("Mnogo veliki tablo.");
}

void ulancaj_tabloe(int index)
{
  int i;
  Broj_naslednika=0;
  odredi_naslednike(Tablo[index].svet,Tablo[index].broj_naslednika);
  Tablo[index].broj_naslednika=0;
  for(i=1;i<Broj_naslednika;i++)
  {
    uvecaj_broj_tabloa();
    Tablo[Zadnji_tablo].ime=Tablo[index].ime;
    Tablo[Zadnji_tablo].svet=Naslednici[i];
    Tablo[Zadnji_tablo].broj_naslednika=0;
    Tablo[Zadnji_tablo].vrednost=Tablo[index].vrednost;
    Tablo[Zadnji_tablo].levo=Tablo[index].levo;
    Tablo[index].levo=Zadnji_tablo;
  }
}

void pravi_tablo(int index)
{
  Velicina_r_formule++;
  switch(R_formula[Velicina_r_formule-1])
  {
    case OR:
    case AND:
      if(R_formula[Velicina_r_formule-1]==OR==Tablo[index].vrednost)
        if(Tablo[index].broj_naslednika)
        {
          int zadnji;
          int trenutni_broj_obradenih_svetova;
          int trenutna_velicina_r_formule;
          zadnji=Tablo[index].levo;
          trenutni_broj_obradenih_svetova=Broj_obradenih_svetova;
          trenutna_velicina_r_formule=Velicina_r_formule-1;
          ulancaj_tabloe(index);
          do
          {
            int sledeci;
            sledeci=Tablo[index].levo;
            pravi_tablo(index);
            index=sledeci;
            if(index!=zadnji)
            {
              Broj_obradenih_svetova=trenutni_broj_obradenih_svetova;
              Velicina_r_formule=trenutna_velicina_r_formule;
            }
          }
          while(index!=zadnji);
        }
        else
        {
          Tablo[index].ime=OR;
          uvecaj_broj_tabloa();
          Tablo[Zadnji_tablo].svet=Tablo[index].svet;
          Tablo[Zadnji_tablo].broj_naslednika=0;
          Tablo[Zadnji_tablo].vrednost=Tablo[index].vrednost;
          Tablo[Zadnji_tablo].levo=Tablo[index].levo;
          Tablo[index].desno=Zadnji_tablo;
          pravi_tablo(Zadnji_tablo);
          uvecaj_broj_tabloa();
          Tablo[Zadnji_tablo].svet=Tablo[index].svet;
          Tablo[Zadnji_tablo].broj_naslednika=0;
          Tablo[Zadnji_tablo].vrednost=Tablo[index].vrednost;
          Tablo[Zadnji_tablo].levo=Tablo[index].levo;
          Tablo[index].levo=Zadnji_tablo;
          pravi_tablo(Zadnji_tablo);
        }
      else
      {
        uvecaj_broj_tabloa();
        Tablo[Zadnji_tablo].svet=Tablo[index].svet;
        Tablo[Zadnji_tablo].broj_naslednika=Tablo[index].broj_naslednika;
        Tablo[Zadnji_tablo].vrednost=Tablo[index].vrednost;
        Tablo[Zadnji_tablo].levo=Tablo[index].levo;
        Tablo[index].levo=Zadnji_tablo;
        pravi_tablo(Zadnji_tablo);
        pravi_tablo(index);
      }
      break;
    case M:
    case L:
      if(R_formula[Velicina_r_formule-1]==L==Tablo[index].vrednost)
        Tablo[index].broj_naslednika++;
      else
      {
        Tablo[index].svet=Broj_obradenih_svetova;
        Broj_obradenih_svetova++;
        Tablo[index].broj_naslednika=0;
      }
      pravi_tablo(index);
      break;
    case NOT:
      Tablo[index].vrednost=!Tablo[index].vrednost;
      pravi_tablo(index);
      break;
    default:
      Tablo[index].ime=R_formula[Velicina_r_formule-1];
      if(Tablo[index].broj_naslednika)
        ulancaj_tabloe(index);
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
        if(Tablo[Grana[i]].ime==Tablo[Grana[j]].ime&&Tablo[Grana[i]].svet==Tablo[Grana[j]].svet)
          nije_kontradikcija=Tablo[Grana[i]].vrednost==Tablo[Grana[j]].vrednost;
    if(nije_kontradikcija)
      longjmp(Dugi_skok,1);
  }
  else
    if(Tablo[index].ime==OR)
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

void uradi(char *ime_datoteke,int racun)
{
  int i;
  int j;
  int k;
  int ima_promene;
  Datoteka=fopen(ime_datoteke,"r");
  if(Datoteka!=NULL)
  {
    switch(setjmp(Dugi_skok))
    {
      case 0:
        printf("U racunu ");
        switch(racun)
        {
          case RACUN_T:
            printf("T");
            break;
          case RACUN_B:
            printf("B");
            break;
          case RACUN_S4:
            printf("S4");
            break;
          case RACUN_S5:
            printf("S5");
        }
        printf(" formula :\n");
        ucitaj_sledece_slovo_ulaza();
        Broj_imena=0;
        ucitaj_sledecu_leksemu_ulaza();
        Velicina_n_formule=0;
        parsiraj_formulu_a();
        Velicina_r_formule=0;
        n_formulu_u_r_formulu();
        Velicina_r_formule=0;
        Broj_svetova=1;
        Broj_dece=0;
        prebroj_svetove(0,0,FALSE);
        for(i=0;i<Broj_svetova;i++)
          for(j=0;j<Broj_svetova;j++)
            Vidik[i][j]=i==j;
        do
        {
          ima_promene=FALSE;
          for(i=0;i<Broj_dece;i++)
          {
            Broj_naslednika=0;
            odredi_naslednike(Deca[i].roditelj,Deca[i].broj_naslednika);
            for(j=0;j<Broj_naslednika;j++)
              if(!Vidik[Naslednici[j]][Deca[i].dete])
              {
                Vidik[Naslednici[j]][Deca[i].dete]=TRUE;
                ima_promene=TRUE;
              }
          }
        }
        while(ima_promene);
        if(racun==RACUN_B||racun==RACUN_S5)
          for(i=0;i<Broj_svetova-1;i++)
            for(j=i+1;j<Broj_svetova;j++)
            {
              Vidik[i][j]=Vidik[i][j]||Vidik[j][i];
              Vidik[j][i]=Vidik[i][j];
            }
        if(racun==RACUN_S4||racun==RACUN_S5)
          for(i=0;i<Broj_svetova;i++)
            for(j=0;j<Broj_svetova;j++)
              for(k=0;k<Broj_svetova;k++)
                if(Vidik[j][i]&&Vidik[i][k])
                  Vidik[j][k]=TRUE;
        Velicina_r_formule=0;
        Tablo[0].svet=0;
        Tablo[0].broj_naslednika=0;
        Tablo[0].vrednost=FALSE;
        Tablo[0].levo=NIL;
        Zadnji_tablo=0;
        Broj_obradenih_svetova=1;
        pravi_tablo(0);
        Velicina_grane=0;
        izdvoji_grane(0);
        printf("jeste teorema.\n");
        break;
      case 1:
        printf("nije teorema jer dobijamo false u interpretaciji za bar ovu valuaciju :\n");
        for(i=0;i<Velicina_grane;i++)
        {
          j=0;
          while(j<i&&(Tablo[Grana[j]].ime!=Tablo[Grana[i]].ime||Tablo[Grana[j]].svet!=Tablo[Grana[i]].svet||Tablo[Grana[j]].vrednost!=Tablo[Grana[i]].vrednost))
            j++;
          if(j==i)
            printf("\t%s u svetu %d ima vrednost %s.\n",Imena[Tablo[Grana[i]].ime],Tablo[Grana[i]].svet,Tablo[Grana[i]].vrednost?"true":"false");
        }
        if(racun!=RACUN_S5)
        {
          for(i=0;i<Broj_svetova;i++)
            for(j=0;j<Broj_svetova;j++)
              if(i!=j&&Vidik[i][j])
                printf("\tIz sveta %d vidimo svet %d.\n",i,j);
        }
        else
          printf("\tIz svakog sveta vidimo sve svetove.\n");
    }
    fclose(Datoteka);
  }
  else
    printf("Ne mogu otvoriti tu datoteku.\n");
}

void pomoc(void)
{
  printf(
    "Ako pozivamo program iz komandne linije sintaksa je : akcija ime_datoteke."
    "\n"
    "\nSpisak operatora po prioritetima (od najaceg do najslabijeg) :"
    "\n\t1. NOT\tnegacija\tunarni prefiksni,"
    "\n\t1. L\tnuzno\t\tunarni prefiksni,"
    "\n\t1. M\tmoguce\t\tunarni prefiksni,"
    "\n\t2. AND\tkonjunkcija\tbinarni desno asocijativan,"
    "\n\t3. OR\tdisjunkcija\tbinarni desno asocijativan,"
    "\n\t4. THEN\timplikacija\tbinarni desno asocijativan,"
    "\n\t5. EQ\tekvivalencija\tbinarni desno asocijativan."
    "\nZagradama (...) je moguce promeniti prioritet i asocijativnost veznika."
    "\nImena su reci od najvise %d slova ili cifara koje pocinju slovom i"
    "\nrazlikuju se mala i velika slova."
    "\n"
    "\nMoguca akcija je (k.l. oznacava da je to akcija i iz komandne linije) :"
    "\n\tQ. Izlaz iz programa,"
    "\n\tH. Pomoc i sintaksa,"
    "\n\tL. Zadavanje imena datoteke sa formulom,"
    "\nk.l.\tT. Provera formule u datoteci za racun T,"
    "\nk.l.\tB. Provera formule u datoteci za racun B,"
    "\nk.l.\t4. Provera formule u datoteci za racun S4,"
    "\nk.l.\t5. Provera formule u datoteci za racun S5,"
    "\n\tE. Editovanje datoteke sa formulom."
    "\n",
    MAX_DUZINA_IMENA
  );
}

int main(int argc,char *argv[])
{
  if(argc==3)
    switch(*argv[1])
    {
      case 't':
      case 'T':
        uradi(argv[2],RACUN_T);
        break;
      case 'b':
      case 'B':
        uradi(argv[2],RACUN_B);
        break;
      case '4':
        uradi(argv[2],RACUN_S4);
        break;
      case '5':
        uradi(argv[2],RACUN_S5);
        break;
      default:
        pomoc();
    }
  else
  {
    static char ime_editora[DUZINA_ULAZA];
    static char ime_datoteke[DUZINA_ULAZA]="";
    static char komanda[DUZINA_ULAZA];
    char izbor;
    pomoc();
    printf("\nKako se poziva editor : ");
    gets(ime_editora);
    strcat(ime_editora," ");
    printf("\n");
    do
    {
      if(ime_datoteke[0])
      {
        printf("\nIme datoteke je \"%s\", vasa akcija (H za pomoc) : ",ime_datoteke);
        gets(komanda);
        izbor=komanda[0];
        printf("\n");
      }
      else
        izbor='l';
      switch(izbor)
      {
        case 'q':
        case 'Q':
          printf("Izlazim iz programa.\n");
          break;
        case 'h':
        case 'H':
          pomoc();
          break;
        case 'l':
        case 'L':
          printf("Kako se zove datoteka sa formulom : ");
          gets(ime_datoteke);
          break;
        case 't':
        case 'T':
          uradi(ime_datoteke,RACUN_T);
          break;
        case 'b':
        case 'B':
          uradi(ime_datoteke,RACUN_B);
          break;
        case '4':
          uradi(ime_datoteke,RACUN_S4);
          break;
        case '5':
          uradi(ime_datoteke,RACUN_S5);
          break;
        case 'e':
        case 'E':
          strcpy(komanda,ime_editora);
          strcat(komanda,ime_datoteke);
          printf("Izvrsavam : \"%s\".\n",komanda);
          system(komanda);
          break;
        default:
          printf("\aPogresan izbor (H za pomoc).\n");
      }
    }
    while(izbor!='q'&&izbor!='Q');
  }
  return 0;
}
