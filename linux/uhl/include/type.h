#ifndef __UHL__TYPE_H
#define __UHL__TYPE_H

#include <stdint.h>
#include <usb.h>

typedef enum boolean
{
  FALSE = 0,
  TRUE = 1
} boolean;

typedef uint32_t     address_type;
typedef address_type size_type;
typedef uint8_t      value_type;
typedef uint8_t      byte;
typedef uint32_t     integer;

typedef struct processor_type
{
  char *name;
  size_type size_flash;
  size_type size_id;
  size_type size_configuration;
  size_type size_epprom;
} processor_type;

typedef struct memory_type
{
  int processor_index;
  value_type *block[COUNT_MEMORY_INDEX];
  address_type base_address[COUNT_MEMORY_INDEX];
  size_type size[COUNT_MEMORY_INDEX];
  address_type end_address[COUNT_MEMORY_INDEX];
  value_type memory_flash[MAX_SIZE_FLASH];
  value_type memory_id[MAX_SIZE_ID];
  value_type memory_configuration[MAX_SIZE_CONFIGURATION];
  value_type memory_epprom[MAX_SIZE_EPPROM];
} memory_type;

typedef struct hex_line_type
{
  HEX_LENGTH_TYPE length;
  HEX_OFFSET_TYPE offset;
  HEX_TYPE_TYPE type;
  HEX_DATA_TYPE data[HEX_DATA_MAX_LENGTH];
  HEX_CHECKSUM_TYPE checksum;
} hex_line_type;

typedef struct usb_dev_handle usb_type;

#endif
