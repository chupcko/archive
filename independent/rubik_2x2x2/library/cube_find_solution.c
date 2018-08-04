#include "main.h"

typedef struct r2_cube_find_solution_context_t
{
  int        minimal_move_number;
  r2_cube_t* cube;
} r2_cube_find_solution_context_t;

static r2_bool_t r2_cube_find_solution_helper(r2_cube_find_solution_context_t* context, r2_move_t move)
{
  r2_cube_state_t state;
  r2_move_t new_move;

  if(r2_cube_is_solved(context->cube) == R2_TRUE)
  {
    r2_cube_dump(context->cube, stderr);
    if
    (
      context->minimal_move_number < 0 ||
      context->cube->moves_number < context->minimal_move_number
    )
    {
      context->minimal_move_number = context->cube->moves_number;
      r2_cube_dump(context->cube, stdout);
    }
    return R2_TRUE;
  }

  state = context->cube->state;
  if
  (
    move != R2_MOVE_NULL &&
    r2_cube_play(context->cube, move) == R2_FALSE
  )
    return R2_TRUE;

  for(new_move = R2_MOVE_XP; new_move < R2_MOVE_NULL; new_move++)
    if(r2_move_is_same_class(move, new_move) != R2_TRUE)
      CALL(r2_cube_find_solution_helper(context, new_move));

  if(move != R2_MOVE_NULL)
    context->cube->moves_number--;
  context->cube->state = state;
  return R2_TRUE;
}

__FUNCTION_BEGIN__
r2_bool_t r2_cube_find_solution(r2_cube_t* cube)
__FUNCTION_END__
{
  r2_cube_find_solution_context_t context;

  context.minimal_move_number = -1;
  context.cube = cube;
  context.cube->moves_number = 0;
  CALL(r2_cube_find_solution_helper(&context, R2_MOVE_NULL));
  return R2_TRUE;
}
