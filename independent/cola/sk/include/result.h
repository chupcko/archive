#ifndef _RESULT_H_
#define _RESULT_H_

typedef enum result_t
{
  #define RESULT(name, code, text) RESULT_##name = code,
  #include "result.x"
  #undef RESULT
  RESULT_END_
} result_t;

#define RESULT_CALL(...)    \
do                          \
{                           \
  result_t _result_;        \
                            \
  _result_ = __VA_ARGS__;   \
  if(_result_ != RESULT_OK) \
    return _result_;        \
} while(0);                 \

#endif
