#include <stdio.h>

#include "sunce.h"

int main(void)
{
  /***/
  sunce_json_t json;
  sunce_json_init(&json);
  if(sunce_xml_read_file(&json, stdin) != 0)
  {
    printf("ERROR\n");
    return 1;
  }
  sunce_json_debug(&json);
  sunce_json_free(&json);
  return 0;
}
