#include "main.h"

__FUNCTION_BEGIN__
int r2_cube_side(int index)
__FUNCTION_END__
{
  if(index < R2_CUBE_ON_SIDE)
    return 0;
  if(index < R2_CUBE_ARRAY_SIZE/2)
    return (index-R2_CUBE_ON_SIDE)/2+1;
  if(index < R2_CUBE_ARRAY_SIZE-R2_CUBE_ON_SIDE)
    return (index-R2_CUBE_ARRAY_SIZE/2)/2+1;
  return R2_CUBE_SIDE_NUMBER-1;
}
