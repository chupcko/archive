#include "main.h"

void SDK_init_postscript_flags(SDK_postscript_flags_type *flags)
{
  int x;
  int y;

  for(x = 0; x < SDK_XY_MAX; x++)
    for(y = 0; y < SDK_XY_MAX; y++)
    {
      int index;

      (*flags)[x][y].background = 0;
      (*flags)[x][y].foreground = 0;
      (*flags)[x][y].marker = 0;
      for(index = 0; index < SDK_CHARACTER_SET_INDEX_MAX; index++)
        (*flags)[x][y].possibility_marker[index] = 0;
    }
}

void SDK_set_background_in_postscript_flags(SDK_postscript_flags_type *flags, int x, int y, int color)
{
  (*flags)[x][y].background = color;
}

void SDK_set_foreground_in_postscript_flags(SDK_postscript_flags_type *flags, int x, int y, int color)
{
  (*flags)[x][y].foreground = color;
}

void SDK_set_marker_in_postscript_flags(SDK_postscript_flags_type *flags, int x, int y, int marker)
{
  (*flags)[x][y].marker = marker;
}

void SDK_set_possibility_marker_in_postscript_flags(SDK_postscript_flags_type *flags, int x, int y, int index, int marker)
{
  (*flags)[x][y].possibility_marker[index] = marker;
}

void SDK_set_background_on_shape_in_postscript_flags(SDK_postscript_flags_type *flags, SDK_table_type *table, SDK_shape_type shape, int theta, int color)
{
  int radius;

  for(radius = 0; radius < table->xy; radius ++)
    (*flags)[SDK_shape_x(table, shape, theta, radius)][SDK_shape_y(table, shape, theta, radius)].background = color;
}
