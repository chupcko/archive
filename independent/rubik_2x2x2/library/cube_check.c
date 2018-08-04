#include "main.h"

static r2_bool_t r2_cube_check_content(r2_cube_t* cube)
{
  int i;

  for(i = 0; i < R2_CUBE_ARRAY_SIZE; i++)
    if
    (
      cube->state.array[i] < 0 ||
      cube->state.array[i] >= R2_CUBE_SIDE_NUMBER
    )
      return R2_FALSE;
  return R2_TRUE;
}

static r2_bool_t r2_cube_check_count(r2_cube_t* cube)
{
  int count[R2_CUBE_SIDE_NUMBER];
  int i;

  for(i = 0; i < R2_CUBE_SIDE_NUMBER; i++)
    count[i] = 0;

  for(i = 0; i < R2_CUBE_ARRAY_SIZE; i++)
    count[cube->state.array[i]]++;

  for(i = 0; i < R2_CUBE_SIDE_NUMBER; i++)
    if(count[i] != R2_CUBE_ON_SIDE)
      return R2_FALSE;
  return R2_TRUE;
}

__FUNCTION_BEGIN__
r2_bool_t r2_cube_check(r2_cube_t* cube)
__FUNCTION_END__
{
  CALL(r2_cube_check_content(cube));
  CALL(r2_cube_check_count(cube));
  return R2_TRUE;
}
