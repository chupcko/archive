#ifndef __TYPE_CUBE_H__
#define __TYPE_CUBE_H__

__INCLUDE_BEGIN__
#define R2_CUBE_ON_SIDE (R2_CUBE_DIMENSION*R2_CUBE_DIMENSION)
#define R2_CUBE_ARRAY_SIZE (R2_CUBE_ON_SIDE*R2_CUBE_SIDE_NUMBER)
typedef struct r2_cube_state_t
{
  int array[R2_CUBE_ARRAY_SIZE];
} r2_cube_state_t;

#define R2_CUBE_MOVES_SIZE 12
typedef struct r2_cube_t
{
  r2_cube_state_t state;
  int moves_number;
  r2_move_t moves[R2_CUBE_MOVES_SIZE];
} r2_cube_t;
__INCLUDE_END__

#endif
