#include "main.h"

__FUNCTION_BEGIN__
void r2_cube_dump(r2_cube_t* cube, FILE* file)
__FUNCTION_END__
{
  int i;

  for(i = 0; i < R2_CUBE_ARRAY_SIZE; i++)
    fprintf(file, "%d", cube->state.array[i]);
  fprintf(file, "\n");
  if(cube->moves_number > 0)
  {
    for(i = 0; i < cube->moves_number; i++)
    {
      if(i != 0)
        fprintf(file, " ");
      fprintf(file, "%s", r2_move_string(cube->moves[i]));
    }
    fprintf(file, "\n");
  }
}
