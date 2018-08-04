#include "main.h"

static int expression_print_helper(expression_t* expression, index_t root, FILE* file)
{
  int length;
  boolean_t pass_first;
  index_t item_index;

  length = 0;
  pass_first = FALSE;
  item_index = root;
  while(item_index != INDEX_NULL)
  {
    switch(expression->items[item_index].type)
    {
      case ITEM_TYPE_SUB_ITEM:
        if(pass_first == TRUE)
          length += fprintf(file, " ");
        else
          pass_first = TRUE;
        length += fprintf(file, "( ");
        length += expression_print_helper(expression, expression->items[item_index].data, file);
        length += fprintf(file, " )");
        break;
      case ITEM_TYPE_COMBINATOR:
        if(pass_first == TRUE)
          length += fprintf(file, " ");
        else
          pass_first = TRUE;
        length += fprintf(file, "%s", expression->names[expression->items[item_index].data]);
        break;
    }
    item_index = expression->items[item_index].next;
  }
  return length;
}

_BEGIN_DECLARATION_
int expression_print(expression_t* expression, FILE* file)
_END_DECLARATION_
{
  return expression_print_helper(expression, expression->root, file);
}
