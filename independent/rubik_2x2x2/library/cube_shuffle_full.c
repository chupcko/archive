#include "main.h"

__FUNCTION_BEGIN__
void r2_cube_shuffle_full(r2_cube_t* cube)
__FUNCTION_END__
{
  static r2_bool_t seed_initiated = R2_FALSE;
  static unsigned int seed = 0;

  if(seed_initiated != R2_TRUE)
  {
    seed_initiated = R2_TRUE;
    seed = (unsigned int)time((time_t*)NULL);
  }
  r2_cube_shuffle(cube, R2_CUBE_MOVES_SIZE*3/4+rand_r(&seed)%(R2_CUBE_MOVES_SIZE/4+1));
}
