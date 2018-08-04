#include "main.h"

_LIBRARY_DECLARATION_BEGIN_
void sunce_json_free(sunce_json_t* json)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE();
  sunce_json_page_t* page = json->pages;
  while(page != SUNCE_END)
  {
    sunce_json_page_t* old_page = page;
    page = page->next;
    free(old_page);
  }
}
