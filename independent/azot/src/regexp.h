#ifndef AZOT_regexp
#define AZOT_regexp

#include <limits.h>
#include <stdio.h>
#include "setof.h"

#define RE_MAX_DUZINA_VREDNOSTI_LEKSEME 32
#define RE_MAX_DUZINA_AKCIJE RE_MAX_DUZINA_VREDNOSTI_LEKSEME
#define RE_MAX_BROJ_STANJA 512

typedef char RE_tip_ime_akcije[RE_MAX_DUZINA_AKCIJE+1];

SO_tip_def(RE_skup_slova,UCHAR_MAX+1);
SO_tip_def(RE_skup_stanja,RE_MAX_BROJ_STANJA);

typedef struct
{
  int broj_skupova_slova;
  SO_tip_RE_skup_slova *skupovi_slova;
  int broj_stanja;
  int broj_akcija;
  struct RE_struct_KA_akcija
  {
    RE_tip_ime_akcije ime;
    SO_tip_RE_skup_stanja stanja;
  } *akcije;
  int broj_manje_vece;
  struct RE_struct_KA_manje_vece
  {
    SO_tip_RE_skup_stanja manje;
    SO_tip_RE_skup_stanja vece;
  } *manje_vece;
  SO_tip_RE_skup_stanja akcija_zavrsna;
  int *prelazi;
} RE_KA;

typedef struct
{
  int nasao;
  int pocetak;
  int kraj;
} RE_tip_manje_vece;

typedef struct
{
  int nasao;
  int pocetak;
  int kraj;
  int broj_akcija;
  int max_broj_akcija;
  int *akcije;
  int broj_manje_vece;
  RE_tip_manje_vece *manje_vece;
} RE_run_results;

typedef struct
{
  int nasao;
  int duzina;
  int max_duzina;
  char *vrednost;
  int broj_akcija;
  int max_broj_akcija;
  int *akcije;
  int broj_manje_vece;
  RE_tip_manje_vece *manje_vece;
} RE_frun_results;

int RE_pos;
int RE_r_pos;
char *RE_error;

int RE_parser(char *,RE_KA *);
void RE_free_KA(RE_KA *);

void RE_cache_init(void);
RE_KA *RE_cache_find(char *s);

int RE_run_init(RE_KA *,RE_run_results *);
int RE_run(RE_KA *,char *,RE_run_results *,int);
void RE_free_run_results(RE_run_results *);

int RE_frun_init(RE_KA *,int,RE_frun_results *);
int RE_frun(RE_KA *,FILE *,RE_frun_results *,int);
void RE_free_frun_results(RE_frun_results *);

#endif
