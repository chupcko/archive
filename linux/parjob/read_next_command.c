#include "main.h"

static boolean_t is_empty_command(job_data_t* job_data, int index)
{
  int i;

  i = 0;
  while(job_data->children_data[index].command[i] != '\0')
  {
    if(isspace(job_data->children_data[index].command[i]) == 0)
      return FALSE;
  }
  return TRUE;
}

boolean_t read_next_command(job_data_t* job_data, int index)
{
  char* trim;

  do
  {
    if(fgets(job_data->children_data[index].command, MAX_COMMAND_SIZE, job_data->file) == NULL)
      return FALSE;
    trim = strchr(job_data->children_data[index].command, '\n');
    if(trim != NULL)
      *trim = '\0';
    trim = strchr(job_data->children_data[index].command, '#');
    if(trim != NULL)
      *trim = '\0';
  }
  while(is_empty_command(job_data, index) == TRUE);
  return TRUE;
}
