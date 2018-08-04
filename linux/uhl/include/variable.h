#ifndef __UHL__VARIABLE_H
#define __UHL__VARIABLE_H

EXTERN processor_type Processor[] INIT
(
  {
    { "18f452", 0x00008000u, MAX_SIZE_ID, MAX_SIZE_CONFIGURATION, 0x00000100u },
    { NULL,     0,           0,           0,                      0           }
  };
);

EXTERN char *Hex_load_error_string[] INIT
(
  {
    "OK",
    "line after end",
    "missing column",
    "small length",
    "bad length",
    "checksum",
    "empty data",
    "bad address",
    "data on end",
    "offset on end",
    "bad length on segment",
    "offset on segment",
    "segment",
    "bad length on linear",
    "offset on linear",
    "linear",
    "unknown type"
  }
);

#endif
