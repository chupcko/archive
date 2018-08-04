#ifndef __TYPE_MOVE_H__
#define __TYPE_MOVE_H__

typedef enum r2_move_t
{
  #define R2_MOVE(name, string) R2_MOVE_##name,
  #include "type_move.x"
  #undef R2_MOVE
  R2_MOVE_END_
} r2_move_t;

#endif
