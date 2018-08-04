#include "main.h"

__FUNCTION_BEGIN__
void r2_cube_play_x(r2_cube_t* cube)
__FUNCTION_END__
{
  r2_cube_swap(cube, 0, 19, 21, 6);
  r2_cube_swap(cube, 1, 11, 20, 14);
  r2_cube_swap(cube, 4, 12, 13, 5);
}
