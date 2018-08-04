#include <stdio.h>

#include "main.h"

static void SDK_print_table_separator(SDK_table_type *table, FILE *file)
{
  int x;

  for(x = 0; x < table->xy; x++)
  {
    if(x % table->x == 0)
      fprintf(file, "%c", SDK_PRINT_CHARACTER_JOIN_SEPARATOR);
    fprintf(file, "%c", SDK_PRINT_CHARACTER_HORIZONTAL_SEPARATOR);
  }
  fprintf(file, "%c\n", SDK_PRINT_CHARACTER_JOIN_SEPARATOR);
}

static void SDK_print_table_row(SDK_table_type *table, FILE *file, int y)
{
  int x;

  for(x = 0; x < table->xy; x++)
  {
    if(x % table->x == 0)
      fprintf(file, "%c", SDK_PRINT_CHARACTER_VERTICAL_SEPARATOR);
    if(table->cell[x][y].fixed == SDK_TRUE)
      fprintf(file, "%c", SDK_character(table->cell[x][y].character_set_index));
    else
      fprintf(file, "%c", SDK_PRINT_CHARACTER_NO_FIXED);
  }
  fprintf(file, "%c\n", SDK_PRINT_CHARACTER_VERTICAL_SEPARATOR);
}

void SDK_print_table(SDK_table_type *table, FILE *file)
{
  int y;

  for(y = 0; y < table->xy; y++)
  {
    if(y % table->y == 0)
      SDK_print_table_separator(table, file);
    SDK_print_table_row(table, file, y);
  }
  SDK_print_table_separator(table, file);
}
