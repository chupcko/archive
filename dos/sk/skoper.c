
/*********************************************************
//
//  SKOPER.C
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

#include <alloc.h>
#include <string.h>

#include "sknode.h"
#include "skstack.h"
#include "skmemory.h"
#include "skoper.h"
#include "skls.h"


#define SK_MAX_USEROP 512

struct userop_struct
{
	char name[LS_LEN_VALUE+1];
	Cell *opcell;
} useroperators[SK_MAX_USEROP];

/* broj dodefinisanih operatora */
int numuseroperators=0;

/*
//  funkcije koje obezbedjuju interfejs prema operatorima
*/

Cell* sk_op_getuserop( Cell* n )
{
	return n<numuseroperators ? useroperators[(long)n].opcell : NULL;
}

char* sk_op_getuseropname( Cell* n )
{
	return useroperators[(long)n].name;
}

char* sk_op_getsysopname( Cell* n )
{
	return sysoperators[(long)n].name;
}

int sk_op_getarity( Cell* n )
{
	return sysoperators[(long)n].arity;
}

int sk_op_getstrict( Cell* n )
{
	return sysoperators[(long)n].strict;
}

void  sk_op_evalsysop( Cell* n, Cell* redexroot )
{
	sysoperators[(long)n].fun( redexroot );
}

int sk_op_finduserop(char *s)
{
	int i=0;
	while(i<numuseroperators && strcmp(useroperators[i].name,s))
		i++;
	return i==numuseroperators ? -1 : i;
}

int sk_op_findsysop(char *s)
{
	int i=0;
	while(sysoperators[i].fun!=NULL && strcmp(sysoperators[i].name,s))
		i++;
	return sysoperators[i].fun==NULL ? -1 :i;
}

int sk_op_putuserop(char *s)
{
	if(numuseroperators==SK_MAX_USEROP)
		return -1;
	strcpy(useroperators[numuseroperators].name,s);
	useroperators[numuseroperators].opcell=NULL;
	numuseroperators++;
	return numuseroperators-1;
}

void sk_op_putuseropcell(int i,Cell *p)
{
	useroperators[i].opcell=p;
}

Cell *sk_op_getuseropcell(int i)
{
	return useroperators[i].opcell;
}

int sk_op_veruserop(void)
{
	int i;
	i=0;
	while(i<numuseroperators&&useroperators[i].opcell!=NULL)
		i++;
	return i<numuseroperators;
}
