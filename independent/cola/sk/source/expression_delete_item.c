#include "main.h"

_BEGIN_DECLARATION_
void expression_delete_item(expression_t* expression, index_t index)
_END_DECLARATION_
{
  expression->items[index].type = ITEM_TYPE_FREE;
  expression->items[index].data = INDEX_NULL;
  expression->items[index].next = INDEX_NULL;
  /* # uvezi ako treba */
}
