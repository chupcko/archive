#include "main.h"

_BEGIN_DECLARATION_
result_t expression_reduction_combinator_c(expression_t* expression, index_t* root)
_END_DECLARATION_
{
  if
  (
    expression_compare_name(expression, *root, COMBINATOR_C_NAME) == RESULT_OK &&
    expression_length(expression, *root) >= 4
  )
  {
    index_t item_head_index;
    index_t item_1_index;
    index_t item_2_index;
    index_t item_3_index;
    index_t item_tail_index;

    item_head_index = *root;
    item_1_index = expression->items[item_head_index].next;
    item_2_index = expression->items[item_1_index].next;
    item_3_index = expression->items[item_2_index].next;
    item_tail_index = expression->items[item_3_index].next;

    expression_delete(expression, item_head_index);
    *root = item_1_index;
    expression->items[item_1_index].next = item_3_index;
    expression->items[item_3_index].next = item_2_index;
    expression->items[item_2_index].next = item_tail_index;

    return RESULT_DONE;
  }
  return RESULT_OK;
}
