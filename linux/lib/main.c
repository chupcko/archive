#include <stdio.h>

#include "ll.h"

int main(void)
{
  ll_init();
  printf("## %d\n",ll_next(3));
  return 0;
}
