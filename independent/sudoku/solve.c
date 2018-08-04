#include <stdio.h>

#include "main.h"

/* ovo nekako sredi */

static SDK_postscript_flags_type flags;
static int page;

static SDK_boolean SDK_solve_find_single_in_cell(SDK_table_type *table, FILE *file)
{
  int x;
  int y;
  int index;

  if(SDK_find_single_in_cell(table, &x, &y, &index) == SDK_TRUE)
  {
    SDK_init_postscript_flags(&flags);
    SDK_set_background_in_postscript_flags(&flags, x, y, SDK_BACKGROUND_GRAY_1);
    SDK_set_possibility_marker_in_postscript_flags(&flags, x, y, index, SDK_MARKER_ROUND);
    SDK_postscript_debug_table(table, &flags, file, page);
    page++;
    SDK_fixate_cell_in_table(table, x, y, index, SDK_FALSE);
    return SDK_TRUE;
  }
  return SDK_FALSE;
}

static SDK_boolean SDK_solve_find_single_in_all_shape(SDK_table_type *table, FILE *file)
{
  SDK_shape_type shape;
  int theta;
  int radius;
  int index;

  for(shape = SDK_SHAPE_MIN; shape <= SDK_SHAPE_MAX; shape++)
    for(theta = 0; theta < table->xy; theta++)
      if(SDK_find_single_in_shape(table, shape, theta, &radius, &index) == SDK_TRUE)
      {
        int x;
        int y;

        x = SDK_shape_x(table, shape, theta, radius);
        y = SDK_shape_y(table, shape, theta, radius);
        SDK_init_postscript_flags(&flags);
        SDK_set_background_on_shape_in_postscript_flags(&flags, table, shape, theta, SDK_BACKGROUND_GRAY_1);
        SDK_set_possibility_marker_in_postscript_flags(&flags, x, y, index, SDK_MARKER_ROUND);
        SDK_postscript_debug_table(table, &flags, file, page);
        page++;
        SDK_fixate_cell_in_table(table, x, y, index, SDK_FALSE);
        return SDK_TRUE;
      }
  return SDK_FALSE;
}

void SDK_solve(SDK_table_type *table, FILE *file)
{
  int x;
  int y;

  page = 1;
  SDK_postscript_head(file);
  do
  {
    if(SDK_solve_find_single_in_cell(table, file) == SDK_TRUE)
      continue;
    if(SDK_solve_find_single_in_all_shape(table, file) == SDK_TRUE)
      continue;
    break;
  } while(SDK_TRUE);
  SDK_init_postscript_flags(&flags);
  for(x = 0; x < table->xy; x++)
    for(y = 0; y < table->xy; y++)
      if(table->cell[x][y].initial == SDK_TRUE)
        SDK_set_foreground_in_postscript_flags(&flags, x, y, SDK_FOREGROUND_GRAY_2);
  SDK_postscript_debug_table(table, &flags, file, page);
  SDK_postscript_tail(file);
}
