#include "uhl.h"

#define ROW_COUNT 1024
#define SEGMENT_SIZE 8
#define SEGMENT_COUNT (ROW_COUNT*SEGMENT_SIZE)
#define ROW_RAW_SIZE ((MAX_SIZE_FLASH/SEGMENT_COUNT+2)*SEGMENT_SIZE)

static byte output_1[] = { 0x0bu, 0x00u };
static byte output_2[ROW_RAW_SIZE];

boolean uhl_usb_flash(usb_type *usb, memory_type *memory)
{
  size_type size;
  size_type end_size;
  int i;
  int j;
  int k;

  size = memory->size[MEMORY_INDEX_FLASH]/SEGMENT_COUNT;
  end_size = (size+2)*SEGMENT_SIZE;
  output_1[1] = size;
  if(uhl_set_descriptor_request(usb, output_1, sizeof(output_1)) != sizeof(output_1))
    return FALSE;
  for(i = size*SEGMENT_SIZE; i < end_size; i++)
    output_2[i] = 0x00u;
  for(i = 0; i < ROW_COUNT; i++)
  {
    for(j = 0; j < size; j++)
      for(k = 0; k < SEGMENT_SIZE; k++)
        output_2[j*SEGMENT_SIZE+k] = memory->memory_flash[j*SEGMENT_COUNT+i*SEGMENT_SIZE+k];
    if(uhl_set_descriptor_request(usb, output_2, end_size) != end_size)
      return FALSE;
  }
  return TRUE;
}
