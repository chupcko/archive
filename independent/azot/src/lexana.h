#ifndef AZOT_lexana
#define AZOT_lexana

#include <stdio.h>
#include "azot.h"

enum
{
  LA_izvor_file,
  LA_izvor_string
} LA_izvor;

typedef enum
{
  LA_NISTA=-1,
  LA_ime,
  LA_integer,
  LA_real,
  LA_string,
  LA_dodela,
  LA_l_zag,
  LA_d_zag,
  LA_l_u_zag,
  LA_d_u_zag,
  LA_zarez,
  LA_separator,
  LA_eq,
  LA_neq,
  LA_lt,
  LA_le,
  LA_gt,
  LA_ge,
  LA_puta,
  LA_podeljeno,
  LA_plus,
  LA_minus,
  LA_tacka,
  LA_k_and,
  LA_k_begin,
  LA_k_break,
  LA_k_continue,
  LA_k_do,
  LA_k_else,
  LA_k_end,
  LA_k_false,
  LA_k_for,
  LA_k_function,
  LA_k_if,
  LA_k_in,
  LA_k_is,
  LA_k_loop,
  LA_k_mod,
  LA_k_not,
  LA_k_or,
  LA_k_procedure,
  LA_k_return,
  LA_k_sfin,
  LA_k_sfout,
  LA_k_then,
  LA_k_true,
  LA_k_until,
  LA_k_while,
  LA_EOF
} LA_tip_lekseme;

LA_tip_lekseme LA_leksema;

#define LA_MAX_DUZINA_VREDNOSTI_LEKSEME AZOT_DUZINA_STRINGA

char LA_vrednost_lekseme[LA_MAX_DUZINA_VREDNOSTI_LEKSEME];

typedef struct
{
  int nl;
  int cur;
  int slovo;
  long pos;
} LA_pozicija;

void LA_error(char *s);
void LA_scanner(void);
void LA_uzmi_poziciju(LA_pozicija *);
void LA_idi_na_poziciju(LA_pozicija *);
void LA_file_init(FILE *);
void LA_string_init(char *);

#endif
