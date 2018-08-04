
/*********************************************************
//
//	SKMEMORY.C
//
//	SK-Machine
//	Kombinatorska SK masina
//
//	Memory functions implementation
//
//	Copyright (c) 1995 by Sasa Malkov
//	All Rights Reserved.
//
//*********************************************************/

#include <alloc.h>

#include "sknode.h"
#include "skmemory.h"

#define SKHEAP_MAXBLOCKS 50
#define SKHEAP_BLOCKLEN 1000

/*
//	nasa globalna promenljiva koja sadrzi podatke o heap-u
*/

Cell*	heap_blocks[SKHEAP_MAXBLOCKS];
int	 	heap_nOfBlocks;
long	heap_nOfCells;
long	heap_nOfFreeCells;
Cell*	heap_freeCellList;
long	heap_minfree;

/*
//	operacije alokacije i dealokacije heap-a
*/

int sk_heap_alloc()
{
	Cell *cells, *newCells;
	int i;

	heap_nOfBlocks = 0;
	heap_nOfCells = 0;
	cells = NULL;

	while(heap_nOfBlocks < SKHEAP_MAXBLOCKS){
		newCells = calloc( SKHEAP_BLOCKLEN, sizeof( Cell ));
		if( !newCells ) break;
		heap_blocks[heap_nOfBlocks++] = newCells;
		/* uvezemo nove celije u listu slobodnih */
		for( i=0; i<SKHEAP_BLOCKLEN; i++ ){
			newCells->left = (long)cells;
			cells = newCells;
			newCells++;
			}
		heap_nOfCells += SKHEAP_BLOCKLEN;
		}

	heap_freeCellList = cells;
	heap_nOfFreeCells = heap_nOfCells;
	heap_minfree = heap_nOfFreeCells;
	return heap_nOfCells!=0;
}

void sk_heap_free()
{
	while( heap_nOfBlocks )
		free( heap_blocks[--heap_nOfBlocks] );
	heap_freeCellList = NULL;
	heap_nOfFreeCells = heap_nOfCells = 0;
}

Cell* sk_heap_alloccell()
{
	Cell* r;
	if( r=heap_freeCellList ){ /* namerno dodeljujemo */
		heap_freeCellList = (Cell*) r->left;
		heap_nOfFreeCells--;
		r->refcount = 1;
		}
	if( heap_nOfFreeCells < heap_minfree )
		heap_minfree = heap_nOfFreeCells;
	return r;
}

void sk_heap_addcellref( Cell* c )
{
	/*	ako smo dosli do 0, vratimo se za 1 */
	if( !(++c->refcount) )
		c->refcount--;
}

void sk_heap_freecell( Cell* c )
{
	if( !(--c->refcount) ){
		/* ovo bi trebalo resiti bez rekurzije */
		if( c->lefttype == SKTYPE_POINTER )
			sk_heap_freecell( (Cell*)c->left );
		if( c->righttype == SKTYPE_POINTER )
			sk_heap_freecell( (Cell*)c->right );
		c->left = (long)heap_freeCellList;
		heap_freeCellList = c;
		heap_nOfFreeCells++;
		}
	/*ako smo bili na -1, tu i ostajemo */
	else if( c->refcount == 65534u )
		c->refcount++;
}

int sk_heap_garbagecollect()
{
	/*
	// sve dok imamo manje od 65536 celija, ne mozemo imati toliko referisanja,
	// pa nema potrebe ni za uklanjanjem viskova,
	// zanemarujemo cikljicne grupe, za sada
	*/
	return 1;
}

long sk_heap_getsize()
{
	return heap_nOfCells;
}

long sk_heap_getfree()
{
	return heap_nOfFreeCells;
}
