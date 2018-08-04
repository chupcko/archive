#include "main.h"

SDK_boolean SDK_find_single_in_shape(SDK_table_type *table, SDK_shape_type shape, int theta, int *radius, int *index)
{
  int index1;

  for(index1 = table->character_set_index_min; index1 <= table->character_set_index_max; index1++)
  {
    int radius1;
    int count;

    count = 0;
    for(radius1 = 0; radius1 < table->xy; radius1++)
    {
      int x;
      int y;

      x = SDK_shape_x(table, shape, theta, radius1);
      y = SDK_shape_y(table, shape, theta, radius1);
      if
      (
        table->cell[x][y].fixed != SDK_TRUE &&
        table->cell[x][y].possibility[index1] == SDK_TRUE
      )
      {
        *radius = radius1;
        count++;
      }
    }
    if(count == 1)
    {
      *index = index1;
      return SDK_TRUE;
    }
  }
  return SDK_FALSE;
}

SDK_boolean SDK_find_single_in_cell(SDK_table_type *table, int *x, int *y, int *index)
{
  int x1;
  int y1;
  int index1;

  for(x1 = 0; x1 < table->xy; x1++)
    for(y1 = 0; y1 < table->xy; y1++)
      if(table->cell[x1][y1].possibility_count == 1)
        for(index1 = table->character_set_index_min; index1 <= table->character_set_index_max; index1++)
          if
          (
            table->cell[x1][y1].fixed != SDK_TRUE &&
            table->cell[x1][y1].possibility[index1] == SDK_TRUE
          )
          {
            *x = x1;
            *y = y1;
            *index = index1;
            return SDK_TRUE;
          }
  return SDK_FALSE;
}
