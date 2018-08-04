#include <stdio.h>
#include <stdlib.h>

#include "main.h"

int main(void)
{
  r2_cube_t cube;

  r2_cube_init(&cube);

  r2_cube_shuffle_full(&cube);

  r2_cube_dump(&cube, stdout);

  return EXIT_SUCCESS;
}
