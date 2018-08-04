#include "main.h"

_BEGIN_DECLARATION_
index_t expression_copy_item(expression_t* expression, index_t source_index)
_END_DECLARATION_
{
  index_t destination_index;

  destination_index = expression_add_item(expression);
  if(destination_index == INDEX_NULL)
    return INDEX_NULL;
  expression->items[destination_index].type = expression->items[source_index].type;
  switch(expression->items[source_index].type)
  {
    case ITEM_TYPE_SUB_ITEM:
      expression->items[destination_index].data = expression_copy(expression, expression->items[source_index].data);
      if(expression->items[destination_index].data == INDEX_NULL)
        return INDEX_NULL;
      break;
    case ITEM_TYPE_COMBINATOR:
      expression->items[destination_index].data = expression->items[source_index].data;
      break;
  }
  return destination_index;
}
