#include <stdio.h>
#include "out.h"

int main(int argc,char *argv[])
{
  if(argc==2)
    if((AGLA_file=fopen(argv[1],"r"))!=NULL)
    {
      do
      {
        AGLA_scanner();
        if(AGLA_class==FIND)
          printf("Red %d slovo %d: %s\n",AGLA_old_nl,AGLA_old_pos,AGLA_value);
      }
      while(AGLA_class!=AGLA_EOF);
      fclose(AGLA_file);
    }
    else
      puts("Neispravan ulazni fajl");
  else
    puts("Prosledi parametar sa imenom ulaznog fajla");
  return 0;
}
