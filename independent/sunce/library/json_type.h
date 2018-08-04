#ifndef __JSON_TYPE__H__
#define __JSON_TYPE__H__

_LIBRARY_INCLUDE_BEGIN_
typedef enum sunce_json_value_type_t
{
  SUNCE_JSON_VALUE_TYPE_UNKNOWN = 0,
  SUNCE_JSON_VALUE_TYPE_BOOLEAN = 1,
  SUNCE_JSON_VALUE_TYPE_INTEGER = 2,
  SUNCE_JSON_VALUE_TYPE_FLOAT   = 3,
  SUNCE_JSON_VALUE_TYPE_STRING  = 4,
  SUNCE_JSON_VALUE_TYPE_MAP     = 5,
  SUNCE_JSON_VALUE_TYPE_ARRAY   = 6
} sunce_json_value_type_t;

typedef struct sunce_json_node_t sunce_json_node_t;

typedef union sunce_json_value_value_t
{
  sunce_boolean_t    boolean_u;
  sunce_integer_t    integer_u;
  sunce_float_t      float_u;
  sunce_string_t     string_u;
  sunce_json_node_t* map_u;
  sunce_json_node_t* array_u;
} sunce_json_value_value_t;

typedef struct sunce_json_value_t
{
  sunce_json_value_type_t  type;
  sunce_json_value_value_t value;
} sunce_json_value_t;

struct sunce_json_node_t
{
  sunce_string_t     name;
  sunce_json_value_t value;
  sunce_json_node_t* next;
};

typedef struct sunce_json_page_t sunce_json_page_t;

struct sunce_json_page_t
{
  sunce_size_t       size;
  sunce_address_t    address;
  sunce_json_page_t* next;
};

typedef struct sunce_json_t
{
  sunce_size_t       default_page_size;
  sunce_json_page_t* pages;
  sunce_json_node_t* nodes;
} sunce_json_t;

_LIBRARY_INCLUDE_END_

#define SUNCE_JSON_DEFAULT_PAGE_SIZE 1048576

typedef struct sunce_json_parser_context_t
{
  sunce_json_t*   json;
  sunce_address_t lexical;
} sunce_json_parser_context_t;

#endif
