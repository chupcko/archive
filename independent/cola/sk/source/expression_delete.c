#include "main.h"

static void expression_delete_helper(expression_t* expression, index_t root)
{
  index_t item_index;
  index_t delete_item_index;

  item_index = root;
  while(item_index != INDEX_NULL)
  {
    if(expression->items[item_index].type == ITEM_TYPE_SUB_ITEM)
      expression_delete(expression, expression->items[item_index].data);
    delete_item_index = item_index;
    item_index = expression->items[item_index].next;
    expression_delete_item(expression, delete_item_index);
  }
}

_BEGIN_DECLARATION_
void expression_delete(expression_t* expression, index_t root)
_END_DECLARATION_
{
  if(expression->items[root].type == ITEM_TYPE_SUB_ITEM)
    expression_delete_helper(expression, expression->items[root].data);
  expression_delete_item(expression, root);
}