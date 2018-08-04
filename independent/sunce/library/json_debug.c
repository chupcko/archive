#include "main.h"

static void sunce_json_debug_pages(sunce_json_page_t* start_page)
{
  SUNCE_TRACE();
  printf("pages_begin\n");
  sunce_json_page_t* page = start_page;
  while(page != SUNCE_END)
  {
    printf("  %p : %p %ld %p\n", page, page->next, page->size, page->address);
    page = page->next;
  }
  printf("pages_end\n");
}

_LIBRARY_DECLARATION_BEGIN_
void sunce_json_debug(sunce_json_t* json)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE();
  printf("default_page_size = %ld\n", json->default_page_size);
  sunce_json_debug_pages(json->pages);
  sunce_json_nodes_debug(json->nodes, SUNCE_TRUE, 0);
}
