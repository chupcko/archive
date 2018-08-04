#include <stdio.h>

#include "main.h"

int main(void)
{
  SDK_table_type table;

  SDK_init_character_set();
  SDK_read_table(&table, stdin);
  SDK_solve(&table, stdout);
  return 0;
}
