#include "main.h"

static index_t expression_copy_helper(expression_t* expression, index_t source_index)
{
  index_t source_item_index;
  index_t destination_index;
  index_t* new_item_index;

  source_item_index = source_index;
  new_item_index = &destination_index;
  while(source_item_index != INDEX_NULL)
  {
    *new_item_index = expression_copy(expression, source_item_index);
    if(*new_item_index == INDEX_NULL)
      return INDEX_NULL;
    new_item_index = &expression->items[*new_item_index].next;
    source_item_index = expression->items[source_item_index].next;
  }
  return destination_index;
}

_BEGIN_DECLARATION_
index_t expression_copy(expression_t* expression, index_t source_index)
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
      expression->items[destination_index].data = expression_copy_helper(expression, expression->items[source_index].data);
      if(expression->items[destination_index].data == INDEX_NULL)
        return INDEX_NULL;
      break;
    case ITEM_TYPE_COMBINATOR:
      expression->items[destination_index].data = expression->items[source_index].data;
      break;
  }
  return destination_index;
}
