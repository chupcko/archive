
/*********************************************************
//
//  SKLS.H
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

#ifndef __SKLS_H
#define __SKLS_H

#include <stdio.h>
#include "sknode.h"

#define LS_LEN_VALUE 16

extern char *LS_error;
extern int LS_old_nl;
extern int LS_old_pos;
extern Cell *LS_top;

int LS_parser(FILE *);

/*

  LS_parser pozivamo sa pokazivachem na datoteku iz koje citamo.

  LS_parser nam vracja 1 ako je doshlo do greske ili 0 ako je sve ok.
  Ako je vraceno 1 tada su popunjeni sledeci objekti:
    LA_error - pokazivac na string sa opisom greske,
    LA_old_nl - red u kome se desila greska,
    LS_old_pos - pozicija u redu gde se desila greska.
  Ako je vraceno 0 tada su popunjeni sledeci objekti:
    LS_top - pokazivac na drvo,
    useroperators - niz korisnickih operatora (ne koristoi se neposredno
      vec preko funkcije sk_op_getuserop).

*/

/* #ifndef __SKOPER_H */
#endif
