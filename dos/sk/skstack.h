
/*********************************************************
//
//	SKSTACK.H
//
//	SK-Machine
//	Kombinatorska SK masina
//
//	Redex-Stack functions definition
//
//	Copyright (c) 1995 by Sasa Malkov
//	All Rights Reserved.
//
//*********************************************************/

#ifndef __SKSTACK_H
#define __SKSTACK_H

#ifndef __SKNODE_H
	#include "sknode.h"
#endif

void sk_stack_init( void );
void sk_stack_push( Cell* );
Cell* sk_stack_pop( void );
Cell* sk_stack_popstrict( void );
int sk_stack_test( int );
void sk_stack_pushstate( Cell*, int  );
int sk_stack_popstate( Cell**, int* );
Cell* sk_stack_getarg( int );
int sk_stack_islost( void );

/* #ifndef __SKSTACK_H */
#endif
