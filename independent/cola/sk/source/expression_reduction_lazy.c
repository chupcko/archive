#include "main.h"

_BEGIN_DECLARATION_
result_t expression_reduction_lazy(expression_t* expression)
_END_DECLARATION_
{
  RESULT_CALL(expression_post_walk(expression, &expression_reduction_single));
  RESULT_CALL(expression_post_walk(expression, &expression_reduction_associative));
  RESULT_CALL(expression_pre_walk(expression, &expression_reduction_combinator_helper));
  return RESULT_OK;
}
