
/*********************************************************
//
//  SKSYSOP.C
//
//  SK-Machine
//  Kombinatorska SK masina
//
//  System combinators definitions
//
//  Copyright (c) 1995 by Sasa Malkov
//  All Rights Reserved.
//
//*********************************************************/

#include <alloc.h>
#include <string.h>

#include "sknode.h"
#include "skstack.h"
#include "skmemory.h"
#include "skoper.h"

/*  sistemski operatori,
//  ne moramo brinuti o predjasnjem sadrzaju redexroot celije,
//  to je prethodno regulisano */

void sk_sys_S( Cell* redexroot )
{
	Cell* l1 = sk_heap_alloccell();
	Cell* l2 = sk_heap_alloccell();
	Cell* arg1 = sk_stack_pop();
	Cell* arg2 = sk_stack_pop();
	Cell* arg3 = sk_stack_pop();

	l1->lefttype = arg1->righttype;
	l1->left = arg1->right;
	l1->righttype = arg3->righttype;
	l1->right = arg3->right;
	if( l1->lefttype == SKTYPE_POINTER )
		sk_heap_addcellref( l1->left );
	if( l1->righttype == SKTYPE_POINTER )
		sk_heap_addcellref( l1->right );

	l2->lefttype = arg2->righttype;
	l2->left = arg2->right;
	l2->righttype = arg3->righttype;
	l2->right = arg3->right;
	if( l2->lefttype == SKTYPE_POINTER )
		sk_heap_addcellref( l2->left );
	if( l2->righttype == SKTYPE_POINTER )
		sk_heap_addcellref( l2->right );

	redexroot->left = l1;
	redexroot->right = l2;
	redexroot->lefttype = redexroot->righttype = SKTYPE_POINTER;
}

void sk_sys_K( Cell* redexroot )
{
	Cell* arg1 = sk_stack_pop();
	sk_stack_pop();

	redexroot->lefttype = arg1->righttype;
	redexroot->left = arg1->right;
	if( arg1->righttype == SKTYPE_POINTER )
		sk_heap_addcellref( arg1->right );
	redexroot->righttype = SKTYPE_EMPTY;
}

void sk_sys_I( Cell* redexroot )
{
	Cell* arg1 = sk_stack_pop();

	redexroot->lefttype = arg1->righttype;
	redexroot->left = arg1->right;
	if( arg1->righttype == SKTYPE_POINTER )
		sk_heap_addcellref( arg1->right );
	redexroot->righttype = SKTYPE_EMPTY;
}

void sk_sys_B( Cell* redexroot )
{
	Cell* l1 = sk_heap_alloccell();
	Cell* arg1 = sk_stack_pop();
	Cell* arg2 = sk_stack_pop();
	Cell* arg3 = sk_stack_pop();

	l1->lefttype = arg2->righttype;
	l1->left = arg2->right;
	l1->righttype = arg3->righttype;
	l1->right = arg3->right;
	if( l1->lefttype == SKTYPE_POINTER )
		sk_heap_addcellref( l1->left );
	if( l1->righttype == SKTYPE_POINTER )
		sk_heap_addcellref( l1->right );

	redexroot->lefttype = arg1->righttype;
	redexroot->left = arg1->right;
	if( redexroot->lefttype == SKTYPE_POINTER )
		sk_heap_addcellref( redexroot->left );
	redexroot->righttype = SKTYPE_POINTER;
	redexroot->right = l1;
}

void sk_sys_C( Cell* redexroot )
{
	Cell* l1 = sk_heap_alloccell();
	Cell* arg1 = sk_stack_pop();
	Cell* arg2 = sk_stack_pop();
	Cell* arg3 = sk_stack_pop();

	l1->lefttype = arg1->righttype;
	l1->left = arg1->right;
	l1->righttype = arg3->righttype;
	l1->right = arg3->right;
	if( l1->lefttype == SKTYPE_POINTER )
		sk_heap_addcellref( l1->left );
	if( l1->righttype == SKTYPE_POINTER )
		sk_heap_addcellref( l1->right );

	redexroot->righttype = arg2->righttype;
	redexroot->right = arg2->right;
	if( redexroot->righttype == SKTYPE_POINTER )
		sk_heap_addcellref( redexroot->right );
	redexroot->lefttype = SKTYPE_POINTER;
	redexroot->left = l1;
}

void sk_sys_D( Cell* redexroot )
{
	Cell* arg1 = sk_stack_pop();

	redexroot->lefttype = redexroot->righttype = arg1->righttype;
	redexroot->left = redexroot->right = arg1->right;
	if( arg1->righttype == SKTYPE_POINTER ){
		sk_heap_addcellref( arg1->right );
		sk_heap_addcellref( arg1->right );
		}
}

void sk_sys_P( Cell* redexroot )
{
	Cell* arg1 = sk_stack_pop();
	Cell* arg2 = sk_stack_pop();

	redexroot->lefttype = arg2->righttype;
	redexroot->left = arg2->right;
	if( arg2->righttype == SKTYPE_POINTER )
		sk_heap_addcellref( arg2->right );
	redexroot->righttype = arg1->righttype;
	redexroot->right = arg1->right;
	if( arg1->righttype == SKTYPE_POINTER )
		sk_heap_addcellref( arg1->right );
}

