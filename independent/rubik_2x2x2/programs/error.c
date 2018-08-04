#include "main.h"

void error(char* format, ...)
{
  va_list arguments;

  va_start(arguments, format);
  vfprintf(stderr, format, arguments);
  va_end(arguments);
  fprintf(stderr, "\n");
  exit(EXIT_FAILURE);
}
