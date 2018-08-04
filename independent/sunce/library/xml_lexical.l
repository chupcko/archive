%top{
#include "main.h"

#define YY_TYPEDEF_YY_SCANNER_T
typedef sunce_address_t yyscan_t;
#define YY_EXTRA_TYPE sunce_xml_parser_context_t*
}

%option bison-bridge
%option bison-locations
%option prefix="sunce_xml_yy"
%option reentrant
%option yylineno

%%

. return (int)yytext[0];

%%
