#include "main.h"

boolean_t job_data_init(job_data_t* job_data, int size, char* job_file_name)
{
  int i;

  job_data->children_data = (child_data_t*)calloc(size, sizeof(child_data_t));
  if(job_data->children_data == NULL)
    ERROR("No free space for job data");
  job_data->size = size;
  for(i = 0; i < size; i++)
    job_data->children_data[i].used = FALSE;
  if(strcmp(job_file_name, "-") == 0)
    job_data->file = stdin;
  else
  {
    job_data->file = fopen(job_file_name, "r");
    if(job_data->file == NULL)
      ERROR("Cannot open file \'%s\'", job_file_name);
  }
  return TRUE;
}
