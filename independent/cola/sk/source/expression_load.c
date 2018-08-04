#include "main.h"

typedef enum lexeme_t
{
  LEXEME_END,
  LEXEME_OPEN_PARENTHESIS,
  LEXEME_CLOSE_PARENTHESIS,
  LEXEME_NAME,
} lexeme_t;

typedef struct lexical_t
{
  const char* input;
  lexeme_t    lexeme;
  name_t      name;
} lexical_t;

static result_t lexical_next(lexical_t* lexical)
{
  while(isspace(*lexical->input) != 0)
    ++lexical->input;
  if(*lexical->input == '\0')
  {
    lexical->lexeme = LEXEME_END;
    return RESULT_OK;
  }
  if(*lexical->input == '(')
  {
    lexical->lexeme = LEXEME_OPEN_PARENTHESIS;
    ++lexical->input;
    return RESULT_OK;
  }
  if(*lexical->input == ')')
  {
    lexical->lexeme = LEXEME_CLOSE_PARENTHESIS;
    ++lexical->input;
    return RESULT_OK;
  }
  if(isalnum(*lexical->input) != 0)
  {
    index_t i;

    lexical->lexeme = LEXEME_NAME;
    i = 0;
    do
    {
      if(i < NAME_MAX_LENGTH-1)
      {
        lexical->name[i] = *lexical->input;
        i++;
      }
      ++lexical->input;
    }
    while(isalnum(*lexical->input) != 0);
    lexical->name[i] = '\0';
    return RESULT_OK;
  }
  return RESULT_UNKNOWN_CHARACTER;
}

static result_t lexical_init(lexical_t* lexical, const char* input)
{
  lexical->input = input;
  RESULT_CALL(lexical_next(lexical))
  return RESULT_OK;
}

static result_t expression_load_helper(expression_t* expression, index_t* root, lexical_t* lexical)
{
  index_t* item_index;
  index_t new_item_index;

  item_index = root;
  if
  (
    lexical->lexeme != LEXEME_OPEN_PARENTHESIS &&
    lexical->lexeme != LEXEME_NAME
  )
    return RESULT_MISSING_EXPRESSION;
  do
  {
    new_item_index = expression_add_item(expression);
    if(new_item_index == INDEX_NULL)
      return RESULT_NO_SPACE_FOR_ITEM;
    *item_index = new_item_index;
    item_index = &expression->items[new_item_index].next;
    switch(lexical->lexeme)
    {
      case LEXEME_OPEN_PARENTHESIS:
        expression->items[new_item_index].type = ITEM_TYPE_SUB_ITEM;
        RESULT_CALL(lexical_next(lexical));
        RESULT_CALL(expression_load_helper(expression, &expression->items[new_item_index].data, lexical));
        if(lexical->lexeme != LEXEME_CLOSE_PARENTHESIS)
          return RESULT_MISSING_CLOSE_PARENTHESIS;
        RESULT_CALL(lexical_next(lexical));
        break;
      case LEXEME_NAME:
        expression->items[new_item_index].type = ITEM_TYPE_COMBINATOR;
        expression->items[new_item_index].data = expression_add_name(expression, lexical->name);
        if(expression->items[new_item_index].data == INDEX_NULL)
          return RESULT_NO_SPACE_FOR_NAME;
        RESULT_CALL(lexical_next(lexical));
        break;
    }
  }
  while
  (
    lexical->lexeme == LEXEME_OPEN_PARENTHESIS ||
    lexical->lexeme == LEXEME_NAME
  );
  return RESULT_OK;
}

_BEGIN_DECLARATION_
result_t expression_load(expression_t* expression, const char* input)
_END_DECLARATION_
{
  lexical_t lexical;

  RESULT_CALL(lexical_init(&lexical, input));
  RESULT_CALL(expression_load_helper(expression, &expression->root, &lexical));
  if(lexical.lexeme != LEXEME_END)
    return RESULT_SOMETHING_AFTER_EXPRESSION;
  return RESULT_OK;
}
