#ifndef __TYPE__H__
#define __TYPE__H__

_LIBRARY_INCLUDE_BEGIN_
typedef enum sunce_boolean_t
{
  SUNCE_FALSE = 0,
  SUNCE_TRUE = 1
} sunce_boolean_t;
typedef long   sunce_integer_t;
typedef double sunce_float_t;
typedef char*  sunce_string_t;
typedef long   sunce_size_t;
typedef void*  sunce_address_t;

#define SUNCE_END  NULL
#define SUNCE_NULL NULL
_LIBRARY_INCLUDE_END_

#endif
