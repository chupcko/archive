#include <stdio.h>

#include "sunce.h"

char* INPUT =
  "{\n"
  "  \"a\": 1,\n"
  "  \"b\": 2,\n"
  "  \"c\": 3,\n"
  "  \"d\": 4\n"
  "}\n";

int main(void)
{
  sunce_json_t json;
  sunce_json_init(&json);
  if(sunce_json_read_string(&json, INPUT) != 0)
  {
    printf("ERROR\n");
    return 1;
  }
  sunce_json_debug(&json);
  sunce_json_free(&json);
  return 0;
}
