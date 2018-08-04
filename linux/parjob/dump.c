#include "main.h"

void dump(int signal)
{
  int i;

  for(i = 0; i < Job_data.size; i++)
    if(Job_data.children_data[i].used == TRUE)
      fprintf(stderr, "DUMP: position=%d/%d pid=%d command=\'%s\'\n", i+1, Job_data.size, Job_data.children_data[i].pid, Job_data.children_data[i].command);
}
