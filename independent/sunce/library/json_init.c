#include "main.h"

_LIBRARY_DECLARATION_BEGIN_
void sunce_json_init(sunce_json_t* json)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE();
  json->default_page_size = SUNCE_JSON_DEFAULT_PAGE_SIZE;
  json->pages = SUNCE_END;
  json->nodes = SUNCE_END;
}
