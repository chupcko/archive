#include "main.h"

_BEGIN_DECLARATION_
index_t expression_add_name(expression_t* expression, char* name)
_END_DECLARATION_
{
  index_t new_index;

  for(new_index = 0; new_index < expression->names_number; new_index++)
    if(strncmp(expression->names[new_index], name, NAME_MAX_LENGTH) == 0)
      return new_index;

  if(expression->names_number >= EXPRESSION_MAX_NAMES_NUMBER)
    return INDEX_NULL;
  new_index = expression->names_number;
  snprintf(expression->names[new_index], NAME_MAX_LENGTH, "%s", name);
  expression->names_number++;
  return new_index;
}
