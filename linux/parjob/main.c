#define __MAIN__C__

#include "main.h"

static void usage(char* name)
{
  fprintf
  (
    stderr,
    "Usage: %s [-h] [-d] [-n number] [job_file]\n"
    "  -h\t\tHelp\n"
    "  -d\t\tTurn debug on (default off)\n"
    "  -n\t\tMax number of children (default %d)\n"
    "  job_file\tFile with command on each row (default \'%s\' aka stdin)\n",
    name,
    DEFAULT_CHILD_DATA_SIZE,
    DEFAULT_JOB_FILE_NAME
  );
  exit(EXIT_FAILURE);
}

int main(int arguments_number, char* arguments_values[], char* arguments_enviroment[])
{
  int child_data_size;
  char* job_file_name;
  int option;

  child_data_size = DEFAULT_CHILD_DATA_SIZE;
  job_file_name = DEFAULT_JOB_FILE_NAME;
  Debug = FALSE;
  opterr = 0;
  while(TRUE)
  {
    option = getopt(arguments_number, arguments_values, "hdn:");
    if(option == -1)
      break;
    switch(option)
    {
      case 'h':
        usage(arguments_values[0]);
        break;
      case 'd':
        Debug = TRUE;
        break;
      case 'n':
        child_data_size = atoi(optarg);
        if(child_data_size <= 0)
          usage(arguments_values[0]);
        break;
      default:
        usage(arguments_values[0]);
    }
  }
  if(optind == arguments_number-1)
    job_file_name = arguments_values[optind];
  else if(optind != arguments_number)
    usage(arguments_values[0]);

  DEBUG("INIT");
  job_data_init(&Job_data, child_data_size, job_file_name);
  signal(SIGCHLD, &child_dead);
  signal(SIGHUP, &dump);
  while(TRUE)
  {
    if(start_new_child(&Job_data, arguments_enviroment) != TRUE)
      break;
    usleep(1000);
  }
  wait_all_children(&Job_data);
  job_data_clean(&Job_data);
  DEBUG("DONE");

  return EXIT_SUCCESS;
}
