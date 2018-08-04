#include "main.h"

_BEGIN_DECLARATION_
index_t expression_add_item(expression_t* expression)
_END_DECLARATION_
{
  index_t new_index;

  if(expression->items_number >= EXPRESSION_MAX_ITEMS_NUMBER)
    return INDEX_NULL;
  new_index = expression->items_number;
  expression->items[new_index].type = ITEM_TYPE_USED;
  expression->items[new_index].data = INDEX_NULL;
  expression->items[new_index].next = INDEX_NULL;
  expression->items_number++;
  return new_index;
}
