#include "main.h"

void SDK_fixate_cell_in_table(SDK_table_type *table, int x, int y, int index, SDK_boolean initial)
{
  SDK_shape_type shape;

  for(shape = SDK_SHAPE_MIN; shape <= SDK_SHAPE_MAX; shape++)
  {
    int theta;
    int radius;

    theta = SDK_shape_theta(table, shape, x, y);
    for(radius = 0; radius < table->xy; radius++)
    {
      int xi;
      int yi;

      xi = SDK_shape_x(table, shape, theta, radius);
      yi = SDK_shape_y(table, shape, theta, radius);
      if(table->cell[xi][yi].possibility[index] == SDK_TRUE)
      {
        table->cell[xi][yi].possibility[index] = SDK_FALSE;
        table->cell[xi][yi].possibility_count--;
      }
    }
  }
  table->cell[x][y].initial = initial;
  table->cell[x][y].fixed = SDK_TRUE;
  table->cell[x][y].character_set_index = index;
  table->cell[x][y].possibility_count = 0;
  for(index = table->character_set_index_min; index <= table->character_set_index_max; index++)
    table->cell[x][y].possibility[index] = SDK_FALSE;
}
