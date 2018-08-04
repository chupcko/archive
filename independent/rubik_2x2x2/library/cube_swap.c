#include "main.h"

__FUNCTION_BEGIN__
void r2_cube_swap(r2_cube_t* cube, int index_1, int index_2, int index_3, int index_4)
__FUNCTION_END__
{
  int temporary;

  temporary = cube->state.array[index_4];
  cube->state.array[index_4] = cube->state.array[index_3];
  cube->state.array[index_3] = cube->state.array[index_2];
  cube->state.array[index_2] = cube->state.array[index_1];
  cube->state.array[index_1] = temporary;
}
