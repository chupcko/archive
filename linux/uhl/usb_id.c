#include "uhl.h"

static byte output_1[] =
{
  0x08u, 0x00u, 0x3cu, 0x0eu, 0x08u, 0x00u, 0xf8u, 0x6eu,
  0x08u, 0x00u, 0x00u, 0x0eu, 0x08u, 0x00u, 0xf7u, 0x6eu,
  0x08u, 0x00u, 0x06u, 0x0eu, 0x08u, 0x00u, 0xf6u, 0x6eu
};
static byte output_2[] = { 0x08u, 0x0cu, 0x00u, 0x00u };
static byte output_3[] = { 0x08u, 0x00u, 0xa6u, 0x8eu };
static byte output_4[] = { 0x08u, 0x00u, 0xa6u, 0x9cu };
static byte output_5[] =
{
  0x08u, 0x00u, 0x20u, 0x0eu, 0x08u, 0x00u, 0xf8u, 0x6eu,
  0x08u, 0x00u, 0x00u, 0x0eu, 0x08u, 0x00u, 0xf7u, 0x6eu,
  0x08u, 0x00u, 0x00u, 0x0eu, 0x08u, 0x00u, 0xf6u, 0x6eu
};
static byte output_6[] =
{
  0x08u, 0x0du, 0x00u, 0x00u, 0x08u, 0x0du, 0x00u, 0x00u,
  0x08u, 0x0du, 0x00u, 0x00u, 0x08u, 0x0fu, 0x00u, 0x00u
};
static byte output_7[] = { 0x0au, 0x02u };

boolean uhl_usb_id(usb_type *usb, memory_type *memory)
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
  size = (memory->size[MEMORY_INDEX_ID]+1)/2;
  if(size*4 != sizeof(output_6))
    return FALSE;
  for(i = 0; i < size; i++)
  {
    output_6[i*4+2] = memory->memory_id[i*2];
    output_6[i*4+3] = memory->memory_id[i*2+1];
  }
  if(uhl_set_descriptor_request(usb, output_6, sizeof(output_6)) != sizeof(output_6))
    return FALSE;
  if(uhl_set_descriptor_request(usb, output_7, sizeof(output_7)) != sizeof(output_7))
    return FALSE;
  return TRUE;
}
