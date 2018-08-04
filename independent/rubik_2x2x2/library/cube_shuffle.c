#include "main.h"

__FUNCTION_BEGIN__
void r2_cube_shuffle(r2_cube_t* cube, int moves_number)
__FUNCTION_END__
{
  r2_move_t last_move;
  int i;
  r2_move_t new_move;

  cube->moves_number = 0;
  last_move = R2_MOVE_NULL;
  for(i = 0; i < moves_number; i++)
  {
    do
      new_move = r2_move_random();
    while(r2_move_is_same_class(last_move, new_move) == R2_TRUE);
    if(r2_cube_play(cube, new_move) != R2_TRUE)
      return;
    last_move = new_move;
  }
}
