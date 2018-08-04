
/*********************************************************
//
//	SKSTACK.C
//
//	SK-Machine
//	Kombinatorska SK masina
//
//	Redex-Stack functions implementation
//
//	Copyright (c) 1995 by Sasa Malkov
//	All Rights Reserved.
//
//*********************************************************/

#include <alloc.h>

#include "sknode.h"
#include "skmemory.h"
#include "skstack.h"

#define SKSTACK_LEN 1024
#define SKSTACK_MASK 1023

/*struct redex_stack_struct {*/
	int		depth;
	int		localdepth;
	int		cellindex;
	Cell*	cells[SKSTACK_LEN];
	int		lost;
/*	};
typedef struct redex_stack_struct RdxStack;

RdxStack OurRdxStack;*/

void sk_stack_init()
{
	depth = localdepth = cellindex = lost = 0;
}

void sk_stack_push( Cell* c )
{
	if( c->righttype != SKTYPE_EMPTY ){
		cells[cellindex] = c;
		cellindex++;
		cellindex &= SKSTACK_MASK;
		if( ++localdepth > SKSTACK_LEN )
			localdepth--;
		if( ++depth > SKSTACK_LEN ){
			depth--;
			lost = 1;
			}
		}
}

Cell* sk_stack_pop()
{
	if( localdepth>0 && depth>0){
		localdepth--;
		depth--;
		cellindex--;
		cellindex &= SKSTACK_MASK;
		return cells[cellindex];
		}
	else
		return NULL;
}

Cell* sk_stack_popstrict()
{
	Cell* retcell = sk_stack_pop();
	Cell* oldptr;
	if( retcell )
		while( retcell->righttype == SKTYPE_POINTER
				&& ((Cell*)(retcell->right))->righttype == SKTYPE_EMPTY )
			{
			oldptr = (Cell*)retcell->right;
			retcell->righttype = ((Cell*)(retcell->right))->lefttype;
			retcell->right = ((Cell*)(retcell->right))->left;
			if( retcell->righttype == SKTYPE_POINTER )
			sk_heap_addcellref((Cell*)retcell->right );
			sk_heap_freecell( oldptr );
			}
	return retcell;
}

int sk_stack_test( int n )
{
	return ( localdepth>=n && depth>=n);
}

void sk_stack_pushstate( Cell* activecell, int argno )
{
	cells[cellindex] = activecell;
	cellindex++; cellindex &= SKSTACK_MASK;
	cells[cellindex] = (Cell*)(long)argno;
	cellindex++; cellindex &= SKSTACK_MASK;
	cells[cellindex] = (Cell*)(long)localdepth;
	cellindex++; cellindex &= SKSTACK_MASK;

	localdepth = 0;
	if( (depth+=3) > SKSTACK_LEN ){
		depth = SKSTACK_LEN;
		lost = 1;
		}
}

int sk_stack_popstate( Cell** activecell, int* argno )
{
	if( depth < localdepth+3 )
		return 1;
	else{
		depth -= localdepth;
		cellindex -= localdepth;
		cellindex--; cellindex &= SKSTACK_MASK;
		localdepth = (long)cells[cellindex];
		cellindex--; cellindex &= SKSTACK_MASK;
		*argno = (long)cells[cellindex];
		cellindex--; cellindex &= SKSTACK_MASK;
		*activecell = cells[cellindex];
		depth -= 3;
		return 0;
		}
}

Cell* sk_stack_getarg( int n )
{
	Cell* retcell = cells[ (cellindex-n) & SKSTACK_MASK ];
	Cell* oldptr;
	while( retcell->righttype == SKTYPE_POINTER
			&& ((Cell*)(retcell->right))->righttype == SKTYPE_EMPTY )
		{
		oldptr = (Cell*)retcell->right;
		retcell->righttype = ((Cell*)(retcell->right))->lefttype;
		retcell->right = ((Cell*)(retcell->right))->left;
		if( retcell->righttype == SKTYPE_POINTER )
			sk_heap_addcellref((Cell*)retcell->right );
		sk_heap_freecell( oldptr );
		}
	return retcell;
}

int sk_stack_islost()
{
	return lost && (localdepth >= depth);
}
