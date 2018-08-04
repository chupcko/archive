#include <stdio.h>
#include <stdlib.h>

#include "mylib.h"

int main(void)
{
  printf("pre %d\n", mylib_v);
  mylib_v++;
  printf("post %d\n", mylib_v);
  printf("func %d\n", mylib_a());
  sleep(1000);
  return 0;
}
