#include "main.h"

__FUNCTION_BEGIN__
r2_move_t r2_move_random(void)
__FUNCTION_END__
{
  static r2_bool_t seed_initiated = R2_FALSE;
  static unsigned int seed = 0;

  if(seed_initiated != R2_TRUE)
  {
    seed_initiated = R2_TRUE;
    seed = (unsigned int)time((time_t*)NULL);
  }
  return (r2_move_t)(R2_MOVE_XP+rand_r(&seed)%(R2_MOVE_NULL-R2_MOVE_XP));
}
