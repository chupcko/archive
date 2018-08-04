#include <ctype.h>

#include "main.h"

static SDK_character_set_type SDK_character_set;

void SDK_init_character_set(void)
{
  int xy;

  for(xy = 0; xy < SDK_CHARACTER_SET_INDEX_MAX; xy++)
    if(xy < 10)
      SDK_character_set[xy] = '0'+(char)xy;
    else
      SDK_character_set[xy] = 'A'+(char)xy-10;
}

char SDK_character(int index)
{
  if(index >= 0 && index < SDK_CHARACTER_SET_INDEX_MAX)
    return SDK_character_set[index];
  return SDK_CHARACTER_NO_FIXED;
}

int SDK_find_in_character_set(char character)
{
  int xy;

  for(xy = 0; xy < SDK_CHARACTER_SET_INDEX_MAX; xy++)
    if(SDK_character_set[xy] == toupper(character))
      return xy;
  return SDK_CHARACTER_SET_NO_INDEX;
}
