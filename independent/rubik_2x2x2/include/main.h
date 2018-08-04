#ifndef __MAIN_H__
#define __MAIN_H__

#define __FUNCTION_BEGIN__
#define __FUNCTION_END__
#define __INCLUDE_BEGIN__
#define __INCLUDE_END__

__INCLUDE_BEGIN__
#include <stdio.h>
__INCLUDE_END__

#include <stdlib.h>
#include <time.h>

#include "configuration.h"
#include "type.h"
#include "type_move.h"
#include "type_cube.h"
#include "prototype.h"

#define CALL(...)         \
do                        \
{                         \
  r2_bool_t __result;     \
                          \
  __result = __VA_ARGS__; \
  if(__result != R2_TRUE) \
    return __result;      \
}                         \
while(0)                  \

#endif
