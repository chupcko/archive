#ifndef __UHL__UHL_H
#define __UHL__UHL_H

#undef EXTERN
#undef INIT
#ifdef __UHL__MAIN_C
  #define EXTERN
  #define INIT(...) = __VA_ARGS__
#else
  #define EXTERN extern
  #define INIT(...)
#endif

#include "configuration.h"
#include "constant.h"
#include "type.h"
#include "variable.h"
#include "prototype.h"

#endif
