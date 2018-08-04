#include <stdint.h>

#include "uhl.h"

static int16_t sum(int16_t old, byte new)
{
  return (old+(int16_t)new)&0xff;
}

byte calculate_checksum(hex_line_type *hex_line)
{
  uint16_t checksum;
  int i;

  checksum = sum(checksum, hex_line->length);
  checksum = sum(checksum, (byte)(hex_line->offset&0xff));
  checksum = sum(checksum, (byte)(hex_line->offset>>8&0xff));
  checksum = sum(checksum, hex_line->type);
  for(i = 0; i < hex_line->length; i++)
    checksum = sum(checksum, hex_line->data[i]);
  return (byte)(-checksum&0xff);
}
