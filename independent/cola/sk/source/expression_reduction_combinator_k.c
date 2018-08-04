#include "main.h"

_BEGIN_DECLARATION_
result_t expression_reduction_combinator_k(expression_t* expression, index_t* root)
_END_DECLARATION_
{
  if
  (
    expression_compare_name(expression, *root, COMBINATOR_K_NAME) == RESULT_OK &&
    expression_length(expression, *root) >= 3
  )
  {
    index_t item_head_index;
    index_t item_1_index;
    index_t item_2_index;
    index_t item_tail_index;

    item_head_index = *root;
    item_1_index = expression->items[item_head_index].next;
    item_2_index = expression->items[item_1_index].next;
    item_tail_index = expression->items[item_2_index].next;

    expression_delete(expression, item_head_index);
    expression_delete(expression, item_2_index);
    *root = item_1_index;
    expression->items[item_1_index].next = item_tail_index;

    return RESULT_DONE;
  }
  return RESULT_OK;
}
