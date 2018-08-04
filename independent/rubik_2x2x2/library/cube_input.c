#include "main.h"

__FUNCTION_BEGIN__
r2_bool_t r2_cube_input(r2_cube_t* cube, FILE* file)
__FUNCTION_END__
{
  int i;

  r2_cube_init(cube);
  for(i = 0; i < R2_CUBE_ARRAY_SIZE; i++)
    if(fscanf(file, "%1d", &cube->state.array[i]) != 1)
      return R2_FALSE;
  CALL(r2_cube_check(cube));
  return R2_TRUE;
}
