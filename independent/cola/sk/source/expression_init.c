#include "main.h"

_BEGIN_DECLARATION_
void expression_init(expression_t* expression)
_END_DECLARATION_
{
  expression->items_number = 0;
  expression->names_number = 0;
  expression->root = INDEX_NULL;
}
