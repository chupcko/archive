#ifndef __XML_TYPE__H__
#define __XML_TYPE__H__

_LIBRARY_INCLUDE_BEGIN_
typedef int sunce_xml_t;
_LIBRARY_INCLUDE_END_

typedef struct sunce_xml_parser_context_t
{
  sunce_xml_t*    xml;
  sunce_address_t lexical;
} sunce_xml_parser_context_t;

#endif
