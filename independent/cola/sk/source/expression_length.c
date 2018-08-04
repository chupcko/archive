#include "main.h"

_BEGIN_DECLARATION_
index_t expression_length(expression_t* expression, index_t root)
_END_DECLARATION_
{
  index_t length;
  index_t item_index;

  length = 0;
  item_index = root;
  while(item_index != INDEX_NULL)
  {
    length++;
    item_index = expression->items[item_index].next;
  }
  return length;
}
