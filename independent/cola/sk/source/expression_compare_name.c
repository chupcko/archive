#include "main.h"

_BEGIN_DECLARATION_
result_t expression_compare_name(expression_t* expression, index_t root, char* name)
_END_DECLARATION_
{
  if
  (
    expression->items[root].type == ITEM_TYPE_COMBINATOR &&
    strncmp(expression->names[expression->items[root].data], name, NAME_MAX_LENGTH) == 0
  )
    return RESULT_OK;
  return RESULT_NO;
}
