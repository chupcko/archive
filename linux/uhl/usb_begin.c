#include "uhl.h"

static byte output_1[] = { 0x10u, 0x01u };
static byte output_2[] = { 0x10u, 0x02u };
static byte output_3[] = { 0x0fu, 0x1au };
static byte output_4[] = { 0x01u, 0x01u };

#define MAX_INPUT_LENGTH 64
static byte input[MAX_INPUT_LENGTH];

boolean uhl_usb_begin(usb_type *usb)
{
  if(uhl_set_descriptor_request(usb, output_1, sizeof(output_1)) != sizeof(output_1))
    return FALSE;
  if(uhl_get_descriptor_request(usb, input, MAX_INPUT_LENGTH) <= 0)
    return FALSE;
  if(uhl_set_descriptor_request(usb, output_2, sizeof(output_2)) != sizeof(output_2))
    return FALSE;
  if(uhl_get_descriptor_request(usb, input, MAX_INPUT_LENGTH) <= 0)
    return FALSE;
  if(uhl_set_descriptor_request(usb, output_3, sizeof(output_3)) != sizeof(output_3))
    return FALSE;
  if(uhl_set_descriptor_request(usb, output_4, sizeof(output_4)) != sizeof(output_4))
    return FALSE;
  return TRUE;
}
