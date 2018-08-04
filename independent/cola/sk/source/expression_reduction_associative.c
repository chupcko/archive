#include "main.h"

_BEGIN_DECLARATION_
result_t expression_reduction_associative(expression_t* expression, index_t* root)
_END_DECLARATION_
{
  index_t item_index;
  index_t sub_index;

  item_index = *root;
  if(expression->items[item_index].type == ITEM_TYPE_SUB_ITEM)
  {
    sub_index = expression->items[item_index].data;
    *root = sub_index;
    while(expression->items[sub_index].next != INDEX_NULL)
      sub_index = expression->items[sub_index].next;
    expression->items[sub_index].next = expression->items[item_index].next;
    expression_delete_item(expression, item_index);
    return RESULT_DONE;
  }
  return RESULT_OK;
}
