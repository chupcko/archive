
/*********************************************************
//
//	SKMEMORY.H
//
//	SK-Machine
//	Kombinatorska SK masina
//
//	Memory functions definition
//
//	Copyright (c) 1995 by Sasa Malkov
//	All Rights Reserved.
//
//*********************************************************/

#ifndef __SKMEMORY_H
#define __SKMEMORY_H

#ifndef __SKNODE_H
	#include "sknode.h"
#endif

int sk_heap_alloc( void );			/* alokacija heap-a */
void sk_heap_free( void );			/* oslobadjanje heap-a */
Cell* sk_heap_alloccell( void );	/* alokacija celije sa heap-a */
void sk_heap_addcellref(Cell*);		/*	povecava broj referisanja celije */
void sk_heap_freecell( Cell* );		/* oslobadjanje celije */
long sk_heap_getsize( void );
long sk_heap_getfree( void );

/* #ifndef __SKMEMORY_H */
#endif
