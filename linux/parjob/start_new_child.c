#include "main.h"

boolean_t start_new_child(job_data_t* job_data, char* enviroment[])
{
  static char* arguments_value[] = {"sh", "-c", NULL, NULL};
  int i;
  pid_t child_pid;

  for(i = 0; i < job_data->size; i++)
    if(job_data->children_data[i].used == FALSE)
    {
      if(read_next_command(job_data, i) != TRUE)
        return FALSE;
      job_data->children_data[i].pid = fork();
      if(job_data->children_data[i].pid == -1)
        ERROR("Cannot fork");
      if(job_data->children_data[i].pid == 0)
      {
        arguments_value[2] = job_data->children_data[i].command;
        execve("/bin/sh", arguments_value, enviroment);
        ERROR("Cannot exec \'%s\'", job_data->children_data[i].command);
      }
      job_data->children_data[i].used = TRUE;
      DEBUG("START pid=%d command=\'%s\'", job_data->children_data[i].pid, job_data->children_data[i].command);
    }
  return TRUE;
}
