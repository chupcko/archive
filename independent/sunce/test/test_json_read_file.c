#include <stdio.h>

#include "sunce.h"

int main(int arguments_count, char* arguments_value[])
{
  if(arguments_count != 2)
    return 10;
  FILE* file = fopen(arguments_value[1], "r");
  if(file == NULL)
    return 11;
  sunce_json_t json;
  sunce_json_init(&json);
  if(sunce_json_read_file(&json, file) != 0)
  {
    printf("ERROR\n");
    return 1;
  }
  sunce_json_debug(&json);
  sunce_json_free(&json);
  fclose(file);
  return 0;
}
