#include "main.h"

__FUNCTION_BEGIN__
void r2_cube_play_z(r2_cube_t* cube)
__FUNCTION_END__
{
  r2_cube_swap(cube, 0, 1, 2, 3);
  r2_cube_swap(cube, 4, 6, 8, 10);
  r2_cube_swap(cube, 5, 7, 9, 11);
}
