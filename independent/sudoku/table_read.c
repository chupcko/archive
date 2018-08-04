#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void SDK_read_table(SDK_table_type *table, FILE *file)
{
  char buffer[SDK_READ_BUFFER_SIZE+1+1];
  int x;
  int y;
  int yi;
  SDK_boolean pass_init;

  x = SDK_X_DEFAULT;
  y = SDK_Y_DEFAULT;
  yi = 0;
  pass_init = SDK_FALSE;
  while(yi < x*y && fgets(buffer, SDK_READ_BUFFER_SIZE+1+1, file) != NULL)
  {
    SDK_boolean found_cell;
    int column;
    int xi;

    if(buffer[0] == '\n')
      continue;
    if(buffer[0] == SDK_READ_CHARACTER_COMMAND)
    {
      if(pass_init != SDK_TRUE)
        switch(toupper(buffer[1]))
        {
          case SDK_READ_CHARACTER_X:
            x = atoi(&buffer[2]);
            break;
          case SDK_READ_CHARACTER_Y:
            y = atoi(&buffer[2]);
            break;
        }
      continue;
    }
    found_cell = SDK_FALSE;
    column = 0;
    xi = 0;
    while(xi < x*y && buffer[column] != '\0')
    {
      if
      (
        buffer[column] == SDK_READ_CHARACTER_NO_FIXED ||
        buffer[column] == SDK_READ_CHARACTER_NO_FIXED_ALTERNATIVE
      )
      {
        found_cell = SDK_TRUE;
        xi++;
      }
      else
      {
        int index;

        index = SDK_find_in_character_set(buffer[column]);
        if(index != SDK_CHARACTER_SET_NO_INDEX)
        {
          if(pass_init != SDK_TRUE)
          {
            SDK_init_table(table, x, y);
            pass_init = SDK_TRUE;
          }
          SDK_fixate_cell_in_table(table, xi, yi, index, SDK_TRUE);
          found_cell = SDK_TRUE;
          xi++;
        }
      }
      column++;
    }
    if(found_cell == SDK_TRUE)
      yi++;
  }
}
