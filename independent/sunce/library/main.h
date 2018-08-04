#ifndef __MAIN__H__
#define __MAIN__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef _FUNCTION_DECLARATION_BEGIN_
#define _FUNCTION_DECLARATION_BEGIN_
#undef _FUNCTION_DECLARATION_END_
#define _FUNCTION_DECLARATION_END_
#undef _LIBRARY_DECLARATION_BEGIN_
#define _LIBRARY_DECLARATION_BEGIN_
#undef _LIBRARY_DECLARATION_END_
#define _LIBRARY_DECLARATION_END_
#undef _LIBRARY_INCLUDE_BEGIN_
#define _LIBRARY_INCLUDE_BEGIN_
#undef _LIBRARY_INCLUDE_END_
#define _LIBRARY_INCLUDE_END_

#include "type.h"
#include "json_type.h"
#include "xml_type.h"

#include "static_prototype.h"
#include "generated_prototype.h"

#include "json_syntax.h"
#include "xml_syntax.h"

#undef SUNCE_TRACE
#ifdef SUNCE_DEBUG
  #define SUNCE_TRACE(format, ...) fprintf(stderr, "# %s " format "\n", __func__, ##__VA_ARGS__)
#else
  #define SUNCE_TRACE(format, ...)
#endif

#define SUNCE_INDENT_FORMAT "%*s"
#define SUNCE_INDENT(indent, indent_addendum, indent_step) ((indent)+(indent_addendum))*(indent_step), ""
#define SUNCE_INDENT_STEP 2

#endif
