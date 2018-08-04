#include "main.h"

_LIBRARY_DECLARATION_BEGIN_
char* sunce_boolean_string(sunce_boolean_t value)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE();
  if(value == SUNCE_TRUE)
    return ("true");
  return("false");
}
