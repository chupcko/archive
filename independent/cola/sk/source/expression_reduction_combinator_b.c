#include "main.h"

_BEGIN_DECLARATION_
result_t expression_reduction_combinator_b(expression_t* expression, index_t* root)
_END_DECLARATION_
{
  if
  (
    expression_compare_name(expression, *root, COMBINATOR_B_NAME) == RESULT_OK &&
    expression_length(expression, *root) >= 4
  )
  {
    index_t item_head_index;
    index_t item_1_index;
    index_t item_2_index;
    index_t item_3_index;
    index_t item_tail_index;
    index_t new_sub_item_index;

    item_head_index = *root;
    item_1_index = expression->items[item_head_index].next;
    item_2_index = expression->items[item_1_index].next;
    item_3_index = expression->items[item_2_index].next;
    item_tail_index = expression->items[item_3_index].next;

    expression_delete(expression, item_head_index);

    new_sub_item_index = expression_add_item(expression);
    if(new_sub_item_index == INDEX_NULL)
      return RESULT_NO_SPACE_FOR_ITEM;
    expression->items[new_sub_item_index].type = ITEM_TYPE_SUB_ITEM;

    *root = item_1_index;
    expression->items[item_1_index].next = new_sub_item_index;
    expression->items[new_sub_item_index].next = item_tail_index;

    expression->items[new_sub_item_index].data = item_2_index;
    expression->items[item_2_index].next = item_3_index;
    expression->items[item_3_index].next = INDEX_NULL;

    return RESULT_DONE;
  }
  return RESULT_OK;
}
