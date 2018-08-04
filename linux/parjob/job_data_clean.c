#include "main.h"

void job_data_clean(job_data_t* job_data)
{
  free((void*)job_data->children_data);
  fclose(job_data->file);
}
