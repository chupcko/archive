#include "main.h"

_BEGIN_DECLARATION_
result_t expression_reduction_combinator_helper(expression_t* expression, index_t* root)
_END_DECLARATION_
{
  RESULT_CALL(expression_reduction_combinator_s(expression, root));
  RESULT_CALL(expression_reduction_combinator_k(expression, root));
  RESULT_CALL(expression_reduction_combinator_i(expression, root));
  RESULT_CALL(expression_reduction_combinator_f(expression, root));
  RESULT_CALL(expression_reduction_combinator_b(expression, root));
  RESULT_CALL(expression_reduction_combinator_c(expression, root));
  RESULT_CALL(expression_reduction_combinator_w(expression, root));
  RESULT_CALL(expression_reduction_combinator_j(expression, root));
  RESULT_CALL(expression_reduction_combinator_m(expression, root));
  return RESULT_OK;
}
