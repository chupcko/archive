#include "main.h"

static r2_bool_t r2_move_is_class_x(r2_move_t move)
{
  switch(move)
  {
    case R2_MOVE_XP:
    case R2_MOVE_XT:
    case R2_MOVE_XM:
      return R2_TRUE;
      break;
  }
  return R2_FALSE;
}

static r2_bool_t r2_move_is_class_y(r2_move_t move)
{
  switch(move)
  {
    case R2_MOVE_YP:
    case R2_MOVE_YT:
    case R2_MOVE_YM:
      return R2_TRUE;
      break;
  }
  return R2_FALSE;
}

static r2_bool_t r2_move_is_class_z(r2_move_t move)
{
  switch(move)
  {
    case R2_MOVE_ZP:
    case R2_MOVE_ZT:
    case R2_MOVE_ZM:
      return R2_TRUE;
      break;
  }
  return R2_FALSE;
}

__FUNCTION_BEGIN__
r2_bool_t r2_move_is_same_class(r2_move_t move_1, r2_move_t move_2)
__FUNCTION_END__
{
  switch(move_1)
  {
    case R2_MOVE_XP:
    case R2_MOVE_XT:
    case R2_MOVE_XM:
      return r2_move_is_class_x(move_2);
      break;
    case R2_MOVE_YP:
    case R2_MOVE_YT:
    case R2_MOVE_YM:
      return r2_move_is_class_y(move_2);
      break;
    case R2_MOVE_ZP:
    case R2_MOVE_ZT:
    case R2_MOVE_ZM:
      return r2_move_is_class_z(move_2);
      break;
  }
  return R2_FALSE;
}
