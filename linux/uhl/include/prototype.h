#ifndef __UHL__PROTOTYPE_H
#define __UHL__PROTOTYPE_H

#include <stdio.h>

/* checksum.c */
byte calculate_checksum(hex_line_type *);

/* hex.c */
boolean load_hex(FILE *, memory_type *, int *, hex_load_error_type *);

/* hex_line.c */
int chop_line(char *);
integer found_in_hex_line(char *, int, int);

/* memory.c */
void init_memory(memory_type *, int);
boolean memory_write(memory_type *, address_type, value_type);
value_type memory_read(memory_type *, address_type);

/* processor.c */
int find_processor(char *);

/* usb.c */
usb_type *uhl_usb_open(void);
int uhl_set_descriptor_request(usb_type *, byte *, int);
int uhl_get_descriptor_request(usb_type *, byte *, int);
void uhl_usb_close(usb_type *);

/* usb_begin.c */
boolean uhl_usb_begin(usb_type *);

/* usb_configuration.c */
boolean uhl_usb_configuration(usb_type *, memory_type *);

/* usb_end.c */
boolean uhl_usb_end(usb_type *);

/* usb_epprom.c */
boolean uhl_usb_epprom(usb_type *, memory_type *);

/* usb_erase.c */
boolean uhl_usb_erase(usb_type *);

/* usb_flash.c */
boolean uhl_usb_flash(usb_type *, memory_type *);

/* usb_id.c */
boolean uhl_usb_id(usb_type *, memory_type *);

#endif