void sk_sys_F( Cell* redexroot )
{
	Cell* arg1;
	sk_stack_pop();
	arg1 = sk_stack_pop();

	redexroot->lefttype = arg1->righttype;
	redexroot->left = arg1->right;
	if( arg1->righttype == SKTYPE_POINTER )
		sk_heap_addcellref( arg1->right );
	redexroot->righttype = SKTYPE_EMPTY;
}

void sk_sys_succ( Cell* redexroot )
{
  Cell* arg1 = sk_stack_popstrict();
	redexroot->lefttype = SKTYPE_NUMBER;
	redexroot->left = (long)arg1->right +1;
	if( arg1->righttype == SKTYPE_POINTER )
		sk_heap_addcellref( arg1->right );
	redexroot->righttype = SKTYPE_EMPTY;
}

void sk_sys_pred( Cell* redexroot )
{
  Cell* arg1 = sk_stack_popstrict();
	redexroot->lefttype = SKTYPE_NUMBER;
	redexroot->left = (long)(arg1->right) -1;
	if( arg1->righttype == SKTYPE_POINTER )
		sk_heap_addcellref( arg1->right );
	redexroot->righttype = SKTYPE_EMPTY;
}

void sk_sys_add( Cell* redexroot )
{
  Cell* arg1 = sk_stack_popstrict();
  Cell* arg2 = sk_stack_popstrict();
	redexroot->lefttype = SKTYPE_NUMBER;
	(long)redexroot->left = (long)(arg1->right) + (long)(arg2->right);
	if( arg1->righttype == SKTYPE_POINTER )
		sk_heap_addcellref( (Cell*)arg1->right );
	redexroot->righttype = SKTYPE_EMPTY;
}

void sk_sys_mul( Cell* redexroot )
{
  Cell* arg1 = sk_stack_popstrict();
  Cell* arg2 = sk_stack_popstrict();
	redexroot->lefttype = SKTYPE_NUMBER;
	(long)redexroot->left = (long)(arg1->right) * (long)(arg2->right);
	if( arg1->righttype == SKTYPE_POINTER )
		sk_heap_addcellref( (Cell*)arg1->right );
	redexroot->righttype = SKTYPE_EMPTY;
}

void sk_sys_if( Cell* redexroot )
{
	Cell* arg1 = sk_stack_popstrict();
	Cell* arg2 = sk_stack_pop();
	Cell* arg3 = sk_stack_pop();
	if( arg1->right ){
		if((redexroot->lefttype = arg2->righttype) == SKTYPE_POINTER )
			sk_heap_addcellref( arg2->right );
		redexroot->left = arg2->right;
		}
	else{
		if((redexroot->lefttype = arg3->righttype) == SKTYPE_POINTER )
			sk_heap_addcellref( arg3->right );
		redexroot->left = arg3->right;
		}
	redexroot->righttype = SKTYPE_EMPTY;
}

void sk_sys_less( Cell* redexroot )
{
  Cell* arg1 = sk_stack_popstrict();
  Cell* arg2 = sk_stack_popstrict();
	redexroot->lefttype = SKTYPE_NUMBER;
	(long)redexroot->left = (long)(arg1->right) < (long)(arg2->right);
	if( arg1->righttype == SKTYPE_POINTER )
		sk_heap_addcellref( (Cell*)arg1->right );
	redexroot->righttype = SKTYPE_EMPTY;
}

/*
void sk_sys_cumul0( Cell* redexroot )
/*
	cumul0 0 1 x mul = if ( = 0 x ) 1 ( mul x ( cumul0 0 1 (pred x ) mul))
	tj. cumul 0 1 x mul = fact x,
	cumul0 0 0 x add = sum x

	ako uvedemo : cumul =
/
{
	Cell* arg1 = sk_stack_popstrict();
	Cell* arg2 = sk_stack_popstrict();
	Cell* arg3 = sk_stack_popstrict();
	Cell* arg4 = sk_stack_pop();

	long i = (long)arg3->right;
	long startvalue = (long)arg
	if( i>



	if( arg1->right ){
		if((redexroot->lefttype = arg2->righttype) == SKTYPE_POINTER )
			sk_heap_addcellref( arg2->right );
		redexroot->left = arg2->right;
		}
	else{
		if((redexroot->lefttype = arg3->righttype) == SKTYPE_POINTER )
			sk_heap_addcellref( arg3->right );
		redexroot->left = arg3->right;
		}
	redexroot->righttype = SKTYPE_EMPTY;
}
*/

/*  tabela svih sistemskih operatora */
struct sysop_struct	sysoperators[] = {
	{"S", sk_sys_S, 3, 0 },
	{"K", sk_sys_K, 2, 0 },
	{"I", sk_sys_I, 1, 0 },
	{"B", sk_sys_B, 3, 0 },
	{"C", sk_sys_C, 3, 0 },
	{"D", sk_sys_D, 1, 0 },
	{"P", sk_sys_P, 2, 0 },
	{"F", sk_sys_F, 2, 0 },
	{"succ", sk_sys_succ, 1, 1 },
	{"pred", sk_sys_pred, 1, 1 },
	{"add", sk_sys_add, 2, 2 },
	{"mul", sk_sys_mul, 2, 2 },
	{"if", sk_sys_if, 3, 1 },
	{"less", sk_sys_less, 2, 2 },
	{"", NULL, 0, 0 }
	};
