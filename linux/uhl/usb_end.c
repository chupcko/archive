#include "uhl.h"

static byte output_1[] = { 0x01u, 0x02u };
static byte output_2[] = { 0x0fu, 0x00u };

boolean uhl_usb_end(usb_type *usb)
{
  if(uhl_set_descriptor_request(usb, output_1, sizeof(output_1)) != sizeof(output_1))
    return FALSE;
  if(uhl_set_descriptor_request(usb, output_2, sizeof(output_2)) != sizeof(output_2))
    return FALSE;
  return TRUE;
}
