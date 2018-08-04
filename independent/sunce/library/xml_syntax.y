%{
#include "main.h"
#include "xml_lexical.h"

#define YYLEX_PARAM context->lexical

void sunce_xml_yyerror(YYLTYPE* location, sunce_xml_parser_context_t* context, const char* string)
{
}

int sunce_xml_yywrap(yyscan_t yyscanner)
{
  return 1;
}
%}

%define api.pure
%defines
%locations
%name-prefix "sunce_xml_yy"

%lex-param {YYLEX_PARAM}
%parse-param {sunce_xml_parser_context_t* context}

%token ERROR
%token OPEN
%token CLOSE
%token END
%token NAME
%token STRING

%start xml

%%

xml:
  preambule
  tag
  {
  };

preambule:
  {
  };

tag:
  OPEN attributes '>' tags CLOSE
  {
  }|
  OPEN attributes END
  {
  };

attributes:
  {
  }|
  attribute attributes
  {
  };

attribute:
  NAME '=' STRING
  {
  };

tags:
  {
  }|
  tag tags
  {
  };
