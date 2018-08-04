#include "main.h"

_BEGIN_DECLARATION_
result_t expression_check(expression_t* expression)
_END_DECLARATION_
{
  index_t item_index;

  if(expression->root == INDEX_NULL)
    return RESULT_BAD_EXPRESSION;
  /*# proveri da li ima petlji, tesko */
  for(item_index = 0; item_index < expression->items_number; item_index++)
    if
    (
      (
        expression->items[item_index].type == ITEM_TYPE_SUB_ITEM ||
        expression->items[item_index].type == ITEM_TYPE_COMBINATOR
      ) &&
      expression->items[item_index].data == INDEX_NULL
    )
      return RESULT_BAD_EXPRESSION;
  return RESULT_OK;
}
