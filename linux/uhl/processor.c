#include <stdio.h>
#include <string.h>

#include "uhl.h"

int find_processor(char *name)
{
  int i;

  i = 0;
  while(Processor[i].name != NULL)
    if(strcmp(Processor[i].name, name) == 0)
      return i;
    else
      i++;
  return -1;
}
