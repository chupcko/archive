#include <stdio.h>

#include "uhl.h"

static boolean set_hex_load_error(hex_load_error_type *error, hex_load_error_type value)
{
  *error = value;
  return FALSE;
}

boolean load_hex(FILE *file, memory_type *memory, int *line_number, hex_load_error_type *error)
{
  boolean pass_end;
  boolean linear_model;
  address_type address_base;
  char line[HEX_LINE_MAX_SIZE+1+1];

  *line_number = 0;
  *error = HEX_LOAD_OK;
  pass_end = FALSE;
  linear_model = TRUE;
  address_base = 0;
  while(fgets(line, HEX_LINE_MAX_SIZE+1, stdin) != NULL)
  {
    int line_length;
    hex_line_type hex_line;
    int i;

    (*line_number)++;
    if(pass_end == TRUE)
      return set_hex_load_error(error, HEX_LOAD_ERROR_LINE_AFTER_END);
    line_length = chop_line(line);
    if(line[HEX_COLUMN_OFFSET] != HEX_COLUMN)
      return set_hex_load_error(error, HEX_LOAD_ERROR_MISSING_COLUMN);
    if(line_length < sizeof(HEX_COLUMN_TYPE)+sizeof(HEX_LENGTH_TYPE)*2)
      return set_hex_load_error(error, HEX_LOAD_ERROR_SMALL_LENGTH);
    hex_line.length = (HEX_LENGTH_TYPE)found_in_hex_line(line, sizeof(HEX_LENGTH_TYPE), HEX_LENGTH_OFFSET);
    if(line_length != HEX_LINE_SIZE(hex_line.length))
      return set_hex_load_error(error, HEX_LOAD_ERROR_BAD_LENGTH);
    hex_line.offset = (HEX_OFFSET_TYPE)found_in_hex_line(line, sizeof(HEX_OFFSET_TYPE), HEX_OFFSET_OFFSET);
    hex_line.type = (HEX_TYPE_TYPE)found_in_hex_line(line, sizeof(HEX_TYPE_TYPE), HEX_TYPE_OFFSET);
    for(i = 0; i < hex_line.length; i++)
       hex_line.data[i] = (HEX_DATA_TYPE)found_in_hex_line(line, sizeof(HEX_DATA_TYPE), HEX_DATA_OFFSET+i*2);
    hex_line.checksum = (HEX_CHECKSUM_TYPE)found_in_hex_line(line, sizeof(HEX_CHECKSUM_TYPE), line_length-2);
    if(hex_line.checksum != calculate_checksum(&hex_line))
      return set_hex_load_error(error, HEX_LOAD_ERROR_CHECKSUM);
    switch(hex_line.type)
    {
      case HEX_TYPE_DATA_RECORD:
        if(hex_line.length == 0)
          return set_hex_load_error(error, HEX_LOAD_ERROR_EMPTY_DATA);
        for(i = 0; i < hex_line.length; i++)
        {
          address_type address;

          if(linear_model == TRUE)
            address = address_base+(address_type)hex_line.offset+(address_type)i;
          else
            address = address_base+((address_type)hex_line.offset+(address_type)i)&0xffff;
          if(memory_write(memory, address, hex_line.data[i]) != TRUE)
            return set_hex_load_error(error, HEX_LOAD_ERROR_BAD_ADDRESS);
        }
        break;
      case HEX_TYPE_END_OF_FILE_RECORD:
        if(hex_line.length != HEX_TYPE_END_OF_FILE_RECORD_LENGTH)
          return set_hex_load_error(error, HEX_LOAD_ERROR_DATA_ON_END);
        if(hex_line.offset != 0)
          return set_hex_load_error(error, HEX_LOAD_ERROR_OFFSET_ON_END);
        pass_end = TRUE;
        break;
      case HEX_TYPE_EXTENDED_SEGMENT_ADDRESS_RECORD:
        if(hex_line.length != HEX_TYPE_EXTENDED_SEGMENT_ADDRESS_RECORD_LENGTH)
          return set_hex_load_error(error, HEX_LOAD_ERROR_BAD_LENGTH_ON_SEGMENT);
        if(hex_line.offset != 0)
          return set_hex_load_error(error, HEX_LOAD_ERROR_OFFSET_ON_SEGMENT);
        linear_model = FALSE;
        address_base = (address_type)hex_line.data[0]<<12|(address_type)hex_line.data[1]<<4;
        break;
      case HEX_TYPE_START_SEGMENT_ADDRESS_RECORD:
        return set_hex_load_error(error, HEX_LOAD_ERROR_SEGMENT);
        break;
      case HEX_TYPE_EXTENDED_LINEAR_ADDRESS_RECORD:
        if(hex_line.length != HEX_TYPE_EXTENDED_LINEAR_ADDRESS_RECORD_LENGTH)
          return set_hex_load_error(error, HEX_LOAD_ERROR_BAD_LENGTH_ON_LINEAR);
        if(hex_line.offset != 0)
          return set_hex_load_error(error, HEX_LOAD_ERROR_OFFSET_ON_LINEAR);
        linear_model = TRUE;
        address_base = (address_type)hex_line.data[0]<<24|(address_type)hex_line.data[1]<<16;
        break;
      case HEX_TYPE_START_LINEAR_ADDRESS_RECORD:
        return set_hex_load_error(error, HEX_LOAD_ERROR_LINEAR);
        break;
      default:
        return set_hex_load_error(error, HEX_LOAD_ERROR_UNKNOWN_TYPE);
    }
  }
  return TRUE;
}
