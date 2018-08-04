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
  RE_frun_results fr;
  int i;
  FILE *d;
  if(RE_parser(argv[1],&ka))
    error();
  d=fopen(argv[2],"r");
  i=0;
  while(i<atoi(argv[3]))
  {
    putchar(fgetc(d));
    i++;
  }
  printf("%%\n");
  if(RE_frun_init(&ka,1024,&fr))
    error();
  if(RE_frun(&ka,d,&fr,1))
    error();
  while((i=fgetc(d))!=EOF)
    putchar(i);
  fclose(d);
  printf("%%\nBroj akcija: %d\nMax broj akcija: %d\nBroj manje_vece: %d\nAkcije:",fr.broj_akcija,fr.max_broj_akcija,fr.broj_manje_vece);
  for(i=0;i<fr.broj_akcija;i++)
    printf(" %d",fr.akcije[i]);
  printf("\nNasao: %d Duzina: %d Vrednost: [%s]\n",fr.nasao,fr.duzina,fr.vrednost);
  for(i=0;i<fr.broj_manje_vece;i++)
    printf("%d: Nasao: %d Pocetak: %d Kraj: %d\n",i,fr.manje_vece[i].nasao,fr.manje_vece[i].pocetak,fr.manje_vece[i].kraj);
  return 0;
}
