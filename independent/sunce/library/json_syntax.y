%{
#include "main.h"
#include "json_lexical.h"

#define YYLEX_PARAM context->lexical

void sunce_json_yyerror(YYLTYPE* location, sunce_json_parser_context_t* context, const char* string)
{
}

int sunce_json_yywrap(yyscan_t yyscanner)
{
  return 1;
}
%}

%define api.pure
%defines
%locations
%name-prefix "sunce_json_yy"

%lex-param {YYLEX_PARAM}
%parse-param {sunce_json_parser_context_t* context}

%union
{
  sunce_boolean_t    boolean_v;
  sunce_integer_t    integer_v;
  sunce_float_t      float_v;
  sunce_string_t     string_v;
  sunce_json_node_t* node_ptr_v;
}

%token ERROR
%token <boolean_v> BOOLEAN
%token <integer_v> INTEGER
%token <float_v>   FLOAT
%token <string_v>  STRING

%type <node_ptr_v> map
%type <node_ptr_v> definitions
%type <node_ptr_v> definition
%type <node_ptr_v> value
%type <node_ptr_v> array
%type <node_ptr_v> values

%start json

%%

json:
  map
  {
    sunce_json_set_root(context->json, $1);
  };

map:
  '{' definitions '}'
  {
    $$ = $2;
  };

definitions:
  definition
  {
    $$ = $1;
  }|
  definition ',' definitions
  {
    sunce_json_set_next(context->json, $1, $3);
    $$ = $1;
  };

definition:
  STRING ':' value
  {
    sunce_json_set_name(context->json, $3, $1);
    $$ = $3;
  };

value:
  BOOLEAN
  {
    sunce_json_node_t* new_node = sunce_json_new_node(context->json);
    if(new_node == SUNCE_NULL)
      YYABORT;
    sunce_json_set_value_boolean(new_node, $1);
    $$ = new_node;
  }|
  INTEGER
  {
    sunce_json_node_t* new_node = sunce_json_new_node(context->json);
    if(new_node == SUNCE_NULL)
      YYABORT;
    sunce_json_set_value_integer(new_node, $1);
    $$ = new_node;
  }|
  FLOAT
  {
    sunce_json_node_t* new_node = sunce_json_new_node(context->json);
    if(new_node == SUNCE_NULL)
      YYABORT;
    sunce_json_set_value_float(new_node, $1);
    $$ = new_node;
  }|
  STRING
  {
    sunce_json_node_t* new_node = sunce_json_new_node(context->json);
    if(new_node == SUNCE_NULL)
      YYABORT;
    sunce_json_set_value_string(new_node, $1);
    $$ = new_node;
  }|
  map
  {
    sunce_json_node_t* new_node = sunce_json_new_node(context->json);
    if(new_node == SUNCE_NULL)
      YYABORT;
    sunce_json_set_value_map(new_node, $1);
    $$ = new_node;
  }|
  array
  {
    sunce_json_node_t* new_node = sunce_json_new_node(context->json);
    if(new_node == SUNCE_NULL)
      YYABORT;
    sunce_json_set_value_array(new_node, $1);
    $$ = new_node;
  };

array:
  '[' values ']'
  {
    $$ = $2;
  };

values:
  value
  {
    $$ = $1;
  }|
  value ',' values
  {
    sunce_json_set_next(context->json, $1, $3);
    $$ = $1;
  };
