#include <stdio.h>

#define __UHL__MAIN_C

#include "uhl.h"

int main(void)
{
  int processor_index;
  memory_type memory;
  int line_number;
  hex_load_error_type error;
  usb_type *usb;

  processor_index = find_processor(DEFAULT_PROCESSOR);
  if(processor_index < 0)
  {
    fprintf(stderr, "no processor\n");
    return 10;
  }
  init_memory(&memory, processor_index);
  if(load_hex(stdin, &memory, &line_number, &error) != TRUE)
  {
    fprintf(stderr, "bad hex on line: %d error: %s\n", line_number, Hex_load_error_string[error]);
    return 11;
  }
  usb = uhl_usb_open();
  if(usb == NULL)
  {
    fprintf(stderr, "no usb\n");
    return 12;
  }
  fprintf(stderr, "begin\n");
  if(uhl_usb_begin(usb) != TRUE)
  {
    fprintf(stderr, "protocol begin\n");
    return 13;
  }
  fprintf(stderr, "erase\n");
  if(uhl_usb_erase(usb) != TRUE)
  {
    fprintf(stderr, "protocol erase\n");
    return 14;
  }
  fprintf(stderr, "flash\n");
  if(uhl_usb_flash(usb, &memory) != TRUE)
  {
    fprintf(stderr, "protocol flash\n");
    return 15;
  }
  fprintf(stderr, "id\n");
  if(uhl_usb_id(usb, &memory) != TRUE)
  {
    fprintf(stderr, "protocol id\n");
    return 16;
  }
  fprintf(stderr, "configurtion\n");
  if(uhl_usb_configuration(usb, &memory) != TRUE)
  {
    fprintf(stderr, "protocol configurtion\n");
    return 17;
  }
  fprintf(stderr, "epprom\n");
  if(uhl_usb_epprom(usb, &memory) != TRUE)
  {
    fprintf(stderr, "protocol epprom\n");
    return 18;
  }
  fprintf(stderr, "end\n");
  if(uhl_usb_end(usb) != TRUE)
  {
    fprintf(stderr, "protocol end\n");
    return 19;
  }
  uhl_usb_close(usb);
  fprintf(stderr, "done\n");
  return 0;
}
