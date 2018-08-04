#include "main.h"

int SDK_shape_x(SDK_table_type *table, SDK_shape_type shape, int theta, int radius)
{
  switch(shape)
  {
    case SDK_SHAPE_REGION:
      return theta%table->y*table->x+radius%table->x;
      break;
    case SDK_SHAPE_ROW:
      return radius;
      break;
    case SDK_SHAPE_COLUMN:
      return theta;
      break;
  }
  return 0;
}

int SDK_shape_y(SDK_table_type *table, SDK_shape_type shape, int theta, int radius)
{
  switch(shape)
  {
    case SDK_SHAPE_REGION:
      return theta/table->y*table->y+radius/table->x;
      break;
    case SDK_SHAPE_ROW:
      return theta;
      break;
    case SDK_SHAPE_COLUMN:
      return radius;
      break;
  }
  return 0;
}

int SDK_shape_theta(SDK_table_type *table, SDK_shape_type shape, int x, int y)
{
  switch(shape)
  {
    case SDK_SHAPE_REGION:
      return y/table->y*table->y+x/table->x;
      break;
    case SDK_SHAPE_ROW:
      return y;
      break;
    case SDK_SHAPE_COLUMN:
      return x;
      break;
  }
  return 0;
}

int SDK_shape_radius(SDK_table_type *table, SDK_shape_type shape, int x, int y)
{
  switch(shape)
  {
    case SDK_SHAPE_REGION:
      return y%table->y*table->x+x%table->x;
      break;
    case SDK_SHAPE_ROW:
      return x;
      break;
    case SDK_SHAPE_COLUMN:
      return y;
      break;
  }
  return 0;
}
