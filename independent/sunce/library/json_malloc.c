#include "main.h"

_LIBRARY_DECLARATION_BEGIN_
sunce_address_t sunce_json_malloc(sunce_json_t* json, sunce_size_t size)
_LIBRARY_DECLARATION_END_
{
  SUNCE_TRACE();
  sunce_json_page_t* page = json->pages;
  while(page != NULL && page->size < size)
    page = page->next;
  if(page == NULL)
  {
    sunce_size_t new_size = json->default_page_size;
    if(size > new_size)
      new_size = size;
    page = (sunce_json_page_t*)malloc(sizeof(sunce_json_page_t)+new_size);
    if(page == NULL)
      return SUNCE_NULL;
    page->size = new_size;
    page->address = (void*)(page+sizeof(sunce_json_page_t));
    page->next = json->pages;
    json->pages = page;
  }
  page->size -= size;
  sunce_address_t return_address = page->address;
  page->address += size;
  return return_address;
}
