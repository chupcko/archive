
/*********************************************************
//
//  SKOPER.H
//
//  SK-Machine
//  Kombinatorska SK masina
//
//  Operators structurs definitions
//
//  Copyright (c) 1995 by Sasa Malkov & Goran Lazic
//  All Rights Reserved.
//
//*********************************************************/

#ifndef __SKOPER_H
#define __SKOPER_H

#include "skls.h"

typedef void (*sysop_fnctype)( Cell* );
struct sysop_struct {
	char name[LS_LEN_VALUE+1];
	sysop_fnctype   fun;
	int       arity;
	int       strict;
	};

extern struct sysop_struct sysoperators[];


Cell* sk_op_getuserop( Cell* );
void sk_op_evalsysop( Cell*, Cell* );
int sk_op_getarity( Cell* );
int sk_op_getstrict( Cell* );
char* sk_op_getsysopname( Cell* );
char* sk_op_getuseropname( Cell* );

int sk_op_finduserop(char *); /* vraca -1 ako ne postoji */
int sk_op_findsysop(char *); /* vraca -1 ako ne postoji */
int sk_op_putuserop(char *); /* vraca -1 ako nema mesta */
void sk_op_putuseropcell(int,Cell *);
Cell *sk_op_getuseropcell(int i);
int sk_op_veruserop(void); /* vraca 1 ako nisu svi definisani */

/* #ifndef __SKOPER_H */
#endif
