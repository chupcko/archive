#include <stdio.h>

#include "skmemory.h"
#include "skeval.h"
#include "skoper.h"
#include "skls.h"
#include "skstack.h"

void sk_printexp( Cell* );
extern long heap_minfree;

int main( int argc, char* argv[] )
{
	char* filename;
	if( argc > 1 )
		filename = argv[1];
	else
		filename = "default.sk";

/*  sk_heap_alloc();
  sk_stack_init();
  printf("Slobodnih celija %ld\n\r",sk_heap_getfree());
  if(LS_parser(fopen("a","r")))
	printf( "%s, %d, %d \n\r", LS_error, LS_old_nl, LS_old_pos );
  else{
	puts("aha");
	sk_printexp( LS_top );
	printf("Slobodnih celija %ld\n\r",sk_heap_getfree());
	getchar();
	sk_evaluate_all( LS_top );
	sk_printexp( LS_top );
	}
  printf("Slobodnih celija %ld\n\r",sk_heap_getfree());
  sk_heap_free();
  printf("Slobodnih celija %ld\n\r",sk_heap_getfree());
  printf("Minimum slobodnih celija %ld\n\r",heap_minfree);
  return 0;
*/


  sk_heap_alloc();
  sk_stack_init();
  printf("Alocirano je %ld celija.\n\r",sk_heap_getfree());
  if(LS_parser(fopen(filename,"r")))
	printf( "Sintaksna greska: %s, %d, %d \n\r", LS_error, LS_old_nl, LS_old_pos );
  else{
	printf( "Posle prevodjenja ostalo je %ld slobodnih celija.\n\r",sk_heap_getfree());
	printf( "Zadati izraz:\n\r    " );
	sk_printexp( LS_top );
	sk_evaluate_all( LS_top );
	printf( "\n\rRezultat:\n\r    " );
	sk_printexp( LS_top );
	}
  printf("Nakon izracunavanja ostalo je %ld slobodnih celija.\n\r",sk_heap_getfree());
  printf("Tokom izracunavanja bilo je najmanje %ld slobodnih celija.\n\r",heap_minfree);
  sk_heap_free();
  return 0;
}
