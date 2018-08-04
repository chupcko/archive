#include "main.h"
#include "json_lexical.h"

_LIBRARY_DECLARATION_BEGIN_
int sunce_json_read_file(sunce_json_t* json, FILE* file)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE();
  sunce_json_parser_context_t parser_context;
  parser_context.json = json;
  sunce_json_yylex_init(&parser_context.lexical);
  sunce_json_yyset_extra(&parser_context, parser_context.lexical);
  sunce_json_yyrestart(file, parser_context.lexical);
  int return_value = sunce_json_yyparse(&parser_context);
  sunce_json_yylex_destroy(parser_context.lexical);
  return return_value;
}
