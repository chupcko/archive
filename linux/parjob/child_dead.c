#include "main.h"

void child_dead(int signal)
{
  pid_t pid;
  int status;
  int i;

  while(TRUE)
  {
    pid = waitpid(-1, &status, WNOHANG);
    if(pid == -1)
      if(errno == ECHILD)
        break;
      else
        ERROR("Cannot waitpid");
    if(pid == 0)
      break;
    for(i = 0; i < Job_data.size; i++)
      if(Job_data.children_data[i].pid == pid)
      {
        Job_data.children_data[i].used = FALSE;
        if(WIFEXITED(status))
          DEBUG("END pid=%d status=%d command=\'%s\'", pid, WEXITSTATUS(status), Job_data.children_data[i].command);
        else if(WIFSIGNALED(status))
          DEBUG("END pid=%d signal=%d command=\'%s\'", pid, WTERMSIG(status), Job_data.children_data[i].command);
        else
          DEBUG("END pid=%d command=\'%s\'", pid, Job_data.children_data[i].command);
        break;
      }
  }
}
