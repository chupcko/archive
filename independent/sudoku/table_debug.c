#include <stdio.h>

#include "main.h"

static void SDK_debug_table_separator(SDK_table_type *table, FILE *file)
{
  int x;

  for(x = 0; x < table->xy; x++)
  {
    int index;

    if(x % table->x == 0)
      fprintf(file, "%c", SDK_DEBUG_CHARACTER_JOIN_SEPARATOR);
    fprintf(file, "%c", SDK_DEBUG_CHARACTER_HORIZONTAL_SEPARATOR);
    for(index = table->character_set_index_min; index <= table->character_set_index_max; index++)
      fprintf(file, "%c", SDK_DEBUG_CHARACTER_HORIZONTAL_SEPARATOR);
    fprintf(file, "%c", SDK_DEBUG_CHARACTER_HORIZONTAL_SEPARATOR);
  }
  fprintf(file, "%c\n", SDK_DEBUG_CHARACTER_JOIN_SEPARATOR);
}

static void SDK_debug_table_row(SDK_table_type *table, FILE *file, int y)
{
  int x;

  for(x = 0; x < table->xy; x++)
  {
    int index;

    if(x % table->x == 0)
      fprintf(file, "%c", SDK_DEBUG_CHARACTER_VERTICAL_SEPARATOR);
    if(table->cell[x][y].fixed == SDK_TRUE)
    {
      fprintf(file, "%c", SDK_DEBUG_CHARACTER_NO_FIXED);
      fprintf(file, "%c", SDK_character(table->cell[x][y].character_set_index));
      for(index = table->character_set_index_min; index <= table->character_set_index_max; index++)
        fprintf(file, "%c", SDK_DEBUG_CHARACTER_NO_FIXED);
    }
    else
    {
      fprintf(file, "%c", SDK_DEBUG_CHARACTER_POSSIBILITY_BEGIN);
      for(index = table->character_set_index_min; index <= table->character_set_index_max; index++)
        if(table->cell[x][y].possibility[index] == SDK_TRUE)
          fprintf(file, "%c", SDK_character(index));
        else
          fprintf(file, "%c", SDK_DEBUG_CHARACTER_NO_FIXED);
      fprintf(file, "%c", SDK_DEBUG_CHARACTER_POSSIBILITY_END);
    }
  }
  fprintf(file, "%c\n", SDK_DEBUG_CHARACTER_VERTICAL_SEPARATOR);
}

void SDK_debug_table(SDK_table_type *table, FILE *file)
{
  int y;

  for(y = 0; y < table->xy; y++)
  {
    if(y % table->y == 0)
      SDK_debug_table_separator(table, file);
    SDK_debug_table_row(table, file, y);
  }
  SDK_debug_table_separator(table, file);
}
