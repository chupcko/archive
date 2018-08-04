#include <stdio.h>

#include "main.h"

/* ako je flgas null sredi nekako */

void SDK_postscript_debug_table(SDK_table_type *table, SDK_postscript_flags_type *flags, FILE *file, int page)
{
  int y;

  fprintf
  (
    file,
    "%%%%Page: %d %d\n"
    "SDK_init_page\n"
    "%d %d\n"
    "[\n",
    page, page, table->x, table->y
  );
  for(y = 0; y < table->xy; y++)
  {
    int x;

    fprintf(file, "  [\n");
    for(x = 0; x < table->xy; x++)
    {
      fprintf(file, "    [");
      if(table->cell[x][y].fixed == SDK_TRUE)
        fprintf
        (
          file, "0 %d %d %d (%c)",
          (*flags)[x][y].background,
          (*flags)[x][y].foreground,
          (*flags)[x][y].marker,
          SDK_character(table->cell[x][y].character_set_index)
        );
      else
      {
        int index;

        fprintf(file, "1 %d %d [", (*flags)[x][y].background, (*flags)[x][y].foreground);
        for(index = table->character_set_index_min; index <= table->character_set_index_max; index++)
          fprintf(file, "%d ", (*flags)[x][y].possibility_marker[index]);
        fprintf(file, "] [");
        for(index = table->character_set_index_min; index <= table->character_set_index_max; index++)
          if(table->cell[x][y].possibility[index] == SDK_TRUE)
            fprintf(file, "(%c)", SDK_character(index));
          else
            fprintf(file, "(%c)", SDK_CHARACTER_NO_FIXED);
        fprintf(file, "]");
      }
      fprintf(file, "]\n");
    }
    fprintf(file, "  ]\n");
  }
  fprintf
  (
    file,
    "]\n"
    "SDK_print_table\n"
    "showpage\n"
  );
}
