#include "main.h"

static result_t expression_post_walk_helper(expression_t* expression, index_t* root, walk_function_t function)
{
  index_t* item_index;

  item_index = root;
  while(*item_index != INDEX_NULL)
  {
    if(expression->items[*item_index].type == ITEM_TYPE_SUB_ITEM)
      RESULT_CALL(expression_post_walk_helper(expression, &expression->items[*item_index].data, function))
    item_index = &expression->items[*item_index].next;
  }
  RESULT_CALL((*function)(expression, root));
  return RESULT_OK;
}

_BEGIN_DECLARATION_
result_t expression_post_walk(expression_t* expression, walk_function_t function)
_END_DECLARATION_
{
  return expression_post_walk_helper(expression, &expression->root, function);
}
