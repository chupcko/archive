#include "main.h"

static struct
{
  result_t result;
  char*    text;
} result_text_table[] =
{
  #define RESULT(name, code, text) {RESULT_##name, text},
  #include "result.x"
  #undef RESULT
  {RESULT_END_, NULL}
};


_BEGIN_DECLARATION_
char* result_text(result_t result)
_END_DECLARATION_
{
  index_t index;

  for(index = 0; result_text_table[index].text != NULL; index++)
    if(result_text_table[index].result == result)
      return result_text_table[index].text;
  return "Unknown";
}
