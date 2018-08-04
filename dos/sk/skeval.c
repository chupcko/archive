
/*********************************************************
//
//	SKEVAL.C
//
//	SK-Machine
//	Kombinatorska SK masina
//
//	Redex evaluation functions implementation
//
//	Copyright (c) 1995 by Sasa Malkov
//	All Rights Reserved.
//
//*********************************************************/

#include <stdlib.h>

#include "sknode.h"
#include "skmemory.h"
#include "skstack.h"
#include "skoper.h"
#include "skls.h"

void sk_print(Cell* c)
{
  if(c){
    switch( c->lefttype ){
      case SKTYPE_POINTER:
        sk_print(c->left);
        break;
      case SKTYPE_SYSTEMOP:
		printf( "%s ", sk_op_getsysopname( c->left ));
		break;
	  case SKTYPE_USEROP:
		printf( "%s ", sk_op_getuseropname( c->left ));
		break;
	  case SKTYPE_NUMBER:
		printf( "%ld ", c->left );
		break;
	  }
	switch( c->righttype ){
	  case SKTYPE_POINTER:
		printf("( ");
		sk_print(c->right);
		printf(") ");
		break;
	  case SKTYPE_SYSTEMOP:
		printf( "%s ", sk_op_getsysopname( c->right ));
		break;
	  case SKTYPE_USEROP:
		printf( "%s ", sk_op_getuseropname( c->right ));
		break;
	  case SKTYPE_NUMBER:
		printf( "%ld ", c->right );
		break;
      }
    }
}

void sk_printexp( Cell* c )
{
  sk_print( c );
  printf( "\n\r" );
}

/*
**	idemo rekurzivno kroz stablo i sve reference na user operatore zamenjujemo pokazivacima
*/

void sk_eval_point(Cell* c)
{
  if(c){
	switch( c->lefttype ){
	  case SKTYPE_POINTER:
		sk_eval_point(c->left);
		break;
	  case SKTYPE_USEROP:
		c->lefttype = SKTYPE_POINTER;
		c->left = sk_op_getuserop( c->left );
		sk_heap_addcellref( c->left );
	  }
	switch( c->righttype ){
	  case SKTYPE_POINTER:
		sk_eval_point(c->right);
		break;
	  case SKTYPE_USEROP:
		c->righttype = SKTYPE_POINTER;
		c->right = sk_op_getuserop( c->right );
		sk_heap_addcellref( c->right );
	  }
	}
}

Cell* sk_eval_systemop( Cell* activecell, int arity )
{
	Cell* redexroot = sk_stack_getarg( arity );
	Cell* redl = ( redexroot->lefttype == SKTYPE_POINTER ? redexroot->left : NULL );
	Cell* redr = ( redexroot->righttype == SKTYPE_POINTER ? redexroot->right : NULL );

	sk_op_evalsysop( activecell->left, redexroot );

	if( redl ) sk_heap_freecell( redl );
	if( redr ) sk_heap_freecell( redr );

	return redexroot;
}

/* 	funkcija sk_evaluate
//	izracunava izraz trazeci redeks spustanjem niz kicmu.
//	ako u toku racunanja dodje do nedostatka steka, vraca se
//	dubina do koje smo dosli,
//	a ako smo zavrsili vraca se 0
*/

int sk_evaluate( Cell* evalroot )
{
	/* do koje celije smo stigli */
	Cell* activecell = evalroot;
	/* koliko smo duboko u podizrazima, za striktna izracunavanja */
	int depth = 0;
	/* kolika je arnost operatora */
	int arity;
	/* pokazivac na argument */
	Cell* argumentcell;
	/* koliko ima striktnih argumenata */
	int strict;
	/* do kog argumenta smo stigli */
	int argno;

  start:
	switch( activecell->lefttype ){
		case SKTYPE_USEROP:
			activecell->lefttype = SKTYPE_POINTER;
			activecell->left = sk_op_getuserop( activecell->left );
			sk_heap_addcellref( activecell->left );
		case SKTYPE_POINTER:
			sk_stack_push( activecell );
			activecell = activecell->left;
			goto start;

		case SKTYPE_SYSTEMOP:
			sk_stack_push( activecell );
			/* najpre proverimo arnost */
			arity = sk_op_getarity( activecell->left );
			if( sk_stack_test( arity ))
				if( strict = sk_op_getstrict( activecell->left )) /* namerno dodeljujemo */
					goto strictop;
				else
					goto systemop;
			else
				/* ako nemamo dovoljno argumenata, proverimo ispravnost steka */
				return sk_stack_islost();

		case SKTYPE_NUMBER:
			if( activecell->righttype != SKTYPE_EMPTY )
				return 0;
		}

	/*  ako smo u podizrazu, vratimo se nazad za jedan korak,
	//	a ako nismo, onda zavrsimo	*/
	if( depth ){
		if( sk_stack_popstate( &activecell, &argno ) )
			return 1;
		arity = sk_op_getarity( activecell->left );
		strict = sk_op_getstrict( activecell->left );
		depth--;
		goto strictop2;
		}
	else
		/* gotovo je */
		return 0;

  strictop:
	/*	polazimo od prvog striktnog argumenta */
	argno = 1;

  strictop2:
	/*	izracunamo sledeci striktni argument */
	while( argno<=strict ){
		/*	kada radimo sa striktnim moramo ponovo proveriti
			broj dostupnih argumenata, jer menja se stek tokom rada */
		if( !sk_stack_test(argno) )
			return 1;
		argumentcell = sk_stack_getarg( argno++ );
		switch( argumentcell->righttype ){
			case SKTYPE_USEROP:
				argumentcell->righttype = SKTYPE_POINTER;
				argumentcell->right = sk_op_getuserop( argumentcell->right );
				sk_heap_addcellref( argumentcell->right );
			case SKTYPE_POINTER:
				/*	sacuvamo:
				//			 activecell - koju celiju izracunavamo
				//			 argno - do kog striktnog argumenta smo stigli */
				sk_stack_pushstate( activecell, argno );
				activecell = argumentcell->right;
				depth++;
				goto start;
			default:;
				/* ako je izracunat argument, ne silazimo u njega */
			}
		}
	/*	kada radimo sa striktnim moramo ponovo proveriti
		broj dostupnih argumenata, jer menja se stek tokom rada */
	if( !sk_stack_test( arity ))
		return 1;

  systemop:
	activecell = sk_eval_systemop( activecell, arity );
//	sk_printexp( LS_top );
	printf(".");
	goto start;
}

/* glavna funkcija za izracunavanje izraza */

void sk_evaluate_all( Cell* evalroot )
{
	/*	iz sk_evaluate vracamo 0 ako smo gotovi,
		a 1 ako smo se vratili zbog izgubljenog steka */
/*	int i=0;
	Cell* userop;
	while( userop = sk_op_getuserop( i++ ))
		sk_eval_point( userop );
*/
	while( sk_evaluate( evalroot )){
		printf("!");
		sk_stack_init();
		}
}
