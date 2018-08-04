#include <stdio.h>
#include "out.h"

int main(int argc,char *argv[])
{
  FILE *izlaz;
  if(argc==3)
    if((AGLA_file=fopen(argv[1],"r"))!=NULL&&(izlaz=fopen(argv[2],"w"))!=NULL)
    {
      do
      {
        AGLA_scanner();
        if(AGLA_class==REST)
          fputc((int)*AGLA_value,izlaz);
      }
      while(AGLA_class!=AGLA_EOF);
      fclose(AGLA_file);
      fclose(izlaz);
    }
    else
      puts("Neispravni ulazni fajlovi");
  else
    puts("Prosledi 2 parametara sa imenima ulaznog i izlaznog fajla");
  return 0;
}
