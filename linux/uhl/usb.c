#include <stdio.h>
#include <unistd.h>
#include <usb.h>

#include "uhl.h"

static struct usb_device *find_device(int vendor_id, int product_id)
{
  struct usb_bus *bus;
  struct usb_device *device;

  for(bus = usb_get_busses(); bus != NULL ; bus = bus->next)
    for(device = bus->devices; device != NULL; device = device->next)
      if
      (
        device->descriptor.idVendor == vendor_id &&
        device->descriptor.idProduct == product_id
      )
        return device;
  return NULL;
}

usb_type *uhl_usb_open(void)
{
  struct usb_dev_handle *handle;
  struct usb_device *device;

  usb_init();
  usb_find_busses();
  usb_find_devices();
  device = find_device(USB_VENDOR_ID, USB_PRODUCT_ID);
  if(device == NULL)
    return NULL;

  handle = usb_open(device);
  if(handle == NULL)
    return NULL;
  if(usb_set_configuration(handle, USB_CONFIGURATION) != 0)
    return NULL;
  if(usb_claim_interface(handle, USB_INTERFACE) != 0)
    return NULL;
  if(usb_set_altinterface(handle, USB_ALTSETTING) != 0)
    return NULL;
  return (usb_type *)handle;
}

static void debug_buffer(char *name, byte *buffer, int buffer_length)/***/
{
  int i;

  printf("%s %d :", name, buffer_length);
  for(i = 0; i < buffer_length; i++)
  {
    if(i != 0)
      printf(" ");
    printf("%02x", buffer[i]);
  }
  printf("\n");
}/***/

int uhl_set_descriptor_request(usb_type *usb, byte *buffer, int buffer_length)
{
  int return_valuei;

  return_valuei = usb_control_msg
  (
    (struct usb_dev_handle *)usb,
    USB_ENDPOINT_OUT,
    USB_REQ_SET_DESCRIPTOR,
    USB_DT_STRING<<8|USB_INDEX,
    USB_LANGUAGE_ID,
    (void *)buffer,
    buffer_length,
    USB_TIMEOUT
  );
  usleep(USB_USLEEP);
  return return_valuei;
}

int uhl_get_descriptor_request(usb_type *usb, byte *buffer, int buffer_length)
{
  return usb_control_msg
  (
    (struct usb_dev_handle *)usb,
    USB_ENDPOINT_IN,
    USB_REQ_GET_DESCRIPTOR,
    USB_DT_STRING<<8|USB_INDEX,
    USB_LANGUAGE_ID,
    (void *)buffer,
    buffer_length,
    USB_TIMEOUT
  );
}

void uhl_usb_close(usb_type *usb)
{
  usb_close((struct usb_dev_handle *)usb);
}
