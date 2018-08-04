#include <stdio.h>
#include <stdlib.h>
#include "setof.h"
#include "regexp.h"

void error(void)
{
  printf("Pozicija: %d, greska: %s\n",RE_pos,RE_error);
  exit(1);
}

int main(int argc,char *argv[])
{
  RE_KA ka;
  RE_run_results rr;
  int i;
  if(RE_parser(argv[1],&ka))
    error();
  if(RE_run_init(&ka,&rr))
    error();
  if(RE_run(&ka,argv[2],&rr,1))
    error();
  printf("Broj akcija: %d\nMax broj akcija: %d\nBroj manje_vece: %d\nAkcije:",rr.broj_akcija,rr.max_broj_akcija,rr.broj_manje_vece);
  for(i=0;i<rr.broj_akcija;i++)
    printf(" %d",rr.akcije[i]);
  printf("\nNasao: %d Pocetak: %d Kraj: %d\n",rr.nasao,rr.pocetak,rr.kraj);
  for(i=0;i<rr.broj_manje_vece;i++)
    printf("%d: Nasao: %d Pocetak: %d Kraj: %d\n",i,rr.manje_vece[i].nasao,rr.manje_vece[i].pocetak,rr.manje_vece[i].kraj);
  return 0;
}
