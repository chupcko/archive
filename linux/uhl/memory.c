#include "uhl.h"

static address_type memory_base[COUNT_MEMORY_INDEX] =
{
  BASE_ADDRESS_FLASH,
  BASE_ADDRESS_ID,
  BASE_ADDRESS_CONFIGURATION,
  BASE_ADDRESS_EPPROM,
};

void init_memory(memory_type *memory, int processor_index)
{
  int i;

  memory->processor_index = processor_index;
  memory->block[MEMORY_INDEX_FLASH] = memory->memory_flash;
  memory->base_address[MEMORY_INDEX_FLASH] = memory_base[MEMORY_INDEX_FLASH];
  memory->size[MEMORY_INDEX_FLASH] = Processor[processor_index].size_flash;
  memory->end_address[MEMORY_INDEX_FLASH] = memory->base_address[MEMORY_INDEX_FLASH]+memory->size[MEMORY_INDEX_FLASH]-1;
  memory->block[MEMORY_INDEX_ID] = memory->memory_id;
  memory->base_address[MEMORY_INDEX_ID] = memory_base[MEMORY_INDEX_ID];
  memory->size[MEMORY_INDEX_ID] = Processor[processor_index].size_id;
  memory->end_address[MEMORY_INDEX_ID] = memory->base_address[MEMORY_INDEX_ID]+memory->size[MEMORY_INDEX_ID]-1;
  memory->block[MEMORY_INDEX_CONFIGURATION] = memory->memory_configuration;
  memory->base_address[MEMORY_INDEX_CONFIGURATION] = memory_base[MEMORY_INDEX_CONFIGURATION];
  memory->size[MEMORY_INDEX_CONFIGURATION] = Processor[processor_index].size_configuration;
  memory->end_address[MEMORY_INDEX_CONFIGURATION] = memory->base_address[MEMORY_INDEX_CONFIGURATION]+memory->size[MEMORY_INDEX_CONFIGURATION]-1;
  memory->block[MEMORY_INDEX_EPPROM] = memory->memory_epprom;
  memory->base_address[MEMORY_INDEX_EPPROM] = memory_base[MEMORY_INDEX_EPPROM];
  memory->size[MEMORY_INDEX_EPPROM] = Processor[processor_index].size_epprom;
  memory->end_address[MEMORY_INDEX_EPPROM] = memory->base_address[MEMORY_INDEX_EPPROM]+memory->size[MEMORY_INDEX_EPPROM]-1;
  for(i = 0; i < memory->size[MEMORY_INDEX_FLASH]; i++)
    memory->memory_flash[i] = VALUE_FILLER;
  for(i = 0; i < memory->size[MEMORY_INDEX_ID]; i++)
    memory->memory_id[i] = VALUE_FILLER;
  for(i = 0; i < memory->size[MEMORY_INDEX_CONFIGURATION]; i++)
    memory->memory_configuration[i] = VALUE_FILLER;
  for(i = 0; i < memory->size[MEMORY_INDEX_EPPROM]; i++)
    memory->memory_epprom[i] = VALUE_FILLER;
}

boolean memory_write(memory_type *memory, address_type address, value_type value)
{
  int i;

  for(i = MIN_MEMORY_INDEX; i <= MAX_MEMORY_INDEX; i++)
    if
    (
      address >= memory->base_address[i] &&
      address <= memory->end_address[i]
    )
    {
      memory->block[i][address-memory->base_address[i]] = value;
      return TRUE;
    }
  return FALSE;
}

value_type memory_read(memory_type *memory, address_type address)
{
  int i;

  for(i = MIN_MEMORY_INDEX; i <= MAX_MEMORY_INDEX; i++)
    if
    (
      address >= memory->base_address[i] &&
      address <= memory->end_address[i]
    )
      return memory->block[i][address-memory->base_address[i]];
  return VALUE_FILLER;
}
