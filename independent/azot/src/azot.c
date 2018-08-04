#include <stdio.h>
#include "semana.h"

int main(int argc,char *argv[])
{
  FILE *f;
  f=fopen(argv[1],"r");
  SA_file_parser(f);
/* SA_string_parser(argv[1]); */
  return 0;
}
