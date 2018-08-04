#include <stdio.h>
#include "out.h"

char *Imena[AGLA_MAX_CLASS]=
{
  "Pragma",
  "Identifikator",
  "Celi broj",
  "Realni broj",
  "Znak",
  "String",
  "Separator",
  "Kraj datoteke"
};

int main(int argc,char *argv[])
{
  if(argc==2)
    if((AGLA_file=fopen(argv[1],"r"))!=NULL)
    {
      do
      {
        if(AGLA_scanner())
        {
          printf("Red %d slovo %d - %s\n",AGLA_old_nl,AGLA_old_pos,AGLA_error);
          break;
        }
        printf("%-13s = %s\n",Imena[AGLA_class],AGLA_value);
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
