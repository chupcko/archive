#include "main.h"

__FUNCTION_BEGIN__
r2_bool_t r2_cube_play(r2_cube_t* cube, r2_move_t move)
__FUNCTION_END__
{
  if(move == R2_MOVE_NULL)
    return R2_TRUE;

  if(cube->moves_number >= R2_CUBE_MOVES_SIZE)
    return R2_FALSE;
  cube->moves[cube->moves_number] = move;
  cube->moves_number++;
  switch(move)
  {
    case R2_MOVE_XM:
      r2_cube_play_x(cube);
    case R2_MOVE_XT:
      r2_cube_play_x(cube);
    case R2_MOVE_XP:
      r2_cube_play_x(cube);
      break;
    case R2_MOVE_YM:
      r2_cube_play_y(cube);
    case R2_MOVE_YT:
      r2_cube_play_y(cube);
    case R2_MOVE_YP:
      r2_cube_play_y(cube);
      break;
    case R2_MOVE_ZM:
      r2_cube_play_z(cube);
    case R2_MOVE_ZT:
      r2_cube_play_z(cube);
    case R2_MOVE_ZP:
      r2_cube_play_z(cube);
      break;
    default:
      return R2_FALSE;
  }
  return R2_TRUE;
}
