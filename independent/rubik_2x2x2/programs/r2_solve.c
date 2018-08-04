#include <stdio.h>
#include <stdlib.h>

#include "main.h"

int main(void)
{
  r2_cube_t cube;

  r2_cube_init(&cube);

  if(r2_cube_input(&cube, stdin) != R2_TRUE)
    error("Input ERROR");

  r2_cube_dump(&cube, stdout);

  if(r2_cube_find_solution(&cube) != R2_TRUE)
    error("Find ERROR");

  return EXIT_SUCCESS;
}
