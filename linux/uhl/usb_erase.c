#include "uhl.h"

static byte output_1[] =
{
  0x08u, 0x00u, 0x3cu, 0x0eu, 0x08u, 0x00u, 0xf8u, 0x6eu,
  0x08u, 0x00u, 0x00u, 0x0eu, 0x08u, 0x00u, 0xf7u, 0x6eu,
  0x08u, 0x00u, 0x04u, 0x0eu, 0x08u, 0x00u, 0xf6u, 0x6eu
};
static byte output_2[] = { 0x08u, 0x0cu, 0x80u, 0x00u };
static byte output_3[] = { 0x08u, 0x00u, 0x00u, 0x00u };
static byte output_4[] = { 0x0au, 0x01u };

boolean uhl_usb_erase(usb_type *usb)
{
  if(uhl_set_descriptor_request(usb, output_1, sizeof(output_1)) != sizeof(output_1))
    return FALSE;
  if(uhl_set_descriptor_request(usb, output_2, sizeof(output_2)) != sizeof(output_2))
    return FALSE;
  if(uhl_set_descriptor_request(usb, output_3, sizeof(output_3)) != sizeof(output_3))
    return FALSE;
  if(uhl_set_descriptor_request(usb, output_4, sizeof(output_4)) != sizeof(output_4))
    return FALSE;
  return TRUE;
}
