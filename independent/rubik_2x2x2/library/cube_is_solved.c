#include "main.h"

__FUNCTION_BEGIN__
r2_bool_t r2_cube_is_solved(r2_cube_t* cube)
__FUNCTION_END__
{
  int sides[R2_CUBE_SIDE_NUMBER];
  int i;
  int side_index;

  for(i = 0; i < R2_CUBE_SIDE_NUMBER; i++)
    sides[i] = -1;

  for(i = 0; i < R2_CUBE_ARRAY_SIZE; i++)
  {
    side_index = r2_cube_side(i);
    if(sides[side_index] == -1)
      sides[side_index] = cube->state.array[i];
    else
      if(sides[side_index] != cube->state.array[i])
        return R2_FALSE;
  }
  return R2_TRUE;
}
