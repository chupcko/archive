#include "main.h"
#include "xml_lexical.h"

_LIBRARY_DECLARATION_BEGIN_
int sunce_xml_read_string(sunce_xml_t* xml, char* string)
_LIBRARY_DECLARATION_END_
{
/***/
  SUNCE_TRACE();
  sunce_xml_parser_context_t parser_context;
  parser_context.xml = xml;
  sunce_xml_yylex_init(&parser_context.lexical);
  sunce_xml_yyset_extra(&parser_context, parser_context.lexical);
  sunce_xml_yy_scan_string(string, parser_context.lexical);
  int return_value = sunce_xml_yyparse(&parser_context);
  sunce_xml_yylex_destroy(parser_context.lexical);
  return return_value;
}
