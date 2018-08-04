#define _POSIX_SOURCE
#define _ISOC99_SOURCE

#include <stdio.h>
#include <time.h>
#include <limits.h>

#define BUFFER_SIZE (4096+1)

char* make_output_name(char* name, int name_size, char* prefix, struct tm* name_tm)
{
  int size = 0;

  size += snprintf(&name[size], name_size-size, "%s-", prefix);
  size += strftime(&name[size], name_size-size, "%H:%M.log", name_tm);
  return name;
}

int main(int argc, char* argv[])
{
  char buffer[BUFFER_SIZE];
  FILE* output = NULL;
  time_t output_time;
  struct tm output_tm;
  time_t now_time;
  struct tm now_tm;

  if(argc != 2)
    return 1;

  while(fgets(buffer, BUFFER_SIZE, stdin) != NULL)
  {
    now_time = time(NULL);
    localtime_r(&now_time, &now_tm);

    if(now_tm.tm_hour != output_tm.tm_hour || now_tm.tm_min != output_tm.tm_min)
    {
      char name[PATH_MAX];

      output_time = now_time;
      output_tm = now_tm;
      if(output != NULL)
        fclose(output);
      output = fopen(make_output_name(name, PATH_MAX, argv[1], &output_tm), "a");
      if(output == NULL)
        return 2;
    }
    fprintf(output, "%s", buffer);
    fflush(output);
  }
  return 0;
}
