#include "main.h"

static struct
{
  r2_move_t move;
  char*     string;
} Moves_strings[] =
{
  #define R2_MOVE(name, string) { R2_MOVE_##name, string },
  #include "type_move.x"
  #undef R2_MOVE
  { R2_MOVE_END_, NULL }
};

__FUNCTION_BEGIN__
char* r2_move_string(r2_move_t move)
__FUNCTION_END__
{
  int i;

  for(i = 0; Moves_strings[i].string != NULL; i++)
    if(Moves_strings[i].move == move)
      return Moves_strings[i].string;
  return "Unknown";
}
