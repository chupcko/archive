#include "main.h"

__FUNCTION_BEGIN__
void r2_cube_init(r2_cube_t* cube)
__FUNCTION_END__
{
  int i;

  for(i = 0; i < R2_CUBE_ARRAY_SIZE; i++)
    cube->state.array[i] = r2_cube_side(i);
  cube->moves_number = 0;
}
