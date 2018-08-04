%top{
#include "main.h"

#define YY_TYPEDEF_YY_SCANNER_T
typedef sunce_address_t yyscan_t;
#define YY_EXTRA_TYPE sunce_json_parser_context_t*
}

%option bison-bridge
%option bison-locations
%option prefix="sunce_json_yy"
%option reentrant
%option yylineno

DIGIT [0-9]

%%

{DIGIT}+            yylval->integer_v = atol(yytext); return INTEGER;
{DIGIT}+"."{DIGIT}* yylval->float_v = atof(yytext); return FLOAT;
(?i:true)           yylval->boolean_v = SUNCE_TRUE; return BOOLEAN;
(?i:false)          yylval->boolean_v = SUNCE_FALSE; return BOOLEAN;
\"([^\"]|\\.)*\"    {
  yylval->string_v = sunce_json_new_string(yyextra->json, yytext);
  if(yylval->string_v == SUNCE_NULL)
    return ERROR;
  else
    return STRING;
}
[ \t\n]+
\/\/.*
.                   return (int)yytext[0];

%%
