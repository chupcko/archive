#include "main.h"

void wait_all_children(job_data_t* job_data)
{
  int i;
  boolean_t all_done;

  while(TRUE)
  {
    all_done = TRUE;
    for(i = 0;  i < job_data->size; i++)
      if(job_data->children_data[i].used == TRUE)
      {
        all_done = FALSE;
        break;
      }
    if(all_done == TRUE)
      break;
    usleep(1000);
  }
}
