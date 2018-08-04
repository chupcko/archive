#include "main.h"

_BEGIN_DECLARATION_
result_t expression_reduction_combinator_j(expression_t* expression, index_t* root)
_END_DECLARATION_
{
  if
  (
    expression_compare_name(expression, *root, COMBINATOR_J_NAME) == RESULT_OK &&
    expression_length(expression, *root) >= 1
  )
  {
    index_t item_head_index;
    index_t item_1_index;
    index_t item_tail_index;
    index_t new_s_item_index;
    index_t new_k_item_index;

    item_head_index = *root;
    item_1_index = expression->items[item_head_index].next;
    item_tail_index = expression->items[item_1_index].next;

    expression_delete(expression, item_head_index);

    new_s_item_index = expression_add_item(expression);
    if(new_s_item_index == INDEX_NULL)
      return RESULT_NO_SPACE_FOR_ITEM;
    expression->items[new_s_item_index].type = ITEM_TYPE_COMBINATOR;
    expression->items[new_s_item_index].data = expression_add_name(expression, COMBINATOR_S_NAME);
    if(expression->items[new_s_item_index].data == INDEX_NULL)
      return RESULT_NO_SPACE_FOR_NAME;

    new_k_item_index = expression_add_item(expression);
    if(new_k_item_index == INDEX_NULL)
      return RESULT_NO_SPACE_FOR_ITEM;
    expression->items[new_k_item_index].type = ITEM_TYPE_COMBINATOR;
    expression->items[new_k_item_index].data = expression_add_name(expression, COMBINATOR_K_NAME);
    if(expression->items[new_k_item_index].data == INDEX_NULL)
      return RESULT_NO_SPACE_FOR_NAME;

    *root = item_1_index;
    expression->items[item_1_index].next = new_s_item_index;
    expression->items[new_s_item_index].next = new_k_item_index;
    expression->items[new_k_item_index].next = item_tail_index;

    return RESULT_DONE;
  }
  return RESULT_OK;
}
