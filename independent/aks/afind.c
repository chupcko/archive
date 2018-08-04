#include <stdio.h>
#include <string.h>
#include "afind.h"
#include "aks.h"

int main(int argc,char *argv[])
{
  if(argc==3)
    if(!AKS_parser(argv[1]))
      if((AGLA_file=fopen(argv[2],"r"))!=NULL)
      {
        static char ws[AGLA_LEN_VALUE+1];
        long int wd;
        int wn;
        int wp;
        int wb;
        wb=1;
        do
        {
          AGLA_scanner();
          if(AGLA_class==Word)
          {
            long int d;
            d=AKS_df(AGLA_value);
            if(wb||d<wd)
            {
              strcpy(ws,AGLA_value);
              wd=d;
              wn=AGLA_old_nl;
              wp=AGLA_old_pos;
              wb=0;
            }
          }
        }
        while(AGLA_class!=AGLA_EOF);
        fclose(AGLA_file);
        if(!wb)
          printf("Red: %d, pozicija: %d, tezina: %ld, rec: %s\n",wn,wp,wd,ws);
        else
          puts("Nema reci u datoteci");
      }
      else
        puts("Neispravna ulazna datoteka");
    else
      printf("Na mestu %d skupovne niske je greska: %s\n",AKS_old_pos,AKS_error);
  else
    puts("Prosledi rec i ime ulazne datoteke");
  return 0;
}
