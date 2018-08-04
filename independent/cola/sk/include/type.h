#ifndef _TYPE_H_
#define _TYPE_H_

typedef enum boolean_t
{
  FALSE = 0,
  TRUE  = 1
} boolean_t;

typedef int index_t;
#define INDEX_NULL (-1)

typedef enum item_type_t
{
  ITEM_TYPE_FREE,
  ITEM_TYPE_USED,
  ITEM_TYPE_SUB_ITEM,
  ITEM_TYPE_COMBINATOR
} item_type_t;

typedef struct item_t
{
  item_type_t type;
  index_t     data;
  index_t     next;
} item_t;

#define NAME_MAX_LENGTH (32+1)
typedef char name_t[NAME_MAX_LENGTH];

#define EXPRESSION_MAX_ITEMS_NUMBER 2048
#define EXPRESSION_MAX_NAMES_NUMBER 32
typedef struct expression_t
{
  index_t items_number;
  item_t  items[EXPRESSION_MAX_ITEMS_NUMBER];
  index_t names_number;
  name_t  names[EXPRESSION_MAX_NAMES_NUMBER];
  index_t root;
} expression_t;

typedef result_t (*walk_function_t)(expression_t*, index_t*);

#endif
