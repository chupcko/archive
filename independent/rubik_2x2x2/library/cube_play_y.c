#include "main.h"

__FUNCTION_BEGIN__
void r2_cube_play_y(r2_cube_t* cube)
__FUNCTION_END__
{
  r2_cube_swap(cube, 0, 9, 23, 12);
  r2_cube_swap(cube, 3, 17, 20, 4);
  r2_cube_swap(cube, 11, 10, 18, 19);
}
