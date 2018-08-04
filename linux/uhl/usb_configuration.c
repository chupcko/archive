#include "uhl.h"

static byte output_1[] =
{
  0x08u, 0x00u, 0x3cu, 0x0eu, 0x08u, 0x00u, 0xf8u, 0x6eu,
  0x08u, 0x00u, 0x00u, 0x0eu, 0x08u, 0x00u, 0xf7u, 0x6eu,
  0x08u, 0x00u, 0x06u, 0x0eu, 0x08u, 0x00u, 0xf6u, 0x6eu
};
static byte output_2[] = { 0x08u, 0x0cu, 0x00u, 0x00u };
static byte output_3[] = { 0x08u, 0x00u, 0xa6u, 0x8eu };
static byte output_4[] = { 0x08u, 0x00u, 0xa6u, 0x8cu };
static byte output_5[] =
{
  0x08u, 0x00u, 0x30u, 0x0eu, 0x08u, 0x00u, 0xf8u, 0x6eu,
  0x08u, 0x00u, 0x00u, 0x0eu, 0x08u, 0x00u, 0xf7u, 0x6eu,
  0x08u, 0x00u, 0x00u, 0x0eu, 0x08u, 0x00u, 0xf6u, 0x6eu
};
static byte output_6[] = { 0x08u, 0x0fu, 0x00u, 0xffu };
static byte output_7[] = { 0x0au, 0x02u };
static byte output_8[] = { 0x08u, 0x00u, 0xf6u, 0x2au };
static byte output_9[] = { 0x08u, 0x0fu, 0xffu, 0x00u };
static byte output_10[] =
{
  0x08u, 0x00u, 0x30u, 0x0eu, 0x08u, 0x00u, 0xf8u, 0x6eu,
  0x08u, 0x00u, 0x00u, 0x0eu, 0x08u, 0x00u, 0xf7u, 0x6eu,
  0x08u, 0x00u, 0x0bu, 0x0eu, 0x08u, 0x00u, 0xf6u, 0x6eu
};
static byte output_11[] = { 0x08u, 0x0fu, 0xffu, 0xe0u };

boolean uhl_usb_configuration(usb_type *usb, memory_type *memory)
{
  size_type size;
  int i;

  if(uhl_set_descriptor_request(usb, output_1, sizeof(output_1)) != sizeof(output_1))
    return FALSE;
  if(uhl_set_descriptor_request(usb, output_2, sizeof(output_2)) != sizeof(output_2))
    return FALSE;
  if(uhl_set_descriptor_request(usb, output_3, sizeof(output_3)) != sizeof(output_3))
    return FALSE;
  if(uhl_set_descriptor_request(usb, output_4, sizeof(output_4)) != sizeof(output_4))
    return FALSE;
  if(uhl_set_descriptor_request(usb, output_5, sizeof(output_5)) != sizeof(output_5))
    return FALSE;
  size = (memory->size[MEMORY_INDEX_CONFIGURATION]+1)/2;
  for(i = 0; i < size; i++)
  {
    output_6[2] = memory->memory_configuration[i*2];
    if(uhl_set_descriptor_request(usb, output_6, sizeof(output_6)) != sizeof(output_6))
      return FALSE;
    if(uhl_set_descriptor_request(usb, output_7, sizeof(output_7)) != sizeof(output_7))
      return FALSE;
    if(uhl_set_descriptor_request(usb, output_8, sizeof(output_8)) != sizeof(output_8))
      return FALSE;
    output_9[3] = memory->memory_configuration[i*2+1];
    if(uhl_set_descriptor_request(usb, output_9, sizeof(output_9)) != sizeof(output_9))
      return FALSE;
    if(uhl_set_descriptor_request(usb, output_7, sizeof(output_7)) != sizeof(output_7))
      return FALSE;
    if(uhl_set_descriptor_request(usb, output_8, sizeof(output_8)) != sizeof(output_8))
      return FALSE;
  }
  if(uhl_set_descriptor_request(usb, output_10, sizeof(output_10)) != sizeof(output_10))
    return FALSE;
  if(uhl_set_descriptor_request(usb, output_11, sizeof(output_11)) != sizeof(output_11))
    return FALSE;
  if(uhl_set_descriptor_request(usb, output_7, sizeof(output_7)) != sizeof(output_7))
    return FALSE;
  return TRUE;
}
