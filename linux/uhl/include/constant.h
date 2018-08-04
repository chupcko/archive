#ifndef __UHL__CONSTANT_H
#define __UHL__CONSTANT_H

#include <stdint.h>

#define BASE_ADDRESS_FLASH         0x00000000u
#define BASE_ADDRESS_ID            0x00200000u
#define BASE_ADDRESS_CONFIGURATION 0x00300000u
#define BASE_ADDRESS_EPPROM        0x00f00000u

#define MAX_ADDRESS_FLASH         0x0001ffffu
#define MAX_ADDRESS_ID            0x00200007u
#define MAX_ADDRESS_CONFIGURATION 0x0030000du
#define MAX_ADDRESS_EPPROM        0x00f003ffu

#define MAX_SIZE_FLASH         (MAX_ADDRESS_FLASH-BASE_ADDRESS_FLASH+1)
#define MAX_SIZE_ID            (MAX_ADDRESS_ID-BASE_ADDRESS_ID+1)
#define MAX_SIZE_CONFIGURATION (MAX_ADDRESS_CONFIGURATION-BASE_ADDRESS_CONFIGURATION+1)
#define MAX_SIZE_EPPROM        (MAX_ADDRESS_EPPROM-BASE_ADDRESS_EPPROM+1)

#define MEMORY_INDEX_FLASH         0
#define MEMORY_INDEX_ID            1
#define MEMORY_INDEX_CONFIGURATION 2
#define MEMORY_INDEX_EPPROM        3
#define MIN_MEMORY_INDEX           MEMORY_INDEX_FLASH
#define MAX_MEMORY_INDEX           MEMORY_INDEX_EPPROM
#define COUNT_MEMORY_INDEX         (MAX_MEMORY_INDEX-MIN_MEMORY_INDEX+1)

#define HEX_COLUMN          ':'
#define HEX_COLUMN_TYPE     char
#define HEX_COLUMN_OFFSET   0
#define HEX_LENGTH_TYPE     uint8_t
#define HEX_LENGTH_OFFSET   1
#define HEX_OFFSET_TYPE     uint16_t
#define HEX_OFFSET_OFFSET   3
#define HEX_TYPE_TYPE       uint8_t
#define HEX_TYPE_OFFSET     7
#define HEX_DATA_TYPE       uint8_t
#define HEX_DATA_OFFSET     9
#define HEX_DATA_MAX_LENGTH 256
#define HEX_CHECKSUM_TYPE   uint8_t
#define HEX_LINE_SIZE(n)    (\
                              sizeof(HEX_COLUMN_TYPE)+\
                              (\
                                sizeof(HEX_LENGTH_TYPE)+\
                                sizeof(HEX_OFFSET_TYPE)+\
                                sizeof(HEX_TYPE_TYPE)+\
                                (n)*sizeof(HEX_DATA_TYPE)+\
                                sizeof(HEX_CHECKSUM_TYPE)\
                              )*2\
                            )
#define HEX_LINE_MAX_SIZE   HEX_LINE_SIZE(HEX_DATA_MAX_LENGTH)

#define HEX_TYPE_DATA_RECORD                     0x00u
#define HEX_TYPE_END_OF_FILE_RECORD              0x01u
#define HEX_TYPE_EXTENDED_SEGMENT_ADDRESS_RECORD 0x02u
#define HEX_TYPE_START_SEGMENT_ADDRESS_RECORD    0x03u
#define HEX_TYPE_EXTENDED_LINEAR_ADDRESS_RECORD  0x04u
#define HEX_TYPE_START_LINEAR_ADDRESS_RECORD     0x05u

#define HEX_TYPE_END_OF_FILE_RECORD_LENGTH              0u
#define HEX_TYPE_EXTENDED_SEGMENT_ADDRESS_RECORD_LENGTH 2u
#define HEX_TYPE_EXTENDED_LINEAR_ADDRESS_RECORD_LENGTH  2u

typedef enum hex_load_error_type
{
  HEX_LOAD_OK                          =  0,
  HEX_LOAD_ERROR_LINE_AFTER_END        =  1,
  HEX_LOAD_ERROR_MISSING_COLUMN        =  2,
  HEX_LOAD_ERROR_SMALL_LENGTH          =  3,
  HEX_LOAD_ERROR_BAD_LENGTH            =  4,
  HEX_LOAD_ERROR_CHECKSUM              =  5,
  HEX_LOAD_ERROR_EMPTY_DATA            =  6,
  HEX_LOAD_ERROR_BAD_ADDRESS           =  7,
  HEX_LOAD_ERROR_DATA_ON_END           =  8,
  HEX_LOAD_ERROR_OFFSET_ON_END         =  9,
  HEX_LOAD_ERROR_BAD_LENGTH_ON_SEGMENT = 10,
  HEX_LOAD_ERROR_OFFSET_ON_SEGMENT     = 11,
  HEX_LOAD_ERROR_SEGMENT               = 12,
  HEX_LOAD_ERROR_BAD_LENGTH_ON_LINEAR  = 13,
  HEX_LOAD_ERROR_OFFSET_ON_LINEAR      = 14,
  HEX_LOAD_ERROR_LINEAR                = 15,
  HEX_LOAD_ERROR_UNKNOWN_TYPE          = 16,
} hex_load_error_type;

#endif
