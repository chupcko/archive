#include "main.h"

void SDK_init_table(SDK_table_type *table, int x_init, int y_init)
{
  int x;
  int y;

  if(x_init < SDK_X_MIN || x_init > SDK_X_MAX)
    x_init = SDK_X_DEFAULT;
  if(y_init < SDK_Y_MIN || y_init > SDK_Y_MAX)
    y_init = SDK_Y_DEFAULT;
  table->x = x_init;
  table->y = y_init;
  table->xy = table->x*table->y;
  if(table->xy < 10)
  {
    table->character_set_index_min = 1;
    table->character_set_index_max = table->xy;
  }
  else
  {
    table->character_set_index_min = 0;
    table->character_set_index_max = table->xy-1;
  }
  for(x = 0; x < table->xy; x++)
    for(y = 0; y < table->xy; y++)
    {
      int index;

      table->cell[x][y].initial = SDK_FALSE;
      table->cell[x][y].fixed = SDK_FALSE;
      table->cell[x][y].character_set_index = SDK_CHARACTER_SET_NO_INDEX;
      table->cell[x][y].possibility_count = 0;
      for(index = table->character_set_index_min; index <= table->character_set_index_max; index++)
      {
        table->cell[x][y].possibility[index] = SDK_TRUE;
        table->cell[x][y].possibility_count++;
      }
    }
}
