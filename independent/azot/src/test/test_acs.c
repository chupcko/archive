#include <stdio.h>
#include "aprcom.h"
#include "setof.h"

int main(int argc,char *argv[])
{
  AC_uzorak u;
  if(AC_parser(argv[1],&u))
  {
    printf("Pozicija: %d, greska: %s\n",AC_pos,AC_error);
    exit(1);
  }
  printf("%ld\n",AC_acs(&u,argv[2],1));
  return 0;
}
