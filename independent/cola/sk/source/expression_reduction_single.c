#include "main.h"

_BEGIN_DECLARATION_
result_t expression_reduction_single(expression_t* expression, index_t* root)
_END_DECLARATION_
{
  index_t item_index;
  index_t sub_index;

  item_index = *root;
  while(item_index != INDEX_NULL)
  {
    if(expression->items[item_index].type == ITEM_TYPE_SUB_ITEM)
    {
      sub_index = expression->items[item_index].data;
      if(expression->items[sub_index].next == INDEX_NULL)
      {
        expression->items[item_index].type =  expression->items[sub_index].type;
        expression->items[item_index].data =  expression->items[sub_index].data;
        expression_delete_item(expression, sub_index);
        return RESULT_DONE;
      }
    }
    item_index = expression->items[item_index].next;
  }
  return RESULT_OK;
}
