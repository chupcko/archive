#include "main.h"

_LIBRARY_DECLARATION_BEGIN_
sunce_string_t sunce_json_new_string(sunce_json_t* json, char* value)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE("\"%s\"", value);
  sunce_size_t value_length = strlen(value);
  if
  (
    value_length < 3 ||
    value[0] != '\"' ||
    value[value_length-1] != '\"'
  )
    return SUNCE_NULL;
  sunce_string_t string = (sunce_string_t)sunce_json_malloc(json, value_length-2+1);
  if(string == SUNCE_NULL)
    return SUNCE_NULL;
  strncpy(string, &value[1], value_length-2);
  string[value_length-2] = '\0';
  return string;
}
