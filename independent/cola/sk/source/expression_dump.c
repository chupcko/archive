#include "main.h"

static char* item_type_name(item_type_t item_type)
{
  switch(item_type)
  {
    case ITEM_TYPE_FREE:
      return "FREE";
      break;
    case ITEM_TYPE_USED:
      return "USED";
      break;
    case ITEM_TYPE_SUB_ITEM:
      return "SUB";
      break;
    case ITEM_TYPE_COMBINATOR:
      return "COMB";
      break;
  }
  return "NONE";
}

static int index_null_printf(index_t index, FILE* file)
{
  if(index == INDEX_NULL)
    return fprintf(file, "NULL");
  return fprintf(file, "%-4d", index);
}

_BEGIN_DECLARATION_
int expression_dump(expression_t* expression, FILE* file)
_END_DECLARATION_
{
  int length;
  index_t index;

  length = 0;
  length += fprintf(file, "items:%-4d\tnames:%-4d\troot:", expression->items_number, expression->names_number);
  length += index_null_printf(expression->root, file);
  length += fprintf(file, "\n");
  for(index = 0; index < expression->items_number; index++)
  {
    length += fprintf(file, "item:%-4d\ttype:%s\tdata:", index, item_type_name(expression->items[index].type));
    length += index_null_printf(expression->items[index].data, file);
    length += fprintf(file, "\tnext:");
    length += index_null_printf(expression->items[index].next, file);
    if(expression->items[index].type == ITEM_TYPE_COMBINATOR)
      length += fprintf(file, "\tname:\"%s\"", expression->names[expression->items[index].data]);
    length += fprintf(file, "\n");
  };
  for(index = 0; index < expression->names_number; index++)
    length += fprintf(file, "name:%-4d\tvalue:\"%s\"\n", index, expression->names[index]);
  return length;
}
