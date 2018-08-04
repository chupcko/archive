#include "main.h"

_BEGIN_DECLARATION_
result_t expression_reduction_combinator_m(expression_t* expression, index_t* root)
_END_DECLARATION_
{
  if
  (
    expression_compare_name(expression, *root, COMBINATOR_M_NAME) == RESULT_OK &&
    expression_length(expression, *root) >= 2
  )
  {
    index_t item_head_index;
    index_t item_1_index;
    index_t item_tail_index;
    index_t new_item_1_index;

    item_head_index = *root;
    item_1_index = expression->items[item_head_index].next;
    item_tail_index = expression->items[item_1_index].next;

    expression_delete(expression, item_head_index);

    new_item_1_index = expression_copy(expression, item_1_index);
    if(new_item_1_index == INDEX_NULL)
      return RESULT_NO_SPACE_FOR_ITEM;

    *root = item_1_index;
    expression->items[item_1_index].next = new_item_1_index;
    expression->items[new_item_1_index].next = item_tail_index;

    return RESULT_DONE;
  }
  return RESULT_OK;
}
