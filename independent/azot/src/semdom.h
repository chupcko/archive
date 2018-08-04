#ifndef AZOT_semdom
#define AZOT_semdom

#include <stdio.h>
#include "lexana.h"

#define MAX_DUZINA_IMENA 32
#define MAX_DUZINA_STRINGA AZOT_DUZINA_STRINGA
#define MAX_BROJ_INDEKSA 4096
#define MAX_BROJ_VARIJABLI 2048
#define MAX_BROJ_FUNC_PROC 64
#define MAX_BROJ_ARGUMENATA 16
#define MAX_DUBINA_STEKA 4096
#define MAX_BROJ_POZIVA 4096
#define MAX_BROJ_DATOTEKA 32

typedef char Ime[MAX_DUZINA_IMENA+1];

struct
{
  enum
  {
    Tip_FP_function,
    Tip_FP_procedure
  } tip;
  Ime ime;
  int broj_argumenata;
  Ime argumenti[MAX_BROJ_ARGUMENATA];
  LA_pozicija pozicija;
} Func_proc[MAX_BROJ_FUNC_PROC];
int Broj_func_proc;
int Koju_func_proc_definisemo;

typedef struct
{
  Ime ime;
  void (*f)(void);
} I_func_proc;

I_func_proc I_func[];
I_func_proc I_proc[];

FILE *Datoteke[MAX_BROJ_DATOTEKA];
int Broj_datoteka;

typedef char String[MAX_DUZINA_STRINGA+1];

typedef enum
{
  Tip_bool,
  Tip_integer,
  Tip_real,
  Tip_string,
  Tip_array,
  Tip_file,
  Tip_func_proc,
  Tip_function,
  Tip_procedure,
  Tip_celija,
  Tip_unknown
} Tip;

typedef struct _Celija
{
  Tip tip;
  union
  {
    int v_bool;
    long v_integer;
    double v_real;
    String *v_string;
    struct _Array *v_array;
    int v_file;
    int v_func_proc;
    struct _Celija *v_celija;
  } vrednost;
} Celija;

typedef struct
{
  Celija indeks;
  Celija celija;
} Indeks;

typedef struct _Array
{
  Indeks *indeksi;
  int max_broj_indeksa;
  int broj_indeksa;
} Array;

struct
{
  Ime ime;
  Celija celija;
} Varijable[MAX_BROJ_VARIJABLI];
int Broj_varijabli;

struct
{
  enum
  {
    Tip_POZIV_I,
    Tip_POZIV_U
  } tip;
  int func_proc;
  int stek;
  Celija rezultat;
} Pozivi_func_proc[MAX_BROJ_POZIVA];
int Broj_poziva_func_proc;
int Pravi_poziv_func_proc;

Celija Stek[MAX_DUBINA_STEKA];
int Dubina_steka;

enum
{
  R_normal,
  R_stop,
  R_break,
  R_continue,
  R_return
} Radi;

String *Novi_string(void);
void Konkatenacija(String,String);
void Kopiraj_string_od_do(String,String,int,int);
Array *Novi_niz(void);
void Oslobodi_celiju(Celija *);
int Celija_nije_prostog_tipa(Celija *);
int Uporedi_celije(Celija *,Celija *);
void Konvertuj_celiju_u_bool(Celija *);
void Konvertuj_celiju_u_integer(Celija *);
void Konvertuj_celiju_u_real(Celija *);
void Konvertuj_celiju_u_string(Celija *);
void Konvertuj_celiju_u_niz(Celija *);
void Konvertuj_celiju_u_file(Celija *);
void Konvertuj_celiju_u_indeks(Celija *);
void Kopiraj_celiju(Celija *,Celija *,int);
int Jeste_indeks(Array *,int,Celija *);
int Pronadji_indeks(Array *,Celija *);
Celija *Ubaci_indeks(Array *,Celija *);
void Obrisi_niz(Array *);
void Obrisi_indeks(Array *,Celija *);
int Uporedi_indekse_indeks(Indeks *,Indeks *);
int Uporedi_indekse_celija(Indeks *,Indeks *);
void Proveri_broj_argumenata(int);
void Proveri_najmanji_broj_argumenata(int);
void Proveri_od_do_broj_argumenata(int,int);
void SD_init(void);

#endif
